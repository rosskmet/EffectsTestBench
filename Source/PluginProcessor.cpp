/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "math.h"

//==============================================================================
EffectsTestBenchAudioProcessor::EffectsTestBenchAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
	: AudioProcessor(BusesProperties()
						#if ! JucePlugin_IsMidiEffect
						#if ! JucePlugin_IsSynth
								.withInput("Input", juce::AudioChannelSet::stereo(), true)
						#endif
								.withOutput("Output", juce::AudioChannelSet::stereo(), true)
						#endif
							),
parameters(*this, nullptr, "PluginState", createParameterLayout())
#endif
{
	AudioProcessor::ProcessingPrecision(doublePrecision);
}

EffectsTestBenchAudioProcessor::~EffectsTestBenchAudioProcessor()
{
}

//==============================================================================
juce::AudioProcessorValueTreeState::ParameterLayout EffectsTestBenchAudioProcessor::createParameterLayout()
{
	std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

	//Sliders
	auto outputVolumeParam = std::make_unique<juce::AudioParameterFloat>(OUTPUTVOLUME_ID, "Output Volume", -60.0f, 0.0f, -6.0f);
	params.push_back(std::move(outputVolumeParam));

	auto distGainParam = std::make_unique<juce::AudioParameterFloat>(DISTGAIN_ID, "Distortion Gain", 0.0f, 100.0f, 50.0f);
	params.push_back(std::move(distGainParam));
	auto distCharacterParam = std::make_unique<juce::AudioParameterFloat>(DISTCHARACTER_ID, "Distortion Character", 0.01f, 1.0f, 0.5f);
	params.push_back(std::move(distCharacterParam));
	auto distAmountParam = std::make_unique<juce::AudioParameterFloat>(DISTAMOUNT_ID, "Distortion Amount", 0.0f, 1.0f, 0.5f);
	params.push_back(std::move(distAmountParam));

    auto filterCutoffParam = std::make_unique<juce::AudioParameterFloat>(FILTERCUTOFF_ID, "Filter Cutoff", 26.0f, 20500.0f, 12000.0f);
    params.push_back(std::move(filterCutoffParam));
    auto filterResonanceParam = std::make_unique<juce::AudioParameterFloat>(FILTERRESONANCE_ID, "Filter Resonance", 0.1f, 1.0f, 0.2f);
    params.push_back(std::move(filterResonanceParam));


	//ComboBoxes
	auto distTypeComboBoxParam = std::make_unique<juce::AudioParameterChoice>(DISTTYPECOMBOBOX_ID, "Distortion Type",
        juce::StringArray{ "Saturation", "Tube", "Overdrive", "Exponential" }, 0);
	params.push_back(std::move(distTypeComboBoxParam));
    auto filterTypeComboBoxParam = std::make_unique<juce::AudioParameterChoice>(FILTERTYPECOMBOBOX_ID, "Filter Type",
        juce::StringArray{ "LP_1stOrder", "LP_2ndOrder", "LP_Moog", "HP_1stOrder", "HP_2ndOrder", "HP_Moog", "BP_2ndOrder",
        "BP_Moog", "BS_2ndOrder", "AP_1stOrder", "AP_2ndOrder" }, 0);
    params.push_back(std::move(filterTypeComboBoxParam));


	//Buttons
	auto distBypassParam = std::make_unique<juce::AudioParameterBool>(DISTBYPASS_ID, "Distortion Bypass", true);
	params.push_back(std::move(distBypassParam));
    auto filterBypassParam = std::make_unique<juce::AudioParameterBool>(FILTERBYPASS_ID, "Filter Bypass", true);
    params.push_back(std::move(filterBypassParam));

	return { params.begin(), params.end() };
}

//==============================================================================
const juce::String EffectsTestBenchAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool EffectsTestBenchAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool EffectsTestBenchAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool EffectsTestBenchAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double EffectsTestBenchAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int EffectsTestBenchAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int EffectsTestBenchAudioProcessor::getCurrentProgram()
{
    return 0;
}

void EffectsTestBenchAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String EffectsTestBenchAudioProcessor::getProgramName (int index)
{
    return {};
}

void EffectsTestBenchAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void EffectsTestBenchAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    for (int channel = 0; channel < getNumOutputChannels(); channel++) {
        amplifiers.add(Amplifier());
        filters.add(Filter());
    }
}

void EffectsTestBenchAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool EffectsTestBenchAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void EffectsTestBenchAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.


    for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
    {
        for (int channel = 0; channel < totalNumOutputChannels; ++channel)
        {
            auto* channelData = buffer.getWritePointer(channel);

            if (*parameters.getRawParameterValue(FILTERBYPASS_ID) == true)
            {
                Filter* filter = &filters.getReference(channel);
                channelData[sample] = filter->filterSelector(channelData[sample],
                    *parameters.getRawParameterValue(FILTERCUTOFF_ID), *parameters.getRawParameterValue(FILTERRESONANCE_ID), (float)getSampleRate(),
                    *parameters.getRawParameterValue(FILTERTYPECOMBOBOX_ID));
            }

            Amplifier* amplifier = &amplifiers.getReference(channel);
            channelData[sample] = amplifier->applyAmplifier(channelData[sample], *parameters.getRawParameterValue(OUTPUTVOLUME_ID));
        }
    }
}

//==============================================================================
bool EffectsTestBenchAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* EffectsTestBenchAudioProcessor::createEditor()
{
    return new EffectsTestBenchAudioProcessorEditor (*this);
}

//==============================================================================
void EffectsTestBenchAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.

    std::unique_ptr<juce::XmlElement> xmlFile(parameters.state.createXml());
    copyXmlToBinary(*xmlFile, destData);
}

void EffectsTestBenchAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.

    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName(parameters.state.getType()))
            parameters.replaceState(juce::ValueTree::fromXml(*xmlState));
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new EffectsTestBenchAudioProcessor();
}

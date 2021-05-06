/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Amplifier.h"
//#include "Distortion.h"
#include "Filter.h"

#define DISTGAIN_ID "distGain"
#define DISTCHARACTER_ID "distCharacter"
#define DISTAMOUNT_ID "distAmount"
#define DISTTYPECOMBOBOX_ID "distTypeBox"
#define DISTBYPASS_ID "distBypass"

#define FILTERCUTOFF_ID "filterCutoff"
#define FILTERRESONANCE_ID "filterResonance"
#define FILTERTYPECOMBOBOX_ID "filterTypeBox"
#define FILTERBYPASS_ID "filterBypass"

#define OUTPUTVOLUME_ID "outputVolume"

//==============================================================================
/**
*/
class EffectsTestBenchAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    EffectsTestBenchAudioProcessor();
    ~EffectsTestBenchAudioProcessor() override;

    //==============================================================================
    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    juce::AudioProcessorValueTreeState parameters;

    juce::Array<Filter> filters;
    juce::Array<Amplifier> amplifiers;

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EffectsTestBenchAudioProcessor)
};

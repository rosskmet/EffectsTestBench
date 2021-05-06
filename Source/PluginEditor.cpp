/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
EffectsTestBenchAudioProcessorEditor::EffectsTestBenchAudioProcessorEditor (EffectsTestBenchAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
	//Component Window Properties ==============================================
	setSize(1200, 275);

	//addAndMakeVisible(filterGUI);

	//Parameter Tree States (For Automation)====================================
	outputVolumeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
		(audioProcessor.parameters, OUTPUTVOLUME_ID, outputVolumeSlider);

	distGainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
		(audioProcessor.parameters, DISTGAIN_ID, distGainSlider);
	distCharacterAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
		(audioProcessor.parameters, DISTCHARACTER_ID, distCharacterSlider);
	distAmountAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
		(audioProcessor.parameters, DISTAMOUNT_ID, distAmountSlider);

	filterCutoffAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
		(audioProcessor.parameters, FILTERCUTOFF_ID, filterCutoffSlider);
	filterResonanceAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
		(audioProcessor.parameters, FILTERRESONANCE_ID, filterResonanceSlider);

	distTypeComboBoxAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>
		(audioProcessor.parameters, DISTTYPECOMBOBOX_ID, distTypeComboBox);
	filterTypeComboBoxAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>
		(audioProcessor.parameters, FILTERTYPECOMBOBOX_ID, filterTypeComboBox);

	distBypassAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>
		(audioProcessor.parameters, DISTBYPASS_ID, distBypassButton);
	filterBypassAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>
		(audioProcessor.parameters, FILTERBYPASS_ID, filterBypassButton);


	outputVolumeSlider.setSliderStyle(juce::Slider::LinearBarVertical);
	outputVolumeSlider.setRange(-60.0f, 0.0f, 0.001f);
	outputVolumeSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
	outputVolumeSlider.setPopupDisplayEnabled(true, false, this);
	outputVolumeSlider.setTextValueSuffix(" Volume");
	outputVolumeSlider.addListener(this);

	distGainSlider.setSliderStyle(juce::Slider::LinearBarVertical);
	distGainSlider.setRange(0.0f, 100.0f, 0.01f);
	distGainSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
	distGainSlider.setPopupDisplayEnabled(true, false, this);
	distGainSlider.setTextValueSuffix("% Drive");
	distGainSlider.addListener(this);

	distCharacterSlider.setSliderStyle(juce::Slider::LinearBarVertical);
	distCharacterSlider.setRange(0.01f, 1.0f, 0.01f);
	distCharacterSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
	distCharacterSlider.setPopupDisplayEnabled(true, false, this);
	distCharacterSlider.setTextValueSuffix(" Character");
	distCharacterSlider.addListener(this);

	distAmountSlider.setSliderStyle(juce::Slider::LinearBarVertical);
	distAmountSlider.setRange(0.0f, 1.0f, 0.01f);
	distAmountSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
	distAmountSlider.setPopupDisplayEnabled(true, false, this);
	distAmountSlider.setTextValueSuffix(" Amount");
	distAmountSlider.addListener(this);

	filterCutoffSlider.setSliderStyle(juce::Slider::LinearBarVertical);
	filterCutoffSlider.setRange(26.0f, 20500.00f, 1.0f);
	filterCutoffSlider.setSkewFactor(0.3);
	filterCutoffSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
	filterCutoffSlider.setPopupDisplayEnabled(true, false, this);
	filterCutoffSlider.setTextValueSuffix(" Cutoff");
	filterCutoffSlider.addListener(this);

	filterResonanceSlider.setSliderStyle(juce::Slider::LinearBarVertical);
	filterResonanceSlider.setRange(0.1f, 1.0f, 0.001);
	filterResonanceSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
	filterResonanceSlider.setPopupDisplayEnabled(true, false, this);
	filterResonanceSlider.setTextValueSuffix(" Resonance");
	filterResonanceSlider.addListener(this);

	addAndMakeVisible(&outputVolumeSlider);
	addAndMakeVisible(&distGainSlider);
	addAndMakeVisible(&distCharacterSlider);
	addAndMakeVisible(&distAmountSlider);
	addAndMakeVisible(&filterCutoffSlider);
	addAndMakeVisible(&filterResonanceSlider);

	distTypeComboBox.addItem("Saturation", 1);
	distTypeComboBox.addItem("Tube", 2);
	distTypeComboBox.addItem("Overdrive", 3);
	distTypeComboBox.addItem("Exponential", 4);

	filterTypeComboBox.addItem("LP_1stOrder", 1);
	filterTypeComboBox.addItem("LP_2ndOrder", 2);
	filterTypeComboBox.addItem("LP_Moog", 3);
	filterTypeComboBox.addItem("HP_1stOrder", 4);
	filterTypeComboBox.addItem("HP_2ndOrder", 5);
	filterTypeComboBox.addItem("HP_Moog", 6);
	filterTypeComboBox.addItem("BP_2ndOrder", 7);
	filterTypeComboBox.addItem("BP_Moog", 8);
	filterTypeComboBox.addItem("BS_2ndOrder", 9);
	filterTypeComboBox.addItem("AP_1stOrder", 10);
	filterTypeComboBox.addItem("AP_2ndOrder", 11);

	addAndMakeVisible(&distTypeComboBox);
	addAndMakeVisible(&filterTypeComboBox);

	distBypassButton.setClickingTogglesState(true);
	filterBypassButton.setClickingTogglesState(true);

	addAndMakeVisible(&distBypassButton);
	addAndMakeVisible(&filterBypassButton);
}

EffectsTestBenchAudioProcessorEditor::~EffectsTestBenchAudioProcessorEditor()
{
}

//==============================================================================
void EffectsTestBenchAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    //g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void EffectsTestBenchAudioProcessorEditor::resized()
{
	//Slider Locations
	distCharacterSlider.setBounds(10, 35, 20, getHeight() - 100);
	distGainSlider.setBounds(40, 35, 20, getHeight() - 100);
	distAmountSlider.setBounds(70, 35, 20, getHeight() - 100);

	filterCutoffSlider.setBounds(200, 35, 20, getHeight() - 100);
	filterResonanceSlider.setBounds(230, 35, 20, getHeight() - 100);

	outputVolumeSlider.setBounds(1170, 30, 20, getHeight() - 100);

	//ComboBox Locations
	distTypeComboBox.setBounds(40, 5, 140, 20);
	filterTypeComboBox.setBounds(230, 5, 140, 20);

	//Button Locations
	distBypassButton.setBounds(10, 5, 20, 20);
	filterBypassButton.setBounds(200, 5, 20, 20);
}

void EffectsTestBenchAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
}

void EffectsTestBenchAudioProcessorEditor::comboBoxChanged(juce::ComboBox* comboBox)
{
}

void EffectsTestBenchAudioProcessorEditor::buttonClicked(juce::Button* button)
{
}

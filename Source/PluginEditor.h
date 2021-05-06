/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class EffectsTestBenchAudioProcessorEditor  : public juce::AudioProcessorEditor,
    public juce::Slider::Listener, public juce::ComboBox::Listener, public juce::Button::Listener
{
public:
    EffectsTestBenchAudioProcessorEditor (EffectsTestBenchAudioProcessor&);
    ~EffectsTestBenchAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    //==============================================================================
    void sliderValueChanged(juce::Slider* slider) override;
    void comboBoxChanged(juce::ComboBox* comboBox) override;
    void buttonClicked(juce::Button* button) override;

private:

    //Sliders
    juce::Slider outputVolumeSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> outputVolumeAttachment;

    juce::Slider distGainSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> distGainAttachment;

    juce::Slider distCharacterSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> distCharacterAttachment;

    juce::Slider distAmountSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> distAmountAttachment;

    juce::Slider filterCutoffSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> filterCutoffAttachment;

    juce::Slider filterResonanceSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> filterResonanceAttachment;

    //ComboBoxes
    juce::ComboBox distTypeComboBox;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> distTypeComboBoxAttachment;

    juce::ComboBox filterTypeComboBox;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> filterTypeComboBoxAttachment;

    //Buttons
    juce::ToggleButton distBypassButton;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> distBypassAttachment;

    juce::ToggleButton filterBypassButton;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> filterBypassAttachment;

    EffectsTestBenchAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EffectsTestBenchAudioProcessorEditor)
};

/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class BasicParametricEQAudioProcessorEditor  : public juce::AudioProcessorEditor,
    public juce::Slider::Listener
{
public:
    BasicParametricEQAudioProcessorEditor (BasicParametricEQAudioProcessor&);
    ~BasicParametricEQAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void sliderValueChanged(juce::Slider* slider) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    juce::Slider peaking_1Slider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> peaking_1Attachment;

    juce::Slider peaking_1QSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> peaking_1QAttachment;

    juce::Slider peaking_1GainSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> peaking_1GainAttachment;

    BasicParametricEQAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BasicParametricEQAudioProcessorEditor)
};

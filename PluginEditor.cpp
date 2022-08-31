/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
BasicParametricEQAudioProcessorEditor::BasicParametricEQAudioProcessorEditor (BasicParametricEQAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    peaking_1Slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    peaking_1Slider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 100, 100);
    peaking_1Slider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::green);
    addAndMakeVisible(peaking_1Slider);

    peaking_1Attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "cutoffFreq1", peaking_1Slider);

    peaking_1QSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    peaking_1QSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 100, 100);
    peaking_1QSlider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::green);
    addAndMakeVisible(peaking_1QSlider);

    peaking_1QAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "q1", peaking_1QSlider);

    peaking_1GainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    peaking_1GainSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 100, 100);
    peaking_1GainSlider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::green);
    addAndMakeVisible(peaking_1GainSlider);

    peaking_1GainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "gain1", peaking_1GainSlider);


    setSize (1000, 1000);
}

BasicParametricEQAudioProcessorEditor::~BasicParametricEQAudioProcessorEditor()
{
}

//==============================================================================
void BasicParametricEQAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(juce::Colour::fromRGB(0, 0, 0));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);/*
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);*/
    g.fillAll(juce::Colour::fromRGB(0, 0, 0));
    g.setColour(juce::Colours::white);
    g.setFont(75.f);
    g.drawText("Basic EQ", getLocalBounds(), juce::Justification::centredTop);

    peaking_1Slider.setBounds({ 450, 450, 100, 100 });
    peaking_1QSlider.setBounds({ 450, 575, 100, 100 });
    peaking_1GainSlider.setBounds({ 450, 700, 100, 100 });
}

void BasicParametricEQAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

void BasicParametricEQAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &peaking_1Slider)
    {
        audioProcessor.updateFilter();
    }
}


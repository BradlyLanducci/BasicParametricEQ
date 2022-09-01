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






    peaking_2Slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    peaking_2Slider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 100, 100);
    peaking_2Slider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::yellow);
    addAndMakeVisible(peaking_2Slider);

    peaking_2Attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "cutoffFreq2", peaking_2Slider);

    peaking_2QSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    peaking_2QSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 100, 100);
    peaking_2QSlider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::yellow);
    addAndMakeVisible(peaking_2QSlider);

    peaking_2QAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "q2", peaking_2QSlider);

    peaking_2GainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    peaking_2GainSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 100, 100);
    peaking_2GainSlider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::yellow);
    addAndMakeVisible(peaking_2GainSlider);

    peaking_2GainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "gain2", peaking_2GainSlider);





    peaking_3Slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    peaking_3Slider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 100, 100);
    peaking_3Slider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::purple);
    addAndMakeVisible(peaking_3Slider);

    peaking_3Attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "cutoffFreq3", peaking_3Slider);

    peaking_3QSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    peaking_3QSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 100, 100);
    peaking_3QSlider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::purple);
    addAndMakeVisible(peaking_3QSlider);

    peaking_3QAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "q3", peaking_3QSlider);

    peaking_3GainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    peaking_3GainSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 100, 100);
    peaking_3GainSlider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::purple);
    addAndMakeVisible(peaking_3GainSlider);

    peaking_3GainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "gain3", peaking_3GainSlider);


    setSize (500, 500);
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

    peaking_1Slider.setBounds({ 75, 100, 100, 100 });
    peaking_1QSlider.setBounds({ 75, 225, 100, 100 });
    peaking_1GainSlider.setBounds({ 75, 350, 100, 100 });

    peaking_2Slider.setBounds({ 200, 100, 100, 100 });
    peaking_2QSlider.setBounds({ 200, 225, 100, 100 });
    peaking_2GainSlider.setBounds({ 200, 350, 100, 100 });

    peaking_3Slider.setBounds({ 325, 100, 100, 100 });
    peaking_3QSlider.setBounds({ 325, 225, 100, 100 });
    peaking_3GainSlider.setBounds({ 325, 350, 100, 100 });
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


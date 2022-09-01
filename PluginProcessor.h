/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "filters.h"

//==============================================================================
/**
*/
class BasicParametricEQAudioProcessor  : public juce::AudioProcessor
                            #if JucePlugin_Enable_ARA
                             , public juce::AudioProcessorARAExtension
                            #endif
{
public:
    //==============================================================================
    BasicParametricEQAudioProcessor();
    ~BasicParametricEQAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void updateFilter();
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

    juce::AudioProcessorValueTreeState apvts;

    Filters filterL;
    Filters filterR;

    Filters filterL2;
    Filters filterR2;

    Filters filterL3;
    Filters filterR3;

private:
    juce::AudioProcessorValueTreeState::ParameterLayout createParameters();

    double s_rate = 0.f;

    float cutoffFreq1 = 0.f;
    float qualityFactor1 = 0.f;
    float gain1 = 0.f;

    float cutoffFreq2 = 0.f;
    float qualityFactor2 = 0.f;
    float gain2 = 0.f;

    float cutoffFreq3 = 0.f;
    float qualityFactor3 = 0.f;
    float gain3 = 0.f;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BasicParametricEQAudioProcessor)
};

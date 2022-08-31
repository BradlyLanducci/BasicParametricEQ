/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
BasicParametricEQAudioProcessor::BasicParametricEQAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), apvts(*this, nullptr, "BasicEQ", createParameters())
#endif
{
    apvts.state = juce::ValueTree("BasicEQ Parameters");
}

BasicParametricEQAudioProcessor::~BasicParametricEQAudioProcessor()
{
}

//==============================================================================
const juce::String BasicParametricEQAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool BasicParametricEQAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool BasicParametricEQAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool BasicParametricEQAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double BasicParametricEQAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int BasicParametricEQAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int BasicParametricEQAudioProcessor::getCurrentProgram()
{
    return 0;
}

void BasicParametricEQAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String BasicParametricEQAudioProcessor::getProgramName (int index)
{
    return {};
}

void BasicParametricEQAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void BasicParametricEQAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..

    s_rate = sampleRate;

    updateFilter();
}

void BasicParametricEQAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool BasicParametricEQAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void BasicParametricEQAudioProcessor::updateFilter()
{
    cutoffFreq1 = apvts.getRawParameterValue("cutoffFreq1")->load();
    qualityFactor1 = apvts.getRawParameterValue("q1")->load();
    gain1 = apvts.getRawParameterValue("gain1")->load();

    filterL.setSampleRate(s_rate);
    filterL.setPeakingCoefficients(cutoffFreq1, qualityFactor1, gain1);
    filterR.setSampleRate(s_rate);
    filterR.setPeakingCoefficients(cutoffFreq1, qualityFactor1, gain1);
}

void BasicParametricEQAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());

    float* channelL = buffer.getWritePointer(0);
    float* channelR = buffer.getWritePointer(1);

    for (int sample = 0; sample < buffer.getNumSamples(); sample++)
    {
        updateFilter();

        channelL[sample] = filterL.processSample(channelL[sample]);
        channelR[sample] = filterR.processSample(channelR[sample]);
    }
}

//==============================================================================
bool BasicParametricEQAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* BasicParametricEQAudioProcessor::createEditor()
{
    return new BasicParametricEQAudioProcessorEditor (*this);
}

//==============================================================================
void BasicParametricEQAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void BasicParametricEQAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

juce::AudioProcessorValueTreeState::ParameterLayout BasicParametricEQAudioProcessor::createParameters()
{

    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    auto normRange = juce::NormalisableRange<float>(80.f, 18000.0f);
    normRange.setSkewForCentre(500.f);

    params.push_back(std::make_unique<juce::AudioParameterFloat>("cutoffFreq1", "CutoffFreq1", normRange, 500.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("q1", "Q1", 0.5f, 5.0f, (5.0 - 0.5f) / 2.f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("gain1", "Gain1", 5.0f, 50.0f, 5.0f));

    return { params.begin(), params.end() };
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new BasicParametricEQAudioProcessor();
}

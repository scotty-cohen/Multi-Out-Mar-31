/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"



//==============================================================================
void Week3SineGeneratorAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    mDelayL.initialize(sampleRate, samplesPerBlock);
    mDelayR.initialize(sampleRate, samplesPerBlock);
//    
}


void Week3SineGeneratorAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    /* boiler plate stuff to not touch */

//    jassert(buffer.getNumChannels() == getTotalNumOutputChannels() || buffer.getNumChannels() == 2);
    
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    
//    jassert(buffer.getNumChannels() == getTotalNumOutputChannels() || buffer.getNumChannels() == 2);
    
    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    
    
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        
        



    
    jassert(buffer.getNumChannels() == getTotalNumOutputChannels() || buffer.getNumChannels() == 2);

//
    
    // Get the panning position from the parameters
    float panPosition = mParameterManager->getTreeState().getParameterAsValue(ParameterIDStrings[AppParameterID::Size]).getValue();
    // Pan the audio buffer
    mPanning->panAudioBuffer(buffer, panPosition, 4);

    //ALL THE COMMENTED OUT CODE BETWEEN THE JASSERTS CAUSES.... JASSERTS WHEN THE PLUGIN IS INITIALIZED
        
//        jassert(buffer.getNumChannels() == getTotalNumOutputChannels());
//

    
    jassert(buffer.getNumChannels() == getTotalNumOutputChannels());
    
    
    mDelayL.setParameters(mParameterManager->getCurrentParameterValue(AppParameterID::Time),
                          mParameterManager->getCurrentParameterValue(AppParameterID::Feedback),
                          mParameterManager->getCurrentParameterValue(AppParameterID::Mix),
                          mParameterManager->getCurrentParameterValue(AppParameterID::Lowpass),
                          mParameterManager->getCurrentParameterValue(AppParameterID::Highpass));
//
    mDelayR.setParameters(mParameterManager->getCurrentParameterValue(AppParameterID::Time),
                          mParameterManager->getCurrentParameterValue(AppParameterID::Feedback),
                          mParameterManager->getCurrentParameterValue(AppParameterID::Mix),
                          mParameterManager->getCurrentParameterValue(AppParameterID::Lowpass),
                          mParameterManager->getCurrentParameterValue(AppParameterID::Highpass));
////
////
        mDelayL.processBlock(buffer.getWritePointer(0), buffer.getNumSamples());
        mDelayR.processBlock(buffer.getWritePointer(1), buffer.getNumSamples());




}
                          


//

//==============================================================================
Week3SineGeneratorAudioProcessor::Week3SineGeneratorAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)

//This is where we add 4 extra output buses: "Name", Channel Config, Activated By Default
                       .withOutput ("Bus #1",  juce::AudioChannelSet::stereo(), true)
                       .withOutput ("Bus #2",  juce::AudioChannelSet::stereo(), true)
                       .withOutput ("Bus #3",  juce::AudioChannelSet::stereo(), true)
                       .withOutput ("Bus #4",  juce::AudioChannelSet::stereo(), true)
#endif
                       )


{
    mParameterManager = std::make_unique<ParameterManager>(this);
    mPanning = std::make_unique<Panning>(this);
}

#endif
//{
//
//}




Week3SineGeneratorAudioProcessor::~Week3SineGeneratorAudioProcessor()
{
}

//==============================================================================
const juce::String Week3SineGeneratorAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Week3SineGeneratorAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Week3SineGeneratorAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Week3SineGeneratorAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Week3SineGeneratorAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Week3SineGeneratorAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Week3SineGeneratorAudioProcessor::getCurrentProgram()
{
    return 0;
}

void Week3SineGeneratorAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String Week3SineGeneratorAudioProcessor::getProgramName (int index)
{
    return {};
}

void Week3SineGeneratorAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

void Week3SineGeneratorAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Week3SineGeneratorAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

//==============================================================================
bool Week3SineGeneratorAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* Week3SineGeneratorAudioProcessor::createEditor()
{
    return new Week3SineGeneratorAudioProcessorEditor (*this);
}

//==============================================================================
void Week3SineGeneratorAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
//
//    auto state = mParameterState.copyState();
//    std::unique_ptr<juce::XmlElement> xml (state.createXml());
//    copyXmlToBinary (*xml, destData);
//    
    

}

void Week3SineGeneratorAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    
//    std::unique_ptr<juce::XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));
//    mParameterState.replaceState (juce::ValueTree::fromXml (*xmlState));

//

}

ParameterManager* Week3SineGeneratorAudioProcessor::getParameterManager()
{
    return mParameterManager.get();
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Week3SineGeneratorAudioProcessor();
}

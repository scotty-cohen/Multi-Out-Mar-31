/*
  ==============================================================================

    Panning.h
    Created: 1 Apr 2023 7:04:12pm
    Author:  Scott Cohen

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>



//#include <JuceHeader.h>

class Panning{
public:
    
    Panning(juce::AudioProcessor* inAudioProcessor);
    
    ~Panning();
    
    /* */
    void panAudioBuffer(juce::AudioBuffer<float>& buffer, float panPosition, int numBuses);

    
    static const size_t MAX_NUM_BUSES = 32;


private:
    /* */
    void updateBusBuffers(juce::AudioBuffer<float>& buffer, int numBuses);
    
    juce::AudioProcessor* mAudioProcessor;
    std::array<juce::AudioBuffer<float>, MAX_NUM_BUSES> mBusBuffers;

    
};

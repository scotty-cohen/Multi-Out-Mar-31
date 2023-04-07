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
    
    Panning();
    
    /* */
    void panAudioBuffer(juce::AudioBuffer<float>& buffer, float panPosition, int numBuses,std::vector<juce::AudioBuffer<float>>& busBuffers);
    
    /* */
    void createBusBuffers(juce::AudioBuffer<float>& buffer, int numBuses, std::vector<juce::AudioBuffer<float>>& busBuffers);


    
private:
     


    
};

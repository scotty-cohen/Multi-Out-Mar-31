/*
  ==============================================================================

    Panning.cpp
    Created: 1 Apr 2023 7:04:12pm
    Author:  Scott Cohen

  ==============================================================================
*/

#include "Panning.h"
#include <JuceHeader.h>

Panning::Panning(juce::AudioProcessor* inAudioProcessor)
{
    mAudioProcessor = inAudioProcessor;
}

Panning::~Panning() = default;

void Panning::panAudioBuffer(juce::AudioBuffer<float>& buffer, float panPosition, int numBuses)
{
    updateBusBuffers(buffer, numBuses);
    
    //linear panning algorythm for gain knob
    //the width of a 'notch' in the slider
    auto notch = 1.0/numBuses;
             
    //home of position of each bus on the slider
    std::vector<float> homePositions(numBuses);
    for (int i = 0; i < numBuses; ++i) {
        homePositions[i] = notch * i;
    }

    //normalized slider position (0 - 1)
    auto sliderPosition = panPosition;

    std::vector<double> levelsL(numBuses);
    std::vector<double> levelsR(numBuses);
    
    
    for (int i = 0; i < numBuses; ++i) {
        double levelL = juce::jlimit(0.0, 1.0, std::abs((homePositions[i] - sliderPosition) / notch));
        double levelR = juce::jlimit(0.0, 1.0, std::abs((homePositions[i] - sliderPosition) / notch));
        levelL = 1 - levelL;
        levelR = 1 - levelR;
        
        levelsL[i] = levelL;
        levelsR[i] = levelR;
    }
    
    for (int sample = 0; sample < buffer.getNumSamples(); ++sample) {
        auto left_sample = buffer.getSample(0, sample);
        auto right_sample = buffer.getSample(1, sample);

        
        //PROBLEM
        for (int i = 0; i < numBuses; i++) {
            mBusBuffers[i].setSample(0, sample, (left_sample * levelsL[i]));
            mBusBuffers[i].setSample(1, sample, (right_sample * levelsR[i]));

        }
        
    }


}

void Panning::updateBusBuffers(juce::AudioBuffer<float>& buffer, int numBuses)
{
    // Create bus buffers with the same number of channels as the input buffer (assuming stereo)
    jassert(numBuses <= MAX_NUM_BUSES);
    
    for (int i = 0; i < numBuses; ++i) {
        mBusBuffers[i] = mAudioProcessor->getBusBuffer(buffer, false, i + 1);
    }
}
    

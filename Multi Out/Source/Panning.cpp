/*
  ==============================================================================

    Panning.cpp
    Created: 1 Apr 2023 7:04:12pm
    Author:  Scott Cohen

  ==============================================================================
*/

#include "Panning.h"
#include <JuceHeader.h>

Panning::Panning ()
{
    
}

void Panning::panAudioBuffer(juce::AudioBuffer<float>& buffer, float panPosition, int numBuses, std::vector<juce::AudioBuffer<float>>& busBuffers)
{
    
    
    // create bus buffers if they don't exist
    if (busBuffers.size() != numBuses) {
        createBusBuffers(buffer, numBuses, busBuffers);
    }
    //linear panning algorythm for gain knob
    //the width of a 'notch' in the slider
    auto notch = 1.0/numBuses;
             
    //home of position of each bus on the slider
    std::vector<float> homePositions(numBuses);
    for (int i = 0; i < numBuses; ++i) {
        homePositions[i] = notch * i;
    }

//    //normalized slider position (0 - 1)
    auto sliderPosition = panPosition;
//
    std::vector<double> levelsL(numBuses);
    std::vector<double> levelsR(numBuses);
    
    
    for (int i = 0; i < numBuses; ++i) {
        double levelL = juce::jlimit(0.0, 1.0, std::abs((homePositions[i] - sliderPosition + notch/2.0) / notch));
        double levelR = juce::jlimit(0.0, 1.0, std::abs((homePositions[i] - sliderPosition + notch/2.0) / notch));
        levelsL[i] = levelL;
        levelsR[i] = levelR;

            auto& busBuffer = busBuffers[i];

            for (int sample = 0; sample < buffer.getNumSamples(); ++sample) {
                auto left_sample = buffer.getSample(0, sample);
                auto right_sample = buffer.getSample(1, sample);

                
                //PROBLEM
                busBuffer.setSample(0, sample, (left_sample * levelsL[i]));
                busBuffer.setSample(1, sample, (right_sample * levelsR[i]));

            }

    }
}
//
//void Panning::createBusBuffers(juce::AudioBuffer<float>& buffer, int numBuses, std::vector<juce::AudioBuffer<float>>& busBuffers)
//{
//    // Create bus buffers with the same number of channels as the input buffer (assuming stereo)
//    for (int i = 0; i < numBuses; ++i) {
//        busBuffers.push_back(getBusBuffer(buffer, false, 1));
//    }
//}
//    




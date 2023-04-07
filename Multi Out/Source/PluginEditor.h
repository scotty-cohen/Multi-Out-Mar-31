/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "SliderContainer.h"
#include "MyLookAndFeel.h"

//==============================================================================
/**
*/
class Week3SineGeneratorAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                                public juce::Timer
{
public:
    Week3SineGeneratorAudioProcessorEditor (Week3SineGeneratorAudioProcessor&);
    ~Week3SineGeneratorAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void timerCallback() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    
    MyLookAndFeel mLookAndFeel;
    
    
    //Slider Container
    juce::OwnedArray<SliderContainer> mSliderContainers;
    
    
    //Rotary Gain/Position Slider
    juce::Slider mGain;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mGainAttachment;
//
//
   //Buttons
    juce::TextButton dToggle {"On/Off"};
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> dToggleAttachment;

 //Combobox For configuration
    juce::ComboBox mComboBox;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> mComboBoxAttachment;
    
    juce::FlexBox mFlexbox;

    
  Week3SineGeneratorAudioProcessor& audioProcessor;
    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Week3SineGeneratorAudioProcessorEditor)
};

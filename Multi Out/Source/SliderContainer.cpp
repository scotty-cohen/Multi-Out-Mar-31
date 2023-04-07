/*
  ==============================================================================

    SliderContainer.cpp
    Created: 31 Mar 2023 9:36:21pm
    Author:  Scott Cohen

  ==============================================================================
*/

#include "SliderContainer.h"


/**/
SliderContainer::SliderContainer()
{
    
    
    mSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
     
    mLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(mSlider);
    addAndMakeVisible(mLabel);
    
    

}

/**/
void SliderContainer::setParameterToControl(juce::AudioProcessorValueTreeState& inVTS, const juce::String& inParamID)
{
    mLabel.setText(inParamID, juce::dontSendNotification);
    mAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(inVTS, inParamID, mSlider));
}
 
/**/
void SliderContainer::resized()
{
    
    auto bounds = getLocalBounds();
    int knobSize = mLookAndFeel.getKnobSize();
    
    mSlider.setBounds(bounds.removeFromTop(getHeight()*.8f));
    mSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, knobSize, mSlider.getHeight() * 0.03f);
    
    mLabel.setBounds(bounds);
    mLabel.setFont(Font(14.0f));
    mLabel.setColour(Label::textColourId, Colours::black);


}

    

    
    
    
    
    

//


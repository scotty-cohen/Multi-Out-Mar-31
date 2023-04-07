/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "ParameterDefines.h"



//==============================================================================
Week3SineGeneratorAudioProcessorEditor::Week3SineGeneratorAudioProcessorEditor (Week3SineGeneratorAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setLookAndFeel(&mLookAndFeel);
    
    
    auto& tree_state = audioProcessor.getParameterManager()->getTreeState();

    for (int i = 0; i < audioProcessor.getParameters().size();i++) {
        mSliderContainers.add(new SliderContainer());
        mSliderContainers[i]->setParameterToControl(tree_state, ParameterIDStrings[i]);
        addAndMakeVisible(mSliderContainers[i]);
        
    }
   

    
    
    
    
    
    
    

//    auto gain_range = float_param -> getNormalisableRange();
    addAndMakeVisible (mGain);
    mGain.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
//    mGainAttachment.reset (new juce::AudioProcessorValueTreeState::SliderAttachment (tree_state, "Gain", mGain));
//    mGain.setRange(gain_range.start, gain_range.end);
//    mGain.setValue(gain_range.convertFrom0to1(float_param -> get()));
//
//    //lamba expression
//    mGain.onValueChange = [this, float_param] () {
//
//        float_param -> setValueNotifyingHost(mGain.getValue());
//        audioProcessor.setGain(mGain.getValue());
//    };
//


//
//    //Add Button
    addAndMakeVisible(dToggle);
//
//    //Add ComboBox
    addAndMakeVisible(mComboBox);
    mComboBox.setTextWhenNothingSelected("Configure");
    mComboBox.addItem("4", 1);
    mComboBox.addItem("6", 2);
    mComboBox.addItem("8", 3);
    mComboBox.addItem("10", 4);



    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (800, 475);

    
    
}

Week3SineGeneratorAudioProcessorEditor::~Week3SineGeneratorAudioProcessorEditor()
{
    setLookAndFeel(nullptr);
}

//==============================================================================
void Week3SineGeneratorAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (Colour(194,220,226));
}

void Week3SineGeneratorAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    
    
    //GAIN/PAN KNOB PLACEMENT
    auto leftMargin = getWidth() * 0.02;
    auto topMargin = getHeight() * 0.15;
    auto sliderSize = getWidth() * 0.5;
    mGain.setBounds (leftMargin, topMargin, sliderSize, sliderSize);
    mGain.setTextBoxStyle(juce::Slider::TextBoxBelow, true, getWidth(), 20);
    
    auto bounds = getLocalBounds();
    auto flexbox_width = bounds.getWidth() * 0.3;
    auto flexbox_bounds = bounds.removeFromRight(flexbox_width).withY(-100);
    
    
    mFlexbox.flexDirection = FlexBox::Direction::row;
    mFlexbox.flexWrap = juce::FlexBox::Wrap::wrap;
    mFlexbox.justifyContent = juce::FlexBox::JustifyContent::center;
    mFlexbox.alignContent = FlexBox::AlignContent::center;
    Array<FlexItem> itemArray;
    
    for (auto* i : mSliderContainers)
    {
        mFlexbox.items.add (juce::FlexItem (*i).withMinHeight (75.0f).withMinWidth (75.0f).withFlex (1));
    
    juce::FlexBox fb;
                fb.flexDirection = juce::FlexBox::Direction::column;
     
        fb.items.add (juce::FlexItem (mFlexbox).withFlex (2.5));
     
                fb.performLayout (flexbox_bounds.toFloat());
            }
    
    

    
    
//
//
    //size combo box
    mComboBox.setBounds(mGain.getX() + (mGain.getWidth()*1.5), topMargin * 4, sliderSize * .25, sliderSize * .10);
//
//
    //size button
    dToggle.setBounds(mGain.getX() + (leftMargin*35), topMargin/8, sliderSize * .15, sliderSize * .10);
}

void Week3SineGeneratorAudioProcessorEditor::timerCallback()
{
    
}

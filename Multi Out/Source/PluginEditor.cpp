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

    for (int i = 0; i < audioProcessor.getParameters().size(); i++) {
        mSliderContainers.add(new SliderContainer());
        mSliderContainers[i]->setParameterToControl(tree_state, ParameterIDStrings[i]);
        addAndMakeVisible(mSliderContainers[i]);
    }
    
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
        fb.performLayout (getLocalBounds().toFloat());
    }
}

void Week3SineGeneratorAudioProcessorEditor::timerCallback()
{
    
}

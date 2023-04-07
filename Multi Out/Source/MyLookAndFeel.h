/*
  ==============================================================================

    LookAndFeel.h
    Created: 2 Apr 2023 9:59:41pm
    Author:  Scott Cohen

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class MyLookAndFeel: public juce::LookAndFeel_V4
{
    
public:
    
    int getKnobSize() const
    {
        return mKnobSize;
    }
    
 void drawRotarySlider (Graphics& g, int x, int y, int width, int height,
                                              float sliderPosProportional,
                                              float rotaryStartAngle,
                                              float rotaryEndAngle,
                                              Slider&) override;
    
    
    
private:
    
    int mKnobSize = 0;

  
};

/*
  ==============================================================================

    LookAndFeel.cpp
    Created: 2 Apr 2023 9:59:41pm
    Author:  Scott Cohen

  ==============================================================================
*/

#include "MyLookAndFeel.h"


void MyLookAndFeel::drawRotarySlider (Graphics& g, int x, int y, int width, int height,
                                             float sliderPos,
                                             float rotaryStartAngle,
                                             float rotaryEndAngle,
                                             Slider& slider)
{
    int knob_size = jmin(width, height);
    
    
    mKnobSize = knob_size;
    
    Rectangle<float> container_bounds { (float) x ,(float) y,(float) width,(float) height};
    Rectangle<float> knob_bounds { container_bounds.getCentreX() - knob_size/2,
        container_bounds.getCentreY() - knob_size/2,
        (float) knob_size,
        (float) knob_size};
    Point<float> center = knob_bounds.getCentre();
    
    g.setColour(Colour(100,100,100));
    g.fillEllipse(knob_bounds);
    
    g.setColour(Colour(255, 255, 255));
    g.fillEllipse(knob_bounds.reduced(knob_size*.01, knob_size*.01));
    
    g.setColour(Colour (100, 100, 100));
    g.fillEllipse(knob_bounds.reduced(knob_size*.08, knob_size*.08));
    

    
        auto toAngle = rotaryStartAngle + sliderPos * (MathConstants<float>::twoPi/2);

        auto knobCenter = knob_bounds.getCentre();
        auto thumbRadius = knob_size;
        auto thumbRadius2 = knob_size *.5;
        auto rectBounds = knob_bounds.withSizeKeepingCentre(knob_size * 0.6, knob_size * 0.5);
        auto rectCenter = rectBounds.getCentre();
        auto rectAngle = toAngle;


        // Rotate the graphics context around the center of the knob
        g.addTransform (AffineTransform::rotation (toAngle, knobCenter.x, knobCenter.y));

        
        // Draw line
        g.setColour (Colours::black);
        for (int i = 0; i < 1; i++) {
            g.drawLine (rectCenter.getX(), rectCenter.getY(),
                        rectCenter.getX() + (thumbRadius * 0.5) * std::cos(rectAngle),
                        rectCenter.getY() + (thumbRadius * 0.5) * std::sin(rectAngle),
                        knob_size * 0.075);

            
            
    }
    
    // Draw line
    g.setColour(Colour (100, 100, 100));
    g.strokePath(Path().createPathWithRoundedCorners(4), PathStrokeType(10.0));
    for (int i = 0; i < 1; i++) {
        g.drawLine (rectCenter.getX(), rectCenter.getY(),
                    rectCenter.getX() + (thumbRadius2 * 0.5) * std::cos(rectAngle),
                    rectCenter.getY() + (thumbRadius2 * 0.5) * std::sin(rectAngle),
                    knob_size * 0.1);
        
    }

    // Draw the center circle
    auto centerSize = knob_size * 0.1f;
    auto centerBounds = Rectangle<float>(center.x - centerSize / 2.0f,
                                         center.y - centerSize / 2.0f,
                                         centerSize,
                                         centerSize);
    g.setColour(Colour(100, 100, 100));
    g.fillEllipse(centerBounds);


}

//void drawLinearSlider(juce::Graphics& g, int x, int y, int width, int height,
//                       float sliderPos, float minSliderPos, float maxSliderPos,
//                       const juce::Slider::SliderStyle style, juce::Slider& slider)
//{
//    g.fillAll(Colours::transparentBlack);
//
//    if (style == juce::Slider::LinearHorizontal || style == juce::Slider::LinearVertical)
//    {
//        auto sliderBounds = slider.getLocalBounds();
//        auto centerX = sliderBounds.getCentreX();
//        auto centerY = sliderBounds.getCentreY();
//        auto sliderRadius = jmin(sliderBounds.getWidth(), sliderBounds.getHeight()) * 0.25f;
//
//        juce::Path p;
//        if (style == juce::Slider::LinearHorizontal)
//            p.addRectangle(0, 0, sliderPos * sliderBounds.getWidth(), sliderBounds.getHeight());
//        else
//            p.addRectangle(0, sliderBounds.getHeight() - sliderPos * sliderBounds.getHeight(),
//                           sliderBounds.getWidth(), sliderPos * sliderBounds.getHeight());
//
//        g.setColour(slider.findColour(juce::Slider::trackColourId));
//        g.fillPath(p, p.getTransformToScaleToFit(sliderBounds.toFloat(), true));
//
//        g.setColour(slider.findColour(juce::Slider::thumbColourId));
//        g.fillEllipse(centerX + sliderPos * (sliderBounds.getWidth() - sliderRadius * 2.0f) - sliderRadius,
//                      centerY - sliderRadius,
//                      sliderRadius * 2.0f, sliderRadius * 2.0f);
//    }
//}




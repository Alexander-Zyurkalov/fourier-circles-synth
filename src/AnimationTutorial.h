/*
  ==============================================================================

   This file is part of the JUCE tutorials.
   Copyright (c) 2020 - Raw Material Software Limited

   The code included in this file is provided under the terms of the ISC license
   http://www.isc.org/downloads/software-support-policy/isc-license. Permission
   To use, copy, modify, and/or distribute this software for any purpose with or
   without fee is hereby granted provided that the above copyright notice and
   this permission notice appear in all copies.

   THE SOFTWARE IS PROVIDED "AS IS" WITHOUT ANY WARRANTY, AND ALL WARRANTIES,
   WHETHER EXPRESSED OR IMPLIED, INCLUDING MERCHANTABILITY AND FITNESS FOR
   PURPOSE, ARE DISCLAIMED.

  ==============================================================================
*/

/*******************************************************************************
 The block below describes the properties of this PIP. A PIP is a short snippet
 of code that can be read by the Projucer and used to generate a JUCE project.

 BEGIN_JUCE_PIP_METADATA

 name:             AnimationTutorial
 version:          1.0.0
 vendor:           JUCE
 website:          http://juce.com
 description:      Animates a fish.

 dependencies:     juce_core, juce_data_structures, juce_events, juce_graphics,
                   juce_gui_basics, juce_gui_extra
 exporters:        xcode_mac, vs2019, linux_make, xcode_iphone, androidstudio

 type:             Component
 mainClass:        MainContentComponent

 useLocalCopy:     1

 END_JUCE_PIP_METADATA

*******************************************************************************/


#pragma once
#include <juce_graphics/juce_graphics.h>
#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_gui_extra/juce_gui_extra.h>
#include <juce_core/juce_core.h>
#include <juce_dsp/juce_dsp.h>
#include "gui/FourierCircle.h"

//==============================================================================
class MainContentComponent   : public juce::AnimatedAppComponent
{
public:
    //==============================================================================
    MainContentComponent()
    {
        setSize (800, 600);
        setFramesPerSecond(frameRate);
    }

    void update() override
    {
        // This function is called at the frequency specified by the setFramesPerSecond() call
        // in the constructor. You can use it to update counters, animate values, etc.
        rad += juce::MathConstants<float>::pi /(float)frameRate;
        if (rad > juce::MathConstants<float>::pi )
            rad = -juce::MathConstants<float>::pi;
        y = juce::dsp::FastMathApproximations::sin(rad);
        x = juce::dsp::FastMathApproximations::cos(rad);
    }

    void paint (juce::Graphics& g) override
    {
//        / // (Our component is opaque, so we must completely fill the background with a solid colour)
        g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
        g.setColour (getLookAndFeel().findColour (juce::Slider::thumbColourId));

        FourierCircle* prevCircle{nullptr};
        for(int i=0; i< 5; ++i) {
            FourierCircle fourierCircle{prevCircle, getWidth(), getHeight(),
                                        x,
                                        y, 1.0f/((float)i+1.0f)};
            fourierCircle.paint(g);
            delete prevCircle;
            prevCircle = new FourierCircle{fourierCircle};
        }
        delete prevCircle;
    }

    void resized() override
    {
        // This is called when the MainContentComponent is resized.
        // If you add any child components, this is where you should
        // update their positions.
    }

private:
    float rad = 0.0f, y = 0.0f, x = 0.0f;
    int frameRate = 60;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};

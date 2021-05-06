/*
  ==============================================================================

    Filter.h
    Created: 1 May 2021 7:42:29pm
    Author:  rossk

  ==============================================================================
*/

#pragma once

#define _USE_MATH_DEFINES

#include "../JuceLibraryCode/JuceHeader.h"
#include "CircularBuffer.h"
#include "Biquad.h"
//#include "math.h"
#include <cmath>



class Filter
{
public:
    Filter();
    ~Filter();

    float filterSelector(float sample, float cutoff, float q, float sampleRate, int filterType);

protected:
    juce::Array<CircularBuffer> filterBuffer;

    Biquad biquad;
    //float x0, x1, x2, y0, y1, y2;
    //float a1, a2, a3, a4, b1, b2, b3, b4;
    //float input, output;
};
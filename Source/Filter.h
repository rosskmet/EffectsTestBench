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
#include "Ladder.h"
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
    Ladder ladder;

};
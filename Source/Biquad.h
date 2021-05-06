/*
  ==============================================================================

    Biquad.h
    Created: 5 May 2021 8:21:55am
    Author:  rossk

  ==============================================================================
*/

#pragma once

#define _USE_MATH_DEFINES

#include "../JuceLibraryCode/JuceHeader.h"
#include "CircularBuffer.h"
#include <cmath>
//#include "Filter.h"

class Biquad //: public Filter
{
public:
	Biquad();
	~Biquad();

    void calculateBiquad(float cutoff, float q, float sampleRate, int filterType);

    float applyBiquad(float sample);

protected:

    float a0, a1, a2, b1, b2;
    float x0, x1, x2, y1, y2;
    float input, output;
    float theta, d, beta, gamma, alpha, qc;

private:

};
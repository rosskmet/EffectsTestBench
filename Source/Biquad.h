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


class Biquad //: public Filter
{
public:
	Biquad();
	~Biquad();

    void calculateBiquad(double cutoff, double q, double sampleRate, int filterType);

    float applyBiquad(double sample);

protected:

    double a0, a1, a2, b1, b2;
    double x0, x1, x2, y1, y2;
    double input, output;
    double theta, d, beta, gamma, alpha, qc;

private:

};
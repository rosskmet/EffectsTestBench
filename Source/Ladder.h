/*
  ==============================================================================

    Ladder.h
    Created: 6 May 2021 4:29:44pm
    Author:  rossk

  ==============================================================================
*/

#pragma once

#define _USE_MATH_DEFINES

#include "../JuceLibraryCode/JuceHeader.h"
#include "CircularBuffer.h"
#include <cmath>

class Ladder
{
public:
    Ladder();
    ~Ladder();

    void calculateLadder(double cutoff, double q, double sampleRate, int filterType);

    float applyLadder(double sample);

protected:
    double a1, a2, a3, a4, b1, b2, b3, b4;
    double input, output;
    double Gcomp, g, Gres, h0, h1;

private:

};
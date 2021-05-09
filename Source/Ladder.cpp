/*
  ==============================================================================

    Ladder.cpp
    Created: 6 May 2021 4:29:44pm
    Author:  rossk

  ==============================================================================
*/



#include "Ladder.h"

Ladder::Ladder()
{
    input = 0.0;
    output = 0.0;

    a1 = a2 = a3 = a4 = b1 = b2 = b3 = b4 = 0.0;
    h0 = h1 = Gcomp = g = Gres = 0.0;
}

Ladder::~Ladder()
{

}

void Ladder::calculateLadder(double cutoff, double q, double sampleRate, int filterType)
{
    ////float scale = sampleRate / 19999.9999f;

    switch (filterType) {
    //Low-Pass Ladder
    case 2:
        q = 2.0f * q;

        Gcomp = 0.5f;
        //g = (2 * M_PI * cutoff) / sampleRate;
        g = (2 * M_PI * cutoff) / sampleRate;
        //float g = (pi * cutoff) / sampleRate;
        //float g = (2.0f * cutoff) / (2.0f * sampleRate);
        Gres = (q / 2.0f); //Self Oscillates at 4
        h0 = g / 1.3f;
        h1 = g * 0.3f / 1.3f;

        //q = 4.0 * q;

        //wd = 2 * M_PI * cutoff;
        //wa = (2 * sampleRate) * juce::dsp::FastMathApproximations::tan(g * (1 / sampleRate) * 0.5);
        //g = wa * (1 / sampleRate) * 0.5;
        //h
        break;
    default:
        break;
    }

}

float Ladder::applyLadder(double sample)
{

    input = sample;
    input -= 4.0f * Gres * (b4 - Gcomp * input);
    input = tanh(input);

    b1 = (h0 * input) + (h1 * a1) + (1 - g) * b1; // Pole 1
    a1 = input;
    b2 = (h0 * b1) + (h1 * a2) + (1 - g) * b2;  // Pole 2
    a2 = b1;
    b3 = (h0 * b2) + (h1 * a3) + (1 - g) * b3;  // Pole 3
    a3 = b2;
    b4 = (h0 * b3) + (h1 * a4) + (1 - (g / 2)) * b4;  // Pole 4
    b4 = b4 - (b4 * b4 * b4) * 0.166667f;
    a4 = b3;

    //output = (input - 3.0f * (b3 - b4)) - b4;
    output = b4;

    return output;
}
/*
  ==============================================================================

    Amplifier.h
    Created: 5 May 2021 8:24:55am
    Author:  rossk

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class Amplifier {
public:
    Amplifier();
    ~Amplifier();

    float applyAmplifier(float sample, float gain);

private:
    float gain;
};
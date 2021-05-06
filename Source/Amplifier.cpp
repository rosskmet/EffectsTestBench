/*
  ==============================================================================

    Amplifier.cpp
    Created: 5 May 2021 8:24:55am
    Author:  rossk

  ==============================================================================
*/

#include "Amplifier.h"

Amplifier::Amplifier()
{
    gain = 0.5;
}

Amplifier::~Amplifier()
{

}

float Amplifier::applyAmplifier(float sample, float gain)
{
    sample *= pow(10, (gain / 20));

    return sample;
}
/*
  ==============================================================================

    Distortion.cpp
    Created: 1 May 2021 7:08:35pm
    Author:  rossk

  ==============================================================================
*/

#include "Distortion.h"

Distortion::Distortion()
{
    input = 0;
    output = 0;
}

Distortion::~Distortion()
{

}

float Distortion::applyDistortion()
{
    return output;
}
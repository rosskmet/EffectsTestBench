/*
  ==============================================================================

    Distortion.h
    Created: 1 May 2021 7:08:35pm
    Author:  rossk

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "math.h"

class Distortion
{
public:
    Distortion();
    ~Distortion();

    float applyDistortion();

private:
    float input, output;
};
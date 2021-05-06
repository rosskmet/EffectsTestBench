/*
  ==============================================================================

    CircularBuffer.h
    Created: 25 Apr 2021 12:39:03am
    Author:  rossk

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class CircularBuffer {

public:
    CircularBuffer();
    CircularBuffer(int bufferSize, int delayLength);

    float getData();
    void setData(float data);
    void nextSample();
private:
    juce::AudioSampleBuffer buffer;

    int writeIndex;
    int readIndex;
    int delayLength;
};
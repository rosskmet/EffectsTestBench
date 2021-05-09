/*
  ==============================================================================

    Filter.cpp
    Created: 1 May 2021 7:42:29pm
    Author:  rossk

  ==============================================================================
*/

#include "Filter.h"

Filter::Filter()
{
	filterBuffer = juce::Array<CircularBuffer>();

	for (int channel = 0; channel < 2; channel++)
	{
		filterBuffer.add(CircularBuffer(1, 10));
	}

	//input = 0.0;
	//output = 0.0;

	//a1 = 0.0;
	//a2 = 0.0;
	//a3 = 0.0;
	//a4 = 0.0;
	//b1 = 0.0;
	//b2 = 0.0;
	//b3 = 0.0;
	//b4 = 0.0;

	//x0 = 0.0;
	//x1 = 0.0;
	//x2 = 0.0;
	//y0 = 0.0;
	//y1 = 0.0;
	//y2 = 0.0;
}


Filter::~Filter()
{

}

float Filter::filterSelector(float sample, float cutoff, float q, float sampleRate, int filterType)
{

	switch (filterType) {
		case 1:
			biquad.calculateBiquad(cutoff, q, sampleRate, filterType);
			sample = biquad.applyBiquad(sample);
			break;
		case 2:
			ladder.calculateLadder(cutoff, q, sampleRate, filterType);
			sample = ladder.applyLadder(sample);
			break;
		case 4:
			biquad.calculateBiquad(cutoff, q, sampleRate, filterType);
			sample = biquad.applyBiquad(sample);
			break;
		case 6:
			biquad.calculateBiquad(cutoff, q, sampleRate, filterType);
			sample = biquad.applyBiquad(sample);
			break;
		case 8:
			biquad.calculateBiquad(cutoff, q, sampleRate, filterType);
			sample = biquad.applyBiquad(sample);
			break;
		default:
			break;
	}

	return sample;
}






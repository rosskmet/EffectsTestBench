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





//Save "Moog"

//float Filter::applyFilter(float sample, float cutoff, float q, float sampleRate)
//{
		//"Moog" style filter, type depends on "output = "
		//q = 4.0f * q;

		//float fs = sampleRate;
		//float Gcomp = 0.5f;
		////float scale = sampleRate / 19999.9999f;
		//float g = (M_PI * cutoff) / sampleRate;
		////float g = (pi * cutoff) / sampleRate;
		////float g = (2.0f * cutoff) / (2.0f * sampleRate);
		//float Gres = (q / 4.0f); //Self Oscillates at 4
		//float h0 = g / 1.3f;
		//float h1 = g * 0.3f / 1.3f;

		//input = sample;
		//input -= 4.0f * Gres * (b4 - Gcomp * input);
		//input = tanh(input);

		//b1 = (h0 * input) + (h1 * a1) + (1 - g) * b1; // Pole 1
		//a1 = input;
		//b2 = (h0 * b1) + (h1 * a2) + (1 - g) * b2;  // Pole 2
		//a2 = b1;
		//b3 = (h0 * b2) + (h1 * a3) + (1 - g) * b3;  // Pole 3
		//a3 = b2;
		//b4 = (h0 * b3) + (h1 * a4) + (1 - (g / 2)) * b4;  // Pole 4
		//b4 = b4 - (b4 * b4 * b4) * 0.166667f;
		//a4 = b3;

		////output = (input - 3.0f * (b3 - b4)) - b4;
		//output = input - b4;

		//return output;
//}



//Save 2nd Order Highpass

//float Filter::applyFilter(float sample, float cutoff, float q, float sampleRate)
//{
//	//Second Order Highpass
//	q = 0.5f + (19.5f * q);
//
//	//float theta = pi * (cutoff / sampleRate);
//	float scale = sampleRate / 19999.9999f;
//	float theta = (scale * cutoff) / sampleRate;
//	//float fc = pi * cutoff / sampleRate;
//	//float theta = tan(fc / 2.0);
//
//	//BIQUAD
//	float d = 1.0f / q;
//	float beta = 0.5f * ((1.0f - (d / 2.0f) * sin(theta)) / (1.0f + (d / 2.0f) * sin(theta)));
//	float gamma = (0.5f + beta) * cos(theta);
//	float a0 = (0.5f + beta + gamma) / 2.0f;
//	float a1 = -(0.5f + beta + gamma);
//	float a2 = a0;
//	float b1 = -2.0f * gamma;
//	float b2 = 2.0f * beta;
//
//	x2 = x1; //x(n - 2)
//	x1 = x0; //x(n - 1)
//	x0 = sample; //x(n)
//
//	y2 = y1; //y(n - 2)
//	y1 = output; //y(n - 1)
//
//	//p. 49 of DAFX book (UDO ZOLZER, DAFX)
//	//inputdnew = inputd - (b1 * input1d) - (b2 * input2d);
//	//inputd = inputdnew;
//	//outputd = (a0 * inputdnew) + (a1 * input1d) + (a2 * input2d);
//
//	//y(n) = b0*x(n) + b1*x(n-1) + b2*x(n-2) - a0*y(n-1) - a1*y(n-2)
//	output = (a0 * x0) + (a1 * x1) + (a2 * x2) - (b1 * y1) - (b2 * y2);
//
//	//output = (input - 3.0f * (b3 - b4)) - b4;
//	//output = a1 - b4;
//
//	return output;
//}
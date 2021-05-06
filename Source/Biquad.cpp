/*
  ==============================================================================

    Biquad.cpp
    Created: 5 May 2021 8:21:55am
    Author:  rossk

  ==============================================================================
*/

#include "Biquad.h"

Biquad::Biquad()
{
	input = 0.0;
	output = 0.0;

	a0 = a1 = a2 = b1 = b2 = 0.0;
	x0 = x1 = x2 = y1 = y2 = 0.0;
	//theta = d = beta = gamma = alpha;
}

Biquad::~Biquad()
{

}

void Biquad::calculateBiquad(float cutoff, float q, float sampleRate, int filterType)
{
	//float scale = sampleRate / 20500.0f;

	switch (filterType) {
		//2nd Order Low-Pass
		case 1:
				q = 0.25f + (19.5f * q);

				theta = (2 * M_PI * cutoff) / sampleRate;
				d = 1.0f / q;
				beta = 0.5f * ((1.0f - (d / 2.0f) * sin(theta)) / (1.0f + (d / 2.0f) * sin(theta)));
				gamma = (0.5f + beta) * cos(theta);

				a0 = (0.5f + beta - gamma) / 2.0f;
				a1 = 0.5f + beta - gamma;
				a2 = a0;
				b1 = -2.0f * gamma;
				b2 = 2.0f * beta;
			break;
		//2nd Order High-Pass
		case 4:
				q = 0.25f + (19.5f * q);

				theta = (2 * M_PI * cutoff) / sampleRate;
				d = 1.0f / q;
				beta = 0.5f * ((1.0f - (d / 2.0f) * sin(theta)) / (1.0f + (d / 2.0f) * sin(theta)));
				gamma = (0.5f + beta) * cos(theta);

				a0 = (0.5f + beta + gamma) / 2.0f;
				a1 = -(0.5f + beta + gamma);
				a2 = a0;
				b1 = -2.0f * gamma;
				b2 = 2.0f * beta;
			break;
		//2nd Order Band-Pass
		case 6:
				//qc = 1 / (q * 19000.0);
				//qc = 1 / (q * 1.5707f);
				qc = ((0.24 + q * 0.8) * 20500.0f) / cutoff; //Will this help???
				theta = (2 * M_PI * cutoff) / sampleRate;
				alpha = theta / (2.0 * qc);

				if ((alpha >= (M_PI / 2.0f))) //THIS CLAMP MAY NEED TO BE PIECEWISE (Up to pi/2, from pi)?
				{
					alpha = 1.57070f;
				}
				//else if (alpha <= M_PI)
				//{
				//	alpha = 3.16f;
				//}
				//else if (alpha >= M_PI)
				//{
				//	alpha = 4.71f;
				//}

				beta = 0.5f * ((1.0f - tan(alpha)) / (1.0f + tan(alpha)));
				gamma = (0.5f + beta) * cos(theta);
				a0 = (0.5f - beta);
				a1 = 0.0f;
				a2 = -a0;
				b1 = -2.0f * gamma;
				b2 = 2.0f * beta;
			break;
		//2nd Order Notch
		case 8:
				//qc = 1 / (q * 1.5707f);
				qc = ((0.24 + q * 0.8) * 20500.0f) / cutoff;
				theta = (2 * M_PI * cutoff) / sampleRate;
				alpha = theta / (2.0 * qc);

				if ((alpha >= (M_PI / 2.0f)))
				{
					alpha = 1.57070f;
				}

				beta = 0.5f * ((1.0f - tan(alpha)) / (1.0f + tan(alpha)));
				gamma = (0.5f + beta) * cos(theta);
				a0 = 0.5f + beta;
				a1 = -2.0f * gamma;
				a2 = a0;
				b1 = -2.0f * gamma;
				b2 = 2.0f * beta;
			break;
		default:
			break;
	}

}

float Biquad::applyBiquad(float sample)
{
	input = sample;

	x2 = x1; //x(n - 2)
	x1 = x0; //x(n - 1)
	x0 = input; //x(n)

	y2 = y1; //y(n - 2)
	y1 = output; //y(n - 1)

	//y(n) = b0*x(n) + b1*x(n-1) + b2*x(n-2) - a0*y(n-1) - a1*y(n-2)
	output = (a0 * x0) + (a1 * x1) + (a2 * x2) - (b1 * y1) - (b2 * y2);

	return output;
}


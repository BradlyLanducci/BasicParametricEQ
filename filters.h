/*
  ==============================================================================

    filters.h
    Created: 30 Aug 2022 10:13:37pm
    Author:  bradl

  ==============================================================================
*/

#pragma once

#define _USE_MATH_DEFINES

#include "math.h"

class Filters
{
public:
    Filters()
    {
    }
    ~Filters()
    {
    }

    void setSampleRate(double _s_rate)
    {
        s_rate = (float)_s_rate;
    }

    void setPeakingCoefficients(float _cutoffFreq,
                         float _qualityFactor,
                         float _gain)
    {
        cutoffFreq = _cutoffFreq;
        qualityFactor = _qualityFactor;
        gain = _gain;

        A = pow(10, gain / 40.f);
        w0 = (2.f * M_PI * cutoffFreq) / s_rate;
        sn = sin(w0);
        cs = cos(w0);

        alphaQ = sn / (2.0 * qualityFactor);
        alphaBW = 0.f;
        alphaS = 0.f;

        a0 = 1.f + (alphaQ / (float)A);
        a1 = -2.f * cs;
        a2 = 1.f - (alphaQ / (float)A);

        b0 = 1.f + (alphaQ * A);
        b1 = -2.f * cs;
        b2 = 1.f - (alphaQ * A);
    }

    float processSample(float in)
    {
        float out = 0.f;

        out = (1 / a0) * ((b0 * in) + (b1 * x1) + (b2 * x2) - (a1 * y1) - (a2 * y2));

        x2 = x1;
        x1 = in;

        y2 = y1;
        y1 = out;

        return out;
    }


private:
    float x1 = 0.f;
    float x2 = 0.f;

    float y1 = 0.f;
    float y2 = 0.f;

    float a0 = 0.f;
    float a1 = 0.f;
    float a2 = 0.f;

    float b0 = 0.f;
    float b1 = 0.f;
    float b2 = 0.f;

    float cutoffFreq = 0.f;
    float qualityFactor = 0.f;
    float s_rate = 0.f;
    float gain = 0.f;

    float w0 = 0.f;
    float sn = 0.f;
    float cs = 0.f;

    float alphaQ = 0.f;
    float alphaBW = 0.f;
    float alphaS = 0.f;

    float A = 0.f;

    
};
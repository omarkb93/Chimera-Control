﻿#pragma once
#include <vector>

struct rearrangementMove
{
	double initFreq = 0;
	double finFreq = 0;
	/// all of the following can (in principle) be individually calibrated.
	// in ms
	double moveTime = 60e-3;
	// in MHz
	double flashingFreq = 1e6;
	// in ns
	double deadTime = 0;
	// the static / moving ratio.
	double staticMovingRatio = 1;
	// the actual wave, ready for pushing to the niawg.
	std::vector<double> waveVals;
};

enum directions
{
	up,
	down,
	left,
	right
};



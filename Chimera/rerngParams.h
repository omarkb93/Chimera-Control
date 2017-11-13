﻿#pragma once

#include "Expression.h"

struct rerngOptionsForm
{
	bool active = false;
	Expression moveSpeed;
	Expression flashingRate;
	Expression moveBias;
	Expression deadTime;
	// the static / moving time ratio, i.e. if 2 this might imply out of a total 60us move, the static part takes up
	// 40us and the moving part takes up 20us.
	Expression staticMovingRatio;
	//
	bool outputInfo = false;
	bool outputIndv = false;
	bool preprogram = false;
	bool useCalibration = false;
};


enum smartRearrangementOptions
{
	// none places target in center.
	none, 
	// find the optimal convolution match and use that to do the rearrangement algorithm
	convolution,
	// do the full optimization algorithm for all possibilities and use the one with the least moves
	full
};

struct rerngOptions
{
	bool active = false;
	double moveSpeed = 60e-6;
	double flashingRate = 1e6;
	double moveBias=1;
	// 
	double deadTime=0;
	// the static / moving time ratio, i.e. if 2 this might imply out of a total 60us move, the static part takes up
	// 40us and the moving part takes up 20us.
	double staticMovingRatio=1;
	bool outputInfo = false;
	bool outputIndv = false;
	bool preprogram = false;
	bool useCalibration = false;
	smartRearrangementOptions smartOption = full;
};


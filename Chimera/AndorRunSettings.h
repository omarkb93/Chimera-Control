#pragma once
#include "imageParameters.h"
#include <string>
#include <vector>

// this structure contains all of the main options which are necessary to set when starting a camera acquisition. All
// of these settings should be possibly modified by the user of the UI.
struct AndorRunSettings
{
	imageParameters imageSettings;
	//
	bool emGainModeIsOn;
	int emGainLevel;
	int readMode;
	int acquisitionMode;
	int frameTransferMode;
	std::string triggerMode;
	std::string cameraMode;
	bool showPicsInRealTime;
	//
	float kineticCycleTime;
	float accumulationTime;
	int accumulationNumber;
	std::vector<float> exposureTimes;
	//
	UINT picsPerRepetition;
	ULONGLONG repetitionsPerVariation;
	ULONGLONG totalVariations;
	ULONGLONG totalPicsInVariation;
	// this is an int to reflect that the final number that's programmed to the camera is an int
	int totalPicsInExperiment;
	int temperatureSetting;
};


/*
	- Includes AndorRunSettings, which are the settings that the camera itself cares about.
	- Also some auxiliary settings which are never directly programmed to the camera, but are key for the way the 
	camera is used in the code.
*/
struct AndorCameraSettings
{
	AndorRunSettings andor;
	// not directly programmed to camera
	std::array<int, 4> thresholds;
	std::array<int, 4> palleteNumbers;
};


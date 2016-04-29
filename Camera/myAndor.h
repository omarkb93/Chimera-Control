#pragma once
#include <string>

namespace myAndor
{
	int setSystem(void);
	BOOL acquireImageData(void);

	int setAcquisitionMode(void);
	int setReadMode(void);
	int setTemperature(void);
	int setExposures(void);
	int setImageParameters(void);
	int setKineticCycleTime(void);
	int setScanNumber(void);
	int setFrameTransferMode(int mode);
	int checkAcquisitionTimings();
	int getStatus();
	int startAcquisition();
	int setAccumulationCycleTime();
	int setNumberAccumulations();
	
	int setTriggerMode();
	int setGainMode();

	void drawDataWindow(void);
	int writeFits(std::string fileName);

	void switchCoolerOn(void);
	void switchCoolerOff(void);

	std::string andorErrorChecker(int errorCode);
}
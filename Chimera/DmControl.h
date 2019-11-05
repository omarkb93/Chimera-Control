#pragma once
#include "Control.h"
#include "myButton.h"
#include "VisaFlume.h"
#include "Version.h"
#include "DmCore.h"

struct DmInfo
{
	// add any other settings for the whole machine here. 
	std::string serialNumber;
	int ActuatorCount;
};

struct pistonInfo {
	int Value;
};

struct pistonButton {
		
		Control<CEdit> Voltage;
};

class DmControl
{
	public:
	DmControl::DmControl(std::string serialNumber, bool safeMode);
		void initialize(POINT loc, CWnd* parent, int count, std::string serialNumber, LONG width, UINT control_id);
	    void handleOnPress(int i);
		void programNow();
		void setMirror(std::vector<double> A);
		void updateButtons();
		int getActNum();
		HBRUSH handleColorMessage(CWnd* window, CDC* cDC);
		//void rearrange(int cx, int cy);

	private:
		
		DmInfo currentInfo;
		DmCore defObject;
		std::vector<pistonButton> piston;
		//Control<CleanButton> programNow;
		Control<CStatic> onOffLabel;
		std::vector<double> temp;
};
﻿#pragma once
#include "Control.h"
#include "windows.h"
#include "afxwin.h"
#include "nidaqmx2.h"
#include <array>
#include "DaqMxFlume.h"
#include "constants.h"


/*
 * This is a interface for taking analog input data through an NI card that uses DAQmx. These cards are generally 
 * somewhat flexible, but right now I only use it to read and record voltage values from Analog inputs.
 */
class AiSystem
{
	public:
		AiSystem( );
		void initDaqmx( );
		void initialize( POINT& loc, CWnd* parent, int& id );
		void refreshDisplays( );
		void rearrange( int width, int height, fontMap fonts );
		void refreshCurrentValues( );
		std::array<float64, NUMBER_AI_CHANNELS> getSingleSnapArray( UINT n_to_avg );
		std::vector<float64> getSingleSnap( UINT n_to_avg );
		void armAquisition( UINT numSnapshots );
		void getAquisitionData( );
		std::vector<float64> getCurrentValues( );
		bool wantsQueryBetweenVariations( );
		bool wantsContinuousQuery( );
		std::string getSystemStatus( );
	private:
		Control<CStatic> title;
		std::array<Control<CStatic>, NUMBER_AI_CHANNELS> dacLabels;
		std::array<Control<CStatic>, NUMBER_AI_CHANNELS> voltDisplays;
		Control<CButton> getValuesButton;
		Control<CButton> continuousQueryCheck;
		Control<CButton> queryBetweenVariations;
		// float64 should just be a double type.
		std::array<float64, NUMBER_AI_CHANNELS> currentValues;
		std::vector<float64> aquisitionData;
		TaskHandle analogInTask0 = NULL;
		DaqMxFlume daqmx;
};



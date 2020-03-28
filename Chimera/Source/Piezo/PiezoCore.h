﻿#pragma once

#include "PiezoFlume.h"
#include "SerialPiezoFlume.h"
#include "ParameterSystem/Expression.h"
#include "ConfigurationSystems/Version.h"
#include "ConfigurationSystems/ConfigStream.h"
#include "Scripts/ScriptStream.h"

/* a simple wrapper for parameters for which there is one value for each channel, e.g. a double or an expression.*/
template <typename type> struct piezoChan
{
	type x;
	type y;
	type z;
};

class PiezoCore
{
	public:
		// THIS CLASS IS NOT COPYABLE.
		PiezoCore& operator=(const PiezoCore&) = delete;
		PiezoCore(const PiezoCore&) = delete;

		PiezoCore (piezoSetupInfo info);
		void initialize (  );
		std::string getDeviceInfo ( );
		std::string getDeviceList ( );
		void exprProgramPiezo ( UINT variationNumber );
		static std::pair<piezoChan<std::string>, bool> getSettingsFromConfig (ConfigStream& file, Version ver );
		void programAll ( piezoChan<double> vals );
		void setCtrl ( bool ctrl );
		bool wantsCtrl ( );
		double getCurrentXVolt ( );
		void programXNow ( double val );
		double getCurrentYVolt ( );
		void programYNow ( double val );
		double getCurrentZVolt ( );
		void programZNow ( double val );
		void updateExprVals ( piezoChan<Expression> newVals );
		void evaluateVariations ( std::vector<parameterType>& params, UINT totalVariations );
		const std::string configDelim;
	private:
		const PiezoType controllerType;
		bool ctrlOption;
		PiezoFlume flume;
		SerialPiezoFlume serFlume;
		piezoChan<Expression> experimentVals;
};


#pragma once
#include "RsgFlume.h"
#include "ConfigurationSystems/Version.h"
#include "Microwave/WindFreakFlume.h"
#include "Microwave/microwaveSettings.h"
#include "LowLevel/constants.h"

class MicrowaveCore
{
	public:
		MicrowaveCore ();
		std::string queryIdentity ();
		void setFmSettings ();
		void setPmSettings ();
		void programRsg (UINT variationNumber, microwaveSettings settings);
		void interpretKey (std::vector<parameterType>& params, microwaveSettings& settings);
		std::pair<DoRows::which, UINT> getRsgTriggerLine ();
		UINT getNumTriggers (UINT variationNumber, microwaveSettings settings);
		static microwaveSettings getSettingsFromConfig (ConfigStream& openFile, Version ver);
	private:
		const double triggerTime = 0.01;
		const std::pair<DoRows::which, UINT> rsgTriggerLine = { DoRows::which::C, 3 };
		MICROWAVE_FLUME uwFlume;
};
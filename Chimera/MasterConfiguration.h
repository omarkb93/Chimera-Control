#pragma once
#include <string>
#include <array>
#include "TtlSystem.h"
#include "DacSystem.h"

// This configuration system is different in style from the other configuration file system. This is designed to do more auto-saving and 
// auto-load at the beginning of the experiment. There is only supposed to be one such configuration file
class MasterConfiguration
{
	public:
		MasterConfiguration(std::string address);
		//void save(TtlSystem* ttls, DacSystem* dacs, VariableSystem* gloablVars );
		void save(MainWindow* mainWin, DeviceWindow* deviceWin, CameraWindow* camWin);
		//void load(TtlSystem* ttls, DacSystem& dacs, cToolTips& toolTips,
		//		  DeviceWindow* master, VariableSystem* globalVars);
		void load(MainWindow* mainWin, DeviceWindow* deviceWin, CameraWindow* camWin);
		void updateDefaultTTLs(TtlSystem ttls);
		void updateDefaultDacs(DacSystem dacs);
	private:
		//std::array<std::array<bool, 16>, 4> defaultTtls;
		//std::array<int, 24> defaultDacs;
		const std::string configurationFileAddress;
		const std::string version;
};


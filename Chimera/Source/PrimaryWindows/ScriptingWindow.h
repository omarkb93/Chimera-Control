// created by Mark O. Brown
#pragma once

#include "stdafx.h"
#include "Scripts/Script.h"
#include "ExperimentMonitoringAndStatus/ColorBox.h"
#include "ConfigurationSystems/ProfileIndicator.h"
#include "ConfigurationSystems/profileSettings.h"
#include "ExperimentThread/Communicator.h"
#include "Agilent/Agilent.h"
#include "ExperimentThread/MasterThreadInput.h"

class MainWindow;
class AndorWindow;
class AuxiliaryWindow;
class BaslerWindow;

// a convenient structure for containing one object for each script. For example, the address of each script.
template <typename type> struct scriptInfo
{
	type niawg;
	type intensityAgilent;
	type master;
};


class ScriptingWindow : public CDialog
{
	using CDialog::CDialog;
	DECLARE_DYNAMIC(ScriptingWindow);

	public:
		ScriptingWindow();
		void OnRButtonUp( UINT stuff, CPoint clickLocation );
		void OnLButtonUp( UINT stuff, CPoint clickLocation );

		HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
		
		BOOL OnInitDialog() override;
		void OnTimer(UINT_PTR eventID);

		void passCommonCommand(UINT id);

		void checkScriptSaves();
		void loadFriends(MainWindow* mainWin_, AndorWindow* camWin_, AuxiliaryWindow* auxWin_, BaslerWindow* basWin_);
		void fillMasterThreadInput(ExperimentThreadInput* input);
		BOOL OnToolTipText( UINT, NMHDR* pNMHDR, LRESULT* pResult );

		scriptInfo<std::string> getScriptNames();
		scriptInfo<bool> getScriptSavedStatuses();
		scriptInfo<std::string> getScriptAddresses();

		profileSettings getProfileSettings();
		std::string getSystemStatusString();
		BOOL PreTranslateMessage(MSG* pMsg);

		void checkMasterSave();

		void handleNewConfig( std::ofstream& saveFile );
		void handleSavingConfig(std::ofstream& saveFile);

		void updateScriptNamesOnScreen();
		void updateProfile(std::string text);
		void considerScriptLocations();
		void recolorScripts();

		void newIntensityScript();
		void openIntensityScript(CWnd* parent);
		void openIntensityScript(std::string name);
		void saveIntensityScript();
		void saveIntensityScriptAs(CWnd* parent);
		void agilentEditChange();

		void newNiawgScript();
		void openNiawgScript(CWnd* parent);
		void openNiawgScript(std::string name);
		void saveNiawgScript();
		void saveNiawgScriptAs(CWnd* parent);
		void niawgEditChange();

		void newMasterScript();
		void openMasterScript(CWnd* parent);
		void openMasterScript(std::string name);
		void saveMasterScript();
		void saveMasterScriptAs(CWnd* parent);
		void newMasterFunction();
		void saveMasterFunction();
		void deleteMasterFunction();
		void masterEditChange();
		Communicator* comm();
		//void openMasterScript(std::string name);

		void changeBoxColor( systemInfo<char> colors );
		void updateConfigurationSavedStatus(bool status);
		void OnCancel() override;
		void OnSize(UINT nType, int cx, int cy);

		void handleIntensityButtons( UINT id );
		void handleNiawgScriptComboChange();
		void handleAgilentScriptComboChange();
		void handleMasterFunctionChange( );
		void handleIntensityCombo();
		void handleOpenConfig(std::ifstream& configFile, Version ver );
		void catchEnter();
		profileSettings getProfile();
		void setIntensityDefault();
		void setMenuCheck ( UINT menuItem, UINT itemState );
	private:
		DECLARE_MESSAGE_MAP();
		
		MainWindow* mainWin;
		AndorWindow* camWin;
		AuxiliaryWindow* auxWin;
		BaslerWindow* basWin;
		//
		cToolTips tooltips;
		Script niawgScript, masterScript;
		ColorBox statusBox;
		ProfileIndicator profileDisplay;
		CMenu menu;
		Agilent intensityAgilent;
};
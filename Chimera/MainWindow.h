#pragma once
#include "stdafx.h"
#include "ProfileSystem.h"
#include "DebuggingOptionsControl.h"
#include "MainOptionsControl.h"
#include "StatusControl.h"
#include "StatusIndicator.h"
#include "Communicator.h"
#include "SMSTextingControl.h"
#include "NiawgController.h"
#include "EmbeddedPythonHandler.h"
#include "MasterConfiguration.h"
#include "Repetitions.h"
#include "MasterManager.h"
#include "commonFunctions.h"
#include "DataLogger.h"

class ScriptingWindow;
class CameraWindow;
class AuxiliaryWindow;

class MainWindow : public CDialog
{
	using CDialog::CDialog;
	DECLARE_DYNAMIC(MainWindow);
	public:
	    // overrides
		MainWindow(UINT id, CDialog*);
		BOOL OnInitDialog() override;
		HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
		BOOL PreTranslateMessage(MSG* pMsg); 
		void OnSize(UINT nType, int cx, int cy);
		void OnClose();
		void OnCancel() override;
		// stuff directly called (or 1 simple step removed) by message map.
		LRESULT onRepProgress(WPARAM wParam, LPARAM lParam);
		LRESULT onStatusTextMessage(WPARAM wParam, LPARAM lParam);
		LRESULT onErrorMessage(WPARAM wParam, LPARAM lParam);
		LRESULT onFatalErrorMessage(WPARAM wParam, LPARAM lParam);
		LRESULT onNormalFinishMessage(WPARAM wParam, LPARAM lParam);
		LRESULT onColoredEditMessage(WPARAM wParam, LPARAM lParam);
		LRESULT onDebugMessage(WPARAM wParam, LPARAM lParam);		
		//
		void passCommonCommand( UINT id );
		void handlePause();
		void passDebugPress( UINT id );
		void passMainOptionsPress( UINT id );
		void handleDblClick( NMHDR * pNotifyStruct, LRESULT * result );
		void handleRClick( NMHDR * pNotifyStruct, LRESULT * result );
		void handleExperimentCombo();
		void handleCategoryCombo();
		void handleConfigurationCombo();
		void handleSequenceCombo();
		void handleOrientationCombo();
		void passClear( UINT id );

		// auxiliary functions used by the window.
		void setNotes(std::string whichLevel, std::string notes);
		void setNiawgDefaults();
		void fillMasterThreadInput( MasterThreadInput* input );
		void startMaster( MasterThreadInput* input );
		std::string getNotes(std::string whichLevel);
		brushMap getBrushes();
		rgbMap getRgbs();
		fontMap getFonts();
		profileSettings getProfileSettings();
		debugInfo getDebuggingOptions();
		mainOptions getMainOptions();

		void checkProfileReady();
		void checkProfileSave();
		void setOrientation(std::string orientation);
		void updateConfigurationSavedStatus(bool status);

		void setDebuggingOptions(debugInfo options);
		void updateStatusText(std::string whichStatus, std::string text);
		void addTimebar(std::string whichStatus);
		void setShortStatus(std::string text);
		void changeShortStatusColor(std::string color);
		void restartNiawgDefaults();
		void stopNiawg();
		void changeBoxColor(systemInfo<char> colors);
		void handleSaveConfig(std::ofstream& saveFile);
		void handleOpeningConfig(std::ifstream& configFile, double version);
		void abortMasterThread();
		Communicator* getComm();
		std::string getSystemStatusString();

		bool niawgIsRunning();
		bool masterIsRunning();
		void setNiawgRunningState( bool newRunningState );
		RunInfo getRunInfo();
		void handleFinish();
		UINT getRepNumber();
		void logParams( DataLogger* logger, MasterThreadInput* input );

	private:		
		DECLARE_MESSAGE_MAP();
		ScriptingWindow* TheScriptingWindow;
		CameraWindow* TheCameraWindow;
		AuxiliaryWindow* TheAuxiliaryWindow;
		// members that have gui elements
		ProfileSystem profile;
		MasterConfiguration masterConfig;
		NoteSystem notes;
		DebuggingOptionsControl debugger;
		Repetitions repetitionControl;
		MainOptionsControl settings;
		StatusControl mainStatus;
		StatusControl debugStatus;
		StatusControl errorStatus;
		SmsTextingControl texter;
		StatusIndicator shortStatus;
		NiawgController niawg;
		ColorBox boxes;
		// auxiliary members
		Communicator comm;
		brushMap mainBrushes;
		rgbMap mainRGBs;
		fontMap mainFonts;
		MasterManager masterThreadManager;
		CMenu menu;
		RunInfo systemRunningInfo;
		cToolTips tooltips;
		EmbeddedPythonHandler python;
		// friends (try to minimize these)
		friend void commonFunctions::handleCommonMessage( int msgID, CWnd* parent, MainWindow* mainWin,
														  ScriptingWindow* scriptWin, CameraWindow* camWin,
														  AuxiliaryWindow* masterWin );
		CDialog* appSplash;
};

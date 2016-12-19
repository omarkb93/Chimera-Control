#include "stdafx.h"
#include "MainWindow.h"
#include "initializeMainWindow.h"
#include "commonMessages.h"
#include "myAgilent.h"
#include "myNIAWG.h"

IMPLEMENT_DYNAMIC(MainWindow, CDialog)

BEGIN_MESSAGE_MAP(MainWindow, CDialog)
	ON_WM_CTLCOLOR()
	ON_COMMAND_RANGE(ID_ACCELERATOR_ESC, ID_ACCELERATOR_ESC, &MainWindow::passCommonCommand)
	ON_COMMAND_RANGE(ID_ACCELERATOR_F5, ID_ACCELERATOR_F5, &MainWindow::passCommonCommand)
	ON_COMMAND_RANGE(MENU_ID_RANGE_BEGIN, MENU_ID_RANGE_END, &MainWindow::passCommonCommand)
	ON_COMMAND_RANGE(IDC_DEBUG_OPTIONS_RANGE_BEGIN, IDC_DEBUG_OPTIONS_RANGE_END, &MainWindow::passDebugPress)
	ON_COMMAND_RANGE(IDC_MAIN_OPTIONS_RANGE_BEGIN, IDC_MAIN_OPTIONS_RANGE_END, &MainWindow::passMainOptionsPress)
	// 


	ON_CBN_SELENDOK(IDC_EXPERIMENT_COMBO, &MainWindow::handleExperimentCombo)
	ON_CBN_SELENDOK(IDC_CATEGORY_COMBO, &MainWindow::handleCategoryCombo)
	ON_CBN_SELENDOK(IDC_CONFIGURATION_COMBO, &MainWindow::handleConfigurationCombo)
	ON_CBN_SELENDOK(IDC_SEQUENCE_COMBO, &MainWindow::handleSequenceCombo)
	ON_CBN_SELENDOK(IDC_ORIENTATION_COMBO, &MainWindow::handleOrientationCombo)
	// 
	ON_NOTIFY(NM_DBLCLK, IDC_VARIABLES_LISTVIEW, &MainWindow::listViewDblClick)
	ON_NOTIFY(NM_RCLICK, IDC_VARIABLES_LISTVIEW, &MainWindow::listViewRClick)
	ON_REGISTERED_MESSAGE(eGreenMessageID, &MainWindow::onGreenMessage)
	ON_REGISTERED_MESSAGE(eStatusTextMessageID, &MainWindow::onStatusTextMessage)
	ON_REGISTERED_MESSAGE(eErrorTextMessageID, &MainWindow::onErrorMessage)
	ON_REGISTERED_MESSAGE(eFatalErrorMessageID, &MainWindow::onFatalErrorMessage)
	ON_REGISTERED_MESSAGE(eVariableStatusMessageID, &MainWindow::onVariableStatusMessage)
	ON_REGISTERED_MESSAGE(eNormalFinishMessageID, &MainWindow::onNormalFinishMessage)
	ON_REGISTERED_MESSAGE(eColoredEditMessageID, &MainWindow::onColoredEditMessage)
	ON_REGISTERED_MESSAGE(eDebugMessageID, &MainWindow::onDebugMessage)
	ON_COMMAND(ID_FILE_MY_RUN, &MainWindow::OnFileMyRun)

	ON_COMMAND_RANGE(IDC_MAIN_STATUS_BUTTON, IDC_MAIN_STATUS_BUTTON, &MainWindow::passClear)
	ON_COMMAND_RANGE(IDC_ERROR_STATUS_BUTTON, IDC_ERROR_STATUS_BUTTON, &MainWindow::passClear)
	ON_COMMAND_RANGE(IDC_DEBUG_STATUS_BUTTON, IDC_DEBUG_STATUS_BUTTON, &MainWindow::passClear)
END_MESSAGE_MAP()

void MainWindow::passClear(UINT id)
{
	if (id == IDC_MAIN_STATUS_BUTTON)
	{
		this->mainStatus.clear();
	}
	else if (id == IDC_ERROR_STATUS_BUTTON)
	{
		this->errorStatus.clear();
	}
	else if (id == IDC_DEBUG_STATUS_BUTTON)
	{
		this->debugStatus.clear();
	}
	return;
}

void MainWindow::OnCancel()
{
	passCommonCommand(ID_FILE_MY_EXIT);
	return;
}
void MainWindow::OnClose()
{
	passCommonCommand(WM_CLOSE);
	return;
}
void MainWindow::OnDestroy()
{
	errBox("HI");
	return;
}
BOOL MainWindow::OnInitDialog()
{
	this->theScriptingWindow = new ScriptingWindow;
	theScriptingWindow->getFriends(this);
	theScriptingWindow->Create(IDD_LARGE_TEMPLATE, 0);
	//m_pMainWnd = &ScriptWin;
	theScriptingWindow->ShowWindow(SW_SHOW);
	/// PROFILE DATA
	int id = 1000;
	POINT statusPosition = { 0,0 };
	this->mainStatus.initialize(statusPosition, this, id, 975, "EXPERIMENT STATUS", RGB(50, 50, 250));
	statusPosition = { 480, 0 };
	this->errorStatus.initialize(statusPosition, this, id, 480, "ERROR STATUS", RGB(200, 0, 0)); 
	this->debugStatus.initialize(statusPosition, this, id, 480, "DEBUG STATUS", RGB(13, 152, 186));
	POINT configStart = { 960, 0 };
	this->profile.initializeControls(configStart, this, id);
	POINT notesStart = { 960, 235 };
	this->notes.initializeControls(notesStart, this, id);
	POINT controlLocation = { 1440, 95 };
	this->variables.initializeControls(controlLocation, this, id);
	this->settings.initialize(id, controlLocation, this);
	this->debugger.initialize(id, controlLocation, this);
	POINT shortStatusLocation = { 960, 910 };
	this->shortStatus.initialize(shortStatusLocation, this, id);
	//initializeMainWindow(*this);
	CMenu menu;
	menu.LoadMenu(IDR_MAIN_MENU);
	this->SetMenu(&menu);
	this->ShowWindow(SW_MAXIMIZE);
	return TRUE;
}

HBRUSH MainWindow::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	switch (nCtlColor)
	{
		case CTLCOLOR_STATIC:
		{
			HBRUSH ret = this->shortStatus.handleColor(pWnd, pDC, this->mainRGBs, this->mainBrushes);
			if (ret)
			{
				return ret;
			}
			else
			{
				pDC->SetTextColor(mainRGBs["White"]);
				pDC->SetBkColor(mainRGBs["Medium Grey"]);
				return mainBrushes["Medium Grey"];
			}
		}
		case CTLCOLOR_EDIT:
		{
			pDC->SetTextColor(mainRGBs["White"]);
			pDC->SetBkColor(mainRGBs["Dark Blue"]);
			return mainBrushes["Dark Blue"];
		}
		case CTLCOLOR_LISTBOX:
		{
			pDC->SetTextColor(mainRGBs["White"]);
			pDC->SetBkColor(mainRGBs["Dark Grey"]);
			return mainBrushes["Dark Grey"];
		}
		default:
		{
			return mainBrushes["Light Grey"];
		}
	}
	return NULL;
}

void MainWindow::passCommonCommand(UINT id)
{
	// pass the command id to the common function, filling in the pointers to the windows which own objects needed.
	commonMessages::handleCommonMessage(id, this, this, this->theScriptingWindow);
	return;
}

profileSettings MainWindow::getCurentProfileSettings()
{
	return this->profile.getCurrentProfileSettings();
}

bool MainWindow::checkProfileReady()
{
	return this->profile.allSettingsReadyCheck(this->theScriptingWindow, this);
}

bool MainWindow::checkProfileSave()
{
	return this->profile.checkSaveEntireProfile(this->theScriptingWindow, this);
}

bool MainWindow::setOrientation(std::string orientation)
{
	return this->profile.setOrientation(orientation);
}

void MainWindow::updateConfigurationSavedStatus(bool status)
{
	this->profile.updateConfigurationSavedStatus(status);
	return;
}

std::string MainWindow::getNotes(std::string whichLevel)
{
	std::transform(whichLevel.begin(), whichLevel.end(), whichLevel.begin(), ::tolower);
	if (whichLevel == "experiment")
	{
		return this->notes.getExperimentNotes();
	}
	else if (whichLevel == "category")
	{
		return this->notes.getCategoryNotes();
	}
	else if (whichLevel == "configuration")
	{
		return this->notes.getConfigurationNotes();
	}
	else
	{
		throw std::invalid_argument(("The Main window's getNotes function was called with a bad argument:" 
			+ whichLevel + ". Acceptable arguments are \"experiment\", \"category\", and \"configuration\". "
			"This throw can be continued successfully, the notes will just be recorded.").c_str());
	}
	return "";
}
void MainWindow::setNotes(std::string whichLevel, std::string notes)
{
	std::transform(whichLevel.begin(), whichLevel.end(), whichLevel.begin(), ::tolower);
	if (whichLevel == "experiment")
	{
		this->notes.setExperimentNotes(notes);
	}
	else if (whichLevel == "category")
	{
		this->notes.setCategoryNotes(notes);
	}
	else if (whichLevel == "configuration")
	{
		this->notes.setConfigurationNotes(notes);
	}
	else
	{
		throw std::invalid_argument(("The Main window's setNotes function was called with a bad argument:"
			+ whichLevel + ". Acceptable arguments are \"experiment\", \"category\", and \"configuration\". "
			"This throw can be continued successfully, the notes will just not load.").c_str());
	}
	return;
}

std::vector<variable> MainWindow::getAllVariables()
{
	return this->variables.getAllVariables();
}

void MainWindow::clearVariables()
{
	this->variables.clearVariables();
	return;
}

void MainWindow::addVariable(std::string name, bool timelike, bool singleton, double value, int item)
{
	this->variables.addVariable(name, timelike, singleton, value, item);
	return;
}

debugOptions MainWindow::getDebuggingOptions()
{
	return this->debugger.getOptions();
}

void MainWindow::setDebuggingOptions(debugOptions options)
{
	this->debugger.setOptions(options);
	return;
}

mainOptions MainWindow::getMainOptions()
{
	return this->settings.getOptions();
}

void MainWindow::updateStatusText(std::string whichStatus, std::string text)
{
	std::transform(whichStatus.begin(), whichStatus.end(), whichStatus.begin(), ::tolower);
	if (whichStatus == "error")
	{
		this->errorStatus.addStatusText(text);
	}
	else if (whichStatus == "debug")
	{
		this->debugStatus.addStatusText(text);
	}
	else if (whichStatus == "main")
	{
		this->mainStatus.addStatusText(text);
	}
	else
	{
		throw std::invalid_argument("Main Window's updateStatusText function recieved a bad argument for which status"
			" control to update. Options are \"error\", \"debug\", and \"main\", but recieved " + whichStatus + ". This"
			"exception can be safely ignored.");
	}
	return;
}

void MainWindow::addTimebar(std::string whichStatus)
{
	std::transform(whichStatus.begin(), whichStatus.end(), whichStatus.begin(), ::tolower);
	if (whichStatus == "error")
	{
		this->errorStatus.appendTimebar();
	}
	else if (whichStatus == "debug")
	{
		this->debugStatus.appendTimebar();
	}
	else if (whichStatus == "main")
	{
		this->mainStatus.appendTimebar();
	}
	else
	{
		throw std::invalid_argument("Main Window's addTimebar function recieved a bad argument for which status"
			" control to update. Options are \"error\", \"debug\", and \"main\", but recieved " + whichStatus + ". This"
			"exception can be safely ignored.");
	}
	return;
	return;
}

void MainWindow::setShortStatus(std::string text)
{
	this->shortStatus.setText(text);
	return;
}

void MainWindow::changeShortStatusColor(std::string color)
{
	this->shortStatus.setColor(color);
	return;
}

void MainWindow::passDebugPress(UINT id)
{
	this->debugger.handleEvent(id, this);
	return;
}

void MainWindow::passMainOptionsPress(UINT id)
{
	this->settings.handleEvent(id, this);
	return;
}

void MainWindow::listViewDblClick(NMHDR * pNotifyStruct, LRESULT * result)
{
	variables.updateVariableInfo(this, this->theScriptingWindow);
	this->profile.updateConfigurationSavedStatus(false);
	return;
}
void MainWindow::listViewRClick(NMHDR * pNotifyStruct, LRESULT * result)
{
	variables.deleteVariable();
	this->profile.updateConfigurationSavedStatus(false);
	return;
}

void MainWindow::handleExperimentCombo()
{
	this->profile.experimentChangeHandler(this->theScriptingWindow, this);
	return;
}
void MainWindow::handleCategoryCombo()
{
	this->profile.categoryChangeHandler(this->theScriptingWindow, this);
}
void MainWindow::handleConfigurationCombo()
{
	this->profile.configurationChangeHandler(this->theScriptingWindow, this);
}
void MainWindow::handleSequenceCombo()
{
	this->profile.sequenceChangeHandler();
}
void MainWindow::handleOrientationCombo()
{
	this->profile.orientationChangeHandler(this);
}

void MainWindow::setMainOptions(mainOptions options)
{
	this->settings.setOptions(options);
	return;
}

LRESULT MainWindow::onGreenMessage(WPARAM wParam, LPARAM lParam)
{
	this->theScriptingWindow->changeBoxColor("G");
	this->changeShortStatusColor("G");
	return 0;
}

LRESULT MainWindow::onStatusTextMessage(WPARAM wParam, LPARAM lParam)
{
	char* pointerToMessage = (char*)lParam;
	std::string statusMessage(pointerToMessage);
	delete[] pointerToMessage;
	this->mainStatus.addStatusText(statusMessage);
	return 0;
}

LRESULT MainWindow::onErrorMessage(WPARAM wParam, LPARAM lParam)
{
	char* pointerToMessage = (char*)lParam;
	std::string statusMessage(pointerToMessage);
	delete[] pointerToMessage;
	this->errorStatus.addStatusText(statusMessage);
	return 0;
}

LRESULT MainWindow::onFatalErrorMessage(WPARAM wParam, LPARAM lParam)
{
	myAgilent::agilentDefault();
	std::string msgText = "Exited with Error!\r\nPassively Outputting Default Waveform.";
	this->changeShortStatusColor("R");
	this->theScriptingWindow->changeBoxColor("R");
	this->setShortStatus(msgText);
	std::string orientation = this->getCurentProfileSettings().orientation;
	if (!TWEEZER_COMPUTER_SAFEMODE)
	{
		if (myNIAWG::NIAWG_CheckWindowsError(niFgen_ConfigureOutputEnabled(eSessionHandle, SESSION_CHANNELS, VI_FALSE), orientation, this))
		{
			return 0;
		}
		// Officially stop trying to generate anything.
		if (myNIAWG::NIAWG_CheckWindowsError(niFgen_AbortGeneration(eSessionHandle), orientation, this))
		{
			return 0;
		}
		// clear the memory
		if (myNIAWG::NIAWG_CheckWindowsError(niFgen_ClearArbMemory(eSessionHandle), orientation, this))
		{
			return 0;
		}
	}
	ViInt32 waveID;
	//if (eProfile.getOrientation() == HORIZONTAL_ORIENTATION)
	if (false)
	{
		if (!TWEEZER_COMPUTER_SAFEMODE)
		{
			// create waveform (necessary?)
			if (myNIAWG::NIAWG_CheckWindowsError(niFgen_CreateWaveformF64(eSessionHandle, 
				SESSION_CHANNELS, eDefault_hConfigMixedSize, eDefault_hConfigMixedWaveform, &waveID), orientation, this))
			{
				return 0;
			}
			// allocate waveform into the device memory
			if (myNIAWG::NIAWG_CheckWindowsError(niFgen_AllocateNamedWaveform(eSessionHandle, 
				SESSION_CHANNELS, eDefault_hConfigWaveformName.c_str(), eDefault_hConfigMixedSize / 2), orientation, this))
			{
				return 0;
			}
			// write named waveform. on the device. Now the device knows what "waveform0" refers to when it sees it in the script.
			if (myNIAWG::NIAWG_CheckWindowsError(niFgen_WriteNamedWaveformF64(eSessionHandle, 
				SESSION_CHANNELS, eDefault_hConfigWaveformName.c_str(), eDefault_hConfigMixedSize, 
				eDefault_hConfigMixedWaveform), orientation, this))
			{
				return 0;
			}
			// rewrite the script. default_hConfigScript should still be valid.
			if (myNIAWG::NIAWG_CheckWindowsError(niFgen_WriteScript(eSessionHandle,
				SESSION_CHANNELS, eDefault_hConfigScript), orientation, this))
			{
				return 0;
			}
			// start generic waveform to maintain power output to AOM.
			if (myNIAWG::NIAWG_CheckWindowsError(niFgen_ConfigureOutputEnabled(eSessionHandle,
				SESSION_CHANNELS, VI_TRUE), orientation, this))
			{
				return 0;
			}
			if (myNIAWG::NIAWG_CheckWindowsError(niFgen_SetAttributeViString(eSessionHandle, 
				SESSION_CHANNELS, NIFGEN_ATTR_SCRIPT_TO_GENERATE, "DefaultHConfigScript"), orientation, this))
			{
				return 0;
			}
		}
		eCurrentScript = "DefaultHConfigScript";
	}
	else if (false)
		//else if (eProfile.getOrientation() == VERTICAL_ORIENTATION)
	{
		if (!TWEEZER_COMPUTER_SAFEMODE)
		{
			// create waveform (necessary?)
			if (myNIAWG::NIAWG_CheckWindowsError(niFgen_CreateWaveformF64(eSessionHandle, 
				SESSION_CHANNELS, eDefault_vConfigMixedSize, eDefault_vConfigMixedWaveform, &waveID), orientation, this))
			{
				return 0;
			}
			// allocate waveform into the device memory
			if (myNIAWG::NIAWG_CheckWindowsError(niFgen_AllocateNamedWaveform(eSessionHandle, 
				SESSION_CHANNELS, eDefault_vConfigWaveformName.c_str(), eDefault_vConfigMixedSize / 2), orientation, this))
			{
				return 0;
			}
			// write named waveform. on the device. Now the device knows what "waveform0" refers to when it sees it in the script.
			if (myNIAWG::NIAWG_CheckWindowsError(niFgen_WriteNamedWaveformF64(eSessionHandle, 
				SESSION_CHANNELS, eDefault_vConfigWaveformName.c_str(), eDefault_vConfigMixedSize, eDefault_vConfigMixedWaveform), orientation, this))
			{
				return 0;
			}
			// rewrite the script. default_hConfigScript should still be valid.
			if (myNIAWG::NIAWG_CheckWindowsError(niFgen_WriteScript(eSessionHandle, 
				SESSION_CHANNELS, eDefault_vConfigScript), orientation, this))
			{
				return 0;
			}
			// start generic waveform to maintain power output to AOM.
			if (myNIAWG::NIAWG_CheckWindowsError(niFgen_ConfigureOutputEnabled(eSessionHandle, 
				SESSION_CHANNELS, VI_TRUE), orientation, this))
			{
				return 0;
			}
			if (myNIAWG::NIAWG_CheckWindowsError(niFgen_SetAttributeViString(eSessionHandle, 
				SESSION_CHANNELS, NIFGEN_ATTR_SCRIPT_TO_GENERATE, "DefaultVConfigScript"), orientation, this))
			{
				return 0;
			}
		}
		eCurrentScript = "DefaultVConfigScript";
	}
	if (!TWEEZER_COMPUTER_SAFEMODE)
	{

		// Initiate Generation.
		if (myNIAWG::NIAWG_CheckWindowsError(niFgen_InitiateGeneration(eSessionHandle), orientation, this))
		{
			return 0;
		}
	}
	eExperimentIsRunning = false;
	return 0;
}

LRESULT MainWindow::onVariableStatusMessage(WPARAM wParam, LPARAM lParam)
{
	int currentOutput = (int)lParam;
	std::string msgText = "Outpitting Series #" + std::to_string(currentOutput) + ". \r\nWriting Varying Waveforms for Set # "
		+ std::to_string(currentOutput + 1) + "...\r\n";
	this->setShortStatus(msgText);
	this->changeShortStatusColor("Y");
	this->theScriptingWindow->changeBoxColor("Y");
	return 0;
}

LRESULT MainWindow::onNormalFinishMessage(WPARAM wParam, LPARAM lParam)
{
	myAgilent::agilentDefault();
	std::string msgText = "Passively Outputting Default Waveform";
	this->setShortStatus(msgText);
	this->changeShortStatusColor("B");
	this->theScriptingWindow->changeBoxColor("B");
	std::string orientation = this->getCurentProfileSettings().orientation;
	if (!TWEEZER_COMPUTER_SAFEMODE)
	{
		if (myNIAWG::NIAWG_CheckWindowsError(niFgen_ConfigureOutputEnabled(eSessionHandle, SESSION_CHANNELS, VI_FALSE), orientation, this))
		{
			return 0;
		}
		// Officially stop trying to generate anything.
		if (myNIAWG::NIAWG_CheckWindowsError(niFgen_AbortGeneration(eSessionHandle), orientation, this))
		{
			return 0;
		}
		// clear the memory
		if (myNIAWG::NIAWG_CheckWindowsError(niFgen_ClearArbMemory(eSessionHandle), orientation, this))
		{
			return 0;
		}
	}
	ViInt32 waveID;
	if (false)
		//				if (eProfile.getOrientation() == HORIZONTAL_ORIENTATION)
	{
		if (!TWEEZER_COMPUTER_SAFEMODE)
		{
			// create waveform (necessary?)
			if (myNIAWG::NIAWG_CheckWindowsError(niFgen_CreateWaveformF64(eSessionHandle, SESSION_CHANNELS, eDefault_hConfigMixedSize, eDefault_hConfigMixedWaveform, &waveID), orientation, this))
			{
				return 0;
			}
			// allocate waveform into the device memory
			if (myNIAWG::NIAWG_CheckWindowsError(niFgen_AllocateNamedWaveform(eSessionHandle, SESSION_CHANNELS, eDefault_hConfigWaveformName.c_str(), eDefault_hConfigMixedSize / 2), orientation, this))
			{
				return 0;
			}
			// write named waveform. on the device. Now the device knows what "waveform0" refers to when it sees it in the script.
			if (myNIAWG::NIAWG_CheckWindowsError(niFgen_WriteNamedWaveformF64(eSessionHandle, SESSION_CHANNELS, eDefault_hConfigWaveformName.c_str(), eDefault_hConfigMixedSize, eDefault_hConfigMixedWaveform), orientation, this))
			{
				return 0;
			}
			// rewrite the script. default_hConfigScript should still be valid.
			if (myNIAWG::NIAWG_CheckWindowsError(niFgen_WriteScript(eSessionHandle, SESSION_CHANNELS, eDefault_hConfigScript), orientation, this))
			{
				return 0;
			}
			// start generic waveform to maintain power output to AOM.
			if (myNIAWG::NIAWG_CheckWindowsError(niFgen_ConfigureOutputEnabled(eSessionHandle, SESSION_CHANNELS, VI_TRUE), orientation, this))
			{
				return 0;
			}
			if (myNIAWG::NIAWG_CheckWindowsError(niFgen_SetAttributeViString(eSessionHandle, SESSION_CHANNELS, NIFGEN_ATTR_SCRIPT_TO_GENERATE, "DefaultHConfigScript"), orientation, this))
			{
				return 0;
			}
		}
		eCurrentScript = "DefaultHConfigScript";

	}
	else if (false)
		//else if (eProfile.getOrientation() == VERTICAL_ORIENTATION)
	{
		if (!TWEEZER_COMPUTER_SAFEMODE)
		{
			// create waveform (necessary?)
			if (myNIAWG::NIAWG_CheckWindowsError(niFgen_CreateWaveformF64(eSessionHandle, SESSION_CHANNELS, eDefault_vConfigMixedSize, eDefault_vConfigMixedWaveform, &waveID), orientation, this))
			{
				return 0;
			}
			// allocate waveform into the device memory
			if (myNIAWG::NIAWG_CheckWindowsError(niFgen_AllocateNamedWaveform(eSessionHandle, SESSION_CHANNELS, eDefault_vConfigWaveformName.c_str(), eDefault_vConfigMixedSize / 2), orientation, this))
			{
				return 0;
			}
			// write named waveform. on the device. Now the device knows what "waveform0" refers to when it sees it in the script.
			if (myNIAWG::NIAWG_CheckWindowsError(niFgen_WriteNamedWaveformF64(eSessionHandle, SESSION_CHANNELS, eDefault_vConfigWaveformName.c_str(), eDefault_vConfigMixedSize, eDefault_vConfigMixedWaveform), orientation, this))
			{
				return 0;
			}
			// rewrite the script. default_hConfigScript should still be valid.
			if (myNIAWG::NIAWG_CheckWindowsError(niFgen_WriteScript(eSessionHandle, SESSION_CHANNELS, eDefault_vConfigScript), orientation, this))
			{
				return 0;
			}
			// start generic waveform to maintain power output to AOM.
			if (myNIAWG::NIAWG_CheckWindowsError(niFgen_ConfigureOutputEnabled(eSessionHandle, SESSION_CHANNELS, VI_TRUE), orientation, this))
			{
				return 0;
			}

			if (myNIAWG::NIAWG_CheckWindowsError(niFgen_SetAttributeViString(eSessionHandle, SESSION_CHANNELS, NIFGEN_ATTR_SCRIPT_TO_GENERATE, "DefaultVConfigScript"), orientation, this))
			{
				return 0;
			}
		}
		eCurrentScript = "DefaultVConfigScript";
	}
	if (!TWEEZER_COMPUTER_SAFEMODE)
	{
		// Initiate Generation.
		if (myNIAWG::NIAWG_CheckWindowsError(niFgen_InitiateGeneration(eSessionHandle), orientation, this))
		{
			return 0;
		}
	}
	eExperimentIsRunning = false;
	return 0;
}

LRESULT MainWindow::onColoredEditMessage(WPARAM wParam, LPARAM lParam)
{
	char* pointerToMessage = (char*)lParam;
	std::string statusMessage(pointerToMessage);
	delete[] pointerToMessage;
	this->setShortStatus(statusMessage);
	return 0;
}

LRESULT MainWindow::onDebugMessage(WPARAM wParam, LPARAM lParam)
{
	char* pointerToMessage = (char*)lParam;
	std::string statusMessage(pointerToMessage);
	delete[] pointerToMessage;
	this->debugStatus.addStatusText(statusMessage);
	return 0;
}


void MainWindow::OnFileMyRun()
{
	// TODO: Add your command handler code here
	errBox("WTF");
}

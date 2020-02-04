//Created by Max Kolanz
#include "stdafx.h"
#include "AuxiliaryWindow2.h"
#include "MainWindow.h"
#include "commonFunctions.h"
#include "openWithExplorer.h"
#include "saveWithExplorer.h"
#include "ProfileSystem.h"

AuxiliaryWindow2::AuxiliaryWindow2() : CDialog(), DM(DM_SERIAL, DM_SAFEMODE), globalParameters("GLOBAL_PARAMETERS"),
                                       configParameters("CONFIG_PARAMETERS"){
	
}

BOOL AuxiliaryWindow2::OnInitDialog() {
	POINT pos = { 0,0 };
	POINT controlLocation = { 798, 85 };
	int id = 1000;
	UINT ID = IDC_DM_PROGRAMNOW;
	statusBox.initialize(pos, id, this, 480, toolTips);
	DM.initialize(controlLocation, this, DM.getActNum(), DM_SERIAL, 65, ID);

	return TRUE;
}


void AuxiliaryWindow2::loadFriends(MainWindow* mainWin_, ScriptingWindow* scriptWin_, AndorWindow* camWin_,
						  AuxiliaryWindow* auxWin_, BaslerWindow* basWin_) {
	mainWin = mainWin_;
	scriptWin = scriptWin_;
	camWin = camWin_;
	basWin = basWin_;
	auxWin = auxWin_;
}

void AuxiliaryWindow2::OnSize(UINT nType, int cx, int cy)
{
	SetRedraw(false);
	statusBox.rearrange(cx, cy, mainWin->getFonts());
	DM.rearrange(cx, cy, mainWin->getFonts());
	SetRedraw();
	RedrawWindow();
	//DM.rearrange(cx, cy);
}

IMPLEMENT_DYNAMIC(AuxiliaryWindow2, CDialog)


BEGIN_MESSAGE_MAP(AuxiliaryWindow2, CDialog)
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
	ON_COMMAND(IDC_DM_PROGRAMNOW, &handleProgramNow)
	ON_COMMAND(IDC_DM_ADD_ZERNIKE + 15, &handleAbberations)
	ON_CBN_SELENDOK(IDC_DM_PROFILE_COMBO, &handleNewProfile)
	ON_COMMAND_RANGE(MENU_ID_RANGE_BEGIN, MENU_ID_RANGE_END, &AuxiliaryWindow2::passCommonCommand)

	ON_CONTROL_RANGE(EN_CHANGE, IDC_DM_EDIT_START, IDC_DM_EDIT_END, &AuxiliaryWindow2::handlePistonChange)
END_MESSAGE_MAP()



void AuxiliaryWindow2::passCommonCommand(UINT id)
{
	try
	{
		commonFunctions::handleCommonMessage(id, this, mainWin, scriptWin, camWin, auxWin, basWin, this);
	}
	catch (Error & err)
	{
		// catch any extra errors that handleCommonMessage doesn't explicitly handle.
		errBox(err.what());
	}
}

void AuxiliaryWindow2::OnCancel() {
	passCommonCommand(ID_FILE_MY_EXIT);
}

void AuxiliaryWindow2::OnPaint()
{
	CDialog::OnPaint();
	if (!mainWin->masterIsRunning())
	{
		CRect size;
		GetClientRect(&size);
		CDC* cdc = GetDC();
		// for some reason I suddenly started needing to do this. I know that memDC redraws the background, but it used to 
		// work without this and I don't know what changed. I used to do:
		cdc->SetBkColor(_myRGBs["Main-Bkgd"]);
		long width = size.right - size.left, height = size.bottom - size.top;
		// each dc gets initialized with the rect for the corresponding plot. That way, each dc only overwrites the area 
		// for a single plot.
		Mirror->setCurrentDims(width, height);
		Mirror->drawPlot(cdc, _myBrushes["Main-Bkgd"], _myBrushes["Interactable-Bkgd"]);
		
		ReleaseDC(cdc);
	}
}

HBRUSH AuxiliaryWindow2::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH result;

	
	result = DM.handleColorMessage(pWnd, pDC);
	if (result != NULL)
	{
		return result;
	}
	result = *statusBox.handleColoring(pWnd->GetDlgCtrlID(), pDC);
	if (result != NULL)
	{
		return result;
	}

	// default colors
	switch (nCtlColor)
	{
		case CTLCOLOR_STATIC:
		{
			pDC->SetTextColor(_myRGBs["Text"]);
			pDC->SetBkColor(_myRGBs["Static-Bkgd"]);
			return *_myBrushes["Static-Bkgd"];
		}
		case CTLCOLOR_EDIT:
		{
			pDC->SetTextColor(_myRGBs["AuxWin-Text"]);
			pDC->SetBkColor(_myRGBs["Interactable-Bkgd"]);
			return *_myBrushes["Interactable-Bkgd"];
		}
		case CTLCOLOR_LISTBOX:
		{
			pDC->SetTextColor(_myRGBs["AuxWin-Text"]);
			pDC->SetBkColor(_myRGBs["Interactable-Bkgd"]);
			return *_myBrushes["Interactable-Bkgd"];
		}
		default:
			return *_myBrushes["Main-Bkgd"];
	}
}

BOOL AuxiliaryWindow2::handleAccelerators(HACCEL m_haccel, LPMSG lpMsg)
{
	return globalParameters.handleAccelerators(m_haccel, lpMsg);
}

void AuxiliaryWindow2::handleProgramNow() {
	DM.ProgramNow();
}

void AuxiliaryWindow2::handleNewProfile() {
	DM.loadProfile();
}

void AuxiliaryWindow2::handlePistonChange(UINT id) {
	DM.reColor(id);
}

void AuxiliaryWindow2::handleAbberations() {
	DM.add_Changes();
}

DmCore &AuxiliaryWindow2::GetCore() {
	return DM.getCore();
}

void AuxiliaryWindow2::handleNewConfig(std::ofstream& newFile) {
	DM.getCore().handleNewConfig( newFile );
}

void AuxiliaryWindow2::handleOpeningConfig(std::ifstream& configFile, Version ver) {
	try {
		if (ver >= Version("4.7"))
		{
			DMOutputForm form = ProfileSystem::stdGetFromConfig(configFile, "DM", DmCore::handleGetConfig);;
			DM.setCoreInfo(form);
			DM.openConfig();
		}
	}
	catch (Error&)
	{
		throwNested("Auxiliary Window failed to read parameters from the configuration file.");
	}
}


void AuxiliaryWindow2::handleSaveConfig(std::ofstream& newFile) {
	DM.handleSaveConfig(newFile);
}


#pragma once
// This header file includes all of the extern declarations of all of my external (global) variables.
#include "Windows.h"
#include <string>
#include <vector>
#include "niFgen.h"
#include "Control.h"
#include "ConfigurationFileSystem.h"
#include "NoteSystem.h"
#include "VariableSystem.h"
#include "Script.h"
#include "GUI_Debugger.h"
#include "MainWindow.h"
#include "ScriptingWindow.h"
#include "DebuggingOptionsControl.h"
#include "NiawgController.h"

extern std::string WAVEFORM_NAME_FILES[4 * MAX_NIAWG_SIGNALS];
extern std::string WAVEFORM_TYPE_FOLDERS[4 * MAX_NIAWG_SIGNALS];

/// some globals for niawg stuff, only for niawg stuff so I keep it here...?
extern const std::array<int, 2> AXES;
// the following is used to receive the index of whatever axis is not your current axis.
extern const std::array<int, 2> ALT_AXES;
extern const std::array<std::string, 2> AXES_NAMES;
extern const niawgPair<std::string> ORIENTATION_AXES;


extern bool eWaitError;
extern HINSTANCE eGlobalInstance;

// stuff for syntax coloring
extern DWORD eIntensityMinChange, eIntensityMaxChange;
extern DWORD eHorizontalMinChange, eHorizontalMaxChange;
extern DWORD eVerticalMinChange, eVerticalMaxChange;

// Agilent things
extern double eCurrentAgilentLow;
extern double eCurrentAgilentHigh;

extern std::string eCurrentFolderDialogType;

// These Describe the scripts

extern std::string eMostRecentVerticalScriptNames;
extern std::string eMostRecentHorizontalScriptNames;
extern std::string eMostRecentIntensityScriptNames;
/// Global Options Variables

// A variable which records what script is currently being executed by the NIAWG.
extern std::string eCurrentScript;

extern unsigned int eAccumulations;

extern UINT eGreenMessageID, eStatusTextMessageID, eErrorTextMessageID, eFatalErrorMessageID, eVariableStatusMessageID,
			eNormalFinishMessageID, eColoredEditMessageID, eDebugMessageID, eCameraFinishMessageID, 
			eCameraProgressMessageID;

extern bool eCurrentVerticalViewIsParent;
extern bool eCurrentHorizontalViewIsParent;
extern bool eCurrentIntensityViewIsParent;

extern bool eDontActuallyGenerate;
extern bool eAbortNiawgFlag;

extern bool eHorizontalSyntaxColorIsCurrent, eVerticalSyntaxColorIsCurrent, eIntensitySyntaxColorIsCurrent;


/// Colors

extern HBRUSH eYellowBrush;
extern HBRUSH eGreenBrush;
extern HBRUSH blueBrush;
extern HBRUSH eRedBrush;
extern HBRUSH eDarkBlueBrush;
extern HBRUSH eTealBrush;
extern HBRUSH eVeryDarkBlueBrush;
extern HBRUSH eNearBlackBlueBrush;
extern HBRUSH eDarkPurpleBrush;
extern HBRUSH eDullRedBrush;
extern HBRUSH eDarkRedBrush;
extern HBRUSH eNearBlackRedBrush;
extern HBRUSH eGreyRedBrush;

/// Other Global Handles
extern HANDLE eWaitingForNIAWGEvent;
extern HANDLE eExperimentThreadHandle;
extern HANDLE eNIAWGWaitThreadHandle;

/// Global API Handles (Main Window)
// main
extern HWND eMainWindowHandle;
/// Global API Handles (Scripting Window)
// main
extern HWND eScriptingWindowHandle;
/// Beginning Settings Dialog
extern HWND eBeginDialogRichEdit;

/// Temp!
/// view Combos & texts


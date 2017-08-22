#pragma once
#include "Windows.h"

class MainWindow;
class CameraWindow;
class DeviceWindow;

namespace commonFunctions
{
	/// Call to direct message to appropriate function in this namespace
	bool handleCommonMessage( int msgID, CWnd* parent, MainWindow* mainWin, ScriptingWindow* scriptWin, 
							  CameraWindow* camWin, DeviceWindow* masterWin );
	/// Run Menu
	void startNiawg( int msgID, ScriptingWindow* scriptWindow, MainWindow* mainWin, CameraWindow* camWin );
	void startCamera( ScriptingWindow* scriptWindow, MainWindow* mainWin, CameraWindow* camWin );
	void abortNiawg( ScriptingWindow* scriptWin, MainWindow* mainWin );
	void abortCamera( CameraWindow* camWin, MainWindow* mainWin );
	void exitProgram( ScriptingWindow* scriptWindow, MainWindow* mainWin, CameraWindow* camWin );
	/// Scripting Menu
	int saveProfile( ScriptingWindow* scriptWindow, MainWindow* mainWin );
	void helpWindow();
	void reloadNIAWGDefaults( MainWindow* mainWin );
}
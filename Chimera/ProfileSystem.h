#pragma once
#include "Control.h"
#include "ProfileSystem.h"
#include "NiawgController.h"
#include "commonTypes.h"
#include "profileSettings.h"
#include <vector>
#include <string>

class MainWindow;
class ScriptingWindow;

/*
]--- This singleton class manages the entire "profile" system, where "profiles" are my term for the entirety of the settings in the code (strange word choice I
]- know). It consists of the relevant controls, some saved indicators that can be checked to determine if the user should be prompted to save at a given point,
]- and all of the functions for saving, renaming, deleting, and creating new levels within the code. 
*/
class ProfileSystem
{
	public:
		ProfileSystem(std::string fileSystemPath);

		void saveEntireProfile( ScriptingWindow* scriptWindow, MainWindow* mainWin, AuxiliaryWindow* auxWin,
								CameraWindow* camWin );
		void checkSaveEntireProfile( ScriptingWindow* scriptWindow, MainWindow* mainWin, AuxiliaryWindow* auxWin,
									 CameraWindow* camWin );
		void allSettingsReadyCheck( ScriptingWindow* scriptWindow, MainWindow* mainWin, AuxiliaryWindow* auxWin,
									CameraWindow* camWin );

		void saveSequence();
		void saveSequenceAs();
		void renameSequence();
		void deleteSequence();
		void newSequence(CWnd* parent);
		void openSequence(std::string sequenceName);
		void updateSequenceSavedStatus(bool isSaved);
		bool sequenceSettingsReadyCheck();
		bool checkSequenceSave(std::string prompt);
		void sequenceChangeHandler();
		std::string getSequenceNamesString();
		void loadNullSequence();
		void addToSequence(CWnd* parent);
		void reloadSequence(std::string sequenceToReload);

		void saveConfigurationOnly( ScriptingWindow* scriptWindow, MainWindow* mainWin, AuxiliaryWindow* auxWin, 
								    CameraWindow* camWin );
		void newConfiguration( MainWindow* mainWin, AuxiliaryWindow* auxWin, CameraWindow* camWin,
							   ScriptingWindow* scriptWin );
		void saveConfigurationAs( ScriptingWindow* scriptWindow, MainWindow* mainWin, AuxiliaryWindow* auxWin, 
								  CameraWindow* camWin );
		void renameConfiguration();
		void deleteConfiguration();
		void openConfigFromPath( std::string pathToConfig, ScriptingWindow* scriptWin, MainWindow* mainWin,
								 CameraWindow* camWin, AuxiliaryWindow* auxWin );
		static void getVersionFromFile( std::ifstream& f, int& versionMajor, int& versionMinor );
		static void openNiawgFiles( niawgPair<std::fstream>& scriptFiles, profileSettings profile, seqSettings seq, 
									bool programNiawg, std::string configName );
		static std::string ProfileSystem::getMasterAddressFromConfig( profileSettings profile );
		void updateConfigurationSavedStatus( bool isSaved );
		bool configurationSettingsReadyCheck(ScriptingWindow* scriptWindow, MainWindow* mainWin, 
											 AuxiliaryWindow* auxWin, CameraWindow* camWin);
		bool checkConfigurationSave(std::string prompt, ScriptingWindow* scriptWindow, MainWindow* mainWin, 
									AuxiliaryWindow* auxWin, CameraWindow* camWin);
		std::string getCurrentPathIncludingCategory();
		profileSettings getProfileSettings();
		seqSettings getSeqSettings( );

		static std::vector<std::string> searchForFiles(std::string locationToSearch, std::string extensions);
		static void reloadCombo( HWND comboToReload, std::string locationToLook, std::string extension, 
								 std::string nameToLoad );
		bool fileOrFolderExists( std::string filePathway );
		void fullyDeleteFolder(std::string folderToDelete);
		void initialize( POINT& topLeftPosition, CWnd* parent, int& id, cToolTips& tooltips );
		void rearrange(int width, int height, fontMap fonts);
		void handleSelectConfigButton( CWnd* parent, ScriptingWindow* scriptWindow, MainWindow* mainWin,
									   AuxiliaryWindow* auxWin, CameraWindow* camWin );
		static void checkDelimiterLine(std::ifstream& openFile, std::string keyword);
		static bool checkDelimiterLine( std::ifstream& openFile, std::string delimiter, std::string breakCondition );
	private:
		profileSettings currentProfile;
		seqSettings currentSequence;
		std::string FILE_SYSTEM_PATH;
		bool configurationIsSaved;
		bool categoryIsSaved;
		bool experimentIsSaved;
		bool sequenceIsSaved;

		// version = str(versionMain) + "." + str(versionSub)
		const int versionMain = 2;
		const int versionSub = 14;
		Control<CStatic> sequenceLabel;
		Control<CComboBox> sequenceCombo;
		Control<CEdit> sequenceInfoDisplay;
		Control<CButton> sequenceSavedIndicator;
		Control<CButton> configurationSavedIndicator;
		Control<CButton> selectConfigButton;
		Control<CStatic> configDisplay;
};

#pragma once
#include "Control.h"
#include <string>
#include <unordered_map>

class NoteSystem
{
	public:
		NoteSystem(int& startID);
		bool setExperimentNotes(std::string notes);
		bool setCategoryNotes(std::string notes);
		bool setConfigurationNotes(std::string notes);
		bool initializeControls(POINT& topLeftPosition, HWND parentWindow);
		std::string getExperimentNotes();
		std::string getCategoryNotes();
		std::string getConfigurationNotes();
		INT_PTR handleColorMessage(HWND parent, UINT msg, WPARAM wParam, LPARAM lParam, std::unordered_map<std::string, HBRUSH> brushes);
	private:
		ClassControl<CEdit> experimentNotes;
		ClassControl<CStatic> experimentNotesHeader;
		ClassControl<CEdit> categoryNotes;
		ClassControl<CStatic> categoryNotesHeader;
		ClassControl<CEdit> configurationNotes;
		ClassControl<CStatic> configurationNotesHeader;
};
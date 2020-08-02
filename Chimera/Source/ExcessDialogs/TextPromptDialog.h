// created by Mark O. Brown
#pragma once
#include "afxwin.h"
#include <CustomMfcControlWrappers/Control.h>
#include <CustomMfcControlWrappers/myButton.h>

class TextPromptDialog : public CDialog
{
	DECLARE_DYNAMIC(TextPromptDialog);

	public:

		TextPromptDialog::TextPromptDialog( std::string* resultPtr, std::string description, std::string initString, 
											bool isPassword=false) 
			: CDialog(IDD_TEXT_PROMPT_DIALOG), initStringValue(initString)
		{
			passwordOption = isPassword;
			result = resultPtr;
			descriptionText = description;

		}
		void catchf5( );
		BOOL OnInitDialog() override;

		void catchOk();
		void catchCancel();
		HBRUSH OnCtlColor (CDC* pDC, CWnd* pWnd, unsigned nCtlColor);
		

	private:	
		DECLARE_MESSAGE_MAP();
		const std::string initStringValue;
		std::string descriptionText;
		Control<CStatic> description;
		Control<CEdit> prompt;
		Control<CleanPush> okBtn, cancelBtn;
		std::string* result;
		bool passwordOption;
};


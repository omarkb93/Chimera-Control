#include "stdafx.h"
#include "StatusIndicator.h"

void StatusIndicator::initialize(POINT &loc, CWnd* parent, int& id)
{
	this->status.ID = id++;
	status.position = { loc.x, loc.y, loc.x + 960, loc.y + 100 };
	status.Create("Passively Outputing Default Waveform", WS_CHILD | WS_VISIBLE | SS_CENTER, status.position, parent, status.ID);
	status.SetFont(&eLargeHeadingFont);
}

void StatusIndicator::setText(std::string text)
{
	status.SetWindowText(text.c_str());
	return;
}

void StatusIndicator::setColor(std::string color)
{
	currentColor = color;
	status.RedrawWindow();
}

HBRUSH StatusIndicator::handleColor(CWnd* window, CDC* pDC, std::unordered_map<std::string, COLORREF> rgbs, std::unordered_map<std::string, HBRUSH> brushes)
{
	DWORD controlID = GetDlgCtrlID(window->GetSafeHwnd());
	if (controlID == this->status.ID)
	{
		pDC->SetTextColor(rgbs["White"]);
		if (this->currentColor == "G")
		{
			pDC->SetBkColor(rgbs["Green"]);
			return brushes["Green"];
		}
		else if (currentColor == "Y")
		{
			pDC->SetTextColor(rgbs["Black"]);
			pDC->SetBkColor(rgbs["Gold"]);
			return brushes["Gold"];
		}
		else if (currentColor == "R")
		{
			pDC->SetBkColor(rgbs["Dark Red"]);
			return brushes["Dark Red"];
		}
		else
		{
			return NULL;
			// blue
		}
	}
	else
	{
		return NULL;
	}
}


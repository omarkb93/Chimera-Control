// created by Mark O. Brown
#include "stdafx.h"
#include "StatusIndicator.h"

void StatusIndicator::rearrange(int width, int height, fontMap fonts)
{
	status.rearrange( width, height, fonts);
}


void StatusIndicator::initialize(POINT &loc, CWnd* parent, int& id, cToolTips& tooltips)
{
	status.sPos = { loc.x, loc.y, loc.x + 960, loc.y + 100 };
	status.Create("Passively Outputing Default Waveform", WS_CHILD | WS_VISIBLE | SS_CENTER, status.sPos, parent, id++);
	status.fontType = fontTypes::LargeFont;
}


void StatusIndicator::setText(std::string text)
{
	status.SetWindowText(cstr(text));
}


void StatusIndicator::setColor(std::string color)
{
	currentColor = color;
	status.RedrawWindow();
}


CBrush* StatusIndicator::handleColor(CWnd* window, CDC* pDC )
{
	DWORD controlID = GetDlgCtrlID(window->GetSafeHwnd());
	if (controlID == status.GetDlgCtrlID())
	{
		pDC->SetTextColor(_myRGBs["White"]);
		if (this->currentColor == "G")
		{
			pDC->SetBkColor( _myRGBs["Green"]);
			return _myBrushes["Green"];
		}
		else if (currentColor == "Y")
		{
			pDC->SetTextColor( _myRGBs["Black"]);
			pDC->SetBkColor(_myRGBs["Gold"]);
			return _myBrushes["Gold"];
		}
		else if (currentColor == "R")
		{
			pDC->SetBkColor( _myRGBs["Dark Red"]);
			return _myBrushes["Dark Red"];
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

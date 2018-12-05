#include "stdafx.h"
#include "ColorBox.h"
#include <tuple>


void ColorBox::initialize(POINT& pos, int& id, CWnd* parent, int length, cToolTips& tooltips)
{
	//
	boxes.niawg.sPos = { pos.x, pos.y, long(pos.x + length/4.0), pos.y + 20 };
	boxes.niawg.Create("NIAWG", WS_CHILD | WS_VISIBLE | SS_WORDELLIPSIS | SS_CENTER | WS_BORDER,
					 boxes.niawg.sPos, parent, id++ );
	boxes.niawg.fontType = fontTypes::CodeFont;
	//
	boxes.camera.sPos = { long(pos.x + length/ 4.0), pos.y, long(pos.x + 2*length/4.0), pos.y + 20 };
	boxes.camera.Create( "CAMERA", WS_CHILD | WS_VISIBLE | SS_WORDELLIPSIS | SS_CENTER | WS_BORDER, 
					  boxes.camera.sPos, parent, id++ );
	boxes.camera.fontType = fontTypes::CodeFont;
	//
	boxes.master.sPos = { long(pos.x + 2 * length / 4.0), pos.y, pos.x + long(3*length/4.0), pos.y + 20 };
	boxes.master.Create( "MASTER", WS_CHILD | WS_VISIBLE | SS_WORDELLIPSIS | SS_CENTER | WS_BORDER,
						 boxes.master.sPos, parent, id++ );
	boxes.master.fontType = fontTypes::CodeFont;
	//
	boxes.basler.sPos = { long ( pos.x + 3 * length / 4.0 ), pos.y, pos.x + length , pos.y + 20 };
	boxes.basler.Create ( "BASLER", WS_CHILD | WS_VISIBLE | SS_WORDELLIPSIS | SS_CENTER | WS_BORDER,
						  boxes.basler.sPos, parent, id++ );
	boxes.basler.fontType = fontTypes::CodeFont;

	pos.y += 20;
}


void ColorBox::rearrange( int width, int height, fontMap fonts )
{
	boxes.niawg.rearrange( width, height, fonts );
	boxes.camera.rearrange( width, height, fonts );
	boxes.master.rearrange( width, height, fonts );
	boxes.basler.rearrange ( width, height, fonts );
}

CBrush* ColorBox::handleColoring( int id, CDC* pDC )
{
	char code;
	if (id == boxes.niawg.GetDlgCtrlID())
	{
		code = colors.niawg;
	}
	else if (id == boxes.camera.GetDlgCtrlID())
	{
		code = colors.camera;
	}
	else if (id == boxes.master.GetDlgCtrlID())
	{
		code = colors.master;
	}
	else if ( id == boxes.basler.GetDlgCtrlID ( ) )
	{
		code = colors.basler;
	}
	else
	{
		return NULL;
	}

	if (code == 'G')
	{
		// Color Green. This is the "Ready to give next waveform" color. During this color you can also press esc to exit.
		pDC->SetTextColor(_myRGBs["White"]);
		pDC->SetBkColor( _myRGBs["Green"]);
		return _myBrushes["Green"];
	}
	else if (code == 'Y')
	{
		// Color Yellow. This is the "Working" Color.
		pDC->SetTextColor( _myRGBs["White"]);
		pDC->SetBkColor( _myRGBs["Gold"]);
		return _myBrushes["Gold"];
	}
	else if (code == 'R')
	{
		// Color Red. This is a big visual signifier for when the program exited with error.
		pDC->SetTextColor( _myRGBs["White"]);
		pDC->SetBkColor( _myRGBs["Red"]);
		return _myBrushes["Red"];
	}
	else
	{
		// color Blue. This is the default, ready for user input color.
		pDC->SetTextColor( _myRGBs["White"] );
		pDC->SetBkColor( _myRGBs["Dark Grey"] );
		return _myBrushes["Dark Grey"];
	}
}


/*
 * color should be a four-character long 
 */
void ColorBox::changeColor( systemInfo<char> newColors )
{
	if ( newColors.niawg != '-' )
	{
		colors.niawg = newColors.niawg;
		boxes.niawg.RedrawWindow();
	}
	if ( newColors.camera != '-' )
	{
		colors.camera = newColors.camera;
		boxes.camera.RedrawWindow();
	}
	if (newColors.master != '-')
	{
		colors.master = newColors.master;
		boxes.master.RedrawWindow();
	}
	if ( newColors.basler != '-' )
	{
		colors.basler = newColors.basler;
		boxes.basler.RedrawWindow ( );
	}
}
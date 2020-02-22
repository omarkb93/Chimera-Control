﻿#include "stdafx.h"
#include "DigitalOutput.h"


void DigitalOutput::updateStatus ( )
{
	if ( check.m_hWnd == NULL )
	{
		return;
	}
	check.SetCheck ( status );
	check.colorState = 0;
	check.RedrawWindow ( );
}


void DigitalOutput::initLoc ( UINT numIn, DoRows::which rowIn )
{
	row = rowIn;
	num = numIn;
}


void DigitalOutput::set ( bool stat )
{
	status = stat;
	updateStatus ( );
}


bool DigitalOutput::getStatus ( )
{
	return status;
}


std::pair<DoRows::which, UINT> DigitalOutput::getPosition ( )
{
	return { row, num };
}

void DigitalOutput::rearrange ( int width, int height, fontMap fonts )
{
	check.rearrange ( width, height, fonts );
}


HBRUSH DigitalOutput::handleColorMessage ( UINT controlID, CWnd* window, CDC* cDC )
{
	if ( controlID == check.GetDlgCtrlID ( ) )
	{
		if ( check.colorState == -1 )
		{
			cDC->SetBkColor ( _myRGBs[ "Red" ] );
			return *_myBrushes[ "Red" ];
		}
		else if ( check.colorState == 1 )
		{
			cDC->SetBkColor ( _myRGBs[ "Green" ] );
			return *_myBrushes[ "Green" ];
		}
		else if ( check.colorState == 2 )
		{
			cDC->SetBkColor ( _myRGBs[ "White" ] );
			return *_myBrushes[ "White" ];
		}
		else
		{
			cDC->SetBkColor ( _myRGBs[ "Medium Grey" ] );
			return *_myBrushes[ "Medium Grey" ];
		}
	}
	return NULL;
}


void DigitalOutput::setName ( std::string nameStr, cToolTips& toolTips, CWnd* parent )
{
	check.setToolTip ( nameStr, toolTips, parent );
}


int DigitalOutput::getCheckID ( )
{
	return check.GetDlgCtrlID ( );
}


void DigitalOutput::setHoldStatus ( bool stat )
{
	holdStatus = stat;
	check.colorState = stat ? 1 : -1;
	check.RedrawWindow ( );
}


bool DigitalOutput::getShadeStatus ( )
{
	return shadeStatus;
}


void DigitalOutput::initialize ( POINT& pos, CWnd* parent, UINT id, cToolTips& toolTips )
{
	check.sPos = { long ( pos.x ), long ( pos.y  ), long ( pos.x + 28 ), long ( pos.y + 28 ) };
	check.Create ( "", WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_RIGHT | BS_3STATE, check.sPos, parent, id );
}


void DigitalOutput::shade ( bool shadeStat )
{
	if ( shadeStat )
	{
		// shade it.
		check.SetCheck ( BST_INDETERMINATE );
		shadeStatus = true;
		// a grey color is then used.
		check.colorState = 2;
		// don't force immediate redraw.
		check.InvalidateRect ( NULL );
	}
	else
	{
		shadeStatus = false;
		if ( check.colorState == 2 )
		{
			check.colorState = 0;
			check.RedrawWindow ( );
		}
		check.SetCheck ( status ? BST_CHECKED : BST_UNCHECKED );
		enable ( true );
	}
}


void DigitalOutput::enable ( bool enabledStatus )
{
	check.EnableWindow ( enabledStatus );
}


DigitalOutput& allDigitalOutputs::operator()( UINT num, DoRows::which row )
{
	return core[ ULONG ( row ) * 16L + num ];
}

allDigitalOutputs::allDigitalOutputs ( )
{
	for ( auto row : DoRows::allRows )
	{
		for ( auto num : range ( numColumns ) )
		{
			(*this)( num, row ).initLoc ( num, row );
		}
	}
}

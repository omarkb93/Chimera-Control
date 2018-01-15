﻿#include "stdafx.h"
#include "OscilloscopeViewer.h"


ScopeViewer::ScopeViewer( std::string usbAddress, bool safemode, UINT traceNumIn ) : 
	visa( safemode, usbAddress ),
	numTraces( traceNumIn )
{
	visa.open( );
	visa.write( "header off\n" );
	visa.query( "WFMpre:YOFF?\n", yoffset );
	visa.query( "WFMpre:YMULT?\n", ymult );
	visa.close( );
}


void ScopeViewer::refreshPlot(CDC* d, UINT width, UINT height, CBrush* backgroundBrush )
{
	viewPlot->setCurrentDims( width, height );
	memDC dacDC( d, &viewPlot->GetPlotRect( ) );
	viewPlot->drawBackground( dacDC, backgroundBrush );
	viewPlot->drawTitle( dacDC );
	viewPlot->drawBorder( dacDC );
	viewPlot->plotPoints( &dacDC );
}


void ScopeViewer::rearrange( int width, int height, fontMap fonts )
{
	viewPlot->rearrange( width, height, fonts );
}


void ScopeViewer::initialize( POINT& topLeftLoc, UINT width, UINT height, CWnd* parent, std::vector<CPen*> plotPens, 
							  CFont* font )
{
	scopeData.resize( numTraces );
	for ( auto& data : scopeData )
	{
		data = pPlotDataVec( new plotDataVec( 100, { 0,0,0 } ) );
	}
	viewPlot = new PlotCtrl( scopeData, OscilloscopePlot, plotPens, font, "Scope!" );
	viewPlot->init( topLeftLoc, width, height, parent );
	topLeftLoc.y += height;
	//refreshData( );
}


void ScopeViewer::refreshData( )
{
	visa.open( );
	for ( auto line : range( numTraces ) )
	{
		std::string data;
		visa.write( "DATa:SOUrce CH" + str(line+1) );
		visa.query( "Curve?\n", data );
		double count = 0;
		std::lock_guard<std::mutex> lock( viewPlot->dataMutexes[line] );
		scopeData[line]->clear( );
		for ( auto& c : data )
		{
			if ( count++ < 6 )
			{
				continue;
			}
			scopeData[line]->push_back( { count, ((((double)c) - yoffset) * ymult), 0 } );
		}
	}
	visa.close( );
}


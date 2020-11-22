﻿// created by Mark O. Brown
#pragma once

#include "Plotting/dataPoint.h"
#include "gdiplus.h"
#include <QLineSeries>

#include "PrimaryWindows/IChimeraQtWindow.h"
#include <qchart.h>
#include <qchartview.h>
#include <qlineseries.h>
#include <qscatterseries.h>
#include <qobject.h>

#include <mutex>
#include <vector>
#include <memory>

enum class plotStyle{
	// ttl and dac plot use steps.
	TtlPlot,
	DacPlot,
	// uses circs and error bars to represent data and errors
	BinomialDataPlot,
	GeneralErrorPlot,
	// uses bars for histograms
	HistPlot,
	VertHist,
	// 
	OscilloscopePlot
};


typedef std::vector<dataPoint> plotDataVec; 
Q_DECLARE_METATYPE (std::vector<std::vector<plotDataVec>>)

struct plotMinMax { 
	double min_x, min_y, max_x, max_y;
};
/*
* This is a custom object that I use for plotting. All of the drawing is done manually by standard win32 / MFC
* functionality. Plotting used to be done by gnuplot, an external program which my program would send data to in
* real-time, but this custom plotter, while it took some work (it was fun though) allows me to embed plots in the
* main windows and have a little more direct control over the data being plotted.
*/
class PlotCtrl : public QObject {
	Q_OBJECT;
	public: 
		PlotCtrl( unsigned numTraces, plotStyle inStyle, std::vector<int> thresholds,
				  std::string titleIn = "Title!", bool narrowOpt=false, bool plotHistOption=false);
		~PlotCtrl( );
		void init( QPoint& topLeftLoc, LONG width, LONG height, IChimeraQtWindow* parent );
		dataPoint getMainAnalysisResult ( );
		void resetChart ();
		void setStyle (plotStyle newStyle);
		void setTitle (std::string newTitle);
		void setThresholds (std::vector<int> newThresholds);
		void handleContextMenu (const QPoint& pos);

	private:
		const bool narrow;
		std::vector<int> thresholds;
		plotStyle style;
		QtCharts::QChart* chart;
		QtCharts::QChartView* view;
		// first level deliminates different lines which get different colors. second level deliminates different 
		// points within the line.
		std::string title;
		std::vector<QtCharts::QLineSeries*> qtLineData;
		std::vector<QtCharts::QScatterSeries*> qtScatterData;

		QtCharts::QLineSeries* fitData;
		QtCharts::QScatterSeries* calibrationData;

		// a colormap that I use for plot stuffs.
		const std::vector<std::array<int, 3>> GIST_RAINBOW_RGB{ { 255 , 0 , 40 },
								{ 255 , 0 , 35 },
								{ 255 , 0 , 30 },
								{ 255 , 0 , 24 },
								{ 255 , 0 , 19 },
								{ 255 , 0 , 14 },
								{ 255 , 0 , 8 },
								{ 255 , 0 , 3 },
								{ 255 , 1 , 0 },
								{ 255 , 7 , 0 },
								{ 255 , 12 , 0 },
								{ 255 , 18 , 0 },
								{ 255 , 23 , 0 },
								{ 255 , 28 , 0 },
								{ 255 , 34 , 0 },
								{ 255 , 39 , 0 },
								{ 255 , 45 , 0 },
								{ 255 , 50 , 0 },
								{ 255 , 55 , 0 },
								{ 255 , 61 , 0 },
								{ 255 , 66 , 0 },
								{ 255 , 72 , 0 },
								{ 255 , 77 , 0 },
								{ 255 , 82 , 0 },
								{ 255 , 88 , 0 },
								{ 255 , 93 , 0 },
								{ 255 , 99 , 0 },
								{ 255 , 104 , 0 },
								{ 255 , 110 , 0 },
								{ 255 , 115 , 0 },
								{ 255 , 120 , 0 },
								{ 255 , 126 , 0 },
								{ 255 , 131 , 0 },
								{ 255 , 137 , 0 },
								{ 255 , 142 , 0 },
								{ 255 , 147 , 0 },
								{ 255 , 153 , 0 },
								{ 255 , 158 , 0 },
								{ 255 , 164 , 0 },
								{ 255 , 169 , 0 },
								{ 255 , 174 , 0 },
								{ 255 , 180 , 0 },
								{ 255 , 185 , 0 },
								{ 255 , 191 , 0 },
								{ 255 , 196 , 0 },
								{ 255 , 201 , 0 },
								{ 255 , 207 , 0 },
								{ 255 , 212 , 0 },
								{ 255 , 218 , 0 },
								{ 255 , 223 , 0 },
								{ 255 , 228 , 0 },
								{ 255 , 234 , 0 },
								{ 255 , 239 , 0 },
								{ 255 , 245 , 0 },
								{ 255 , 250 , 0 },
								{ 254 , 255 , 0 },
								{ 248 , 255 , 0 },
								{ 243 , 255 , 0 },
								{ 237 , 255 , 0 },
								{ 232 , 255 , 0 },
								{ 227 , 255 , 0 },
								{ 221 , 255 , 0 },
								{ 216 , 255 , 0 },
								{ 210 , 255 , 0 },
								{ 205 , 255 , 0 },
								{ 199 , 255 , 0 },
								{ 194 , 255 , 0 },
								{ 189 , 255 , 0 },
								{ 183 , 255 , 0 },
								{ 178 , 255 , 0 },
								{ 172 , 255 , 0 },
								{ 167 , 255 , 0 },
								{ 162 , 255 , 0 },
								{ 156 , 255 , 0 },
								{ 151 , 255 , 0 },
								{ 145 , 255 , 0 },
								{ 140 , 255 , 0 },
								{ 135 , 255 , 0 },
								{ 129 , 255 , 0 },
								{ 124 , 255 , 0 },
								{ 118 , 255 , 0 },
								{ 113 , 255 , 0 },
								{ 108 , 255 , 0 },
								{ 102 , 255 , 0 },
								{ 97 , 255 , 0 },
								{ 91 , 255 , 0 },
								{ 86 , 255 , 0 },
								{ 81 , 255 , 0 },
								{ 75 , 255 , 0 },
								{ 70 , 255 , 0 },
								{ 64 , 255 , 0 },
								{ 59 , 255 , 0 },
								{ 54 , 255 , 0 },
								{ 48 , 255 , 0 },
								{ 43 , 255 , 0 },
								{ 37 , 255 , 0 },
								{ 32 , 255 , 0 },
								{ 27 , 255 , 0 },
								{ 21 , 255 , 0 },
								{ 16 , 255 , 0 },
								{ 10 , 255 , 0 },
								{ 5 , 255 , 0 },
								{ 0 , 255 , 0 },
								{ 0 , 255 , 5 },
								{ 0 , 255 , 10 },
								{ 0 , 255 , 16 },
								{ 0 , 255 , 21 },
								{ 0 , 255 , 26 },
								{ 0 , 255 , 32 },
								{ 0 , 255 , 37 },
								{ 0 , 255 , 43 },
								{ 0 , 255 , 48 },
								{ 0 , 255 , 53 },
								{ 0 , 255 , 59 },
								{ 0 , 255 , 64 },
								{ 0 , 255 , 69 },
								{ 0 , 255 , 75 },
								{ 0 , 255 , 80 },
								{ 0 , 255 , 86 },
								{ 0 , 255 , 91 },
								{ 0 , 255 , 96 },
								{ 0 , 255 , 102 },
								{ 0 , 255 , 107 },
								{ 0 , 255 , 112 },
								{ 0 , 255 , 118 },
								{ 0 , 255 , 123 },
								{ 0 , 255 , 129 },
								{ 0 , 255 , 134 },
								{ 0 , 255 , 139 },
								{ 0 , 255 , 145 },
								{ 0 , 255 , 150 },
								{ 0 , 255 , 155 },
								{ 0 , 255 , 161 },
								{ 0 , 255 , 166 },
								{ 0 , 255 , 172 },
								{ 0 , 255 , 177 },
								{ 0 , 255 , 182 },
								{ 0 , 255 , 188 },
								{ 0 , 255 , 193 },
								{ 0 , 255 , 198 },
								{ 0 , 255 , 204 },
								{ 0 , 255 , 209 },
								{ 0 , 255 , 215 },
								{ 0 , 255 , 220 },
								{ 0 , 255 , 225 },
								{ 0 , 255 , 231 },
								{ 0 , 255 , 236 },
								{ 0 , 255 , 241 },
								{ 0 , 255 , 247 },
								{ 0 , 255 , 252 },
								{ 0 , 251 , 255 },
								{ 0 , 246 , 255 },
								{ 0 , 241 , 255 },
								{ 0 , 235 , 255 },
								{ 0 , 230 , 255 },
								{ 0 , 224 , 255 },
								{ 0 , 219 , 255 },
								{ 0 , 213 , 255 },
								{ 0 , 208 , 255 },
								{ 0 , 202 , 255 },
								{ 0 , 197 , 255 },
								{ 0 , 192 , 255 },
								{ 0 , 186 , 255 },
								{ 0 , 181 , 255 },
								{ 0 , 175 , 255 },
								{ 0 , 170 , 255 },
								{ 0 , 164 , 255 },
								{ 0 , 159 , 255 },
								{ 0 , 154 , 255 },
								{ 0 , 148 , 255 },
								{ 0 , 143 , 255 },
								{ 0 , 137 , 255 },
								{ 0 , 132 , 255 },
								{ 0 , 126 , 255 },
								{ 0 , 121 , 255 },
								{ 0 , 116 , 255 },
								{ 0 , 110 , 255 },
								{ 0 , 105 , 255 },
								{ 0 , 99 , 255 },
								{ 0 , 94 , 255 },
								{ 0 , 88 , 255 },
								{ 0 , 83 , 255 },
								{ 0 , 77 , 255 },
								{ 0 , 72 , 255 },
								{ 0 , 67 , 255 },
								{ 0 , 61 , 255 },
								{ 0 , 56 , 255 },
								{ 0 , 50 , 255 },
								{ 0 , 45 , 255 },
								{ 0 , 39 , 255 },
								{ 0 , 34 , 255 },
								{ 0 , 29 , 255 },
								{ 0 , 23 , 255 },
								{ 0 , 18 , 255 },
								{ 0 , 12 , 255 },
								{ 0 , 7 , 255 },
								{ 0 , 1 , 255 },
								{ 3 , 0 , 255 },
								{ 8 , 0 , 255 },
								{ 14 , 0 , 255 },
								{ 19 , 0 , 255 },
								{ 25 , 0 , 255 },
								{ 30 , 0 , 255 },
								{ 36 , 0 , 255 },
								{ 41 , 0 , 255 },
								{ 47 , 0 , 255 },
								{ 52 , 0 , 255 },
								{ 57 , 0 , 255 },
								{ 63 , 0 , 255 },
								{ 68 , 0 , 255 },
								{ 74 , 0 , 255 },
								{ 79 , 0 , 255 },
								{ 85 , 0 , 255 },
								{ 90 , 0 , 255 },
								{ 95 , 0 , 255 },
								{ 101 , 0 , 255 },
								{ 106 , 0 , 255 },
								{ 112 , 0 , 255 },
								{ 117 , 0 , 255 },
								{ 123 , 0 , 255 },
								{ 128 , 0 , 255 },
								{ 133 , 0 , 255 },
								{ 139 , 0 , 255 },
								{ 144 , 0 , 255 },
								{ 150 , 0 , 255 },
								{ 155 , 0 , 255 },
								{ 161 , 0 , 255 },
								{ 166 , 0 , 255 },
								{ 172 , 0 , 255 },
								{ 177 , 0 , 255 },
								{ 182 , 0 , 255 },
								{ 188 , 0 , 255 },
								{ 193 , 0 , 255 },
								{ 199 , 0 , 255 },
								{ 204 , 0 , 255 },
								{ 210 , 0 , 255 },
								{ 215 , 0 , 255 },
								{ 220 , 0 , 255 },
								{ 226 , 0 , 255 },
								{ 231 , 0 , 255 },
								{ 237 , 0 , 255 },
								{ 242 , 0 , 255 },
								{ 248 , 0 , 255 },
								{ 253 , 0 , 255 },
								{ 255 , 0 , 251 },
								{ 255 , 0 , 245 },
								{ 255 , 0 , 240 },
								{ 255 , 0 , 234 },
								{ 255 , 0 , 229 },
								{ 255 , 0 , 223 },
								{ 255 , 0 , 218 },
								{ 255 , 0 , 212 },
								{ 255 , 0 , 207 },
								{ 255 , 0 , 202 },
								{ 255 , 0 , 196 },
								{ 255 , 0 , 191 } };

	public Q_SLOTS:
		void setData (std::vector<plotDataVec> newData);

};


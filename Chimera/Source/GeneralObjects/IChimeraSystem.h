#pragma once

#include <qwidget.h>
#include <qobject.h>

class IChimeraQtWindow;

class IChimeraSystem : public QObject {
	Q_OBJECT;
	public:
		IChimeraSystem(IChimeraQtWindow* parent_in);
		IChimeraQtWindow* parentWin;

	public Q_SLOTS:

	Q_SIGNALS:
		void notification (QString msg, unsigned notificationLevel=0, int debugLvl=0);
		void warning (QString msg, unsigned errorLevel = 1);
		void error (QString msg, unsigned errorLevel = 0);
};

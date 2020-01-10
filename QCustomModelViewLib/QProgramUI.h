#pragma once

#include <QWidget>

#ifdef USEPROGRAMUI
#ifdef _DEBUG
#include ".\x64\Debug\uic\ui_QProgramUI.h"
#else
#include ".\x64\Release\uic\ui_QProgramUI.h"
#endif

#else
#ifdef _DEBUG
#include "ui_QProgramUI.h"
#else
#include "ui_QProgramUI.h"
#endif

#endif // USEPROGRAMUI

#include "qcustommodelviewlib_global.h"

class QBaseCommandSource;
class QCUSTOMMODELVIEWLIB_EXPORT QProgramUI : public QWidget, public Ui::QProgramUI
{
	Q_OBJECT

public:
	QProgramUI(QWidget *parent = Q_NULLPTR);
	~QProgramUI();

	void initializeCommandSource(const QStringList& listCommand, const QStringList& listParameter); //≥ı ºªØ√¸¡Ó‘¥
};



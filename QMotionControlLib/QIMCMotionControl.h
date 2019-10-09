#pragma once

#include "IMC_Def4xxx.h"
#include "ParamDef4xxx.h"
#include "IMC_Pkg4xxx.h"

#pragma comment(lib, "../X64/Debug/IMC_Pkg4xxx.lib")

#include "QAbstractMotionControl.h"

class QMOTIONCONTROLLIB_EXPORT QIMCMotionControl : public QAbstractMotionControl
{
public:
	QIMCMotionControl();
	~QIMCMotionControl();
};

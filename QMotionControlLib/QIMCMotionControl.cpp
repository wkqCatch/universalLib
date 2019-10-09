#include "QIMCMotionControl.h"

QIMCMotionControl::QIMCMotionControl()
	: QAbstractMotionControl()
{
	char NICInfo[16][256];
	int NICNum;

	PKG_IMC_FindNetCard(NICInfo, &NICNum);
}

QIMCMotionControl::~QIMCMotionControl()
{

}

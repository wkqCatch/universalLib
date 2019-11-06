#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(QCUSTOMMODELVIEWLIB_LIB)
#  define QCUSTOMMODELVIEWLIB_EXPORT Q_DECL_EXPORT
# else
#  define QCUSTOMMODELVIEWLIB_EXPORT Q_DECL_IMPORT
# endif
#else
# define QCUSTOMMODELVIEWLIB_EXPORT
#endif

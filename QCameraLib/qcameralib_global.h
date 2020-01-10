#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(QCAMERALIB_LIB)
#  define QCAMERALIB_EXPORT Q_DECL_EXPORT
# else
#  define QCAMERALIB_EXPORT Q_DECL_IMPORT
# endif
#else
# define QCAMERALIB_EXPORT
#endif

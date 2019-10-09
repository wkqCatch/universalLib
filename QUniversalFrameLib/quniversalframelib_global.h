#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(QUNIVERSALFRAMELIB_LIB)
#  define QUNIVERSALFRAMELIB_EXPORT Q_DECL_EXPORT
# else
#  define QUNIVERSALFRAMELIB_EXPORT Q_DECL_IMPORT
# endif
#else
# define QUNIVERSALFRAMELIB_EXPORT
#endif

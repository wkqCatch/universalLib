#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(QSERIALPORTLIB_LIB)
#  define QSERIALPORTLIB_EXPORT Q_DECL_EXPORT
# else
#  define QSERIALPORTLIB_EXPORT Q_DECL_IMPORT
# endif
#else
# define QSERIALPORTLIB_EXPORT
#endif

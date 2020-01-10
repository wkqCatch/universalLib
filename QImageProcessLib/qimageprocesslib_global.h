#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(QIMAGEPROCESSLIB_LIB)
#  define QIMAGEPROCESSLIB_EXPORT Q_DECL_EXPORT
# else
#  define QIMAGEPROCESSLIB_EXPORT Q_DECL_IMPORT
# endif
#else
# define QIMAGEPROCESSLIB_EXPORT
#endif

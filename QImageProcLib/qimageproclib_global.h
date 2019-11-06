#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(QIMAGEPROCLIB_LIB)
#  define QIMAGEPROCLIB_EXPORT Q_DECL_EXPORT
# else
#  define QIMAGEPROCLIB_EXPORT Q_DECL_IMPORT
# endif
#else
# define QIMAGEPROCLIB_EXPORT
#endif

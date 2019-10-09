#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(QMOTIONCONTROLLIB_LIB)
#  define QMOTIONCONTROLLIB_EXPORT Q_DECL_EXPORT
# else
#  define QMOTIONCONTROLLIB_EXPORT Q_DECL_IMPORT
# endif
#else
# define QMOTIONCONTROLLIB_EXPORT
#endif

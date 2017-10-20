#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(QTNETWORKPLATFORM_LIB)
#  define QTNETWORKPLATFORM_EXPORT Q_DECL_EXPORT
# else
#  define QTNETWORKPLATFORM_EXPORT Q_DECL_IMPORT
# endif
#else
# define QTNETWORKPLATFORM_EXPORT
#endif

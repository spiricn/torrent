#ifndef BE_GLOBAL_H
#define BE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(BE_LIBRARY)
#  define BE_SHARED_EXPORT Q_DECL_EXPORT
#else
#  define BE_SHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // BE_GLOBAL_H

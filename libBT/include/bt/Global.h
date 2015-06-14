#ifndef BT_GLOBAL_H
#define BT_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(BT_LIBRARY)
#  define BT_SHARED_EXPORT Q_DECL_EXPORT
#else
#  define BT_SHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // BT_GLOBAL_H

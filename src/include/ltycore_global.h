#ifndef LTYCORE_GLOBAL_H
#define LTYCORE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(LTYCORE_LIBRARY)
#  define LTYCORE_EXPORT Q_DECL_EXPORT
#else
#  define LTYCORE_EXPORT Q_DECL_IMPORT
#endif

#endif // LTYCORE_GLOBAL_H
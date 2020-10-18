#ifndef CORE_LTYCORE_GLOBAL_HPP
#define CORE_LTYCORE_GLOBAL_HPP

#include <QtCore/qglobal.h>

#if defined(LTYCORE_LIBRARY)
#  define LTYCORE_EXPORT Q_DECL_EXPORT
#else
#  define LTYCORE_EXPORT Q_DECL_IMPORT
#endif

#endif // CORE_LTYCORE_GLOBAL_HPP

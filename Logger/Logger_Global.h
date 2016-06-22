#ifndef LOGGER_GLOBAL_H
#define LOGGER_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef LOGGER_EXPORTS
# define LOGGER_IMPEXP Q_DECL_EXPORT
#else
# define LOGGER_IMPEXP Q_DECL_IMPORT
#endif

#endif //LOGGER_GLOBAL_H
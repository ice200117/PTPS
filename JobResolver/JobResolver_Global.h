#ifndef JOBRESOLVER_GLOBAL_H
#define JOBRESOLVER_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef JOBRESOLVER_EXPORTS
# define JOBRESOLVER_IMPEXP Q_DECL_EXPORT
#else
# define JOBRESOLVER_IMPEXP Q_DECL_IMPORT
#endif

#endif //PTPSAPP_GLOBAL_H
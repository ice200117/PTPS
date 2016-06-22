#ifndef PTPS_MASTER_GLOBAL_H
#define PTPS_MASTER_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef PTPS_MASTER_EXPORTS
# define PTPS_MASTER_IMPEXP Q_DECL_EXPORT
#else
# define PTPS_MASTER_IMPEXP Q_DECL_IMPORT
#endif

#endif //PTPSAPP_GLOBAL_H
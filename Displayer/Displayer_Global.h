#ifndef DISPLAYER_GLOBAL_H
#define DISPLAYER_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef DISPLAYER_EXPORTS
# define DISPLAYER_IMPEXP Q_DECL_EXPORT
#else
# define DISPLAYER_IMPEXP Q_DECL_IMPORT
#endif

#endif //DISPLAYER_GLOBAL_H
/*  =====================================================================
 *  mdwrkapi.h - Majordomo Protocol Worker API
 *  Implements the MDP/Worker spec at http://rfc.zeromq.org/spec:7.
 *  ===================================================================== */

#ifndef __MDWRKAPI_H_INCLUDED__
#define __MDWRKAPI_H_INCLUDED__

#include "czmq.h"
#include "mdp.h"

#ifdef __cplusplus
extern "C" {
#endif


#if defined _WINDOWS
#  define DECL_EXPORT    __declspec(dllexport) 
#  define DECL_IMPORT    __declspec(dllimport)
#else
#  define DECL_EXPORT     __attribute__((visibility("default")))
#  define DECL_IMPORT     __attribute__((visibility("default")))
#endif

#ifdef CZMQ_WORKER_EXPORTS
#define ZMQWORKER_EXPORT DECL_EXPORT
#else
#define ZMQWORKER_EXPORT DECL_IMPORT
#endif

//Opaque class structure
struct _mdwrk_t {
	zctx_t *ctx;                //  Our context
	char *broker;
	char *service;
	void *worker;               //  Socket to broker
	int verbose;                //  Print activity to stdout

	//  Heartbeat management
	uint64_t heartbeat_at;      //  When to send HEARTBEAT
	size_t liveness;            //  How many attempts left
	int heartbeat;              //  Heartbeat delay, msecs
	int reconnect;              //  Reconnect delay, msecs

	int expect_reply;           //  Zero only at start
	zframe_t *reply_to;         //  Return identity, if any
};

typedef struct _mdwrk_t mdwrk_t;

ZMQWORKER_EXPORT mdwrk_t *
	mdwrk_new (char *broker,char *service, int verbose);
ZMQWORKER_EXPORT zmsg_t *
	mdwrk_recv (mdwrk_t *self, zmsg_t **reply_p);
ZMQWORKER_EXPORT void
    mdwrk_destroy (mdwrk_t **self_p);
ZMQWORKER_EXPORT void
    mdwrk_set_liveness (mdwrk_t *self, int liveness);
ZMQWORKER_EXPORT void
    mdwrk_set_heartbeat (mdwrk_t *self, int heartbeat);
ZMQWORKER_EXPORT void
    mdwrk_set_reconnect (mdwrk_t *self, int reconnect);

ZMQWORKER_EXPORT void
	s_mdwrk_send_to_broker (mdwrk_t *self, char *command, char *option, zmsg_t *msg);

#ifdef __cplusplus
}
#endif

#endif

//  Majordomo Protocol worker example
//  Uses the mdwrk API to hide all MDP aspects
//  Lets us build this source without creating a library
//#include "mdwrkapi.c"
//#include "mdwrkapi.h"
//
//int main (int argc, char *argv [])
//{
//	zmsg_t *reply = 0;
//	mdwrk_t *session = 0;
//	zframe_t * lastFrame = 0;
//	char* lastMsg = 0;
//
//    int verbose = (argc > 1 && streq (argv [1], "-v"));
//	session = mdwrk_new ("tcp://localhost:5555", "echo", verbose);
//	if (!session) return 1;
//	
//    while (true) {
//        zmsg_t *request = mdwrk_recv (session, &reply);
//        if (request == NULL) break;              //  Worker was interrupted
//
//		////////////////////////////////////加入自己的雷达逻辑//////////////////////////////////
//
//		//解析收到的信息
//		lastFrame = zmsg_last(request);
//		lastMsg = zframe_strdup(lastFrame);
//
//		printf("zmsg_t::msg:%s\n", lastMsg);
//		printf("zmsg_t::size:%d\n", zmsg_content_size(request));
//
//		//
//		//
//		//
//		//
//
//		//建立回复信息
//		reply = zmsg_new ();
//		zmsg_pushstr (reply, "Done！");
//
//		////////////////////////////////////////////////////////////////////////////////////////
//
//		zmsg_destroy (&request);
//        //reply = request;        //  Echo is complex... :-)
//    }
//    mdwrk_destroy (&session);
//    return 0;
//}
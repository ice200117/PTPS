//  Majordomo Protocol client example
//  Uses the mdcli API to hide all MDP aspects

//  Lets us build this source without creating a library
//#include "mdcliapi.c"
#include "mdcliapi.h"

int main (int argc, char *argv [])
{
    int verbose = (argc > 1 && streq (argv [1], "-v"));
    mdcli_t *session = mdcli_new ("tcp://localhost:5555", verbose);
	zmsg_t *request;
	zmsg_t *reply;
    int count;

    //for (count = 0; count < 1; count++) {
        request = zmsg_new ();
        zmsg_pushstr (request, "KILL");
        reply = mdcli_send (session, "echo", &request);
        if (reply)
		{
			zframe_t * lastFrame = zmsg_last(reply);
			char* msg = zframe_strdup(lastFrame);
			printf("msg:%s\n", msg);
			printf("size:%d\n", zmsg_content_size(reply));
			//zframe_print(lastFrame,"->");
			zmsg_destroy (&reply);
		}
        //else
        //    break;              //  Interrupt or failure
    //}
    //printf ("%d requests/replies processed\n", count);
    mdcli_destroy (&session);
    return 0;
}

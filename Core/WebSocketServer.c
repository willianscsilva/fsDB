#include "WebSocketServer.h"
#include "JSONDataController.h"
#include "WsReturn.h"
#include <locale.h>

void listener_on_message (noPollCtx * ctx, noPollConn * conn, noPollMsg * msg, noPollPtr * user_data)
{
        *setlocale(LC_ALL,"");
        int shown, bytes, resultParse;
        bytes = nopoll_msg_get_payload_size (msg);
        shown = bytes;
        char content_msg[bytes];

        memset (content_msg, 0, bytes);
        memcpy (content_msg, (const char *) nopoll_msg_get_payload (msg), shown);
        // print the message (for debugging purposes) and reply
        /*printf ("Listener received (size: %d, ctx refs: %d): (first %d bytes, fragment: %d) '%s'\n",
                nopoll_msg_get_payload_size (msg),
                nopoll_ctx_ref_count (ctx), shown, nopoll_msg_is_fragment (msg), content_msg);*/

        // json to parse.
        wsJson = content_msg;
        jsonParse();
        char *returnClient = buildReturnToClientSide(wsReturn.wsArrayReturn, wsReturn.indexArrayReturn);
        // reply to the message
        nopoll_conn_send_text (conn, returnClient, strlen(returnClient));
        return;
}

void initWebSocketServer(char** params)
{
    host = params[2];
    port = params[3];
    printf("host: %s\n", host);
    printf("port: %s\n", port);
    noPollCtx * ctx = nopoll_ctx_new ();
    noPollConn * listener = nopoll_listener_new (ctx, host, port);
    if (! nopoll_conn_is_ok (listener)) {
     // some error handling here
    }
    nopoll_ctx_set_on_msg (ctx, listener_on_message, NULL);
    nopoll_loop_wait (ctx, 0);
    nopoll_ctx_unref (ctx);

}

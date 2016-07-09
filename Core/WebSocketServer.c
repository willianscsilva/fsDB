#include "WebSocketServer.h"
#include <locale.h>

void listener_on_message (noPollCtx * ctx, noPollConn * conn, noPollMsg * msg, noPollPtr * user_data)
{
        *setlocale(LC_ALL,"");
        int shown;
        int bytes;
        bytes = nopoll_msg_get_payload_size (msg);
        shown = bytes;
        char content_msg[bytes];

        memset (content_msg, 0, bytes);
        memcpy (content_msg, (const char *) nopoll_msg_get_payload (msg), shown);
        // print the message (for debugging purposes) and reply
        printf ("Listener received (size: %d, ctx refs: %d): (first %d bytes, fragment: %d) '%s'\n",
                nopoll_msg_get_payload_size (msg),
                nopoll_ctx_ref_count (ctx), shown, nopoll_msg_is_fragment (msg), content_msg);
        wsJson = content_msg;
        jsonParse();
        // reply to the message
        nopoll_conn_send_text (conn, "Successfully received message", 30);
        return;
}

void jsonParse()
{
    char *out;cJSON *json;
    json=cJSON_Parse(wsJson);
    if (!json) {printf("Error before: [%s]\n",cJSON_GetErrorPtr());}
    else
    {
        out=cJSON_Print(json);
        cJSON_Delete(json);
        printf("%s\n",out);
        free(out);
    }
}

int createCollection(const char *collectionName)
{
    int collectionExists;
    int collectionCreated;
    collectionExists = checkCollectionExists(collectionName);
    if(!collectionExists)
    {
        FILE * fp;
        fp = fopen( collectionName, "w" );
        if(fp != NULL)
        {
            collectionCreated = 1;
        }
        else
        {
            collectionCreated = 0;
        }
        fclose(fp);
    }
    else
    {
        collectionCreated = 0;
    }
    return collectionCreated;
}

int checkCollectionExists(const char *collectionName)
{
    FILE * fp;
    fp = fopen( collectionName, "r" );
    if(fp != NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
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

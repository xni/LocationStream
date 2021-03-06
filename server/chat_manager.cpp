//
// Created by Konstantin Nikitin on 06.06.15.
//

#include <signal.h>
#include <stdio.h>
#include <string.h>

#include <hiredis.h>
#include <async.h>
#include <adapters/libev.h>

#include "ChatRoom.h"

void connectCallback(const redisAsyncContext *c, int status) {
    if (status != REDIS_OK) {
        printf("Error: %s\n", c->errstr);
        return;
    }
    printf("Connected...\n");
}

void disconnectCallback(const redisAsyncContext *c, int status) {
    if (status != REDIS_OK) {
        printf("Error: %s\n", c->errstr);
        return;
    }
    printf("Disconnected...\n");
}

void getCallback(redisAsyncContext *c, void *r, void *privdata) {
    redisReply *reply = (redisReply*)r;
    if (reply == NULL) return;
    if ( reply->type == REDIS_REPLY_ARRAY && reply->elements == 3 ) {
        if ( strcmp( reply->element[0]->str, "subscribe" ) != 0 ) {
            printf( "Received[%s] channel %s: %s\n",
                    (char*)privdata,
                    reply->element[1]->str,
                    reply->element[2]->str );
        }
    }
}

int main() {
    signal(SIGPIPE, SIG_IGN);

    redisAsyncContext *c = redisAsyncConnect("127.0.0.1", 6379);
    if (c->err) {
        /* Let *c leak for now... */
        printf("Error: %s\n", c->errstr);
        return 1;
    }

    redisLibevAttach(EV_DEFAULT_ c);
    redisAsyncSetConnectCallback(c,connectCallback);
    redisAsyncSetDisconnectCallback(c,disconnectCallback);

    // redisAsyncCommand(c, getCallback, (char*)"sub", "SUBSCRIBE name");
    new ChatRoom(c, {"79153060652", "79030072726", "79853672651"});
    ev_loop(EV_DEFAULT_ 0);
    return 0;
}

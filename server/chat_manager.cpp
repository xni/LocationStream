//
// Created by Konstantin Nikitin on 06.06.15.
//

#include <signal.h>
#include <stdio.h>

#include <hiredis.h>
#include <async.h>
#include <adapters/libev.h>

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
    printf("argv[%s]: %d %s\n", (char*)privdata, reply->type, reply->str);
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

    redisAsyncCommand(c, getCallback, (char*)"end-1", "SUBSCRIBE name");
    ev_loop(EV_DEFAULT_ 0);
    return 0;
}

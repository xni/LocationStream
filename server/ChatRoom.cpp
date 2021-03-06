//
// Created by Konstantin Nikitin on 07.06.15.
//

#include "ChatRoom.h"

#include <async.h>
#include <string.h>
#include <stdio.h>

#include <functional>
#include <sstream>

#include <boost/bind.hpp>


ChatRoom::ChatRoom(redisAsyncContext* context,
                   const Participants& participants) :
    _participants(participants) {
  for (const auto& participant : _participants) {
    // TODO: check that channel name contains only letters.
    std::ostringstream command;
    command << "SUBSCRIBE ";
    command << participant;
    redisAsyncCommand(context, &ChatRoom::CallbackWrapper, this,
                      command.str().c_str());
  }
}

void ChatRoom::ParticipantMovedCallback(redisAsyncContext* context, void* r) {
  redisReply* reply = (redisReply*)r;
  if (reply == NULL)
    return;
  if (reply->type == REDIS_REPLY_ARRAY && reply->elements == 3) {
    if (strcmp(reply->element[0]->str, "subscribe") != 0) {
      SendUpdates(reply->element[1]->str, reply->element[2]->str);
    }
  }
}

void ChatRoom::SendUpdates(const char* const initiator,
                           const char* const position) {
  for (const auto& participant : _participants) {
    if (participant == initiator)
      continue;
    printf("Sending info about %s to %s\n", initiator, participant.c_str());
  }
}

// static
void ChatRoom::CallbackWrapper(redisAsyncContext* context, void* reply,
                               void* privdata) {
  ((ChatRoom*)privdata)->ParticipantMovedCallback(context, reply);
}

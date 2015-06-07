//
// Created by Konstantin Nikitin on 07.06.15.
//

#ifndef LOCATIONSTREAMSERVER_CHATROOM_H
#define LOCATIONSTREAMSERVER_CHATROOM_H

#include <string>
#include <vector>

class redisAsyncContext;


class ChatRoom {
 public:
  typedef std::vector<std::string> Participants;
  ChatRoom(redisAsyncContext* context, const Participants& participants);

 private:
  static void CallbackWrapper(redisAsyncContext* context, void* reply, void* privdata);
  void ParticipantMovedCallback();
  void SendUpdates(const char* const initiator, const char* const position);
  const Participants _participants;

};


#endif //LOCATIONSTREAMSERVER_CHATROOM_H

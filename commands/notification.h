#include <ProtocolBuffersStream.h>
#include <SensorflowListener.h>
#include "proto/sf.pb.h"
#include "proto/util.h"

#define NOTIFICATION_COMMAND "sfn"
#define EMPTY_NOTIFICATION "none"
void commandGetNotification(SensorflowListener *listener){
  if(listener->notifications.empty()) {
      Notification n;
      //char buffer[1] = {0};
      n.what.funcs.encode = &encode_string_callback;
      n.what.arg = (void *)EMPTY_NOTIFICATION;
      listener->send(Notification_fields, &n);
  } else {
    Notification n = listener->notifications.front();
    listener->notifications.pop();
    listener->setInterrupt(!listener->notifications.empty());
    listener->send(Notification_fields, &n);
  }
}
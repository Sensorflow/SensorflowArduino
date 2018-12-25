#include <ProtocolBuffersStream.h>
#include <SensorflowListener.h>
#include "proto/command_sf.pb.h"


void commandGetNotification(SensorflowListener *listener){
  if(listener->notifications.empty()) {
      Notification n;
      n.what = Notification_NotificationType_NONE;
      listener->send(Notification_fields, &n);
  } else {
    Notification n = listener->notifications.front();
    listener->notifications.pop();
    listener->setInterrupt(!listener->notifications.empty());
    listener->send(Notification_fields, &n);
  }
}
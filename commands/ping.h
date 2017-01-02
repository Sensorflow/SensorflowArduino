#include <ProtocolBuffersStream.h>
#include <SensorflowListener.h>
#include "proto/command_sf.pb.h"



void commandPing(SensorflowListener *listener){
  Ping p = {};
  listener->receive(Ping_fields, &p);
  p.value++;
  listener->send(Ping_fields, &p);
}

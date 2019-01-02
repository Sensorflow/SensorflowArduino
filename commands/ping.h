#include <SensorflowListener.h>
#include "proto/sf.pb.h"

#define PING_COMMAND "sfp"

void commandPing(SensorflowListener *listener){
  Ping p = {};
  listener->receive(Ping_fields, &p);
  p.value++;
  listener->send(Ping_fields, &p);
}

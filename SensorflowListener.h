
#include <Arduino.h>
#include <pb_encode.h>
#include <pb_decode.h>
#include <ProtocolBuffersStream.h>

#ifndef SENSORFLOWLISTENER_H
#define SENSORFLOWLISTENER_H

#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__) || defined(__AVR_ATmega328P__)
#include <StandardCplusplus.h>
#endif

#undef abs
#include <map>
#include <vector>
#include <queue>
#include "Sensor.h"
#include "proto/command_sf.pb.h"


using namespace std;

struct cmp_str
{
   bool operator()(char const *a, char const *b)
   {
      return strcmp(a, b) < 0;
   }
};

typedef std::map<const char*, Sensor*, cmp_str> Devices;
class SensorflowListener;
typedef void (*commandFunction)(SensorflowListener *listener);

struct AvailableCommand {
  int command;
  commandFunction fun;
};

typedef std::vector<AvailableCommand> Commands;

struct AvailableDevice {
    const char *name;
    Sensor* (*fun)(void *data);
};

class SensorflowListener {
  private:
    int interruptPin_;
    int csPin_;
    int max485WritePin_;
    ProtocolBuffersStream *messenger_;
    static void wakeUpNow();
  public:
    /* The manage of max485 is temporally. Later I will move to a more generic way */
    SensorflowListener(Stream *stream, int interruptPin, int csPin, int max485WritePin, unsigned int timeout = 1000);
    Devices devices;
    Commands commands;
    std::queue<Notification> notifications;
    bool send(const pb_field_t fields[], const void *src_struct);
    bool receive(const pb_field_t fields[], void *dest_struct);
    void notify(Notification notification);
    void setInterrupt(bool activated);
    bool next(bool sleepWhenInactive=true);
    void online();
    void sleepNow();
};

#endif //SENSORFLOWLISTENER_H

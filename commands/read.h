#include <SensorflowListener.h>
#include "proto/sf.pb.h"
#include "Sensor.h"
#include "proto/util.h"

#include <vector>
using namespace std;

#define READ_COMMAND "sfr"
#define READ_ALL_COMMAND "sfra"

void commandRead(SensorflowListener *listener){

  SensorRead r = {};
  SensorName sn = {};
  char buffer[50];
  sn.name.funcs.decode = &decode_string;
  sn.name.arg = buffer;

  listener->receive(SensorName_fields, &sn);
  if (listener->devices.find(buffer) != listener->devices.end() ) {
    Sensor *sensor = listener->devices[buffer];
    r.name.funcs.encode = &encode_string_callback;
    r.name.arg = (void *)sensor->getName();

    r.values.funcs.encode = &encode_numbers_list;
    unsigned int totalRead;
    float *v = sensor->getValues(ALL, &totalRead);
    vector<float> values;
    for(unsigned int i=0; i < totalRead; i++){
      values.push_back(v[i]);
    }
    r.values.arg = &values;
  }

  listener->send(SensorRead_fields, &r);

}

void commandReadAll(SensorflowListener *listener){

  SensorReadList l = SensorReadList_init_zero;

  vector<Sensor*> myarray;
  //Cosa a = {"hola"};
  //a.values.push_back(45.65);
  Devices::iterator it;
  for ( it = listener->devices.begin(); it != listener->devices.end(); it++ )
  {
      myarray.push_back(it->second);
  }

  l.reads.funcs.encode = &encode_sensors_callback;
  l.reads.arg = &myarray;
  listener->send(SensorReadList_fields, &l);

}

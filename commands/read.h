#include <SensorflowListener.h>
#include "proto/command_sf.pb.h"
#include "Sensor.h"

#include <vector>
using namespace std;

bool encode_string_callback(pb_ostream_t *stream, const pb_field_t *field, void * const *arg)
{
  char *str = (char *)*arg;
    if (!pb_encode_tag_for_field(stream, field))
        return false;

    return pb_encode_string(stream, (uint8_t*)str, strlen(str));
}



bool encode_numbers_list(pb_ostream_t *stream, const pb_field_t *field, void * const *arg)
{
    vector<float> *data = (vector<float> *)*arg;

    for (vector<float>::iterator it = data->begin() ; it != data->end(); ++it){
      if (!pb_encode_tag_for_field(stream, field))
          return false;
      #if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__) || defined(__AVR_ATmega328P__)
      if (!pb_encode_fixed32(stream, (void *)it))
          return false;
      #else
      if (!pb_encode_fixed32(stream, (void *)&it))
          return false;
      #endif
    }

    return true;
}

bool encode_sensors_callback(pb_ostream_t *stream, const pb_field_t *field, void * const *arg)
{
  vector<Sensor*> *myvector = (vector<Sensor*> *)*arg;
  SensorRead s = {};
  for (vector<Sensor*>::iterator it = myvector->begin() ; it != myvector->end(); ++it){
    Sensor* sensor = *it;
    s.name.funcs.encode = &encode_string_callback;
    s.name.arg = (void *)(sensor->getName());

    s.values.funcs.encode = &encode_numbers_list;
    unsigned int totalRead;
    float *v = sensor->getValues(ALL, &totalRead);
    vector<float> values;
    for(unsigned int i=0; i < totalRead; i++){
      values.push_back(v[i]);
    }
    s.values.arg = &values;
    if (!pb_encode_tag_for_field(stream, field))
        return false;

    if (!pb_encode_submessage(stream, SensorRead_fields, &s))
        return false;
  }

  return true;
}


bool decode_string(pb_istream_t *stream, const pb_field_t *field, void **arg)
{

    uint8_t *buffer = (uint8_t *)*arg;
    // We could read block-by-block to avoid the large buffer...
    // Como no se sabe el tamano real de buffer, no se hace esta comprobacion
    //if (stream->bytes_left > sizeof(buffer) - 1)
    //    return false;
    buffer[stream->bytes_left] = 0;
    if (!pb_read(stream, buffer, stream->bytes_left))
        return false;

    return true;
}

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

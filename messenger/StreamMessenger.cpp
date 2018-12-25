#include "StreamMessenger.h"

StreamMessenger::StreamMessenger(Stream *stream, int interruptPin, int timeout) {
    interruptPin_ = interruptPin;
    protoStream_ = new ProtocolBuffersStream(stream, timeout);
}

bool StreamMessenger::send(const pb_field_t fields[], const void *src_struct){
    bool status = protoStream_->send(fields, src_struct);
    Serial.flush();
    return status;
}

bool StreamMessenger::receive(const pb_field_t fields[], void *src_struct){
    return protoStream_->receive(fields, src_struct);
}

void StreamMessenger::interrupt(bool activated) {
  if(activated) {
    digitalWrite(interruptPin_, HIGH);
  } else {
    digitalWrite(interruptPin_, LOW);
  }
}
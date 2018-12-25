#include <Messenger.h>

#ifndef STREAM_MESSENGER_H
#define STREAM_MESSENGER_H

#include <ProtocolBuffersStream.h>

class StreamMessenger: public Messenger{
private:
    ProtocolBuffersStream *protoStream_;
    int interruptPin_;
public:
    StreamMessenger(Stream *stream, int interruptPin, int timeout=1000);
    bool send(const pb_field_t fields[], const void *src_struct);
    bool receive(const pb_field_t fields[], void *src_struct);
    void interrupt(bool activated);
};

#endif //STREAM_MESSENGER_H

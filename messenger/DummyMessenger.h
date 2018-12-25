#include <Messenger.h>

#ifndef DUMMY_MESSENGER_H
#define DUMMY_MESSENGER_H

class DummyMessenger: public Messenger{
public:
    bool send(const pb_field_t fields[], const void *src_struct);
    bool receive(const pb_field_t fields[], const void *src_struct);
    void interrupt(bool enabled);
};

#endif //DUMMY_MESSENGER_H

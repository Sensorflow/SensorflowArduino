//
// Created by alvaro on 8/08/15.
//

#ifndef MESSENGER_H
#define MESSENGER_H

#include <pb_encode.h>
#include <pb_decode.h>

class Messenger {
public:
    virtual bool send(const pb_field_t fields[], const void *src_struct);
    virtual bool receive(const pb_field_t fields[], void *src_struct);
    virtual void interrupt(bool enabled);
};

#endif //MESSENGER_H



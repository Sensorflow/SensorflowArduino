#include "DummyMessenger.h"


bool DummyMessenger::send(const pb_field_t fields[], const void *src_struct){
    return true;
}

bool DummyMessenger::receive(const pb_field_t fields[], const void *src_struct){
    return true;
}

void DummyMessenger::interrupt(bool enabled){
    
}


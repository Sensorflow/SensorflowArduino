/* Automatically generated nanopb constant definitions */
/* Generated by nanopb-0.3.7 at Thu Dec 22 00:43:58 2016. */

#include "command_sf.pb.h"

/* @@protoc_insertion_point(includes) */
#if PB_PROTO_HEADER_VERSION != 30
#error Regenerate this file with the current version of nanopb generator.
#endif



const pb_field_t Command_fields[2] = {
    PB_FIELD(  1, UENUM   , SINGULAR, STATIC  , FIRST, Command, command, command, 0),
    PB_LAST_FIELD
};

const pb_field_t SensorRead_fields[3] = {
    PB_FIELD(  1, STRING  , SINGULAR, CALLBACK, FIRST, SensorRead, name, name, 0),
    PB_FIELD(  2, FLOAT   , REPEATED, CALLBACK, OTHER, SensorRead, values, name, 0),
    PB_LAST_FIELD
};

const pb_field_t SensorName_fields[2] = {
    PB_FIELD(  1, STRING  , SINGULAR, CALLBACK, FIRST, SensorName, name, name, 0),
    PB_LAST_FIELD
};

const pb_field_t Ping_fields[2] = {
    PB_FIELD(  1, INT32   , SINGULAR, STATIC  , FIRST, Ping, value, value, 0),
    PB_LAST_FIELD
};

const pb_field_t SensorReadList_fields[2] = {
    PB_FIELD(  1, MESSAGE , REPEATED, CALLBACK, FIRST, SensorReadList, reads, reads, &SensorRead_fields),
    PB_LAST_FIELD
};

const pb_field_t Notification_fields[2] = {
    PB_FIELD(  1, UENUM   , SINGULAR, STATIC  , FIRST, Notification, what, what, 0),
    PB_LAST_FIELD
};


/* @@protoc_insertion_point(eof) */

#include <Arduino.h>

#include "SensorflowListener.h"
#include "commands/ping.h"
#include "commands/read.h"
#include "commands/notification.h"
#include "proto/sf.pb.c"
#include "proto/util.h"
#include <avr/sleep.h>
#include <messenger/StreamMessenger.h>

#define NOTIFICATION_ONLINE "online"

SensorflowListener::SensorflowListener(Messenger *messenger){
  messenger_ = messenger;
  // Add default commands
  commands[PING_COMMAND] = (AvailableCommand {&commandPing});
  commands[READ_COMMAND] = (AvailableCommand {&commandRead});
  commands[READ_ALL_COMMAND] = (AvailableCommand {&commandReadAll});
  commands[NOTIFICATION_COMMAND] = (AvailableCommand {&commandGetNotification});
}

bool SensorflowListener::send(const pb_field_t fields[], const void *src_struct){
  bool status = messenger_->send(fields, src_struct);
  return status;
}

bool SensorflowListener::receive(const pb_field_t fields[], void *dest_struct){
  bool status = messenger_->receive(fields, dest_struct);
  return status;
}

bool SensorflowListener::next(bool sleepWhenInactive){
  if(sleepWhenInactive) {
    sleepNow();
  } else {
    Command c = Command_init_zero;
    char buffer[50];
    c.command.funcs.decode = &decode_string;
    c.command.arg = buffer;
    if(receive(Command_fields, &c)) {
      Commands::iterator it = commands.find(buffer);
      if (it != commands.end()) {
          it->second.fun(this);
          return true;
      }
    }
  }
  return false;
}

void SensorflowListener::setInterrupt(bool activated){
  messenger_->interrupt(activated);
}

void SensorflowListener::notify(Notification notification){
  setInterrupt(true);
  notifications.push(notification);
}

void SensorflowListener::online(){
  Notification n;
  n.what.funcs.encode = &encode_string_callback;
  n.what.arg = (void *)NOTIFICATION_ONLINE;
  notify(n);
}


void SensorflowListener::wakeUpNow(){

}

void SensorflowListener::sleepNow()
{
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    // El 1 es es el del pin 3
    attachInterrupt(1,wakeUpNow, RISING);
    sleep_mode();
                             // THE PROGRAM CONTINUES FROM HERE AFTER WAKING UP
    sleep_disable();         // first thing after waking from sleep:
    detachInterrupt(0);
}

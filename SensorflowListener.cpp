#include <Arduino.h>

#include "SensorflowListener.h"
#include "commands/ping.h"
#include "commands/read.h"
#include "commands/notification.h"
#include "proto/command_sf.pb.c"
#include <avr/sleep.h>
#include <messenger/StreamMessenger.h>

SensorflowListener::SensorflowListener(Messenger *messenger){
  messenger_ = messenger;
  // Add default commands
  commands.push_back(AvailableCommand {Command_CommandType_PING, &commandPing});
  commands.push_back(AvailableCommand {Command_CommandType_READ, &commandRead});
  commands.push_back(AvailableCommand {Command_CommandType_READ_ALL, &commandReadAll});
  commands.push_back(AvailableCommand {Command_CommandType_NOTIFICATION, &commandGetNotification});
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
    if(receive(Command_fields, &c)) {
      bool found = false;
      for (Commands::iterator it = commands.begin() ; !found && it != commands.end(); ++it){
        if(it->command == c.command){
          found = true;
          it->fun(this);
        }
      }
      return found;
    } else{
      return false;
    }
  }
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
  n.what = Notification_NotificationType_ONLINE;
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

#include "exp_pedal.h"
#include "controller_system.h"
#include "warnings.h"

DIAGNOSTIC_IGNORE_ALL
#include <MIDIUSB.h>
DIAGNOSTIC_POP

void ExpPedal::midi_send(uint8_t val)
{
  uint8_t usb_header = 0x0B;
  uint8_t status = 0xB0|pt_controller_system_->get_midi_channel();
  uint8_t data0 = get_command();
  uint8_t data1 = val;
  Serial1.write(status);
  Serial1.write(data0);
  Serial1.write(data1);
  midiEventPacket_t event = {
    usb_header,
    status,
    data0,
    data1,
  };
  MidiUSB.sendMIDI(event);
  Serial1.flush();
  MidiUSB.flush();
}

ExpPedal::ExpPedal()
  : command_(0)
  , mode_(expMode::normal)
  , exp_pin_(0)
  , change_delay_millis_(0)
{}

void ExpPedal::setup(uint8_t exp_pin, ControllerSystem* pt_controller_system)
{
  exp_pin_= exp_pin;
  pinMode(exp_pin_, INPUT);
  old_exp_val_ = analogRead(exp_pin_);
  pt_controller_system_ = pt_controller_system;
}

void ExpPedal::set_command(uint8_t command)
{
  command_ = command;
  if (command_ > 127) command_ = 0;
}

void ExpPedal::set_mode(uint8_t mode)
{
  mode_ = mode;
  if (mode_ > 127) mode_ = 0;
}

ExpConfig ExpPedal::get_config()
{
  ExpConfig res;
  res.command = get_command();
  res.mode = get_mode();
  return res;
}

void ExpPedal::set_config(ExpConfig conf)
{
  set_command(conf.command);
  set_mode(conf.mode);
}

void ExpPedal::process()
{
  int16_t cur_exp_val= analogRead(exp_pin_);
  unsigned long cur_millis = millis();

//  Serial.print(" exp val : ");
//  Serial.print(cur_exp_val, DEC);
//  Serial.print("\r\n");
//  if (old_exp_val_ != cur_exp_val)
  if ((cur_millis - change_delay_millis_) > changeDelayTime_)
  {
    int16_t diff = abs(cur_exp_val - old_exp_val_);
    if (diff > dead_zone_)
    {
      change_delay_millis_ = cur_millis;
      switch(mode_)
      {
        case expMode::normal:
          midi_send(cur_exp_val/8);
          break;
        case expMode::reverse:
          midi_send((1023-cur_exp_val)/8);
          break;
      }
      old_exp_val_ = cur_exp_val;
    }
  }
}


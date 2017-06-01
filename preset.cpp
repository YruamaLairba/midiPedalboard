#include "preset.h"

#ifdef DEBUG
#include <Arduino.h>
#endif //DEBUG

//ctor
Preset::Preset(){}

//void Preset::init()
//{
//}

FsMode Preset::get_fsMode(uint8_t fsNumber)
{
  if (fsNumber < nbFsConfigs)
  {
    return fsConfigs[fsNumber].fsMode;
  }
  else
  {
    return 0xFF; //error code
  }
}

void Preset::set_fsMode(uint8_t fsNumber, FsMode fsMode)
{
  if (fsNumber < nbFsConfigs)
  {
    if (fsConfigs[fsNumber].fsMode != fsMode)
    {
      fsConfigs[fsNumber].fsMode = fsMode;
      isModified = true;
#ifdef DEBUG
      Serial.print("setting fs mode: fs ");
      Serial.print(fsNumber,DEC);
      Serial.print(" ,mode ");
      Serial.print(fsMode,DEC);
      Serial.print("\n\r");
#endif //DEBUG
    }
  }
  return;
}

FsCommand Preset::get_fsCommand(uint8_t fsNumber)
{
  if (fsNumber < nbFsConfigs)
  {
    return fsConfigs[fsNumber].fsCommand;
  }
  else
  {
    return 0xFF; //error code
  }
}

void Preset::set_fsCommand(uint8_t fsNumber, FsCommand fsCommand)
{
  if (fsNumber < nbFsConfigs)
  {
    if(fsConfigs[fsNumber].fsCommand != fsCommand)
    {
      fsConfigs[fsNumber].fsCommand = fsCommand;
      isModified = true;
#ifdef DEBUG
      Serial.print("setting fs command: fs ");
      Serial.print(fsNumber,DEC);
      Serial.print(" ,command ");
      Serial.print(fsCommand,DEC);
      Serial.print("\n\r");
#endif //DEBUG
    }
  }
  return;
}

ExpMode Preset::get_expMode(uint8_t expNumber)
{
  if (expNumber < nbExpConfigs)
  {
    return expConfigs[expNumber].expMode;
  }
  else
  {
    return 0xFF; //error code
  }
}

void Preset::set_expMode(uint8_t expNumber, ExpMode expMode)
{
  if (expNumber < nbExpConfigs)
  {
    if (expConfigs[expNumber].expMode != expMode)
    {
      expConfigs[expNumber].expMode = expMode;
      isModified = true;
    }
  }
  return;
}

ExpCommand Preset::get_expCommand(uint8_t expNumber)
{
  if (expNumber < nbExpConfigs)
  {
    return expConfigs[expNumber].expCommand;
  }
  else
  {
    return 0xFF; //error code
  }
}

void Preset::set_expCommand(uint8_t expNumber, ExpCommand expCommand)
{
  if (expNumber < nbExpConfigs)
  {
    if (expConfigs[expNumber].expCommand != expCommand)
    {
      expConfigs[expNumber].expCommand = expCommand;
      isModified = true;
    }
  }
  return;
}

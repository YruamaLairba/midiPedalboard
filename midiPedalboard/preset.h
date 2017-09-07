#ifndef PRESET_H
#define PRESET_H

#include <stdint.h>
#include "setup.h"
#include "footswitch.h"
#include "EEPROM.h"

typedef uint8_t FsMode;
typedef uint8_t FsCommand;
struct FsConfig
{
  FsMode fsMode;
  FsCommand fsCommand;
};

typedef uint8_t ExpMode;
typedef uint8_t ExpCommand;
struct ExpConfig
{
  ExpMode expMode;
  ExpCommand expCommand;
};

#warning "replace litteral values by an abstract value"
class Preset
{
  private:
    struct
    {
      FsConfig fsConfigs [nbFs];
      ExpConfig expConfigs [nbExp];
    }eepromData;
    static const uint8_t nbPreset = (E2END + 1)/sizeof(eepromData);
    uint8_t number; //number of the currently loaded preset
    bool isModified; //is the current preset modified ?
  public:
    Preset();

    //void init(); //for startup initialization

    FsMode get_fsMode(uint8_t fsNumber);
    void set_fsMode(uint8_t fsNumber, FsMode fsMode);
    FsCommand get_fsCommand(uint8_t fsNumber);
    void set_fsCommand(uint8_t fsNumber, FsCommand fsCommand);
    ExpMode get_expMode(uint8_t expNumber);
    void set_expMode(uint8_t expNumber, ExpMode expMode);
    ExpCommand get_expCommand(uint8_t expNumber);
    void set_expCommand(uint8_t expNumber, ExpCommand expCommand);

    void save(uint8_t presetNumber);
    void load(uint8_t presetNumber);
    uint8_t get_nbPreset(){return nbPreset;};
    uint8_t get_presetNumber(){return number;};
    bool isMofified(){return isModified;};
};
#endif //PRESET_H

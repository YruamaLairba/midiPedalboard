#ifndef MENU_SYSTEM_H
#define MENU_SYSTEM_H

#include "setup.h"
#include "rotary_encoder.h"
#include "push_button.h"
#include "footswitch.h"
#include "exp_pedal.h"
#include "controller_system.h"
#include "warnings.h"
#include "display.h"

DIAGNOSTIC_IGNORE_ALL
#ifdef DEBUG
#include <Arduino.h>
#endif //DEBUG
DIAGNOSTIC_POP

class MenuBase;
class MenuConf;
class MenuSystem;

class MenuSystem
{
  class MenuBase
  {
    protected:
      MenuSystem* pt_menu_system_;
    public:
      MenuBase(MenuSystem* pt_menu_system);
      virtual void select_next() = 0;
      virtual void select_prev() = 0;
      virtual void validate() = 0;
      virtual void cancel() = 0;
      virtual void print() = 0;
      //i need to refresh some menu when exp val change
      virtual void exp_refresh(uint8_t exp_num) = 0;
  };

  class MenuTemplate : public MenuBase
  {
    protected:
      uint8_t selection_;
      uint8_t display_offset_;
      virtual uint8_t get_nb_item() = 0;
      virtual void reset();
    public:
      MenuTemplate(MenuSystem* menu_system);
      virtual void select_next();
      virtual void select_prev();

      //this function does nothing here
      virtual void exp_refresh(uint8_t exp_num);
  };

  // for menus with a parent
  class SubMenuTemplate : public MenuTemplate
  {
    protected:
      MenuBase* pt_parent_;
    public:
      SubMenuTemplate(MenuSystem* pt_menu_system, MenuBase* pt_parent);
      virtual void activate();
      virtual void cancel();
  };

  class MenuControllerSetting;

  class MenuFsCmdTyp : public SubMenuTemplate
  {
    private:
      MenuControllerSetting* pt_menu_controller_setting_;
      uint8_t get_nb_item();
    public:
      MenuFsCmdTyp(
          MenuSystem* pt_menu_system,
          MenuBase* pt_parent,
          MenuControllerSetting* pt_menu_controller_setting);
      virtual void activate();
      virtual void validate();
      virtual void print();
  };

  class MenuFsCCVal : public SubMenuTemplate
  {
    private:
      MenuControllerSetting* pt_menu_controller_setting_;
      uint8_t get_nb_item();
    public:
      MenuFsCCVal(
          MenuSystem* pt_menu_system,
          MenuBase* pt_parent,
          MenuControllerSetting* pt_menu_controller_setting);
      virtual void activate();
      virtual void validate();
      virtual void print();
  };

  class MenuFsPGMVal : public SubMenuTemplate
  {
    private:
      MenuControllerSetting* pt_menu_controller_setting_;
      uint8_t get_nb_item();
    public:
      MenuFsPGMVal(
          MenuSystem* pt_menu_system,
          MenuBase* pt_parent,
          MenuControllerSetting* pt_menu_controller_setting);
      virtual void activate();
      virtual void validate();
      virtual void print();
  };

  class MenuFsMMCVal : public SubMenuTemplate
  {
    private:
      MenuControllerSetting* pt_menu_controller_setting_;
      uint8_t get_nb_item();
    public:
      MenuFsMMCVal(
          MenuSystem* pt_menu_system,
          MenuBase* pt_parent,
          MenuControllerSetting* pt_menu_controller_setting);
      virtual void activate();
      virtual void validate();
      virtual void print();
  };


  class MenuFsMode : public SubMenuTemplate
  {
    private:
      MenuControllerSetting* pt_menu_controller_setting_;
      uint8_t get_nb_item();
    public:
      MenuFsMode(
          MenuSystem* pt_menu_system,
          MenuBase* pt_parent,
          MenuControllerSetting* pt_menu_controller_setting);
      virtual void activate();
      virtual void validate();
      virtual void print();
  };

  class MenuFsSetting : public SubMenuTemplate
  {
    private:
      MenuFsCmdTyp menu_fs_cmd_typ_;
      MenuFsCCVal menu_fs_cc_val_;
      MenuFsPGMVal menu_fs_pgm_val_;
      MenuFsMMCVal menu_fs_mmc_val_;
      MenuFsMode menu_fs_mode_;
      MenuControllerSetting* pt_menu_controller_setting_;
      uint8_t get_nb_item();
    public:
      MenuFsSetting(
          MenuSystem* pt_menu_system,
          MenuBase* pt_parent,
          MenuControllerSetting* pt_menu_controller_setting);
      virtual void validate();
      virtual void print();
  };

  class MenuExpCmdTyp : public SubMenuTemplate
  {
    private:
      MenuControllerSetting* pt_menu_controller_setting_;
      uint8_t get_nb_item();
    public:
      MenuExpCmdTyp(
          MenuSystem* pt_menu_system,
          MenuBase* pt_parent,
          MenuControllerSetting* pt_menu_controller_setting);
      virtual void activate();
      virtual void validate();
      virtual void print();
  };

  class MenuExpCommand : public SubMenuTemplate
  {
    private:
      MenuControllerSetting* pt_menu_controller_setting_;
      uint8_t get_nb_item();
    public:
      MenuExpCommand(
          MenuSystem* pt_menu_system,
          MenuBase* pt_parent,
          MenuControllerSetting* pt_menu_controller_setting);
      virtual void activate();
      virtual void validate();
      virtual void print();
  };

  class MenuExpMode : public SubMenuTemplate
  {
    private:
      MenuControllerSetting* pt_menu_controller_setting_;
      uint8_t get_nb_item();
    public:
      MenuExpMode(
          MenuSystem* pt_menu_system,
          MenuBase* pt_parent,
          MenuControllerSetting* pt_menu_controller_setting);
      virtual void activate();
      virtual void validate();
      virtual void print();
  };

  class MenuExpSetting : public SubMenuTemplate
  {
    private:
      MenuExpCmdTyp menu_exp_cmd_typ_;
      MenuExpCommand menu_exp_command_;
      MenuExpMode menu_exp_mode_;
      MenuControllerSetting* pt_menu_controller_setting_;
      uint8_t get_nb_item();
    public:
      MenuExpSetting(
          MenuSystem* pt_menu_system,
          MenuBase* pt_parent,
          MenuControllerSetting* pt_menu_controller_setting);
      virtual void validate();
      virtual void print();
  };

  //menu to select a controller
  class MenuControllerSetting : public SubMenuTemplate
  {
    private:
      MenuFsSetting menu_fs_setting_;
      MenuExpSetting menu_exp_setting_;
      uint8_t get_nb_item();
    public:
      MenuControllerSetting(MenuSystem* menu_system, MenuBase* pt_parent);
      virtual void validate();
      virtual void print();

      uint8_t get_selected_fs();
      uint8_t get_selected_exp();
  };

  class MenuPresetLoad : public SubMenuTemplate
  {
    private:
      uint8_t get_nb_item();
    public:
      MenuPresetLoad(MenuSystem* menu_system, MenuBase* pt_parent);
      virtual void activate();
      virtual void validate();
      virtual void print();
  };

  class MenuPresetSave : public SubMenuTemplate
  {
    private:
      uint8_t get_nb_item();
    public:
      MenuPresetSave(MenuSystem* menu_system, MenuBase* pt_parent);
      virtual void activate();
      virtual void validate();
      virtual void print();
  };

  class MenuMidiChannel : public SubMenuTemplate
  {
    private:
      uint8_t get_nb_item();
    public:
      MenuMidiChannel(MenuSystem* menu_system, MenuBase* pt_parent);
      virtual void activate();
      virtual void validate();
      virtual void print();
  };

  //Menu to calibrate toes position
  //TODO check if another base class is better
  class MenuToesCal : public SubMenuTemplate
  {
    private:
      uint8_t exp_num_;
      uint8_t get_nb_item();
    public:
      MenuToesCal(MenuSystem* menu_system, MenuBase* pt_parent);
      virtual void activate();
      virtual void validate();
      virtual void print();
      virtual void exp_refresh(uint8_t exp_num);
      void set_exp(uint8_t exp_num);
  };

  //Menu to calibrate heel position
  //TODO check if another base class is better
  class MenuHeelCal : public SubMenuTemplate
  {
    private:
      uint8_t exp_num_;
      uint8_t get_nb_item();
    public:
      MenuHeelCal(MenuSystem* menu_system, MenuBase* pt_parent);
      virtual void activate();
      virtual void validate();
      virtual void print();
      virtual void exp_refresh(uint8_t exp_num);
      void set_exp(uint8_t exp_num);
  };

  //Menu to calibrate an Exp
  class MenuExpXCal : public SubMenuTemplate
  {
    private:
      MenuToesCal menu_toes_cal_;
      MenuHeelCal menu_heel_cal_;
      uint8_t exp_num_;
      uint8_t get_nb_item();
    public:
      MenuExpXCal(MenuSystem* menu_system, MenuBase* pt_parent);
      virtual void activate();
      virtual void validate();
      virtual void print();
      void set_exp(uint8_t exp_num);
  };

  //Menu to selected Exp pedal to calibrate
  class MenuExpCalSel : public SubMenuTemplate
  {
    private:
      MenuExpXCal menu_exp_x_cal_;
      uint8_t get_nb_item();
    public:
      MenuExpCalSel(MenuSystem* menu_system, MenuBase* pt_parent);
      virtual void activate();
      virtual void validate();
      virtual void print();
  };

  class MenuGlobalSetting : public SubMenuTemplate
  {
    private:
      MenuMidiChannel menu_midi_channel_;
      MenuExpCalSel menu_exp_cal_sel_;
      uint8_t get_nb_item();
    public:
      MenuGlobalSetting(MenuSystem* menu_system, MenuBase* pt_parent);
      virtual void validate();
      virtual void print();
  };

  class MenuConf : public MenuTemplate
  {
    private:
      MenuControllerSetting menu_controller_setting_;
      MenuPresetLoad menu_preset_load_;
      MenuPresetSave menu_preset_save_;
      MenuGlobalSetting menu_global_setting_;
      uint8_t get_nb_item();
    public:
      MenuConf(MenuSystem* menu_system);
      virtual void validate();
      virtual void cancel();
      virtual void print();
  };

  private:
    MenuConf root_;
    MenuBase* pt_current_;
    RotaryEncoder rotary_encoder_;
    PushButton button_ok_;
    PushButton button_cancel_;
    ControllerSystem* pt_controller_system_;

    int16_t last_exp_val_[nbExp];

  public:
    MenuSystem(ControllerSystem* pt_controller_system);
    void init();
    void set_active(MenuBase* activated);
    void process();
};


#endif //MENU_SYSTEM_H

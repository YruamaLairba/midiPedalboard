#include "menus.h"


//MenuManager
void MenuManager::set_active(MenuBase* activated)
{
  pt_current = activated;
}


bool MenuManager::next()
{
  return pt_current->next();
}

bool MenuManager::prev()
{
  return pt_current->prev();
}

bool MenuManager::validate()
{
  return pt_current->validate();
}

bool MenuManager::cancel()
{
  return pt_current->cancel();
}

void MenuManager::print()
{
  pt_current->print();
}

void MenuFolder::activate()
{
  this->reset();
  manager->set_active(this);
}

bool MenuFolder::next()
{
  bool res = false;
  if (this->selection < this->nbItems -1)
  {
    this->selection++;
    res = true;
  }
  return res;
}

bool MenuFolder::prev()
{
  bool res = false;
  if (this->selection > 0)
  {
    this->selection--;
    res = true;
  }
  return res;
}

bool MenuFolder::validate()
{
  bool res = false;
  if(items[selection].item != NULL)
  {
    items[selection].item->activate();
    res = true;
  }
  return res;
}

bool MenuFolder::cancel()
{
  bool res = false;
  if(parent != NULL)
  {
    manager->set_active(parent);
    res = true;
  }
  return res;
}

bool MenuFolder::reset()
{
  selection = 0;
  return true;
}

void MenuFolder::print()
{
  
  for (int i = 0; i< nbItems; i++)
  {
    Serial.print(items[i].label);
    if (i == selection)
    {
      Serial.print("<<<");
    }
    Serial.print("\n\r");
  }
}



//typedef struct MenuManager MenuManager;
void MenuPresetLoad::activate()
{
  this->reset();
  manager->set_active(this);
}

bool MenuPresetLoad::next()
{
  bool res = false;
  if (this->selection < this->nbPreset -1)
  {
    this->selection++;
    res = true;
  }
  if (selection >= (displayOffset + 4 ))
  {
    displayOffset++;
  }
  return res;
}

bool MenuPresetLoad::prev()
{
  bool res = false;
  if (this->selection > 0)
  {
    this->selection--;
    res = true;
  }
  if (selection < displayOffset)
  {
    displayOffset--;
  }
  return res;
}

bool MenuPresetLoad::validate()
{
  Serial.print("Preset ");
  Serial.print(selection,DEC);
  Serial.print(" loaded\n\r");
  return true;
}

bool MenuPresetLoad::cancel()
{
  bool res = false;
  if(parent != NULL)
  {
    manager->set_active(parent);
    res = true;
  }
  return res;
}

bool MenuPresetLoad::reset()
{
  selection = 0;
  displayOffset = 0;
  return true;
}

void MenuPresetLoad::print()
{
  
  for (int i = displayOffset; i< (displayOffset + 4); i++)
  {
    Serial.print("Preset ");
    Serial.print(i,DEC);
    if (i == selection)
    {
      Serial.print("<<<");
    }
    Serial.print("\n\r");
  }
}


//MenuEnumSelect
void MenuEnumSelect::activate()
{
  this->reset();
  manager->set_active(this);
}

bool MenuEnumSelect::next()
{
  bool res = false;
  if (this->selection < this->nbItems -1)
  {
    this->selection++;
    res = true;
  }
  return res;
}

bool MenuEnumSelect::prev()
{
  bool res = false;
  if (this->selection > 0)
  {
    this->selection--;
    res = true;
  }
  return res;
}

bool MenuEnumSelect::validate()
{
  //TODO
  return true;
}

bool MenuEnumSelect::cancel()
{
  bool res = false;
  if(parent != NULL)
  {
    manager->set_active(parent);
    res = true;
  }
  return res;
}

bool MenuEnumSelect::reset()
{
  selection = 0;
  return true;
}

void MenuEnumSelect::print()
{
  Serial.print(items[selection]);
  Serial.print("\n\r");
}



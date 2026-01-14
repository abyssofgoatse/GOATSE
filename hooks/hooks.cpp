 

#include "hooks.h"
#include "common/common.h"

static rdcarray<LibraryHook *> &LibList()
{
  static rdcarray<LibraryHook *> libs;
  return libs;
}

LibraryHook::LibraryHook()
{
  LibList().push_back(this);
}

void LibraryHooks::RegisterHooks()
{
  BeginHookRegistration();

  for(LibraryHook *lib : LibList())
    lib->RegisterHooks();

  EndHookRegistration();
}

void LibraryHooks::RemoveHookCallbacks()
{
  for(LibraryHook *lib : LibList())
    lib->RemoveHooks();
}

void LibraryHooks::OptionsUpdated()
{
  for(LibraryHook *lib : LibList())
    lib->OptionsUpdated();
}

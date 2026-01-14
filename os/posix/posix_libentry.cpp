 

#include "core/core.h"
#include "hooks/hooks.h"
#include "os/os_specific.h"

void ResetHookingEnvVars();

// DllMain equivalent
void library_loaded()
{
  if(LibraryHooks::Detect(STRINGIZE(RDOC_BASE_NAME) "__replay__marker"))
  {
    RDCDEBUG("Not creating hooks - in replay app");

    RenderDoc::Inst().SetReplayApp(true);

    RenderDoc::Inst().Initialise();

    LibraryHooks::ReplayInitialise();

    return;
  }
  else
  {
    RenderDoc::Inst().Initialise();

    ResetHookingEnvVars();

    rdcstr capturefile = Process::GetEnvVariable("RENDERDOC_CAPFILE");
    rdcstr opts = Process::GetEnvVariable("RENDERDOC_CAPOPTS");

    if(!opts.empty())
    {
      CaptureOptions optstruct;
      optstruct.DecodeFromString(opts);

      RDCLOG("Using delay for debugger %u", optstruct.delayForDebugger);

      RenderDoc::Inst().SetCaptureOptions(optstruct);
    }

    if(!capturefile.empty())
    {
      RenderDoc::Inst().SetCaptureFileTemplate(capturefile);
    }

    rdcstr curfile;
    FileIO::GetExecutableFilename(curfile);

    RDCLOG("Loading into %s", curfile.c_str());

    LibraryHooks::RegisterHooks();

    // we have a short sleep here to allow target control to connect, since unlike windows we can't
    // suspend the process during startup.
    Threading::Sleep(15);
  }
}

// wrap in a struct to enforce ordering. This file is
// linked last, so all other global struct constructors
// should run first
struct init
{
  init() { library_loaded(); }
} do_init;

// we want to be sure the constructor and library_loaded are included even when this is in a static
// library, so we have this global function that does nothing but takes the address.
extern "C" __attribute__((visibility("default"))) void *force_include_libentry()
{
  return &do_init;
}

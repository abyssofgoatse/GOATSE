 

#include "api/replay/rdcstr.h"
#include "common/common.h"

#import <Cocoa/Cocoa.h>

#define MAX_COUNT_KEYS (65536)
static bool s_keysPressed[MAX_COUNT_KEYS];
static id s_eventMonitor;

void apple_InitKeyboard()
{
  s_eventMonitor =
      [NSEvent addLocalMonitorForEventsMatchingMask:(NSEventMaskKeyDown | NSEventMaskKeyUp)
                                            handler:^(NSEvent *incomingEvent) {
                                              NSEvent *result = incomingEvent;
                                              // NSWindow *targetWindowForEvent = [incomingEvent
                                              // window];
                                              // if (targetWindowForEvent == _window)
                                              {
                                                unsigned short keyCode = [incomingEvent keyCode];
                                                if([incomingEvent type] == NSEventTypeKeyDown)
                                                {
                                                  s_keysPressed[keyCode] = true;
                                                }
                                                if([incomingEvent type] == NSEventTypeKeyUp)
                                                {
                                                  s_keysPressed[keyCode] = false;
                                                }
                                              }
                                              return result;
                                            }];
}

bool apple_IsKeyPressed(int appleKeyCode)
{
  return s_keysPressed[appleKeyCode];
}

rdcstr apple_GetExecutablePathFromAppBundle(const char *appBundlePath)
{
  NSString *path = [NSString stringWithCString:appBundlePath encoding:NSUTF8StringEncoding];

  NSBundle *nsBundle = [NSBundle bundleWithPath:path];
  if(!nsBundle)
  {
    RDCWARN("Failed to open application '%s' as an NSBundle", appBundlePath);
    return rdcstr(appBundlePath);
  }

  NSString *executablePath = nsBundle.executablePath;
  if(!executablePath)
  {
    RDCERR("Failed to get executable path from application '%s'", appBundlePath);
    return rdcstr();
  }

  rdcstr result([executablePath cStringUsingEncoding:NSUTF8StringEncoding]);
  return result;
}

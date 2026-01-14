 
#include "core/plugins.h"
#include "os/os_specific.h"
#include "strings/string_utils.h"

rdcstr LocatePluginFile(const rdcstr &path, const rdcstr &fileName)
{
  rdcstr ret;

  rdcstr libpath;
  FileIO::GetLibraryFilename(libpath);
  libpath = get_dirname(libpath);

  rdcarray<rdcstr> paths;

#if defined(RENDERDOC_PLUGINS_PATH)
  string customPath(RENDERDOC_PLUGINS_PATH);

  if(FileIO::IsRelativePath(customPath))
    customPath = libpath + "/" + customPath;

  paths.push_back(customPath);
#endif

  // windows installation
  paths.push_back(libpath + "/plugins");
  // linux installation
  paths.push_back(libpath + "/../share/renderdoc/plugins");
// also search the appropriate OS-specific location in the root
#if ENABLED(RDOC_WIN32) && ENABLED(RDOC_X64)
  paths.push_back(libpath + "/../../plugins-win64");
#endif

#if ENABLED(RDOC_WIN32) && DISABLED(RDOC_X64)
  paths.push_back(libpath + "/../../plugins-win32");
#endif

#if ENABLED(RDOC_LINUX)
  paths.push_back(libpath + "/../../plugins-linux64");
#endif

  // there is no standard path for local builds as we don't provide these plugins in the repository
  // directly. As a courtesy we search the root of the build, from the executable. The user can
  // always put the plugins folder relative to the exe where it would be in an installation too.
  paths.push_back(libpath + "/../../plugins");

  // in future maybe we want to search a user-specific plugins folder? Like ~/.renderdoc/ on linux
  // or %APPDATA%/renderdoc on windows?

  for(uint32_t i = 0; i < paths.size(); i++)
  {
    rdcstr check = paths[i] + "/" + path + "/" + fileName;
    if(FileIO::exists(check))
    {
      ret = check;
      break;
    }
  }

  // if we didn't find it anywhere, just try running it directly in case it's in the PATH
  if(ret.empty())
    ret = fileName;

  return ret;
}

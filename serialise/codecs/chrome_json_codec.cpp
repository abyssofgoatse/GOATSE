 

#include <utility>
#include "api/replay/structured_data.h"
#include "common/common.h"
#include "common/formatting.h"
#include "serialise/rdcfile.h"

RDResult exportChrome(const rdcstr &filename, const RDCFile &rdc, const SDFile &structData,
                      RENDERDOC_ProgressCallback progress)
{
  FILE *f = FileIO::fopen(filename, FileIO::WriteText);

  if(!f)
    RETURN_ERROR_RESULT(ResultCode::FileIOFailed, "Failed to open '%s' for write: %s",
                        filename.c_str(), FileIO::ErrorString().c_str());

  rdcstr str;

  // add header, customise this as needed.
  str = R"({
  "displayTimeUnit": "ns",
  "traceEvents": [)";

  const char *category = "Initialisation";

  // stupid JSON not allowing trailing ,s :(
  bool first = true;

  int i = 0;
  int numChunks = structData.chunks.count();

  for(const SDChunk *chunk : structData.chunks)
  {
    if(chunk->metadata.chunkID == (uint32_t)SystemChunk::FirstDriverChunk + 1)
      category = "Frame Capture";

    if(!first)
      str += ",";

    first = false;

    const char *fmt = R"(
    { "name": "%s", "cat": "%s", "ph": "B", "ts": %llu, "pid": 5, "tid": %u },
    { "ph": "E", "ts": %llu, "pid": 5, "tid": %u })";

    if(chunk->metadata.durationMicro == 0)
    {
      fmt = R"(
    { "name": "%s", "cat": "%s", "ph": "i", "ts": %llu, "pid": 5, "tid": %u })";
    }

    str += StringFormat::Fmt(
        fmt, chunk->name.c_str(), category, chunk->metadata.timestampMicro, chunk->metadata.threadID,
        chunk->metadata.timestampMicro + chunk->metadata.durationMicro, chunk->metadata.threadID);

    if(progress)
      progress(float(i) / float(numChunks));

    i++;
  }

  if(progress)
    progress(1.0f);

  // end trace events
  str += "\n  ]\n}";

  FileIO::fwrite(str.data(), 1, str.size(), f);

  FileIO::fclose(f);

  return ResultCode::Succeeded;
}

static ConversionRegistration XMLConversionRegistration(
    &exportChrome,
    {
        "chrome.json",
        "Chrome profiler JSON",
        R"(Exports the chunk threadID, timestamp and duration data to a JSON format that can be loaded
by chrome's profiler at chrome://tracing)",
        false,
    });

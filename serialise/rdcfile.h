 

#pragma once

#include "core/core.h"
#include "streamio.h"

extern const char *SectionTypeNames[];

struct RDCThumb
{
  bytebuf pixels;
  uint16_t width = 0;
  uint16_t height = 0;
  FileType format = FileType::JPG;
};

struct ExtThumbnailHeader
{
  uint16_t width;
  uint16_t height;
  uint32_t len;
  FileType format;
};

class RDCFile
{
public:
  // version number of overall file format or chunk organisation. If the contents/meaning/order of
  // chunks have changed this does not need to be bumped, there are version numbers within each
  // API that interprets the stream that can be bumped.
  static const uint32_t SERIALISE_VERSION = 0x00000102;

  // this must never be changed - files before this were in the v0.x series and didn't have embedded
  // version numbers
  static const uint32_t V1_0_VERSION = 0x00000100;
  static const uint32_t V1_1_VERSION = 0x00000101;
  static const uint32_t V1_2_VERSION = 0x00000102;

  ~RDCFile();

  // opens an existing file for read and/or modification. Error if file doesn't exist
  void Open(const rdcstr &filename);
  void Open(const bytebuf &buffer);

  RDResult CopyFileTo(const rdcstr &filename);

  // Sets the parameters of an RDCFile in memory.
  void SetData(RDCDriver driver, const rdcstr &driverName, uint64_t machineIdent,
               const RDCThumb *thumb, uint64_t timeBase, double timeFreq);

  // creates a new file with current properties, file will be overwritten if it already exists
  void Create(const rdcstr &filename);

  bool IsUntrusted() const { return m_Untrusted; }
  const RDResult &Error() const { return m_Error; }
  RDCDriver GetDriver() const { return m_Driver; }
  const rdcstr &GetDriverName() const { return m_DriverName; }
  uint64_t GetMachineIdent() const { return m_MachineIdent; }
  uint64_t GetTimestampBase() const { return m_TimeBase; }
  double GetTimestampFrequency() const { return m_TimeFrequency; }
  const RDCThumb &GetThumbnail() const { return m_Thumb; }
  int SectionIndex(SectionType type) const;
  int SectionIndex(const rdcstr &name) const;
  int NumSections() const { return int(m_Sections.size()); }
  const SectionProperties &GetSectionProperties(int index) const { return m_Sections[index]; }
  StreamReader *ReadSection(int index) const;
  StreamWriter *WriteSection(const SectionProperties &props);

  // Only valid if GetDriver returns RDCDriver::Image, passes over the underlying FILE * for use
  // loading the image directly, since the RDC container isn't there to read from a section.
  FILE *StealImageFileHandle(rdcstr &filename);

private:
  void Init(StreamReader &reader);

  FILE *m_File = NULL;
  rdcstr m_Filename;
  bytebuf m_Buffer;

  SectionProperties m_CurrentWritingProps;

  uint32_t m_SerVer = 0;

  RDCDriver m_Driver = RDCDriver::Unknown;
  rdcstr m_DriverName;
  uint64_t m_MachineIdent = 0;
  uint64_t m_TimeBase = 0;
  double m_TimeFrequency = 1.0;
  RDCThumb m_Thumb;

  bool m_Untrusted = false;
  RDResult m_Error;

  struct SectionLocation
  {
    uint64_t headerOffset;
    uint64_t dataOffset;
    uint64_t diskLength;
  };

  rdcarray<SectionProperties> m_Sections;
  rdcarray<SectionLocation> m_SectionLocations;
  rdcarray<bytebuf> m_MemorySections;
};

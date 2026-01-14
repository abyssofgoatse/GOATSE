 

#pragma once

#include "zstd/zstd.h"
#include "streamio.h"

class ZSTDCompressor : public Compressor
{
public:
  ZSTDCompressor(StreamWriter *write, Ownership own);
  ~ZSTDCompressor();

  bool Write(const void *data, uint64_t numBytes);
  bool Finish();

private:
  bool FlushPage();

  bool CompressZSTDFrame(ZSTD_inBuffer &in, ZSTD_outBuffer &out);

  byte *m_Page;
  byte *m_CompressBuffer;
  uint64_t m_PageOffset;

  ZSTD_CStream *m_Stream;
};

class ZSTDDecompressor : public Decompressor
{
public:
  ZSTDDecompressor(StreamReader *read, Ownership own);
  ~ZSTDDecompressor();

  bool Recompress(Compressor *comp);
  bool Read(void *data, uint64_t numBytes);

private:
  bool FillPage();

  byte *m_Page;
  byte *m_CompressBuffer;
  uint64_t m_PageOffset;
  uint64_t m_PageLength;

  ZSTD_DStream *m_Stream;
};

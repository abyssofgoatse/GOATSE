 

#pragma once

#include "lz4/lz4.h"
#include "streamio.h"

class LZ4Compressor : public Compressor
{
public:
  LZ4Compressor(StreamWriter *write, Ownership own);
  ~LZ4Compressor();

  bool Write(const void *data, uint64_t numBytes);
  bool Finish();

private:
  bool FlushPage0();

  byte *m_Page[2];
  byte *m_CompressBuffer;
  uint64_t m_PageOffset;

  LZ4_stream_t *m_LZ4Comp;
};

class LZ4Decompressor : public Decompressor
{
public:
  LZ4Decompressor(StreamReader *read, Ownership own);
  ~LZ4Decompressor();

  bool Recompress(Compressor *comp);
  bool Read(void *data, uint64_t numBytes);

private:
  bool FillPage0();

  byte *m_Page[2];
  byte *m_CompressBuffer;
  uint64_t m_PageOffset;
  uint64_t m_PageLength;

  LZ4_streamDecode_t *m_LZ4Decomp;
};

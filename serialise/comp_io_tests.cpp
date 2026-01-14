 

#include "lz4io.h"
#include "serialiser.h"
#include "zstdio.h"

#if ENABLED(ENABLE_UNIT_TESTS)

#include "catch/catch.hpp"

TEST_CASE("Test LZ4 compression/decompression", "[streamio][lz4]")
{
  StreamWriter buf(StreamWriter::DefaultScratchSize);

  byte *randomData = new byte[1024 * 1024];

  for(int i = 0; i < 1024 * 1024; i++)
    randomData[i] = rand() & 0xff;

  // write the data
  {
    StreamWriter writer(new LZ4Compressor(&buf, Ownership::Nothing), Ownership::Stream);

    byte *fixedData = new byte[1024 * 1024];
    byte *regularData = new byte[1024 * 1024];

    memset(fixedData, 0x7c, 1024 * 1024);

    for(int i = 0; i < 1024 * 1024; i++)
      regularData[i] = i & 0xff;

    writer.Write(fixedData, 1024 * 1024);
    writer.Write(randomData, 1024 * 1024);
    writer.Write(regularData, 1024 * 1024);
    writer.Write(fixedData, 1024 * 1024);

    // check that the compression got good wins out of the above data. The random data will be
    // pretty much untouched but the rest should compress massively.
    CHECK(buf.GetOffset() < 1024 * 1024 + 30 * 1024);
    CHECK(writer.GetOffset() == 4 * 1024 * 1024);

    CHECK_FALSE(writer.IsErrored());

    writer.Finish();

    CHECK_FALSE(writer.IsErrored());

    delete[] fixedData;
    delete[] regularData;
  }

  // we now only have the compressed data, decompress it
  {
    StreamReader reader(
        new LZ4Decompressor(new StreamReader(buf.GetData(), buf.GetOffset()), Ownership::Stream),
        4 * 1024 * 1024, Ownership::Stream);
    // recreate this for easy memcmp'ing
    byte *fixedData = new byte[1024 * 1024];
    byte *regularData = new byte[1024 * 1024];

    memset(fixedData, 0x7c, 1024 * 1024);

    for(int i = 0; i < 1024 * 1024; i++)
      regularData[i] = i & 0xff;

    byte *readData = new byte[1024 * 1024];

    reader.Read(readData, 1024 * 1024);
    CHECK_FALSE(memcmp(readData, fixedData, 1024 * 1024));

    reader.Read(readData, 1024 * 1024);
    CHECK_FALSE(memcmp(readData, randomData, 1024 * 1024));

    reader.Read(readData, 1024 * 1024);
    CHECK_FALSE(memcmp(readData, regularData, 1024 * 1024));

    reader.Read(readData, 1024 * 1024);
    CHECK_FALSE(memcmp(readData, fixedData, 1024 * 1024));

    CHECK_FALSE(reader.IsErrored());
    CHECK(reader.AtEnd());

    delete[] readData;
    delete[] fixedData;
    delete[] regularData;
  }

  delete[] randomData;
};

TEST_CASE("Test ZSTD compression/decompression", "[streamio][zstd]")
{
  StreamWriter buf(StreamWriter::DefaultScratchSize);

  byte *randomData = new byte[1024 * 1024];

  for(int i = 0; i < 1024 * 1024; i++)
    randomData[i] = rand() & 0xff;

  // write the data
  {
    StreamWriter writer(new ZSTDCompressor(&buf, Ownership::Nothing), Ownership::Stream);

    byte *fixedData = new byte[1024 * 1024];
    byte *regularData = new byte[1024 * 1024];

    memset(fixedData, 0x7c, 1024 * 1024);

    for(int i = 0; i < 1024 * 1024; i++)
      regularData[i] = i & 0xff;

    writer.Write(fixedData, 1024 * 1024);
    writer.Write(randomData, 1024 * 1024);
    writer.Write(regularData, 1024 * 1024);
    writer.Write(fixedData, 1024 * 1024);

    // check that the compression got good wins out of the above data. The random data will be
    // pretty much untouched but the rest should compress massively.
    CHECK(buf.GetOffset() < 1024 * 1024 + 4 * 1024);
    CHECK(writer.GetOffset() == 4 * 1024 * 1024);

    CHECK_FALSE(writer.IsErrored());

    writer.Finish();

    CHECK_FALSE(writer.IsErrored());

    delete[] fixedData;
    delete[] regularData;
  }

  // we now only have the compressed data, decompress it
  {
    StreamReader reader(
        new ZSTDDecompressor(new StreamReader(buf.GetData(), buf.GetOffset()), Ownership::Stream),
        4 * 1024 * 1024, Ownership::Stream);
    // recreate this for easy memcmp'ing
    byte *fixedData = new byte[1024 * 1024];
    byte *regularData = new byte[1024 * 1024];

    memset(fixedData, 0x7c, 1024 * 1024);

    for(int i = 0; i < 1024 * 1024; i++)
      regularData[i] = i & 0xff;

    byte *readData = new byte[1024 * 1024];

    reader.Read(readData, 1024 * 1024);
    CHECK_FALSE(memcmp(readData, fixedData, 1024 * 1024));

    reader.Read(readData, 1024 * 1024);
    CHECK_FALSE(memcmp(readData, randomData, 1024 * 1024));

    reader.Read(readData, 1024 * 1024);
    CHECK_FALSE(memcmp(readData, regularData, 1024 * 1024));

    reader.Read(readData, 1024 * 1024);
    CHECK_FALSE(memcmp(readData, fixedData, 1024 * 1024));

    CHECK_FALSE(reader.IsErrored());
    CHECK(reader.AtEnd());

    delete[] readData;
    delete[] fixedData;
    delete[] regularData;
  }

  delete[] randomData;
};

#endif    // ENABLED(ENABLE_UNIT_TESTS)

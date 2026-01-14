 

#pragma once

#include "api/replay/data_types.h"

// Texture data for file reading/writing. Used in more complex cases
// than just a single image, e.g. DDS (can have arrays, mips) or EXR
// (can have mips).
struct tex_data
{
  uint32_t width;
  uint32_t height;
  uint32_t depth;

  uint32_t mips;
  uint32_t slices;

  bool cubemap;

  ResourceFormat format;
};

struct read_tex_data : public tex_data
{
  bytebuf buffer;

  // pairs of {offset, size} into above data buffer
  rdcarray<rdcpair<size_t, size_t>> subresources;
};

struct write_tex_data : public tex_data
{
  rdcarray<byte *> subresources;
};

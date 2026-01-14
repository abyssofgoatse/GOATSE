 

#pragma once

#include <stdio.h>
#include "serialise/streamio.h"
#include "tex_data.h"

extern bool is_dds_file(const byte *headerBuffer, size_t size);
extern RDResult load_dds_from_file(StreamReader *reader, read_tex_data &data);
extern RDResult write_dds_to_file(FILE *f, const write_tex_data &data);

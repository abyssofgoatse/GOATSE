 

#pragma once

#include "api/replay/rdcarray.h"
#include "api/replay/rdcstr.h"

rdcstr strlower(const rdcstr &str);
rdcstr strupper(const rdcstr &str);

uint32_t strhash(const char *str, uint32_t existingHash);
uint32_t strhash(const char *str);

rdcstr get_basename(const rdcstr &path);
rdcstr get_dirname(const rdcstr &path);
rdcstr strip_extension(const rdcstr &path);

// Replace all directory separators combinations with '/'
// i.e. '\' -> '/' and '//' -> '/'
rdcstr standardise_directory_separator(const rdcstr &path);

// remove everything but alphanumeric ' ' and '.'
// It replaces everything else with _
// for logging strings where they might contain garbage characters
void strip_nonbasic(rdcstr &str);

void split(const rdcstr &in, rdcarray<rdcstr> &out, const char sep);
void merge(const rdcarray<rdcstr> &in, rdcstr &out, const char sep);

 

#pragma once

#include "api/replay/rdcstr.h"

namespace StringFormat
{
struct Args
{
  virtual void reset() = 0;

  virtual void error(const char *err) = 0;

  virtual int get_int() = 0;
  virtual unsigned int get_uint() = 0;
  virtual double get_double() = 0;
  virtual void *get_ptr() = 0;
  virtual const char *get_str() = 0;
  virtual uint64_t get_uint64() = 0;
  size_t get_size() { return sizeof(size_t) == 8 ? (size_t)get_uint64() : get_uint(); }
};

rdcstr Fmt(const char *format, ...);
rdcstr Fmt(rdcliteral format, ...);
rdcstr FmtArgs(const char *format, Args &args);
};

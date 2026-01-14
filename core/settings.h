 

#pragma once

#include "api/replay/rdcarray.h"
#include "api/replay/rdcstr.h"
#include "api/replay/version.h"
#include "common/common.h"

struct SDObject;

template <typename T>
struct ConfigVarRegistration;

#define CONFIG_SUPPORT_TYPE(T)                                                    \
  template <>                                                                     \
  struct ConfigVarRegistration<T>                                                 \
  {                                                                               \
    ConfigVarRegistration(rdcliteral name, const T &defaultValue, bool debugOnly, \
                          rdcliteral description);                                \
    T value() const;                                                              \
                                                                                  \
  private:                                                                        \
    SDObject *obj;                                                                \
  };

CONFIG_SUPPORT_TYPE(rdcstr);
CONFIG_SUPPORT_TYPE(bool);
CONFIG_SUPPORT_TYPE(uint64_t);
CONFIG_SUPPORT_TYPE(uint32_t);
CONFIG_SUPPORT_TYPE(rdcarray<rdcstr>);

#undef CONFIG_SUPPORT_TYPE

#define RDOC_CONFIG(type, name, defaultValue, description)                                \
  static ConfigVarRegistration<type> CONCAT(config, __LINE__)(                            \
      STRING_LITERAL(STRINGIZE(name)), defaultValue, false, STRING_LITERAL(description)); \
  type name()                                                                             \
  {                                                                                       \
    return CONCAT(config, __LINE__).value();                                              \
  }
#define RDOC_EXTERN_CONFIG(type, name) extern type name();

// debug configs get set to constants in official stable builds, they will remain configurable
// in nightly builds and of course in development builds
#if RENDERDOC_STABLE_BUILD

#define RDOC_DEBUG_CONFIG(type, name, defaultValue, description)                         \
  static ConfigVarRegistration<type> CONCAT(config, __LINE__)(                           \
      STRING_LITERAL(STRINGIZE(name)), defaultValue, true, STRING_LITERAL(description)); \
  type name()                                                                            \
  {                                                                                      \
    static const type ret = defaultValue;                                                \
    return ret;                                                                          \
  }
#else

#define RDOC_DEBUG_CONFIG(type, name, defaultValue, description)                         \
  static ConfigVarRegistration<type> CONCAT(config, __LINE__)(                           \
      STRING_LITERAL(STRINGIZE(name)), defaultValue, true, STRING_LITERAL(description)); \
  type name()                                                                            \
  {                                                                                      \
    return CONCAT(config, __LINE__).value();                                             \
  }
#endif

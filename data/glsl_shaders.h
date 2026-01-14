 

enum class ShaderType
{
  GLSL,
  GLSLES,
  Vulkan,
  GLSPIRV,
};

#include <functional>
#include "api/replay/rdcstr.h"

rdcstr GenerateGLSLShader(const rdcstr &shader, ShaderType type, int version,
                          const rdcstr &defines = "");

rdcstr InsertSnippetAfterVersion(ShaderType type, const char *source, int len, const char *snippet);

// for unit tests
struct ShaderReflection;
enum class ShaderStage : uint8_t;
using ReflectionMaker = std::function<void(ShaderStage stage, const rdcstr &source,
                                           const rdcstr &entryPoint, ShaderReflection &refl)>;
void TestGLSLReflection(ShaderType testType, ReflectionMaker compile);

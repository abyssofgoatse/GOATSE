 

#pragma once

#if !defined(CONCAT)
#define CONCAT2(a, b) a##b
#define CONCAT(a, b) CONCAT2(a, b)
#endif

#define DECLARE_EMBED(filename)                   \
  extern unsigned char CONCAT(data_, filename)[]; \
  extern int CONCAT(CONCAT(data_, filename), _len);

DECLARE_EMBED(sourcecodepro_ttf);
DECLARE_EMBED(glsl_blit_vert);
DECLARE_EMBED(glsl_checkerboard_frag);
DECLARE_EMBED(glsl_texdisplay_frag);
DECLARE_EMBED(glsl_gltext_vert);
DECLARE_EMBED(glsl_gltext_frag);
DECLARE_EMBED(glsl_vktext_vert);
DECLARE_EMBED(glsl_vktext_frag);
DECLARE_EMBED(glsl_fixedcol_frag);
DECLARE_EMBED(glsl_mesh_vert);
DECLARE_EMBED(glsl_mesh_geom);
DECLARE_EMBED(glsl_mesh_frag);
DECLARE_EMBED(glsl_trisize_geom);
DECLARE_EMBED(glsl_trisize_frag);
DECLARE_EMBED(glsl_minmaxtile_comp);
DECLARE_EMBED(glsl_minmaxresult_comp);
DECLARE_EMBED(glsl_histogram_comp);
DECLARE_EMBED(glsl_glsl_globals_h);
DECLARE_EMBED(glsl_glsl_ubos_h);
DECLARE_EMBED(glsl_gl_texsample_h);
DECLARE_EMBED(glsl_vk_texsample_h);
DECLARE_EMBED(glsl_quadresolve_frag);
DECLARE_EMBED(glsl_quadwrite_frag);
DECLARE_EMBED(glsl_mesh_comp);
DECLARE_EMBED(glsl_array2ms_comp);
DECLARE_EMBED(glsl_ms2array_comp);
DECLARE_EMBED(glsl_deptharr2ms_frag);
DECLARE_EMBED(glsl_depthms2arr_frag);
DECLARE_EMBED(glsl_gles_texsample_h);
DECLARE_EMBED(glsl_pixelhistory_mscopy_comp);
DECLARE_EMBED(glsl_pixelhistory_mscopy_depth_comp);
DECLARE_EMBED(glsl_pixelhistory_primid_frag);
DECLARE_EMBED(glsl_shaderdebug_sample_vert);
DECLARE_EMBED(glsl_texremap_frag);
DECLARE_EMBED(glsl_discard_frag);
DECLARE_EMBED(glsl_vk_ms2buffer_comp);
DECLARE_EMBED(glsl_vk_depthms2buffer_comp);
DECLARE_EMBED(glsl_vk_buffer2ms_comp);
DECLARE_EMBED(glsl_vk_depthbuf2ms_frag);
DECLARE_EMBED(glsl_depth_copy_frag);
DECLARE_EMBED(glsl_depth_copyms_frag);
DECLARE_EMBED(glsl_debug_math_comp);
DECLARE_EMBED(glsl_debug_sample_frag);
DECLARE_EMBED(hlsl_quadswizzle_hlsl);

#undef DECLARE_EMBED

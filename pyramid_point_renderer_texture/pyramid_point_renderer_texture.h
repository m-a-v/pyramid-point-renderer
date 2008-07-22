/*
** pyramid_point_render.h Pyramid Point Based Rendering header.
**
**
**   history:	created  02-Jul-07
*/

#ifndef __PYRAMID_POINT_RENDERER_TEXTURE_H__
#define __PYRAMID_POINT_RENDERER_TEXTURE_H__

#include <cmath>
#include <cassert>

#include "point_based_renderer.h"

#define FBO_BUFFERS_COUNT_6 6

class PyramidPointRendererTexture : public PointBasedRenderer
{
 private:

  void createFBO( void );
  void createShaders ( void );
  void rasterizePhongShading(int bufferIndex);
  int phongShadingCallbackFunc( void );
  void rasterizeSynthesisPyramid();
  int synthesisCallbackFunc( void );
  void copyAnalysisPyramid();
  int copyCallbackFunc( void );
  void rasterizeAnalysisPyramid( void );
  int analysisCallbackFunc( void );
  int projectionCallbackFunc( void );
  void projectSurfels( Primitives* prim );

  pixels_struct generatePixels(int level, GLuint fbo, int buffersCount, GLuint buffer0, GLuint buffer1, GLuint buffer2);
  void rasterizePixels(pixels_struct dest, pixels_struct src0, pixels_struct src1, int phase);
  GLuint getTextureOfBuffer(GLuint buffer);

  double computeHalfPixelSize( void );

 public:
  PyramidPointRendererTexture();
  PyramidPointRendererTexture(int w, int h);
  ~PyramidPointRendererTexture();

  void draw();
  
  void clearBuffers (void);
  void projectSamples ( Primitives* prim );
  void interpolate ( void );

  void setRenderTexture(GLuint tex) {render_texture = tex;}

 private:
  /// Frame buffer object width.
  int fbo_width;
  /// Frame buffer object height.
  int fbo_height;
  /// Number of frame buffer object attachments.
  int fbo_buffers_count;
  /// Canvas border width.
  int canvas_border_width;
  /// Canvas border height.
  int canvas_border_height;

  /// Pointer to the projection shader being used (no_lod or lod)
  glslKernel *shader_projection;
  /// Pyramid copy phase shader.
  glslKernel *shader_copy;
  /// Pyramid analysis phase shader.
  glslKernel *shader_analysis;
  /// Pyramid synthesis phase shader.
  glslKernel *shader_synthesis;
  /// Phong shading shader.
  glslKernel *shader_phong;

  /// The application-created framebuffer object.
  GLuint fbo;

  GLuint fbo_depth;

  /// usually fboBuffers[i] == GL_COLOR_ATTACHMENT0_EXT + i, 
  /// but we don't rely on this assumption
  GLuint fbo_buffers[FBO_BUFFERS_COUNT_6];

  /** Textures bound to the framebuffer object; 
   * the ping-pong rendering switches between pairs 0-2 and 1-3
   * because this can be easily generalized to triples 0-2-4 and 1-3-5 etc.
   * (pairs 0-1 and 2-3 would have to be rearranged to 0-1-2 and 3-4-5).
   * use getTextureOfBuffer to find the texture name of a buffer
   **/
  GLuint fbo_textures[FBO_BUFFERS_COUNT_6];

  /// Number of pyramid levels.
  int levels_count;

  /// Current rasterize level
  int cur_level;

  /// Type of most recently used framebuffer.
  framebuffer_state_enum framebuffer_state; 
  
  /// Current rendering mode.
  render_state_enum render_state;

  /// Num of primitives to be passed to the geom shader when using LOD
  int num_primitives;

  /// Flag for rendering point ids buffer
  bool point_ids_buffer;

  /// Render texture
  GLuint render_texture;
};

#endif
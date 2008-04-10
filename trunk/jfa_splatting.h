/*
** ellipse_rasterization.h
**
** Author: Ricardo Marroquim
**
**   history:	created  29-Feb-08
*/

#ifndef __JFA_SPLATTING_H__
#define __JFA_SPLATTING_H__

#include <cmath>
#include <cassert>

#include "point_based_render.h"

class JFASplatting : public PointBasedRender
{
 private:

  void createFBO( void );
  void createShaders ( void );

  void rasterizePhongShading( void );
  void evaluatePixels( void );
  void projectSurfels( Primitives * );

  void drawQuad( void );
  void switchBuffers( void );

 public:
  JFASplatting();
  JFASplatting(int w, int h);
  ~JFASplatting();

  void draw();
  
  void clearBuffers (void);
  void projectSamples ( Primitives* prim );
  void interpolate ( void );

  void getDataProjectedPixels ( int * );
  void getDataReconstructedPixels ( int buffer );

  void setDistanceType ( int n) { dist_type = n; }

 private:

  // Size of framebuffer, usually a power of 2
  int fbo_width, fbo_height;

  /// Canvas border width.
  int canvas_border_width;
  /// Canvas border height.
  int canvas_border_height;

  /// Projection shader.
  glslKernel *shader_projection;
  /// Evaluate one pixel displaced of delta_i delta_j
  glslKernel *shader_evaluate;
  /// Phong shading shader.
  glslKernel *shader_phong;

  /// The application-created framebuffer object.
  GLuint fbo;
  GLuint fbo_depth;

  GLuint read_buffer, dest_buffer;

  /// usually fboBuffers[i] == GL_COLOR_ATTACHMENT0_EXT + i, 
  /// but we don't rely on this assumption
  GLuint fbo_buffers[FBO_BUFFERS_COUNT];

  /** Textures bound to the framebuffer object; 
   * the ping-pong rendering switches between pairs 0-2 and 1-3
   * because this can be easily generalized to triples 0-2-4 and 1-3-5 etc.
   * (pairs 0-1 and 2-3 would have to be rearranged to 0-1-2 and 3-4-5).
   * use getTextureOfBuffer to find the texture name of a buffer
   **/
  GLuint fbo_textures[FBO_BUFFERS_COUNT];

  /// Type of most recently used framebuffer.
  framebuffer_state_enum framebuffer_state; 

  // Distance type (ellipse, pixel)
  int dist_type;

};

#endif

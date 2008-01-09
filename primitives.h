/**
 *
 * Author: Ricardo Marroquim
 *
 * Data created: 2007-11-19
 *
 **/

#ifndef __PRIMITIVES_H__
#define __PRIMITIVES_H__

#define GL_GLEXT_PROTOTYPES

#include "surfels.h"
#include "quat.h"

#include "GL/glu.h"

typedef enum 
  {
    TRIANGLES,
    LINES,
    PYRAMID_POINTS,
    PYRAMID_TRIANGLES,
    PYRAMID_LINES,
    PYRAMID_HYBRID,
    NONE,
    PYRAMID_POINTS_COLOR,
    EWA_SPLATTING,
    EWA_SPLATTING_INTERPOLATE_NORMALS,
    PYRAMID_HYBRID_TEST

  } point_render_type_enum;

using namespace std;

class Primitives
{
 public:
  
  Primitives() { }

  Primitives(int id_num, GLfloat t) : id(id_num), type(t) {}
     
  Primitives(int id_num) : id(id_num) {}

  ~Primitives() {}

  void render ( void );

  vector<Surfel> * getSurfels ( void ) { return &surfels; }
  vector<Triangle> * getTriangles( void ) { return &triangles; }

  point_render_type_enum getRendererType ( void ) { return renderer_type; }
  void setRendererType ( point_render_type_enum type );

  void setType ( GLfloat t ) {type = t;}
  GLfloat getType ( void ) {return type;}

  void setId ( int id_num ) { id = id_num; }
  int getId ( void ) { return id; }

  int numberPoints ( void ) const { return number_points; }
  int numberTriangles ( void ) const { return number_triangles; }


 private:

  void setPyramidPointsArrays( void );
  void setPyramidPointsArraysColor( void );
  void setPyramidPointsDisplayList( void );
  void setPyramidTrianglesDisplayList( void );
  void setPyramidTrianglesArrays( void );
  void setPyramidHybridDisplayList( void );
  void setPyramidHybridTestDisplayList( void );
  void setPyramidLinesDisplayList( void );
  void setPyramidLinesArraysColor ( void );
  void setTrianglesDisplayList( void );
  void setTrianglesArrays( void );
  void setLinesDisplayList( void );


  // Primitives group identification number.
  int id;

  // Type of primitives (Cylinder, other)
  GLfloat type;

  // Rendering type.
  point_render_type_enum renderer_type;

  /// Vertex buffer
  GLuint vertex_buffer;

  /// Color Buffer
  GLuint color_buffer;

  /// Normal Buffer
  GLuint normal_buffer;

  /// Triangle Display List
  GLuint triangleDisplayList;

  /// Number of samples.
  int number_points;

  /// Number of triangles or lines
  int number_triangles;

  /// Indices vector for vertex arrays for lines
  GLuint *indices;

  // Vector of surfels belonging to this object.
  vector<Surfel> surfels;

  // Vector of triangles belonging to this object.
  vector<Triangle> triangles;

};

#endif

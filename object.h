/**
 *
 * Author: Ricardo Marroquim
 *
 * Data created: 2007-10-17
 *
 **/

#ifndef __OBJECT_H__
#define __OBJECT_H__

#include "primitives.h"

using namespace std;

class Object
{
 public:
  
  Object() { }

  Object(int id_num, double x, double y, double z, Quat q) : _id(id_num) {
    center[0] = x;
    center[1] = y;
    center[2] = z;
    q_rot = q;
  }

  Object(int id_num, double x, double y, double z) : _id(id_num) {
    center[0] = x;
    center[1] = y;
    center[2] = z;
    q_rot.a = 1; 
    q_rot.x = 0.0; 
    q_rot.y = 0.0; 
    q_rot.z = 0.0;
  }

  Object(int id_num) : _id(id_num) {
    center[0] = center[1] = center[2] = 0.0;
    q_rot.a = 1; q_rot.x = 0.0; q_rot.y = 0.0; q_rot.z = 0.0;
  }

  ~Object() {}

  void render ( void );

  void setId ( int id_num ) { _id = id_num; }
  int id ( void ) const { return _id; }

  char* filename( void ) { return _filename; }
  void setFilename ( const char* name ) {
    strcpy (&_filename[0], name);
  }

  double* getCenter ( void ) { return &center[0]; }
  void setCenter ( double c[3] ) { 
    for (int i = 0; i < 3; ++i)
      center[i]=c[i]; 
  }

  Quat* getRotationQuat ( void ) { return &q_rot; }
  void setRotationQuat ( Quat* q ) { q_rot = *q; }

  void addPrimitives( int p_id) { primitives_ids_list.push_back(p_id); }
  vector< int > * getPrimitivesList( void ) { return &primitives_ids_list; }

 private:

  // Center position (for individual translation)
  double center[3];
  vector<Point> centers;

  // Rotation quaternion (for individual rotation)
  Quat q_rot;
  vector<Quat> rotations;

  // Number of instances of this object
  int instances;

  // Pointer to instance of class cointaing primitives (verts, lines, triangles)
  vector< int > primitives_ids_list;

  // Object filename
  char _filename[200];

  // Object identification number.
  int _id;
};

#endif
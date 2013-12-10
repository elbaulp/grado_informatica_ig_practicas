/*
 * Robot.h
 *
 *  Created on: Dec 10, 2013
 *      Author: Alejandro Alcalde
 */

#ifndef ROBOT_H_
#define ROBOT_H_

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
//  #include <windows.h>
#include <GL/glut.h>
#endif

class Robot {

 public:

  Robot();

  /* Enumeration of body parts */
  enum {
    TORSO = 0,
    LUA,
    LLA,
    RUA,
    RLA,
    LUL,
    LLL,
    RUL,
    RLL,
    DANCE,
    QUIT
  };

  void move_lua_up();
  void move_lua_down();
  void move_lla_up();
  void move_lla_down();
  void move_rua_up();
  void move_rua_down();
  void move_rla_up();
  void move_rla_down();
  void move_lul_up();
  void move_lul_down();
  void move_lll_up();
  void move_lll_down();
  void move_rul_up();
  void move_rul_down();
  void move_rll_up();
  void move_rll_down();
  /* Allocate quadrics with filled drawing style */
  void InitQuadrics();

  void head();
  void torso();
  void left_upper_arm();
  void left_lower_arm();
  void right_upper_arm();
  void right_lower_arm();
  void left_upper_leg();
  void left_lower_leg();
  void right_upper_leg();
  void right_lower_leg();

  void toggleDance();
  void static static_Idle(int d);
  void Idle(int d);
  void DrawRobot(float x, float y, float z, float lua, float lla, float rua,
                 float rla, float lul, float lll, float rul, float rll);

  //static GLint getAngle() const;
  //void setAngle(static GLint angle = 0);
  const GLfloat* getCenter() const;
  bool isDance() const;
  void setDance(bool dance = false);
  void setTheta(int);
  short int* getDireccion();
  const GLfloat getHeadHeight() const;
  const GLfloat getHeadRadius() const;
  const GLfloat getLowerArmHeight() const;
  const GLfloat getLowerArmRadius() const;
  const GLfloat getLowerLegHeight() const;
  const GLfloat getLowerLegRadius() const;
  GLUquadricObj* getT() const;
  void setT(GLUquadricObj* t);
  const bool getDance() const;
  GLfloat* getTheta();
  const GLfloat getTorsoHeight() const;
  const GLfloat getTorsoRadius() const;
  const GLfloat getUpperArmHeight() const;
  const GLfloat getUpperArmRadius() const;
  const GLfloat getUpperLegHeight() const;
  const GLfloat getUpperLegRadius() const;

 private:

  /* Variables to control the size of the robot */
  GLfloat HEAD_HEIGHT;
  GLfloat HEAD_RADIUS;

  GLfloat TORSO_HEIGHT;
  GLfloat TORSO_RADIUS;

  GLfloat UPPER_ARM_HEIGHT;
  GLfloat LOWER_ARM_HEIGHT;
  GLfloat UPPER_ARM_RADIUS;
  GLfloat LOWER_ARM_RADIUS;

  GLfloat UPPER_LEG_HEIGHT;
  GLfloat LOWER_LEG_HEIGHT;
  GLfloat UPPER_LEG_RADIUS;
  GLfloat LOWER_LEG_RADIUS;

  GLUquadricObj *t, *h, /* torso and head */
  *lua, *lla, *rua, *rla, /* arms */
  *lul, *lll, *rul, *rll; /* legs */
  /*
   * lua - left upper arm
   * lla - left lower arm
   * rua - right upper arm
   * rla - right lower arm
   * lul - left upper leg
   * lll - left lower leg
   * rul - right upper leg
   * rll - right lower leg
   */

  /* initial joint angles */
  GLfloat theta[QUIT];
  short int direccion[QUIT];
  /* torso position */
  GLfloat center[3];
  /* joint angle to alter interactively */
  //static GLint angle = 0; /* initially, TORSO */
  /* Dance mode or not? */
  bool dance;

  void genDirec();
  double randRange(double min, double max);
};

#endif /* ROBOT_H_ */

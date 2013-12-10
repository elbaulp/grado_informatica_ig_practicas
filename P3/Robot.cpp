/*
 * Robot.cpp
 *
 *  Created on: Dec 10, 2013
 *      Author: Alejandro Alcalde
 */
#include "Robot.h"

Robot::Robot() {
  genDirec();
  InitQuadrics();
  this->dance = false;
  this->center[0] = 0;
  this->center[1] = 0;
  this->center[2] = 0;
  for (int i = 0; i < QUIT; i++) {
    this->theta[i] = 0;
    this->direccion[i] = 1;
  }
  HEAD_HEIGHT = 3.0;
  HEAD_RADIUS = 1.0;

  TORSO_HEIGHT = 5.0;
  TORSO_RADIUS = 1.0;

  UPPER_ARM_HEIGHT = 3.0;
  LOWER_ARM_HEIGHT = 2.0;
  UPPER_ARM_RADIUS = 0.5;
  LOWER_ARM_RADIUS = 0.5;

  UPPER_LEG_HEIGHT = 3.0;
  LOWER_LEG_HEIGHT = 2.0;
  UPPER_LEG_RADIUS = 0.5;
  LOWER_LEG_RADIUS = 0.5;
}

/* Allocate quadrics with filled drawing style */
void Robot::InitQuadrics() {
  t = gluNewQuadric();
  gluQuadricDrawStyle(t, GLU_FILL);
  lua = gluNewQuadric();
  gluQuadricDrawStyle(lua, GLU_FILL);
  h = gluNewQuadric();
  gluQuadricDrawStyle(h, GLU_FILL);
  lla = gluNewQuadric();
  gluQuadricDrawStyle(lla, GLU_FILL);
  rua = gluNewQuadric();
  gluQuadricDrawStyle(rua, GLU_FILL);
  lul = gluNewQuadric();
  gluQuadricDrawStyle(lul, GLU_FILL);
  lll = gluNewQuadric();
  gluQuadricDrawStyle(lll, GLU_FILL);
  rul = gluNewQuadric();
  gluQuadricDrawStyle(rul, GLU_FILL);
  rll = gluNewQuadric();
  gluQuadricDrawStyle(rll, GLU_FILL);
}

void Robot::Robot::head() {
  glPushMatrix();
  glScalef(HEAD_RADIUS, HEAD_HEIGHT / 2, HEAD_RADIUS);
  gluSphere(h, 1.0, 10, 10);
  glPopMatrix();
}

void Robot::torso() {
  glPushMatrix();
  glRotatef(90.0, 1.0, 0.0, 0.0);
  gluCylinder(t, TORSO_RADIUS, TORSO_RADIUS, TORSO_HEIGHT, 10, 10);
  glPopMatrix();
}

void Robot::left_upper_arm() {
  glPushMatrix();
  glRotatef(90, 0, 1, 0);
  gluCylinder(lua, UPPER_ARM_RADIUS, UPPER_ARM_RADIUS, UPPER_ARM_HEIGHT, 10,
              10);
  glPopMatrix();
}

void Robot::left_lower_arm() {
  glPushMatrix();
  glRotatef(90, 0, 1, 0);
  gluCylinder(lla, LOWER_ARM_RADIUS, LOWER_ARM_RADIUS, LOWER_ARM_HEIGHT, 10,
              10);
  glPopMatrix();
}

void Robot::right_upper_arm() {
  glPushMatrix();
  glRotatef(-90, 0, 1, 0);
  gluCylinder(rua, UPPER_ARM_RADIUS, UPPER_ARM_RADIUS, UPPER_ARM_HEIGHT, 10,
              10);
  glPopMatrix();
}

void Robot::right_lower_arm() {
  glPushMatrix();
  glRotatef(-90, 0, 1, 0);
  gluCylinder(lla, LOWER_ARM_RADIUS, LOWER_ARM_RADIUS, LOWER_ARM_HEIGHT, 10,
              10);
  glPopMatrix();
}

void Robot::left_upper_leg() {
  glPushMatrix();
  glRotatef(90, 1, 0, 0);
  gluCylinder(lul, UPPER_LEG_RADIUS, UPPER_LEG_RADIUS, UPPER_LEG_HEIGHT, 10,
              10);
  glPopMatrix();
}

void Robot::left_lower_leg() {
  glPushMatrix();
  glRotatef(90, 1, 0, 0);
  gluCylinder(lll, LOWER_LEG_RADIUS, LOWER_LEG_RADIUS, LOWER_LEG_HEIGHT, 10,
              10);
  glPopMatrix();
}

void Robot::right_upper_leg() {
  glPushMatrix();
  glRotatef(90, 1, 0, 0);
  gluCylinder(rul, UPPER_LEG_RADIUS, UPPER_LEG_RADIUS, UPPER_LEG_HEIGHT, 10,
              10);
  glPopMatrix();
}

void Robot::right_lower_leg() {
  glPushMatrix();
  glRotatef(90, 1, 0, 0);
  gluCylinder(rll, LOWER_LEG_RADIUS, LOWER_LEG_RADIUS, LOWER_LEG_HEIGHT, 10,
              10);
  glPopMatrix();
}

void Robot::DrawRobot(float x, float y, float z, float lua, float lla,
                      float rua, float rla, float lul, float lll, float rul,
                      float rll) {
  torso();
  glPushMatrix();
  glTranslatef(0, HEAD_HEIGHT / 2, 0);
  head();
  glPopMatrix();
  glPushMatrix();
  glTranslatef(TORSO_RADIUS, 0, 0);
  glRotatef(lua, 0, 0, 1);
  left_upper_arm();
  glTranslatef(UPPER_ARM_HEIGHT, 0, 0);
  glRotatef(lla, 0, 0, 1);
  left_lower_arm();
  glPopMatrix();
  glPushMatrix();
  glTranslatef(-TORSO_RADIUS, 0, 0);
  glRotatef(rua, 0, 0, 1);
  right_upper_arm();
  glTranslatef(-UPPER_ARM_HEIGHT, 0, 0);
  glRotatef(rla, 0, 0, 1);
  right_lower_arm();
  glPopMatrix();
  glPushMatrix();
  glTranslatef(TORSO_RADIUS, -TORSO_HEIGHT, 0);
  glRotatef(lul, 1, 0, 0);
  left_upper_leg();
  glTranslatef(0, -UPPER_LEG_HEIGHT, 0);
  glRotatef(lll, 1, 0, 0);
  left_lower_leg();
  glPopMatrix();
  glPushMatrix();
  glTranslatef(-TORSO_RADIUS, -TORSO_HEIGHT, 0);
  glRotatef(rul, 1, 0, 0);
  right_upper_leg();
  glTranslatef(0, -UPPER_LEG_HEIGHT, 0);
  glRotatef(rll, 1, 0, 0);
  right_lower_leg();
  glPopMatrix();
}

/*
 * An idle event is generated when no other event occurs.
 * Robot dances during idle times.
 */
/*
void Robot::Idle(int d) {
  if (d) {
    theta[LUA] += 3 * direccion[LUA];
    theta[LLA] += 3 * direccion[LLA];
    theta[RUA] += 3 * direccion[RUA];
    theta[RLA] += 3 * direccion[RLA];
    theta[LUL] += 3 * direccion[LUL];
    theta[LLL] += 3 * direccion[LLL];
    theta[RUL] += 3 * direccion[RUL];
    theta[RLL] += 3 * direccion[RLL];
    if (theta[LUA] > 60 || theta[LUA] < -60)
      direccion[LUA] *= -1;
    if (theta[LLA] > 30 || theta[LLA] < -30)
      direccion[LLA] *= -1;
    if (theta[RUA] > 60 || theta[RUA] < -60)
      direccion[RUA] *= -1;
    if (theta[RLA] > 30 || theta[RLA] < -30)
      direccion[RLA] *= -1;
    if (theta[LUL] > 90 || theta[LUL] < -90)
      direccion[LUL] *= -1;
    if (theta[LLL] > 45 || theta[LLL] < -45)
      direccion[LLL] *= -1;
    if (theta[RUL] > 90 || theta[RUL] < -90)
      direccion[RUL] *= -1;
    if (theta[RLL] > 45 || theta[RLL] < -45)
      direccion[RLL] *= -1;
    glutPostRedisplay();
  }
  glutTimerFunc(10, this->Idle, dance);
}
*/
void Robot::move_lua_up() {
  theta[LUA] += 5;
}

void Robot::move_lua_down() {
  theta[LUA] -= 5;
}

void Robot::move_lla_up() {
  theta[LLA] += 5;
}

void Robot::move_lla_down() {
  theta[LLA] -= 5;
}

void Robot::move_rua_up() {
  theta[RUA] += 5;
}

void Robot::move_rua_down() {
  theta[RUA] -= 5;
}

void Robot::move_rla_up() {
  theta[RLA] += 5;
}

void Robot::move_rla_down() {
  theta[RLA] -= 5;
}

void Robot::move_lul_up() {
  theta[LUL] += 5;
}

void Robot::move_lul_down() {
  theta[LUL] -= 5;
}

void Robot::move_lll_up() {
  theta[LLL] += 5;
}

void Robot::move_lll_down() {
  theta[LLL] -= 5;
}

void Robot::move_rul_up() {
  theta[RUL] += 5;
}

void Robot::move_rul_down() {
  theta[RUL] -= 5;
}

void Robot::move_rll_up() {
  theta[RLL] += 5;
}

void Robot::move_rll_down() {
  theta[RLL] -= 5;
}

double Robot::randRange(double min, double max) {
  return rand() * (max - min) / RAND_MAX + min;
}

/**
 * Generar direcciones aleatorias
 */
void Robot::genDirec() {
  for (int i = 0; i < QUIT; i++) {
    int s = randRange(-2, 2);
    while (s == 0)
      s = randRange(-2, 2);
    this->direccion[i] = s;
  }
}

//static GLint Robot::getAngle() const {
//  return angle;/
//}

//void Robot::setAngle(static GLint angle = 0) {
//  this->angle = angle;//
//}///
/*
 static const GLfloat* Robot::getCenter() const {
 return center;
 }
 */
bool Robot::isDance() const {
  return dance;
}
/*
 void Robot::setDance(bool dance = false) {
 this->dance = dance;
 }
 */
short int* Robot::getDireccion(){
  return direccion;
}

const GLfloat Robot::getHeadHeight() const {
  return HEAD_HEIGHT;
}

const GLfloat Robot::getHeadRadius() const {
  return HEAD_RADIUS;
}

const GLfloat Robot::getLowerArmHeight() const {
  return LOWER_ARM_HEIGHT;
}

const GLfloat Robot::getLowerArmRadius() const {
  return LOWER_ARM_RADIUS;
}

const GLfloat Robot::getLowerLegHeight() const {
  return LOWER_LEG_HEIGHT;
}

const GLfloat Robot::getLowerLegRadius() const {
  return LOWER_LEG_RADIUS;
}

GLUquadricObj* Robot::getT() const {
  return t;
}

void Robot::setT(GLUquadricObj* t) {
  this->t = t;
}

GLfloat* Robot::getTheta() {
  return theta;
}

const GLfloat Robot::getTorsoHeight() const {
  return TORSO_HEIGHT;
}

const GLfloat Robot::getTorsoRadius() const {
  return TORSO_RADIUS;
}

const GLfloat Robot::getUpperArmHeight() const {
  return UPPER_ARM_HEIGHT;
}

const GLfloat Robot::getUpperArmRadius() const {
  return UPPER_ARM_RADIUS;
}

const GLfloat Robot::getUpperLegHeight() const {
  return UPPER_LEG_HEIGHT;
}

const GLfloat Robot::getUpperLegRadius() const {
  return UPPER_LEG_RADIUS;
}

const bool Robot::getDance() const {
  return this->dance;
}

void Robot::toggleDance() {
  this->dance = !this->dance;
}

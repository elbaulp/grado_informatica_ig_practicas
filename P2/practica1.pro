HEADERS = \
  user_code.h \
  file_ply_stl.h
  
SOURCES = \
  user_code.cc \
  practica1.cc \
  file_ply_stl.cc

LIBS += -L/casa/dmartin/codigo/funciontecas/freeglut/lib \
    -lglut

CONFIG += console
QT += opengl


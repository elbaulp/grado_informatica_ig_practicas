//**************************************************************************
// Práctica 1
//
// Domingo Martin Perandres 2013
//
// GPL
//**************************************************************************

#include <GL/gl.h>
#include <iostream>
#include <vector>

using namespace std;

void draw_cube();
void draw(vector<float> &v, vector<int> &c, string tipo);
void draw_vertices(vector<float> &Vertices);

class Figura{
    vector<vector<GLfloat> > vertex;
    vector<vector<GLint> > caras;
    string tipo;

    vector<vector<GLfloat> > unitobi(vector<float> &v);
    vector<vector<GLint> > unitobi(vector<int> &c);

public:
    
    Figura(vector<float> &vertice, vector<int> &caras, string tipo);
    Figura();
    
    void draw();
};

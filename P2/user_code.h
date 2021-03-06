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
void draw(vector<float> &v, string, unsigned int);
void draw_vertices(vector<float> &Vertices);

class Figura{
    vector<vector<GLfloat> > vertex;
    vector<vector<GLint> > caras;
    vector<vector<GLfloat> > normalesCaras;
    
    // Vector para guardar normales de vertices
    string tipo;
    unsigned int num_filas;
    unsigned int rotaciones;

    vector<vector<GLfloat> > unitobi(vector<float> &v);
    vector<vector<GLint> > unitobi(vector<int> &c);
    vector<GLfloat> productoCartesiano(vector<GLfloat> &v1, vector<GLfloat> &v2);
    void normalizar(vector<GLfloat> &v1);
    void generarRotaciones(unsigned int);
    void calcularNormalesCaras();
public:
    
    Figura(vector<float> &vertice, vector<int> &caras, string tipo);
    Figura(vector<float> &vertice, string tipo, unsigned int rotacion);
    Figura();
    
    void draw_vertices();
    void draw();
    void draw_triangles();
};

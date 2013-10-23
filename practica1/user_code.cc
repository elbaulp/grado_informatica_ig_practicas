//**************************************************************************
// Codigo del usuario
//
// Domingo Martin Perandres 2013
//
// GPL
//**************************************************************************

#include <vector>
#include <stdio.h>

#include "user_code.h"
#include "file_ply_stl.h"
//**************************************************************************
// Funcion para dibujar los vertices de un cubo unidad
//***************************************************************************

void draw(vector<float> &vertices, vector<int> &caras){
    Figura figura(vertices, caras);
    figura.draw();
}

vector<vector<GLfloat> > Figura::unitobi(vector<GLfloat> &v){
    int num_filas = v.size() / 3;
    vector<vector<GLfloat> > vector_dimen(num_filas, vector<GLfloat>(3));

    for (int i = 0; i < v.size(); ++i)
        vector_dimen[i/3][i%3] = v.at(i);

    return vector_dimen;
}

vector<vector<GLint> > Figura::unitobi(vector<GLint> &c){
    int num_filas = c.size() / 3;
    vector<vector<GLint> > vector_dimen(num_filas, vector<GLint>(3));
    
    for (int i = 0; i < c.size(); ++i)
        vector_dimen[i/3][i%3] = c.at(i);

    return vector_dimen;
}

Figura::Figura(vector<GLfloat> &vertice, vector<GLint> &caras){
    this->vertex = this->unitobi(vertice);
    this->caras =  this->unitobi(caras);
}

void Figura::draw(){

    glColor3f(0,0,1);
    glPointSize(2);
   
    glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_LINE);
   
    glBegin(GL_TRIANGLES);

    for (int i = 0; i < this->caras.size(); i++){

        if (i%3==0) glColor3f(0,1,0);
        else if (i%3==1) glColor3f(0,0,1);

        glVertex3fv((GLfloat*) vertex[caras[i][0]].data());
        glVertex3fv((GLfloat*) vertex[caras[i][1]].data());
        glVertex3fv((GLfloat*) vertex[caras[i][2]].data());
    }
    glEnd();
 
}

void draw_cube()
{
    GLfloat Vertices[8][3]= {{-0.5,-0.5,0.5},{0.5,-0.5,0.5},{0.5,0.5,0.5},{-0.5,0.5,0.5},{-0.5,-0.5,-0.5},{0.5,-0.5,-0.5},{0.5,0.5,-0.5},{-0.5,0.5,-0.5}};

    GLint   Caras[12][3] = {
        {0,1,3}, {1,2,3},   // cara 1
        {1,5,2}, {5,6,2},   // cara 2
        {2,6,3}, {3,6,7},   // cara 3
        {7,4,0}, {3,7,0},   // cara 4
        {5,1,0}, {0,4,5},   // cara 5
        {6,5,4}, {4,7,6}    // cara 6
    };  
    
    glColor3f(0,0,1);
    glPointSize(4);
   
   glPolygonMode(GL_FRONT, GL_FILL);
   glPolygonMode(GL_BACK, GL_LINE);
   
   glBegin(GL_TRIANGLES);
    for (int i = 0; i < 12 ; i++){
        glVertex3fv((GLfloat*) &Vertices[Caras[i][0]]);
        glVertex3fv((GLfloat*) &Vertices[Caras[i][1]]);
        glVertex3fv((GLfloat*) &Vertices[Caras[i][2]]);
   }
    glEnd();
}

//**************************************************************************
// Funcion para dibujar vertices
//***************************************************************************

void draw_vertices(vector<float> &Vertices)
{
    //GLfloat ertices[8][3]= {{-0.5,-0.5,0.5},{0.5,-0.5,0.5},{0.5,0.5,0.5},{-0.5,0.5,0.5},{-0.5,-0.5,-0.5},{0.5,-0.5,-0.5},{0.5,0.5,-0.5},{-0.5,0.5,-0.5}};
    
    int num_filas = Vertices.size() / 3;
    GLfloat v[num_filas][3];
    
    for (int i = 0; i < Vertices.size(); ++i)
        v[i/3][i%3] = Vertices.at(i);



    glColor3f(0,1,0);
    glPointSize(4);

    glBegin(GL_POINTS);
    for (unsigned i = 0; i < num_filas ; i++)
        glVertex3fv((GLfloat*) &v[i]);

    glEnd();
}


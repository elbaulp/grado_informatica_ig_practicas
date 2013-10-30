//**************************************************************************
// Codigo del usuario
//
// Domingo Martin Perandres 2013
//
// GPL
//**************************************************************************

#include <vector>
#include <stdio.h>
#include <math.h>

#include "user_code.h"
#include "file_ply_stl.h"
//**************************************************************************
// Funcion para dibujar los vertices de un cubo unidad
//***************************************************************************

void draw(vector<float> &vertices, vector<int> &caras, string tipo){
    Figura figura(vertices, caras, tipo);
    figura.draw();
}

void draw(vector<float> &vertices, string tipo){
    Figura figura(vertices, tipo);
    figura.draw_vertices();
}

Figura::Figura(vector<GLfloat> &vertice, vector<GLint> &caras, string tipo){
    this->vertex = this->unitobi(vertice);
    this->caras =  this->unitobi(caras);
    this->tipo.assign(tipo);
}

Figura::Figura(vector<float> &vertice, string tipo){
    this->vertex = this->unitobi(vertice);
    this->tipo.assign(tipo);

    cout << "Tama" << vertex.size() << endl;
    for (int i=0; i < 11 * 50 ; i++){
        GLfloat x = vertex[i].data()[0] * cos(((360/50) * M_PI)/180)  + vertex[i].data()[2] * sin(((360/50) * M_PI)/180);
        GLfloat y = vertex[i].data()[1];
        GLfloat z = -sin(((360/50)*M_PI)/180) * vertex[i].data()[0] + vertex[i].data()[2] * cos(((360/50)*M_PI)/180);
    
        vector<GLfloat> v;
        v.push_back(x);
        v.push_back(y);
        v.push_back(z);
        this->vertex.push_back(v);
    }
    cout << "af" << vertex.size() << endl;

}

//**************************************************************************
// Funcion para dibujar vertices
//***************************************************************************

void Figura::draw_vertices()
{
    glColor3f(0,1,0);
    glPointSize(4);

    glBegin(GL_POINTS);
    for (unsigned i = 0; i < vertex.size() ; i++)
        glVertex3fv((GLfloat*) vertex[i].data());

    glEnd();
}

void Figura::draw(){

    glColor3f(0,0,1);
    glPointSize(2);

    bool ajedrez = false;

    if (this->tipo.compare("solido")==0)
        glPolygonMode(GL_FRONT, GL_FILL);
    else if (this->tipo.compare("alambre") == 0)
        glPolygonMode(GL_FRONT, GL_LINE);
    else if (this->tipo.compare("ajedrez") == 0){
        glPolygonMode(GL_FRONT, GL_FILL);
        ajedrez = true;
    }
    else glPolygonMode(GL_FRONT, GL_FILL);
    
    glPolygonMode(GL_BACK, GL_LINE);

    glBegin(GL_TRIANGLES);

    for (int i = 0; i < this->caras.size(); i++){
        if (ajedrez){
            if (i%3==0) glColor3f(0,1,0);   
            else if (i%3==1) glColor3f(0,0,1);
        }
        glVertex3fv((GLfloat*) vertex[caras[i][0]].data());
        glVertex3fv((GLfloat*) vertex[caras[i][1]].data());
        glVertex3fv((GLfloat*) vertex[caras[i][2]].data());
    }
    glEnd();
 
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

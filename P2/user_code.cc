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
#include <algorithm>
#include <functional>

#include "user_code.h"
#include "file_ply_stl.h"
//**************************************************************************
// Funcion para dibujar los vertices de un cubo unidad
//***************************************************************************

void draw(vector<float> &vertices, vector<int> &caras, string tipo){
    Figura figura(vertices, caras, tipo);
    figura.draw();
}

void draw(vector<float> &vertices, string tipo, unsigned int rotacion){
    Figura figura(vertices, tipo, rotacion);
    if (tipo.compare("alambre") == 0 ||
            tipo.compare("solido") == 0 ||
            tipo.compare("ajedrez") == 0)
        figura.draw_triangles();
    if (tipo.compare("puntos") == 0)
        figura.draw_vertices();
}

Figura::Figura(vector<GLfloat> &vertice, vector<GLint> &caras, string tipo){
    this->vertex = this->unitobi(vertice);
    this->caras =  this->unitobi(caras);
    this->tipo.assign(tipo);
}

Figura::Figura(vector<float> &vertice, string tipo, unsigned int rotacion){
    this->vertex = this->unitobi(vertice);
    this->caras = std::vector<vector<GLint> >();
    this->normalesCaras = vector<vector<GLfloat> >();
    this->tipo.assign(tipo);
    this->rotaciones = rotacion;

    generarRotaciones(rotacion);
}

vector<GLfloat> Figura::productoCartesiano(vector<GLfloat> &v1, vector<GLfloat> &v2) {
    vector<GLfloat> vR(3);
    
    vR.at(0) =   ( (v1.at(1) * v2.at(2)) - (v1.at(2) * v2.at(1)) );
    vR.at(1) = - ( (v1.at(0) * v2.at(2)) - (v1.at(2) * v2.at(0)) );
    vR.at(2) =   ( (v1.at(0) * v2.at(1)) - (v1.at(1) * v2.at(0)) );

    return vR;
}

void Figura::normalizar(vector<GLfloat> &v) {
    GLfloat modulo;

    modulo = sqrt(pow(v[0], 2)  +
                pow(v[1], 2)    +
                pow(v[2], 2)
            );
    v.at(0) = v.at(0) / modulo;
    v.at(1) = v.at(1) / modulo;
    v.at(2) = v.at(2) / modulo;
}

void Figura::generarRotaciones(unsigned int rot){
    for (uint i=0; i < this->num_filas * rot ; i++){
        GLfloat x = vertex[i].data()[0] * cos((2.0/rot) * M_PI)
            + vertex[i].data()[2] * sin((2.0/rot) * M_PI);
        GLfloat y = vertex[i].data()[1];
        GLfloat z = -sin((2.0/rot)*M_PI) * vertex[i].data()[0] 
            + vertex[i].data()[2] * cos((2.0/rot)*M_PI);
    
        vector<GLfloat> v;
        v.push_back(x);
        v.push_back(y);
        v.push_back(z);

        /* Calcular la normal de las caras */
        this->vertex.push_back(v);

        /* Constrir el vector de caras */
        uint v_number = this->vertex.size()-1;
        vector<GLint> c;
        vector<GLint> c2;
        
        if ( v_number % this->num_filas){
            c.push_back(v_number);
            c.push_back(v_number - 1);
            c.push_back(i);
            
            if ( v_number % this->num_filas != 1){
                c2.push_back(v_number - 1);
                c2.push_back(i - 1);
                c2.push_back(i);
            }
        } else {
            c.push_back(v_number);
            c.push_back(i);
            c.push_back(i + 1);
        }
        this->caras.push_back(c);
        if ( ! c2.empty() ) 
            this->caras.push_back(c2);
    }

    calcularNormalesCaras();
}
/**
 * Calcular las normales de las caras
 */
void Figura::calcularNormalesCaras(){
/*
 * For a face, take vertices {0, 1, 2}. I don't know the Vec3f specification (or if it's a class or C struct), but we can find the normal for all vertices in the quad with:
 *
 * Vec3f va = v0 - v1; // quad vertex 1 -> 0
 * Vec3f vb = v2 - v1; // quad vertex 1 -> 2
 * Vec3f norm = cross(vb, va); // cross product.
 *
 * float norm_len = sqrt(dot(norm, norm));
 * norm /= norm_len; // divide each component of norm by norm_len.
 */
    for (unsigned int i = 0; i < this->caras.size() ; i++){
        vector<GLfloat> v0 = vertex[caras[i][0]];
        vector<GLfloat> v1 = vertex[caras[i][1]];
        vector<GLfloat> v2 = vertex[caras[i][2]];
        
        vector<GLfloat> va;
        vector<GLfloat> vb;

        std::transform(v1.begin(),v1.end(),v0.begin(),v1.begin(),std::minus<GLfloat>());
        std::transform(v2.begin(),v2.end(),v1.begin(),v2.begin(),std::minus<GLfloat>());
        va = v0;
        vb = v2;
        vector<GLfloat> prod = productoCartesiano(vb,va);
        // Asegurarme que no sean cero antes de normalizar
        normalizar(prod);
        this->normalesCaras.push_back(prod);
    }
    cout << "imprimiendo normales de caras" << endl;
    for (int i = 0 ; i < normalesCaras.size() ; i++)
        cout << normalesCaras[i][0] << " " << normalesCaras[i][1] << " " << normalesCaras[i][2] << endl;
}
//**************************************************************************
// Funcion para dibujar vertices
//***************************************************************************
void Figura::draw_vertices()
{
    glColor3f(1,.4,.2);
    glPointSize(4);
    
    glBegin(GL_POINTS);
    for (unsigned i = 0; i < vertex.size() ; i++)
        glVertex3fv((GLfloat*) vertex[i].data());

    glEnd();
}

/**
 * Dibujar con triángulos
 */
void Figura::draw_triangles(){
    glColor3f(.4, 1, 1);
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

    for (int i = 0; i < this->caras.size() - 1; i++){
        if (ajedrez){
            if (i%3==0) glColor3f(1,.4,.2);   
            else if (i%3==1) glColor3f(1,.84,0);
        }
        glVertex3fv((GLfloat*) vertex[caras[i][2]].data());
        glVertex3fv((GLfloat*) vertex[caras[i][1]].data());
        glVertex3fv((GLfloat*) vertex[caras[i][0]].data());
    }
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
    this->num_filas = num_filas;
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

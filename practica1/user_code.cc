//**************************************************************************
// Codigo del usuario
//
// Domingo Martin Perandres 2013
//
// GPL
//**************************************************************************

#include "user_code.h"

//**************************************************************************
// Funcion para dibujar los vertices de un cubo unidad
//***************************************************************************

void draw_cube()
{
    GLfloat Vertices[8][3]= {{-0.5,-0.5,0.5},{0.5,-0.5,0.5},{0.5,0.5,0.5},{-0.5,0.5,0.5},{-0.5,-0.5,-0.5},{0.5,-0.5,-0.5},{0.5,0.5,-0.5},{-0.5,0.5,-0.5}};

    glColor3f(0,0,1);
    glPointSize(4);

glPolygonMode(GL_FRONT,GL_LINES);
glBegin(GL_POLYGON);
            glVertex3f(Vertices[2][0], Vertices[2][1], Vertices[2][2]); // + + +
            glVertex3f(Vertices[3][0], Vertices[3][1], Vertices[3][2]); // - + +
            glVertex3f(Vertices[0][0], Vertices[0][1], Vertices[0][2]); // - - +
            glVertex3f(Vertices[1][0], Vertices[1][1], Vertices[1][2]); // + - +
glEnd();
glBegin(GL_POLYGON);
glColor3f(0,1,0);
            glVertex3f(Vertices[6][0], Vertices[6][1], Vertices[6][2]); // + + -
            glVertex3f(Vertices[7][0], Vertices[7][1], Vertices[7][2]); // - + -
            glVertex3f(Vertices[4][0], Vertices[4][1], Vertices[4][2]); // - - -
            glVertex3f(Vertices[5][0], Vertices[5][1], Vertices[5][2]); // + - -
glEnd();
glBegin(GL_POLYGON);
glColor3f(1,0,0);
            glVertex3f(Vertices[1][0], Vertices[1][1], Vertices[1][2]);
            glVertex3f(Vertices[5][0], Vertices[5][1], Vertices[5][2]);
            glVertex3f(Vertices[6][0], Vertices[6][1], Vertices[6][2]);
            glVertex3f(Vertices[2][0], Vertices[2][1], Vertices[2][2]);
glEnd();
glBegin(GL_POLYGON);
glColor3f(0,0,0);
            glVertex3f(Vertices[7][0], Vertices[7][1], Vertices[7][2]);
            glVertex3f(Vertices[4][0], Vertices[4][1], Vertices[4][2]);
            glVertex3f(Vertices[0][0], Vertices[0][1], Vertices[0][2]);
            glVertex3f(Vertices[3][0], Vertices[3][1], Vertices[3][2]);
glEnd();
glBegin(GL_POLYGON);
glColor3f(0,1,1);
            glVertex3f(Vertices[1][0], Vertices[1][1], Vertices[1][2]);
            glVertex3f(Vertices[5][0], Vertices[5][1], Vertices[5][2]);
            glVertex3f(Vertices[4][0], Vertices[4][1], Vertices[4][2]);
            glVertex3f(Vertices[0][0], Vertices[0][1], Vertices[0][2]);
glEnd();
glBegin(GL_POLYGON);
glColor3f(1,0,1);
            glVertex3f(Vertices[2][0], Vertices[2][1], Vertices[2][2]);
            glVertex3f(Vertices[6][0], Vertices[6][1], Vertices[6][2]);
            glVertex3f(Vertices[7][0], Vertices[7][1], Vertices[7][2]);
            glVertex3f(Vertices[3][0], Vertices[3][1], Vertices[3][2]);
glEnd();

   //         glVertex3fv((GLfloat *) &Vertices[i]);
//           }
        // Hay que dibujar 6 caras, pero como son triangulos son 12.
        // El recorrido para dibujar las caras debe hacerse en el sentido contrario a las agujas del reloj
        // Hay que guardar en la estructura los vertices y la topologia, es decir las caras que se forman, 
        // siempre al contrario de las agujas, USando GL_POLYGON o GL_TRIANGLE
        // Entre el begin se debe llamar 3 veces a glvertex3f usando la topoligia, 
        // Es decir, hace 12 llamadas en las cuales se llama a 3 veces glvertex rellenando en sentido inverso
        // los vertices
        //
        // Para la practica, dado un objeto con n puntos y n caras, hay que pintarlo como solido, como línea y como punto.
        // Crear una ED que para almacenar los vertices y otra para las caras
        // una funcoin pintar_puntos(listapuntos, n), 
        // pintar_aristas(lista_puntos, lista de caras, n)
        // puntar_caras(lista_puntos, lista_caras, n)
        // pintar_caras_ajadrez(igual que la de antes pero impares != color)
}

//**************************************************************************
// Funcion para dibujar vertices
//***************************************************************************

void draw_vertices(vector<float> &Vertices)
{
    //GLfloat Vertices[8][3]= {{-0.5,-0.5,0.5},{0.5,-0.5,0.5},{0.5,0.5,0.5},{-0.5,0.5,0.5},{-0.5,-0.5,-0.5},{0.5,-0.5,-0.5},{0.5,0.5,-0.5},{-0.5,0.5,-0.5}};
    
    glColor3f(0,1,0);
    glPointSize(4);

    glBegin(GL_POINTS);
    for (unsigned i = 0; i < 8 ; i++)
        glVertex3fv((GLfloat*) &Vertices[i]);

    glEnd();
}


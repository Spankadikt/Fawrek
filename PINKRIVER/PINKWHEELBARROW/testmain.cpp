#include "GL/glew.h"
#include "GL/freeglut.h"
#include "pr_model.h"

GLuint VBO;
GLuint IBO;

const char* pVSFileName = "shader.vs";
const char* pFSFileName = "shader.fs";

double rotate_y = 0; 
double rotate_x = 0;
void specialKeys( int key, int x, int y ) 
{
    if (key == GLUT_KEY_RIGHT)
        rotate_y += 5;
    else if (key == GLUT_KEY_LEFT)
        rotate_y -= 5;
    else if (key == GLUT_KEY_UP)
        rotate_x += 5;
    else if (key == GLUT_KEY_DOWN)
        rotate_x -= 5;
    glutPostRedisplay();
}

static void CreateVertexBuffer(Vector3 *Vertices)
{
 	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vector3)*4, Vertices, GL_STATIC_DRAW);
}

static void CreateIndexBuffer(unsigned int *Indices)
{
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int)*12, Indices, GL_STATIC_DRAW);
}

Model model;
void display()
{
    glClearColor( 0, 0, 0, 1 );
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    int w = glutGet( GLUT_WINDOW_WIDTH );
    int h = glutGet( GLUT_WINDOW_HEIGHT );
    gluPerspective( 60, w / h, 0.1, 100 );

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    gluLookAt
        ( 
        3, 3, 3, 
        0, 0, 0,
        0, 0, 1
        );

    glRotatef( rotate_x, 1.0, 0.0, 0.0 );
    glRotatef( rotate_y, 0.0, 1.0, 0.0 );

	//glUniformMatrix4fv(gWVPLocation, 1, GL_TRUE, &s.GetWorldTrans().m[0]);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(0);

    glutSwapBuffers();
}

int main( int argc, char **argv )
{

    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE );
    glutInitWindowSize( 640, 480 );
    glutCreateWindow( "GLUT" );

    glutDisplayFunc( display );
    glutSpecialFunc( specialKeys );
    glEnable( GL_DEPTH_TEST );

	CreateVertexBuffer(model.getMesh()->getVertices());
	CreateIndexBuffer(model.getMesh()->getIndices());

    glutMainLoop();
    return 0;
}
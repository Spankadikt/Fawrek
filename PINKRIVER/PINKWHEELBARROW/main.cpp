#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#include "GL/glew.h"
#include "GL/freeglut.h"

#include "pr_vector3.h"
#include "pr_matrix.h"
#include "pr_model.h"
#include "pr_utils.h"
#include "camera.h"
#include "scene.h"

GLuint VBO;
GLuint IBO;
GLuint gWVPLocation;

const char* pVSFileName = "shader.vs";
const char* pFSFileName = "shader.fs";

const float windowWidth = 1024;
const float windowHeight = 768;

Camera cam;
Scene scene;

static void RenderSceneCB()
{
    glClear(GL_COLOR_BUFFER_BIT);

	static float Scale = 0.0f;

	Scale += 0.01f;
	//float test[16] = {1,0,0,sinf(Scale),0,1,0,0,0,0,1,0,0,0,0,1};
	//float test[16] = {  cosf(Scale),0,-sinf(Scale),0,
	//					0,1,0,0,
	//					sinf(Scale),0,cosf(Scale),0,
	//					0,0,0,1
	//};

	//Matrix World(test);

	Scene s;
    //s.Scale(sinf(Scale * 0.1f), sinf(Scale * 0.1f), sinf(Scale * 0.1f));
    //s.WorldPos(0.0f, 0.0f, 0.0f);
    //s.Rotate(sinf(Scale) * 90.0f, sinf(Scale) * 90.0f, sinf(Scale) * 90.0f);
	s.Scale(0.1f, 0.1f, 0.1f);
    s.WorldPos(0.0f, 0.0f, 0.0f);
    s.Rotate(0, 0, 0);

	Matrix test = s.GetWorldTrans().m;

	glUniformMatrix4fv(gWVPLocation, 1, GL_TRUE, &s.GetWorldTrans().m[0]);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(0);

    glutSwapBuffers();
}


static void InitializeGlutCallbacks()
{
    glutDisplayFunc(RenderSceneCB);
	glutIdleFunc(RenderSceneCB);
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

static void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType)
{
    GLuint ShaderObj = glCreateShader(ShaderType);

    if (ShaderObj == 0) {
        fprintf(stderr, "Error creating shader type %d\n", ShaderType);
        exit(0);
    }

    const GLchar* p[1];
    p[0] = pShaderText;
    GLint Lengths[1];
    Lengths[0]= strlen(pShaderText);
    glShaderSource(ShaderObj, 1, p, Lengths);
    glCompileShader(ShaderObj);
    GLint success;
    glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar InfoLog[1024];
        glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
        fprintf(stderr, "Error compiling shader type %d: '%s'\n", ShaderType, InfoLog);
        exit(1);
    }

    glAttachShader(ShaderProgram, ShaderObj);
}

static void CompileShaders()
{
    GLuint ShaderProgram = glCreateProgram();

    if (ShaderProgram == 0) {
        fprintf(stderr, "Error creating shader program\n");
        exit(1);
    }
    
    string vs, fs;

    if (!ReadFile(pVSFileName, vs)) {
        exit(1);
    };

    if (!ReadFile(pFSFileName, fs)) {
        exit(1);
    };

    AddShader(ShaderProgram, vs.c_str(), GL_VERTEX_SHADER);
    AddShader(ShaderProgram, fs.c_str(), GL_FRAGMENT_SHADER);

    GLint Success = 0;
    GLchar ErrorLog[1024] = { 0 };

    glLinkProgram(ShaderProgram);
    glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &Success);
	if (Success == 0) {
		glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
        exit(1);
	}

    glValidateProgram(ShaderProgram);
    glGetProgramiv(ShaderProgram, GL_VALIDATE_STATUS, &Success);
    if (!Success) {
        glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
        fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
        exit(1);
    }

    glUseProgram(ShaderProgram);

	gWVPLocation = glGetUniformLocation(ShaderProgram, "gWVP");
    assert(gWVPLocation != 0xFFFFFFFF);
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Pink Wheelbarrow");

    InitializeGlutCallbacks();

	Vector3 pos          = Vector3(0.0f, 0.0f, -3.0f);
    Vector3 target       = Vector3(0.0f, 0.0f, 0.0f);
    Vector3 up           = Vector3(0.0f, 1.0f, 0.0f);

	cam.Set(pos,target,up);
	cam.LookAt(cam.GetPos(),cam.GetTarget(),cam.GetUp());
	//cam.PerspectiveFOV(100.0f, windowWidth/windowHeight, 1.0f, 1000.f);
	//gluLookAt(cam.GetPos().x,cam.GetPos().y,cam.GetPos().z,cam.GetTarget().x,cam.GetTarget().y,cam.GetTarget().z,cam.GetUp().x,cam.GetUp().y,cam.GetUp().z);
	//gluPerspective(0.4f * 3.14f,windowWidth/windowHeight, 1.0f,  1000.0f);

    // Must be done after glut is initialized!
    GLenum res = glewInit();
    if (res != GLEW_OK) {
      fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
      return 1;
    }

	printf("GL version: %s\n", glGetString(GL_VERSION));

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	Model model;
	Mesh mesh = *model.getMesh();

	CreateVertexBuffer(mesh.getVertices());
	CreateIndexBuffer(mesh.getIndices());

	CompileShaders();

    glutMainLoop();

    return 0;
}
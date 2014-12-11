#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#include "GL/glew.h"
#include "GL/freeglut.h"

#include "quaternion.h"
#include "model.h"
#include "utils.h"
#include "camera.h"
#include "texture.h"
#include "window.h"
#include "light.h"

#define WINDOW_WIDTH  1024//1920
#define WINDOW_HEIGHT 768//1200

class Fawrek : public ICallbacks
{
public:

    Fawrek()
    {
		camera;
        pTexture;
        pLight;
        directionalLight.Color = Vector3(1.0f, 1.0f, 1.0f);
        directionalLight.AmbientIntensity = 0.5f;
                      
    }

    ~Fawrek()
    {
        delete pLight;
        delete pTexture;
    }

    bool Init()
    {
        camera.PerspectiveFOV(120.0f,4/3,0.01f,100.0f);
		camera.LookAt(camera.pos,camera.target,camera.up);

		mesh.LoadMeshA("model.m");

		CreateVertexBuffer(mesh.vertices);
		CreateIndexBuffer(mesh.indices);

		pLight = new Light();

		if (!pLight->Init())
		{
			return false;
		}

		pLight->Enable();
		pLight->SetTextureUnit(0);

		pTexture = new Texture("img_test.png",GL_TEXTURE_2D,TRUE);

		if (!pTexture->LoadTexture()) {
			exit(1);
		}

        return true;
    }

    void Run()
    {
        GLUTBackendRun(this);
    }

	void RenderSceneCB()
	{
		glClear(GL_COLOR_BUFFER_BIT);

		static float Scale = 0.0f;

		Scale += 0.01f;

		Matrix modelMatrix = Matrix::Identity;

		float n = 2 * cos(Scale);
		Vector3 scale = Vector3(0.5f,0.5f,0.5f);
		Quaternion rotate = Quaternion(0.0f,n,0.0f,1.0f);
		Vector3 translate = Vector3(0.5f,0.0f,0.0f);

		modelMatrix.Scale(scale);
		modelMatrix.Rotate(rotate);
		modelMatrix.Translate(translate);
		
		Matrix modelView = camera.view * modelMatrix;
		Matrix viewProjection = camera.projection * modelView;
		
		pLight->SetWVP(viewProjection);
		pLight->SetDirectionalLight(directionalLight);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)12);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)20);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		pTexture->Bind(GL_TEXTURE0);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);

		glutSwapBuffers();
	}

private:

	void CreateVertexBuffer(Vertex *Vertices)
	{
 		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*8, Vertices, GL_STATIC_DRAW);
	}

	void CreateIndexBuffer(int *Indices)
	{
		glGenBuffers(1, &IBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int)*36, Indices, GL_STATIC_DRAW);
	}


    GLuint VBO;
    GLuint IBO;
    Light *pLight;
    Texture *pTexture;
    Camera camera;
	Mesh mesh;
    DirectionalLight directionalLight;
};

int main(int argc, char *argv[])
{
   	GLUTBackendInit(argc, argv, false, false);

    if (!GLUTBackendCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, false, "Fawrek")) {
        return 1;
    }

    Fawrek *pApp = new Fawrek();

    if (!pApp->Init()) {
        return 1;
    }

    pApp->Run();

    delete pApp;
 
    return 0;
}
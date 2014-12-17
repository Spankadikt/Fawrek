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
        //pTexture;
        pLight;
        directionalLight.Color = Vector3(1.0f, 1.0f, 1.0f);
        directionalLight.AmbientIntensity = 0.75f;
        directionalLight.DiffuseIntensity = 0.2f;
        directionalLight.Direction = Vector3(0.0f, 1.0f, 1.0f);        
    }

    ~Fawrek()
    {
        //delete pLight;
        //delete pTexture;
    }

    bool Init()
    {
        camera.PerspectiveFOV(120.0f,4/3,0.01f,100.0f);
		camera.LookAt(camera.pos,camera.target,camera.up);

		//mesh.LoadMeshA("model.m");

		//CreateVertexBuffer(mesh.vertices,mesh.indices,mesh.nIndices);
		//CreateIndexBuffer(mesh.indices);

		//pLight = new Light();

		if (!pLight.Init())
		{
			return false;
		}

		pLight.Enable();
		pLight.SetTextureUnit(0);

		/*pTexture = new Texture("img_test.png",GL_TEXTURE_2D,TRUE);

		if (!pTexture->LoadTexture()) {
			exit(1);
		}*/

		pMesh = new Mesh();

        return pMesh->LoadMesh("phoenix_ugv.md2");

        //return true;
    }

    void Run()
    {
        GLUTBackendRun(this);
    }

	void RenderSceneCB()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		static float Scale = 0.0f;

		Scale += 0.01f;

		Matrix modelMatrix = Matrix::Identity;

		float n = 2 * cos(Scale);
		Vector3 scale = Vector3(0.1f,0.1f,0.1f);
		Quaternion rotate = Quaternion(0.0f,0.0f,0.0f,1.0f);
		Vector3 translate = Vector3(0.0f,0.0f,0.0f);

		modelMatrix.Scale(scale);
		modelMatrix.Rotate(rotate);
		modelMatrix.Translate(translate);
		
		Matrix modelView = camera.view * modelMatrix;
		Matrix viewProjection = camera.projection * modelView;
		
		pLight.SetWVP(viewProjection);
        pLight.SetWorldMatrix(modelMatrix);
		pLight.SetDirectionalLight(directionalLight);
		pLight.SetEyeWorldPos(camera.pos);
		pLight.SetMatSpecularIntensity(1.0f);
		pLight.SetMatSpecularPower(32);

		/*glEnableVertexAttribArray(0);
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
		glDisableVertexAttribArray(2);*/

		pMesh->Render();

		glutSwapBuffers();
	}

private:

	void CalcNormals(int* pIndices, int IndexCount,
                     Vertex* pVertices, int VertexCount)
    {
        // Accumulate each triangle normal into each of the triangle vertices
        for (unsigned int i = 0 ; i < IndexCount ; i += 3) {
            unsigned int Index0 = pIndices[i];
            unsigned int Index1 = pIndices[i + 1];
            unsigned int Index2 = pIndices[i + 2];
			Vector3 v1 = pVertices[Index1].position - pVertices[Index0].position;
            Vector3 v2 = pVertices[Index2].position - pVertices[Index0].position;
			Vector3 Normal = Vector3::Cross(v1,v2);
            Normal.Normalize();

            pVertices[Index0].normal += Normal;
            pVertices[Index1].normal += Normal;
            pVertices[Index2].normal += Normal;
        }

        // Normalize all the vertex normals
        for (unsigned int i = 0 ; i < VertexCount ; i++) {
            pVertices[i].normal = pVertices[i].normal.Normalize();
        }
    }

	void CreateVertexBuffer(Vertex *_vertices,int* _indices, int _indexCount)
	{
		//unsigned int sizeInBytes = ARRAY_SIZE_IN_ELEMENTS(_vertices);
        CalcNormals(_indices, _indexCount, _vertices, 8);

 		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*8, _vertices, GL_STATIC_DRAW);
	}

	void CreateIndexBuffer(int *_indices)
	{
		unsigned int sizeInBytes = ARRAY_SIZE_IN_ELEMENTS(_indices);
		glGenBuffers(1, &IBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int)*36, _indices, GL_STATIC_DRAW);
	}


    GLuint VBO;
    GLuint IBO;
    Light pLight;
    //Texture *pTexture;
    Camera camera;
	Mesh *pMesh;
    DirectionalLight directionalLight;
};

int main(int argc, char *argv[])
{
   	GLUTBackendInit(argc, argv, true, false);

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
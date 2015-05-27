#include "api.h"

#ifndef PICKINGTEXTURE_H
#define	PICKINGTEXTURE_H

#include <GL/glew.h>

class PickingTexture
{
public:
    PickingTexture();
    ~PickingTexture();

    bool Init(unsigned int WindowWidth, unsigned int WindowHeight);

    void EnableWriting(); 
    void DisableWriting();
    
    struct PixelInfo {
        float ObjectID;
        float DrawID;
        float PrimID;
        
        PixelInfo()
        {
            ObjectID = 0.0f;
            DrawID = 0.0f;
            PrimID = 0.0f;
        }
    };

    PixelInfo ReadPixel(unsigned int x, unsigned int y);
    
private:
    GLuint m_fbo;
    GLuint m_pickingTexture;
    GLuint m_depthTexture;
};

#endif//PICKINGTEXTURE_H
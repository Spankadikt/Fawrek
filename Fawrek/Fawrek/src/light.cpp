#include "light.h"


Light::Light()
{   
}

bool Light::Init()
{
    if (!Shader::Init()) {
        return false;
    }

    if (!AddShader(GL_VERTEX_SHADER, "lighting.vs")) {
        return false;
    }

    if (!AddShader(GL_FRAGMENT_SHADER, "lighting.fs")) {
        return false;
    }

    if (!Finalize()) {
        return false;
    }

    WVPLocation = GetUniformLocation("gWVP");
    samplerLocation = GetUniformLocation("gSampler");
    dirLightColorLocation = GetUniformLocation("gDirectionalLight.Color");
    dirLightAmbientIntensityLocation = GetUniformLocation("gDirectionalLight.AmbientIntensity");

    if (dirLightAmbientIntensityLocation == 0xFFFFFFFF ||
        WVPLocation == 0xFFFFFFFF ||
        samplerLocation == 0xFFFFFFFF ||
        dirLightColorLocation == 0xFFFFFFFF)
    {
        return false;
    }

    return true;
}

void Light::SetWVP(Matrix _WVP)
{
	glUniformMatrix4fv(WVPLocation, 1, GL_FALSE,&_WVP.m[0]);    
}


void Light::SetTextureUnit(unsigned int _textureUnit)
{
    glUniform1i(samplerLocation, _textureUnit);
}


void Light::SetDirectionalLight(const DirectionalLight &_light)
{
    glUniform3f(dirLightColorLocation, _light.Color.x, _light.Color.y, _light.Color.z);
    glUniform1f(dirLightAmbientIntensityLocation, _light.AmbientIntensity);
}
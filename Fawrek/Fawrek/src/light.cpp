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
	worldMatrixLocation = GetUniformLocation("gWorld");
    samplerLocation = GetUniformLocation("gSampler");
    dirLightLocation.Color = GetUniformLocation("gDirectionalLight.Color");
    dirLightLocation.AmbientIntensity = GetUniformLocation("gDirectionalLight.AmbientIntensity");
	dirLightLocation.Direction = GetUniformLocation("gDirectionalLight.Direction");
    dirLightLocation.DiffuseIntensity = GetUniformLocation("gDirectionalLight.DiffuseIntensity");
	matSpecularIntensityLocation = GetUniformLocation("gMatSpecularIntensity");
    matSpecularPowerLocation = GetUniformLocation("gSpecularPower");

    if (dirLightLocation.AmbientIntensity == 0xFFFFFFFF ||
        WVPLocation == 0xFFFFFFFF ||
        worldMatrixLocation == 0xFFFFFFFF ||
        samplerLocation == 0xFFFFFFFF ||
        dirLightLocation.Color == 0xFFFFFFFF ||
        dirLightLocation.DiffuseIntensity == 0xFFFFFFFF ||
        dirLightLocation.Direction == 0xFFFFFFFF ||
		matSpecularIntensityLocation == 0xFFFFFFFF ||
        matSpecularPowerLocation == 0xFFFFFFFF)
	{
        return false;
    }

    return true;
}

void Light::SetWVP(Matrix _WVP)
{
	glUniformMatrix4fv(WVPLocation, 1, GL_FALSE,&_WVP.m[0]);    
}

void Light::SetWorldMatrix(Matrix _worldInverse)
{
	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &_worldInverse.m[0]);
}


void Light::SetTextureUnit(unsigned int _textureUnit)
{
    glUniform1i(samplerLocation, _textureUnit);
}


void Light::SetDirectionalLight(const DirectionalLight _light)
{
    glUniform3f(dirLightLocation.Color, _light.Color.x, _light.Color.y, _light.Color.z);
    glUniform1f(dirLightLocation.AmbientIntensity, _light.AmbientIntensity);
    Vector3 Direction = _light.Direction;
    Direction = Direction.Normalize();
    glUniform3f(dirLightLocation.Direction, Direction.x, Direction.y, Direction.z);
    glUniform1f(dirLightLocation.DiffuseIntensity, _light.DiffuseIntensity);
}

void Light::SetEyeWorldPos(const Vector3 _eyeWorldPos)
{
    glUniform3f(eyeWorldPosLocation, _eyeWorldPos.x, _eyeWorldPos.y, _eyeWorldPos.z);
}

void Light::SetMatSpecularIntensity(float _intensity)
{
    glUniform1f(matSpecularIntensityLocation, _intensity);
}

void Light::SetMatSpecularPower(float _power)
{
    glUniform1f(matSpecularPowerLocation, _power);
}
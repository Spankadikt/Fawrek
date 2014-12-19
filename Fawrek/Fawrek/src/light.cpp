#include "assert.h"

#include "light.h"
#include "utils.h"

Light::Light()
{   
}

bool Light::Init()
{
    if (!Shader::Init()) {
        return false;
    }

    if (!AddShader(GL_VERTEX_SHADER, "skinning.vs")) {
        return false;
    }

    if (!AddShader(GL_FRAGMENT_SHADER, "skinning.fs")) {
        return false;
    }

    if (!Finalize()) {
        return false;
    }

    WVPLocation = GetUniformLocation("gWVP");
	worldMatrixLocation = GetUniformLocation("gWorld");
    samplerLocation = GetUniformLocation("gSampler");
	//eyeWorldPosLocation = GetUniformLocation("gEyeWorldPos");
    dirLightLocation.Color = GetUniformLocation("gDirectionalLight.Base.Color");
    dirLightLocation.AmbientIntensity = GetUniformLocation("gDirectionalLight.Base.AmbientIntensity");
	dirLightLocation.Direction = GetUniformLocation("gDirectionalLight.Direction");
    dirLightLocation.DiffuseIntensity = GetUniformLocation("gDirectionalLight.Base.DiffuseIntensity");
	matSpecularIntensityLocation = GetUniformLocation("gMatSpecularIntensity");
    matSpecularPowerLocation = GetUniformLocation("gSpecularPower");

    if (dirLightLocation.AmbientIntensity == 0xFFFFFFFF ||
        WVPLocation == 0xFFFFFFFF ||
        worldMatrixLocation == 0xFFFFFFFF ||
        samplerLocation == 0xFFFFFFFF ||
		//eyeWorldPosLocation == 0xFFFFFFFF ||
        dirLightLocation.Color == 0xFFFFFFFF ||
        dirLightLocation.DiffuseIntensity == 0xFFFFFFFF ||
        dirLightLocation.Direction == 0xFFFFFFFF ||
		matSpecularIntensityLocation == 0xFFFFFFFF ||
        matSpecularPowerLocation == 0xFFFFFFFF)
	{
        return false;
    }

	for (unsigned int i = 0 ; i < ARRAY_SIZE_IN_ELEMENTS(boneLocation) ; i++) {
        char Name[128];
        memset(Name, 0, sizeof(Name));
        SNPRINTF(Name, sizeof(Name), "gBones[%d]", i);
        boneLocation[i] = GetUniformLocation(Name);
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

void Light::SetBoneTransform(uint _index, const Matrix _transform)
{
    assert(_index < MAX_BONES);
	glUniformMatrix4fv(boneLocation[_index], 1, GL_FALSE, &_transform.m[0]);       
}
#version 330

in vec2 TexCoord0;
in vec3 Normal0;                                                                   
in vec3 WorldPos0;                                                                 

struct VSOutput
{
    vec2 TexCoord;
    vec3 Normal;                                                                   
    vec3 WorldPos;                                                                 
};

struct BaseLight
{
    vec3 Color;
    float AmbientIntensity;
    float DiffuseIntensity;

};
struct DirectionalLight
{
    BaseLight Base;
    vec3 Direction;
};
                                                                             
                                                                                            
uniform DirectionalLight gDirectionalLight;                                         
uniform sampler2D gSampler;                                                         
uniform vec3 gEyeWorldPos;                                                          
uniform float gMatSpecularIntensity;                                                
uniform float gSpecularPower;  


vec4 CalcLightInternal(BaseLight Light, vec3 LightDirection, VSOutput In)            
{                                                                                           
    vec4 AmbientColor = vec4(Light.Color, 1.0) * Light.AmbientIntensity;                   
    float DiffuseFactor = dot(In.Normal, -LightDirection);                                     
                                                                                            
    vec4 DiffuseColor  = vec4(0, 0, 0, 0);                                                  
    vec4 SpecularColor = vec4(0, 0, 0, 0);                                                  
                                                                                            
    if (DiffuseFactor > 0.0)
    {                                                                
        DiffuseColor = vec4(Light.Color, 1.0) * Light.DiffuseIntensity * DiffuseFactor;    
                                                                                            
        vec3 VertexToEye = normalize(gEyeWorldPos - In.WorldPos);                             
        vec3 LightReflect = normalize(reflect(LightDirection, In.Normal));                     
        float SpecularFactor = dot(VertexToEye, LightReflect);                              
        SpecularFactor = pow(SpecularFactor, gSpecularPower);                               
        if (SpecularFactor > 0.0)
        {                                                           
            SpecularColor = vec4(Light.Color, 1.0) *                                       
                            gMatSpecularIntensity * SpecularFactor;                         
        }                                                                                   
    }                                                                                       
                                                                                            
    return (AmbientColor + DiffuseColor + SpecularColor);                                   
}                                                                                           
                                                                                            
vec4 CalcDirectionalLight(VSOutput In)                                                      
{                                                                                           
    return CalcLightInternal(gDirectionalLight.Base, gDirectionalLight.Direction, In);  
}                                                                                           

out vec4 FragColor;
                                                                
void main()
{                                    
    VSOutput In;
    In.TexCoord = TexCoord0;
    In.Normal   = normalize(Normal0);
    In.WorldPos = WorldPos0;
  
    vec4 TotalLight = CalcDirectionalLight(In);                                         
                            
    FragColor = texture(gSampler, In.TexCoord.xy) * TotalLight;     
}

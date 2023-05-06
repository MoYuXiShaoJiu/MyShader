#version 330 core

in vec3 Normal;
in vec2 TexCoord;
in vec3 FragPos;
in vec4 FragPosLightSpace;

out vec4 FragColor;

uniform vec3 lightPos;
uniform vec3 viewPos;

uniform sampler2D tex;
uniform sampler2D shadow;

float ShadowCalculation(vec4 fragPosLightSpace)
{
       // 执行透视除法
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // 变换到[0,1]的范围
    projCoords = projCoords * 0.5 + 0.5;
    // 取得最近点的深度(使用[0,1]范围下的fragPosLight当坐标)
    float closestDepth = texture(shadow, projCoords.xy).r; 
    // 取得当前片段在光源视角下的深度
    float currentDepth = projCoords.z;
    // 检查当前片段是否在阴影中
	float bias = 0.005;
//    float shadow = currentDepth-bias > closestDepth  ? 1.0 : 0.0;
    float shadowNum = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadow, 0);
    for(int x = -1; x <= 1; ++x)
    {
        for(int y = -1; y <= 1; ++y)
        {
            float pcfDepth = texture(shadow, projCoords.xy + vec2(x, y) * texelSize).r; 
            shadowNum += currentDepth - bias > pcfDepth  ? 1.0 : 0.0;        
        }    
    }
    shadowNum /= 9.0;
    // Keep the shadow at 0.0 when outside the far_plane region of the light's frustum.
    if(projCoords.z > 1.0)
        shadowNum = 0.0;        
    return shadowNum;
}

void main()
{
	vec3 color=texture(tex,TexCoord).rgb;
	//ambient
	vec3 ambient=color*0.2;
	//diff
	vec3 lightDir=normalize(lightPos-FragPos);
	vec3 normal=normalize(Normal);
	float diff=max(0.0,dot(lightDir,normal));
	vec3 diffColor=diff*color;
	//sepc
	float spec=0.0;
	vec3 viewDir=normalize(viewPos-FragPos);
	vec3 reflectDir=reflect(-viewDir,normal);

	vec3 halfDir=normalize(lightDir+viewDir);
	spec=pow(max(dot(normal,halfDir),0.0),32);

//	vec3 newreflectDir = reflect(-lightDir, normal);
//    spec = pow(max(dot(viewDir, newreflectDir), 0.0), 8.0);
	vec3 specular=vec3(0.3)*spec;
	//计算阴影
	float m_shaow=ShadowCalculation(FragPosLightSpace);

	FragColor=vec4(ambient+(1.0-m_shaow)*(diffColor+specular),1.0);
	
	
}
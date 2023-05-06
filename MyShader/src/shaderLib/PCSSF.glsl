#version 330 core

//input
in vec3 Normal;
in vec3 FragPos;
in vec4 FragLightSpace;

uniform vec3 LIGHT_COLOR;
uniform vec3 LIGHT_POS;
uniform vec3 VIEW_POS;
uniform vec3 OBJ_COLOR;
uniform sampler2D shadowMap;

// Ouput data
out vec4 color;

//http://developer.download.nvidia.com/whitepapers/2008/PCSS_Integration.pdf
float w_penumbra(float d_receiver, float d_blocker, float w_light) {
    return (d_receiver - d_blocker) * w_light/ d_blocker;
    //这个是用来计算w值的，和我们在games202中看到的是一样的公式
}


float avg_block_depth(vec4 FragLightSpace, float w_light){
    
    int sampleCount = 8;
    float blockerSum = 0;
    int blockerCount = 0;
    //float w_light = 5;
    
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);//得到纹理的大小
    
    vec3 projCoords = FragLightSpace.xyz / FragLightSpace.w;
    projCoords = projCoords * 0.5 + 0.5;
    //float closestDepth = texture(shadowMap, projCoords.xy).r;
    float currentDepth = projCoords.z;
    
    float search_range = w_light * (currentDepth - 0.05) /currentDepth;
    if(search_range <= 0){
        return 0;
    }
    //return search_range / 7.0;
    int range = int(search_range);
    //return range / 10.0;
    
    int window = 3;
    for( int i = -window; i < window; ++i ){
        for( int j = -window; j < window; ++j ){
            vec2 shift = vec2(i * 1.0 * range / window, j * 1.0 * range / window);
            
            //sampleDepth = shadow map value at location (i , j) in the search region
            float sampleDepth = texture(shadowMap, projCoords.xy + shift * texelSize).r;
            
            if ( sampleDepth < currentDepth ){//如果采样的值在curr的前面，也就是挡住了curr
                blockerSum += sampleDepth;
                blockerCount++;//计算block的值
            }
        }
    }
    
    if(blockerCount > 0){
        return blockerSum / blockerCount;//平均block值
    } else {
        return 0; //--> not in shadow~~~~//没有人挡住自然不在shaodow里面
    }
}


float ShadowCalculation(vec4 FragLightSpace)
{
    // perform perspective divide
    vec3 projCoords = FragLightSpace.xyz / FragLightSpace.w;//透视处理
    
    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;//转换到0-1
    
    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(shadowMap, projCoords.xy).r;
    //从纹理中取得最近的值
    
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    //目前的深度值
    
    // calculate bias (based on depth map resolution and slope)
    //这一段是计算bias的
    vec3 normal = normalize(Normal);
    vec3 lightDir = normalize(LIGHT_POS - FragPos);
    float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.001);
    //////////////////////////////////////////////////////////////////////////

    float w_light = 7.0;//直接给出了一个w_light，也就是光线的面接
    
    float avg_depth = avg_block_depth(FragLightSpace, w_light);//计算平均的挡住的值
    //return  avg_depth;
    if(avg_depth == 0){
        return 0.0f;//不在阴影里面
    }
    
    float w_penumbra = w_penumbra(currentDepth, avg_depth, w_light);
    
    //if penumbra is zero, it has solid shadow - dark
    if(w_penumbra == 0){
        return 0;
    }
    
    
    // check whether current frag pos is in shadow
    // float shadow = currentDepth - bias > closestDepth  ? 1.0 : 0.0;
    // PCF
    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    int count = 0;
    
    //pick a searching range based on calculated penumbra width.
    int range = int(w_penumbra/0.09);
    
    //manually set a range if it is too large!
    range = range > 40 ? 40 : range;
    range = range < 1 ? 2 : range;
    
    //return w_penumbra;
    
    for(int x = -range; x <= range; ++x)
    {
        count++;
        for(int y = -range; y <= range; ++y)
        {
            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r;
            shadow += currentDepth - bias > pcfDepth  ? 1.0 : 0.0;
        }
    }
    count = count > 0? count : 1;
    shadow /= (count * count);
    
    // keep the shadow at 0.0 when outside the far_plane region of the light's frustum.
    if(projCoords.z > 1.0)
        shadow = 0.0;
        
        
    return shadow;
}


void main()
{
    // ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * LIGHT_COLOR;
    
    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(LIGHT_POS - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * LIGHT_COLOR;
    
    // specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(VIEW_POS - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * LIGHT_COLOR;
        
    float shadow = ShadowCalculation(FragLightSpace);
    vec3 result = (ambient + (1.0 - shadow) * (diffuse + specular)) * OBJ_COLOR;
    
    
    color = vec4(result, 1.0);
    //color = vec4(vec3(shadow), 1.0);
    //color = FragLightSpace / FragLightSpace.w;
    //color = vec4(vec3(shadow), 1.0);
    //color = vec4(textureSize(shadowMap, 0).x / 2048.0,0, 0, 1);
}
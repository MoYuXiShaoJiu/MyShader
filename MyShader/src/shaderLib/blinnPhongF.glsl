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

//已经实现了PCF

//float CalPenumbra(float d_receiver,float d_blocker,float w_light)
//{
//    //直接按照相似三角形去套公式
//    float w=(d_receiver-d_blocker)*w_light/d_blocker;
//    return w;
//}
//
//float cal_average_blocker_depth(vec4 fragPosLightSpace)
//{
//    //这里是给出一个shading point 
//    //要计算出来一个平均的深度
//
//    float blockerSum=0.0;
//   
//
//    vec2 texelSize=1.0/textureSize(shadow,0);//获得纹理的大小
//    //透视除法
//    vec3 projCoords=fragPosLightSpace.xyz/fragPosLightSpace.w;
//    projCoords=projCoords*0.5+0/5;//变换到[0,1]的范围
//    //这里找一个固定大小的区域去search
//    int givenNum=2;
//     for(int x = -givenNum; x <= givenNum; ++x)
//    {
//        for(int y = -givenNum; y <= givenNum; ++y)
//        {
//            float pcfDepth = texture(shadow, projCoords.xy + vec2(x, y) * texelSize).r; 
//            blockerSum+=pcfDepth;//但是用if好像效率会很低
//           
//        }    
//    }
//
//    return blockerSum/(2*2*givenNum*givenNum);
//}
//
//
//float ShadowCalculation(vec4 fragPosLightSpace)
//{
//       // 执行透视除法
//    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
//    // 变换到[0,1]的范围
//    projCoords = projCoords * 0.5 + 0.5;
//    // 取得最近点的深度(使用[0,1]范围下的fragPosLight当坐标)
//    float closestDepth = texture(shadow, projCoords.xy).r; 
//    // 取得当前片段在光源视角下的深度
//    float currentDepth = projCoords.z;
//    // 检查当前片段是否在阴影中
//	float bias = 0.005;
////    float shadow = currentDepth-bias > closestDepth  ? 1.0 : 0.0;
//    float shadowNum = 0.0;
//    vec2 texelSize = 1.0 / textureSize(shadow, 0);
//
//
//    //计算blocker_size
//    float d_blocker=cal_average_blocker_depth(fragPosLightSpace);
//    float d_blocker_receiver=currentDepth-d_blocker;
//    //if(d_blocker_receiver<0.01f) {return 0.0;}//没有遮挡物，自然不在阴影里面
//    float w_light = 5.0;
//    float w=CalPenumbra(currentDepth ,d_blocker,w_light);
//    if(w==0){return 0.0;}//只有currDepth==d_blocker的时候会出现为0的情况，这种情况也可以说明blocker就贴着投射面
//
//
//      //pick a searching range based on calculated penumbra width.
//    int range = int(w);
//    
//    //manually set a range if it is too large!
//    range = range > 40 ? 40 : range;
//    range = range < 1 ? 2 : range;
//
//
//    //PCSS里面的PCF的部分
//    for(int x=-range;x<=range;++x)
//    {
//        for(int y=-range;y<=range;++y)
//        {
//            float pcfDepth = texture(shadow, projCoords.xy + vec2(x, y) * texelSize).r;
//            shadowNum += currentDepth - bias > pcfDepth  ? 1.0 : 0.0;
//        }
//    }
//    shadowNum /= ((2*range)*(2*range));
//
////pcf
////    for(int x = -1; x <= 1; ++x)
////    {
////        for(int y = -1; y <= 1; ++y)
////        {
////            float pcfDepth = texture(shadow, projCoords.xy + vec2(x, y) * texelSize).r; 
////            shadowNum += currentDepth - bias > pcfDepth  ? 1.0 : 0.0;        
////        }    
////    }
////    shadowNum /= 9.0;
//
//    // Keep the shadow at 0.0 when outside the far_plane region of the light's frustum.
//    if(projCoords.z > 1.0)
//        shadowNum = 0.0;        
//    return shadowNum;
//}
//

float near = 0.1; 
float far  = 100.0; 

float LinearizeDepth(float depth) 
{
    float z = depth * 2.0 - 1.0; // back to NDC 
    return (2.0 * near * far) / (far + near - z * (far - near));    
}

float findBlocker(vec2 uv,float zReceiver)
{
	int blocker=0;
	float ret=0.0;
	//弥散参数修正
	//float r=
	vec2 texelSize=1.0/textureSize(shadow,0);
	float bias=0.05;
	int sampleNum=2;
	for(int x=-sampleNum;x<=sampleNum;x++)
	{
		for(int y=-sampleNum;y<=sampleNum;y++)
		{
			float shadowDepth=texture(shadow,uv+vec2(x,y)*texelSize).r;
			shadowDepth=LinearizeDepth(shadowDepth);
			if(zReceiver-bias>shadowDepth)
			{
				ret+=shadowDepth;
				++blocker;
			}
		}
	}
	if(blocker==0)
	{return -1.0;}
	return ret/blocker;

}


float ShadowCalculation(vec4 fragPosLightSpace)
{
	float lightWidth=4.0; 
	//透视除法
	vec3 projCoords=fragPosLightSpace.xyz/fragPosLightSpace.w;
	//转换到[0,1]
	projCoords=projCoords*0.5+0.5;
	float depth=projCoords.z;
	depth=LinearizeDepth(depth);
	float d_blocker=findBlocker(projCoords.xy,depth);
	if(d_blocker==-1) {return 0.0;}//没有遮挡物

	//penumbra size
	float penumbra=(depth-d_blocker)/d_blocker*lightWidth;
	float filterRadius=penumbra;
	int PCFSampleNum=int(filterRadius);
	if(PCFSampleNum<10){PCFSampleNum=10;}
	if(PCFSampleNum>40){PCFSampleNum=40;}

	float currDepth=projCoords.z;
	vec2 texelSize=1.0/textureSize(shadow,0);
	float shadowSum=0.0;
	float bias=0.05;
	for(int x=-PCFSampleNum;x<=PCFSampleNum;x++)
	{
		for(int y=-PCFSampleNum;y<=PCFSampleNum;y++)
		{
			float shadowDepth=texture(shadow,projCoords.xy+vec2(x,y)*texelSize).r;
			shadowSum+=currDepth-bias>shadowDepth? 1.0:0.0;
		}
	}

	if(projCoords.z > 1.0)
       {return 0.0;}
	float toatl=(2*PCFSampleNum+1);
	return shadowSum/(toatl*toatl);


	
    
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
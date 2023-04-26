#version 330 core
layout (points) in;
layout (triangle_strip, max_vertices = 5) out;

in VS_OUT
{
    vec3 color;
}gs_in[];
out vec3 fColor;

void build_house(vec4 position)
{
//所有发射出的顶点都将嵌有最后储存在fColor中的值，即顶点的颜色属性值
    fColor=gs_in[0].color;
    gl_Position=position+vec4(-0.2,-0.2,0.0,0.0);
    EmitVertex();

    fColor=vec3(1.0,1.0,1.0);
    gl_Position=position+vec4(0.2,-0.2,0.0,0.0);
    EmitVertex();

    fColor=gs_in[0].color;
    gl_Position=position+vec4(-0.2,0.2,0.0,0.0);
    EmitVertex();

    fColor = vec3(1.0, 1.0, 1.0);
    gl_Position=position+vec4(0.2,0.2,0.0,0.0);
    EmitVertex();

    gl_Position=position+vec4(0.0,0.4,0.0,0.0);
    fColor = vec3(1.0, 1.0, 1.0);
    EmitVertex();
    EndPrimitive();
}



void main() 
{    
    build_house(gl_in[0].gl_Position);
}
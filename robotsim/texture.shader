#shader Vertex
#version 330 core
layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texcoords;
out vec2 v_texcoords;
uniform float offsetx;
uniform float offsety;
uniform vec2 sincos;
uniform float zoom;
void main(){
vec2 outpos = vec2(position.x ,position.y );
float x =outpos.x;
outpos.x = outpos.x*sincos.y-outpos.y*sincos.x+ offsetx;
outpos.y = x*sincos.x+outpos.y*sincos.y+ offsety;
outpos.x = outpos.x/100*16* zoom;
outpos.y = outpos.y/100*9 * zoom;
gl_Position = vec4(outpos,0,1);
v_texcoords = texcoords;
};

#shader Fragment
#version 330 core
layout(location = 0)out vec4 colour;

in vec2 v_texcoords;
uniform sampler2D u_Texture; 

void main()
{
   vec4 texColor = texture(u_Texture,v_texcoords);
   colour = texColor;
      
};
        
#pragma once
#include <math.h>
struct vec2
{
	double x;
	double y;
};
struct vec3
{
	double x;
	double y;
	double z;
	
};
struct vec4
{
	double x;

	double y;
	double z;
	double W;
	
};
inline double dis(vec2 startp, vec2 endp) {
	return sqrt((startp.x - endp.x)* (startp.x - endp.x)+ (startp.y - endp.y)* (startp.y - endp.y));
};
struct Vertex
{
	vec3 pos;
};
struct Raydata
{
	double dis;
	int col;
};
inline void rotatevec2(double amount, vec2& dir) {
	double OldDirx = dir.x;
	dir.x = dir.x * cos(amount) - dir.y * sin(amount);
	dir.y = OldDirx * sin(amount) + dir.y * cos(amount);
}
inline double Clamp(double x, double min, double max) {
	if (x <= min)return min;
	if (x >= max)return max;
	return x;
}
inline vec2 dir2points(vec2 a, vec2 b) {
	vec2 dir;
	dir.x = a.x - b.x;
	Clamp(dir.x, -1, 1);
	dir.y = a.y - b.y;
	Clamp(dir.y, -1, 1);
	return{ dir.x,dir.y };
}

#pragma once

#include <SFML\Graphics.hpp>


#define PI_VALUE (3.142f)
typedef sf::Vector2f vec2;

//////////////////////////////////////////////////////////////////////////

float Length(vec2 v)
{
	return sqrt((v.x * v.x) + (v.y * v.y));
}

//////////////////////////////////////////////////////////////////////////

float LengthSq(vec2 v)
{
	return ((v.x * v.x) + (v.y * v.y));
}

//////////////////////////////////////////////////////////////////////////

vec2 Normalize(vec2 v)
{
	float length = Length(v);
	return vec2(v.x / length, v.y / length);
}

//////////////////////////////////////////////////////////////////////////

float Dot(vec2 v1, vec2 v2)
{
	return (v1.x * v2.x) + (v1.y * v2.y);
}

//////////////////////////////////////////////////////////////////////////

float RadiansToDegrees(float deg)
{
	return deg * (180.0f / PI_VALUE);
}

//////////////////////////////////////////////////////////////////////////

float DegreesToRadians(float deg)
{
	return deg * (PI_VALUE / 180.0f);
}

//////////////////////////////////////////////////////////////////////////

float ToAngle(vec2 v)
{
	return atan2f(v.y, v.x);
}

//////////////////////////////////////////////////////////////////////////

vec2 Rotate(vec2 v, float angleRadians)
{
	return vec2(
		v.x * cos(angleRadians) - v.y * sin(angleRadians),
		v.x * sin(angleRadians) + v.y * cos(angleRadians)
	);
}

//////////////////////////////////////////////////////////////////////////

vec2 Reflect(vec2 v, vec2 n)
{
	return v - 2 * Dot(v, n) * n;
}

//////////////////////////////////////////////////////////////////////////

bool CircleToCircleIntersection(vec2 c1, vec2 c2, float r1, float r2)
{
	float xDistance = c1.x - c2.x;
	float yDistance = c1.y - c2.y;
	float radii = r1 + r2;
	return xDistance * xDistance + yDistance * yDistance <= radii * radii;
}

//////////////////////////////////////////////////////////////////////////

// Test intersection between a line and circle
bool LineToCircleIntersection(vec2 p1, vec2 p2, vec2 circleCenter, float circleRadius, vec2 &closestPoint)
{
	vec2 d = p2 - p1;
	vec2 f = circleCenter - p1;

	// find the closest point on the line from circle center
	vec2 du = Normalize(d);
	float proj = Dot(f, du);

	vec2 closest;

	if (proj < 0.0f)
	{
		closest = p1;
	}
	else if (proj > Length(d))
	{
		closest = p2;
	}
	else
	{
		vec2 projV = du * proj;
		closest = projV + p1;
	}

	vec2 closestDiff = circleCenter - closest;
	float closestLen = Length(closestDiff);

	if (closestLen > circleRadius)
	{
		return false;
	}

	closestPoint = closest;
	return true;
}

//////////////////////////////////////////////////////////////////////////


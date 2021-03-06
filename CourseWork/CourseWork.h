#pragma once
#include "resource.h"
#include <stdexcept>
#include <windows.h>

class Ball
{
private:
	INT x, y;
	INT speedX = 0, speedY = 0;
	INT radius;
	HBRUSH brush;
	HPEN pen;
public:
	enum class Side : CHAR { TOP, RIGHT, BOTTOM, LEFT, X, Y };

	Ball(CONST Ball &) = delete;
	Ball & operator = (CONST Ball &) = delete;
	Ball(INT _posX, INT _posY, INT _radius, COLORREF _color);

	VOID move();

	VOID bounceX();

	VOID bounceY();

	INT coord(Side _side) CONST;

	inline INT getRadius() CONST;

	inline INT getSpeedX() CONST;

	inline INT getSpeedY() CONST;
	
	inline HBRUSH getBrush() CONST;
	
	inline HPEN getPen() CONST;

	inline VOID setX(INT _newX);

	inline VOID setY(INT _newY);

	inline VOID setSpeedX(INT _newSpeedX);

	inline VOID setSpeedY(INT _newSpeedY);

	inline VOID changeSpeedX(INT _plusSpeedX);

	inline VOID changeSpeedY(INT _plusSpeedY);

	VOID changeCoords(INT _plusX, INT _plusY);
};

inline INT Ball::getRadius() CONST
{
	return radius;
}

inline INT Ball::getSpeedX() CONST
{
	return speedX;
}

inline INT Ball::getSpeedY() CONST
{
	return speedY;
}

inline VOID Ball::setX(INT _newX)
{
	x = _newX;
}

inline VOID Ball::setY(INT _newY)
{
	y = _newY;
}

inline VOID Ball::setSpeedX(INT _newSpeedX)
{
	speedX = _newSpeedX;
}

inline VOID Ball::setSpeedY(INT _newSpeedY)
{
	speedY = _newSpeedY;
}

inline VOID Ball::changeSpeedX(INT _plusSpeedX)
{
	speedX += _plusSpeedX;
}

inline VOID Ball::changeSpeedY(INT _plusSpeedY)
{
	speedY += _plusSpeedY;
}

inline HBRUSH Ball::getBrush() CONST
{
	return brush;
}

inline HPEN Ball::getPen() CONST
{
	return pen;
}

class Pad
{
private:
	INT x, y;
	INT speed = 0;
	INT width;
	HBRUSH brush;
	HPEN pen;
public:
	enum class Side : CHAR { TOP, RIGHT, BOTTOM, LEFT, X, Y };

	Pad(CONST Pad &) = delete;
	Pad & operator = (CONST Pad &) = delete;
	Pad(INT _posX, INT _posY, INT _width, COLORREF _color);

	VOID move();

	INT coord(Side _side) CONST;

	inline INT getWidth() CONST;

	inline INT getSpeed() CONST;

	inline VOID setSpeed(INT _newSpeed);

	inline VOID setX(INT _newX);

	inline VOID setY(INT _newY);

	inline HBRUSH getBrush() CONST;

	inline HPEN getPen() CONST;

	VOID changeCoords(INT _plusX, INT _plusY);
};

inline INT Pad::getWidth() CONST
{
	return width;
}

inline INT Pad::getSpeed() CONST
{
	return speed;
}

inline VOID Pad::setSpeed(INT _newSpeed)
{
	speed = _newSpeed;
}

inline VOID Pad::setX(INT _newX)
{
	x = _newX;
}

inline VOID Pad::setY(INT _newY)
{
	y = _newY;
}

inline HBRUSH Pad::getBrush() CONST
{
	return brush;
}

inline HPEN Pad::getPen() CONST
{
	return pen;
}

struct Pressed
{
	BOOL leftArrow = 0, rightArrow = 0, W = 0, A = 0, S = 0, D = 0, R = 0;
};
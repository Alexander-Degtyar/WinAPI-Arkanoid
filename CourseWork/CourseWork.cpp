#include "CourseWork.h"
Ball::Ball(INT _posX, INT _posY, INT _radius, COLORREF _color)
	: x(_posX),
	y(_posY),
	radius(_radius),
	brush(CreateSolidBrush(_color)),
	pen(CreatePen(BS_SOLID, 1, _color)){}

VOID Ball::move()
{
	changeCoords(speedX, speedY);
}

VOID Ball::bounceX()
{
	speedX = -speedX;
}

VOID Ball::bounceY()
{
	speedY = -speedY;
}

INT Ball::coord(Side _side) CONST
{
	switch (_side)
	{
	case Side::TOP: return y - radius;
	case Side::BOTTOM: return y + radius;
	case Side::LEFT: return x - radius;
	case Side::RIGHT: return x + radius;
	case Side::X: return x;
	case Side::Y: return y;
	default: throw std::logic_error("Invalid side");
	};
}

VOID Ball::changeCoords(INT _plusX, INT _plusY)
{
	x += _plusX;
	y += _plusY;
}

Pad::Pad(INT _posX, INT _posY, INT _width, COLORREF _color)
	: x(_posX),
	y(_posY),
	width(_width),
	brush(CreateSolidBrush(_color)),
	pen(CreatePen(BS_SOLID, 1, _color)) {}

VOID Pad::move()
{
	changeCoords(speed, 0);
}

INT Pad::coord(Side _side) CONST
{
	switch (_side)
	{
	case Side::TOP: return y - 10;
	case Side::BOTTOM: return y + 10;
	case Side::LEFT: return x - width / 2;
	case Side::RIGHT: return x + width / 2;
	case Side::X: return x;
	case Side::Y: return y;
	default: throw std::logic_error("Invalid side");
	};
}

VOID Pad::changeCoords(INT _plusX, INT _plusY)
{
	x += _plusX;
	y += _plusY;
}
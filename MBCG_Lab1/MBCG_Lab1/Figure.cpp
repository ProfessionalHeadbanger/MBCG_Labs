#include "Figure.h"

Figure::Figure(const int size, const int offsetX, const int offsetY) :
    m_size(size),
    m_offsetX(offsetX),
    m_offsetY(offsetY)
{
    m_isDragging = false;
}


void Figure::moveTo(const int x, const int y)
{
    m_offsetX = x;
    m_offsetY = y;
}

void Figure::move(const int x, const int y)
{
    moveTo(x, y);
}

void Figure::startDragging(const int x, const int y)
{
}

void Figure::drag(const int x, const int y)
{
    
}

bool Figure::isDragging() const
{
    return m_isDragging;
}

void Figure::stopDragging(const int x, const int y)
{
    m_isDragging = false;
}

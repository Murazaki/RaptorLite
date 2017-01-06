#include "RaptorPosition2D.h"
 
RaptorPosition2D::RaptorPosition2D (int x, int y)
{
    setPosition(x,y);
}
 
RaptorPosition2D::RaptorPosition2D (const RaptorPosition2D& pos)
{
    setPosition(pos.x,pos.y);
}
 
int RaptorPosition2D::getX ()
{
    return x;
}
 
int RaptorPosition2D::getY ()
{
    return y;
}
 
void RaptorPosition2D::setX (int x)
{
    this->x = x;
}
 
void RaptorPosition2D::setY (int y)
{
    this->y = y;
}
 
void RaptorPosition2D::setPosition (int x, int y)
{
    this->x = x;
    this->y = y;
}
 
 

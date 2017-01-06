#ifndef RAPTORPOSITION2D_H
#define RAPTORPOSITION2D_H
 
/// class RaptorPosition2D -
class RaptorPosition2D
{
    // Attributes
private:
    int x;
    int y;
    // Operations
public:
    RaptorPosition2D (int x, int y);
    RaptorPosition2D (const RaptorPosition2D& pos);
    int getX ();
    int getY ();
    void setX (int x);
    void setY (int y);
    void setPosition (int x, int y);
};
 
#endif
 

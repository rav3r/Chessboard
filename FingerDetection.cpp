#include "FingerDetection.h"

void FindFingers(IplImage* frame);

extern int palec1x;
extern int palec1y;
extern int palec2x;
extern int palec2y;

void FingerDetection::Update(IplImage* frame)
{
    FindFingers(frame);
}

sf::Vector2f FingerDetection::GetPos1()
{
    return sf::Vector2f(palec1x, palec1y);
}

sf::Vector2f FingerDetection::GetPos2()
{
    return sf::Vector2f(palec2x, palec2y);
}

int FingerDetection::GetFingerCount()
{
    return 0;
}

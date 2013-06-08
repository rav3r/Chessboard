#ifndef FINGER_DET_H
#define	FINGER_DET_H

#include <opencv/cv.h>
#include <opencv/highgui.h>

#define SFML_STATIC
#include <SFML/Graphics.hpp>

class FingerDetection
{
public:
    void Update(IplImage* frame);
    
    sf::Vector2f GetPos1();
    sf::Vector2f GetPos2();
    
    int GetFingerCount();
};

#endif


#ifndef BOARDDETECTION_H
#define	BOARDDETECTION_H

#include "cv.h" 
#include "highgui.h"

#define SFML_STATIC
#include <SFML/Graphics.hpp>

class BoardDetection
{
public:
    sf::Vector2f CamToBoard(float x, float y);
    void Init();
    bool Update(IplImage* frame, sf::RenderWindow& renderWindow); // true - detected, false - detecting
    void Reset();
    IplImage* GetMask();
};

#endif	/* BOARDDETECTION_H */

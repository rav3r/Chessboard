#include <SFML/System/Vector2.hpp>

#include "BoardDetection.h"

#include "Matrix.h"
 
class Accumulator
{
private:
    int tab[2000*200];
public:
    
    void Clear()
    {
        for(int i=0; i<2000*200; i++)
            tab[i] = 0;
    }
    
    void Accumulate(IplImage *image, IplImage *image2)
    {
        int width = image->width;
        int height = image->height; 
        int step= image->widthStep;
        int step2 = image2->widthStep;
             
        unsigned char *data= (unsigned char*)(image->imageData);
        unsigned char *data2 = (unsigned char*)(image2->imageData);
       for (int j=0; j<height; j++)
        {
            for (int i=0; i<width; i++)
            {     
                tab[j*width + i] += abs(int(data[i]) - int(data2[i]));
            }
            data += step;
            data2 += step2;
        }
    }
    
    int GetHotPointPower()
    {
        int maxAbs = 0;
        
        for(int i=0; i<200*2000; i++)
            if(maxAbs < abs(tab[i]))
                maxAbs = abs(tab[i]);
        
        return maxAbs;
    }
    
    sf::Vector2f GetHotPoint(int width, int height)
    {   
        sf::Vector2f out(0,0);
        
        int c = 0;
        int maxAbs = GetHotPointPower();
        
        
        for (int j=0; j<height; j++)
        {
            for (int i=0; i<width; i++)
            {     
                if(maxAbs == abs(tab[j*width + i]))
                {
                    c++;
                    out.x += i;
                    out.y += j;
                }
            }
        }
        
        if(c == 0) c = 1;
        return sf::Vector2f(out.x/c, out.y/c);
    }
};

////////////////////////////////////////////////////////////////////////////////

IplImage* currFrame = 0;
IplImage* prevFrame = 0;
IplImage* substract = 0;
IplImage* mask      = 0;
    
int currMarker = 0;
    
sf::Vector2f points[4];

sf::CircleShape circles[4];

Accumulator acc;
Matrix A(4,4);

////////////////////////////////////////////////////////////////////////////////

void BoardDetection::Init()
{
    circles[0].setPosition(sf::Vector2f(-300, -300) - sf::Vector2f(2.5f, 2.5f));
    circles[1].setPosition(sf::Vector2f(300, -300) - sf::Vector2f(2.5f, 2.5f));
    circles[2].setPosition(sf::Vector2f(300, 300) - sf::Vector2f(2.5f, 2.5f));
    circles[3].setPosition(sf::Vector2f(-300, 300) - sf::Vector2f(2.5f, 2.5f));
    for(int i=0; i<4; i++)
    {
        circles[i].setRadius(5.0f);
    }
    
    Reset();
}

bool BoardDetection::Update(IplImage* frame, sf::RenderWindow& renderWindow)
{
     IplImage* tmpFrame = prevFrame; 
     prevFrame = currFrame;
     currFrame = tmpFrame;
     if(currFrame == 0)
     {
        currFrame = cvCreateImage(cvGetSize(frame), 8, 1);
     }

     cvCvtColor(frame, currFrame, CV_RGB2GRAY);
     if(substract == 0)
     {
         substract = cvCreateImage(cvGetSize(frame), 8, 1);
     }
     if(currFrame != 0 && prevFrame != 0 && currMarker < 4)
     {
         acc.Accumulate(currFrame, prevFrame);
         
         if(acc.GetHotPointPower() > 1000)
         {
             acc.Clear();
             currMarker++;
             if(currMarker == 4)
             {
                 Matrix X(4,4);
                 for(int i=0; i<4; i++)
                 {
                     X(i+1, 1) = points[i].x;
                     X(i+1, 2) = points[i].y;
                     X(i+1, 3) = 1;
                     X(i+1, 4) = points[i].x*points[i].y;
                     
                 }
                 Matrix Y(4, 4);
                 Y(1, 1) = 0; Y(1, 2) = 0; Y(1, 3) = 1; Y(1, 4) = 1;
                 Y(2, 1) = 1; Y(2, 2) = 0; Y(2, 3) = 1; Y(2, 4) = 1;
                 Y(3, 1) = 1; Y(3, 2) = 1; Y(3, 3) = 1; Y(3, 4) = 1;
                 Y(4, 1) = 0; Y(4, 2) = 1; Y(4, 3) = 1; Y(4, 4) = 1;
                 // Y = X*A
                 // A = inv(X)*Y
                 A = Inv(X)*Y;
                 
                 mask = cvCreateImage(cvGetSize(frame), 8, 1);
                 cvSet(mask, cvScalar(255,255,255));
                 
                 CvPoint pts[1][4];
                for(int i=0; i<4; i++)
                {
                    pts[0][i].x = points[i].x;
                    pts[0][i].y = points[i].y;
                }
                CvPoint* ppt[1] = { pts[0] };
                int npt[] = { 4 };
                cvFillPoly(mask, ppt, npt,1, cvScalar( 0, 0, 0 ));
                
                cvShowImage("Board Mask", mask);
             }
         }
     }
     
     //float mx = event.mouseMove.x;
     //float my = event.mouseMove.y;
     
     //float x = A(1, 1)*mx + A(2, 1)*my + A(3, 1) + A(4, 1)*mx*my;
     //float y = A(1, 2)*mx + A(2, 2)*my + A(3, 2) + A(4, 2)*mx*my;
     
     if(currMarker < 4) 
         points[currMarker] = acc.GetHotPoint(frame->width, frame->height);
     for(int i=0; i<4; i++)
     {
        cvCircle(frame, cvPoint(points[i].x, points[i].y), 5, cvScalar(255,0,0,255));
     }
     
//     cvCircle(frame, cvPoint(x, y), 3, cvScalar(0, 255, 255, 255));
     
     cvShowImage( "Board Detection", frame );
     
     static int show = 1;

     show++;
     show %= 3;
     
     renderWindow.clear();
     
     if(currMarker != 4)
     {
         for(int i=0; i<4; i++)
        {
             if(i == currMarker)
            {
                 if(show)
                     circles[i].setFillColor(sf::Color(255,255,255,255));
                else
                     circles[i].setFillColor(sf::Color(0,0,0,255));
            }
            else
                 circles[i].setFillColor(sf::Color(0,255,0,255));
         
            renderWindow.draw(circles[i]);
        }
     }
     
    return currMarker == 4;
}

sf::Vector2f BoardDetection::CamToBoard(float mx, float my)
{
    float x = A(1, 1)*mx + A(2, 1)*my + A(3, 1) + A(4, 1)*mx*my;
    float y = A(1, 2)*mx + A(2, 2)*my + A(3, 2) + A(4, 2)*mx*my;
    return sf::Vector2f(x,y);
}

void BoardDetection::Reset()
{
    currMarker = 0;
    acc.Clear();
}

IplImage* BoardDetection::GetMask()
{
    if(currMarker != 4) return 0;
    return mask;
}
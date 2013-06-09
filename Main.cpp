#include "Config.h"
#ifdef COMPILE_MAIN

#include <iostream>
#define SFML_STATIC
#include <SFML/Graphics.hpp>

#include "Board.h"
#include "Figure.h"

#include "BoardDetection.h"
#include "FingerDetection.h"

enum GameState
{
    NORMAL,
    DETECT_BOARD
};

GameState state = DETECT_BOARD;

void UpdateView(sf::RenderWindow &renderWindow)
{
    float aspect = float(renderWindow.getSize().x)/renderWindow.getSize().y;
        
    bool snapToHeight = aspect > 1;
        
    float w;
    float h;
        
    if(aspect > 1)
    {
        h = 800.0f;
        w = 800.0f*aspect;
    } else
    {
        w = 800.0f;
        h = 800.0f/aspect;
    }
        
    renderWindow.setView(sf::View(sf::Vector2f(0,0), sf::Vector2f(w, h)));
}

void DrawBoard(Board &board, sf::RenderWindow &renderWindow,
        sf::Sprite &boardSprite, sf::Sprite* figuresSprites)
{
    std::vector<Figure* >& black = *board.getBlack();
	std::vector<Figure* >& white = *board.getWhite();
    
    sf::Vector2f hBoard(300,300);
        
    boardSprite.setPosition(-hBoard);
	renderWindow.draw(boardSprite);

	for(int i=0; i<black.size(); i++)
	{
		Figure* figure = black[i];
		int type = figure->getType();
		int x = figure->getX();
		int y = figure->getY();
		figuresSprites[type].setPosition(x*75-hBoard.x, y*75-hBoard.y);
		renderWindow.draw(figuresSprites[type]);
	}

	for(int i=0; i<white.size(); i++)
	{
		Figure* figure = white[i];
		int type = figure->getType();
		int x = figure->getX();
		int y = figure->getY();
		figuresSprites[type+6].setPosition(x*75-hBoard.x, y*75-hBoard.y);
		renderWindow.draw(figuresSprites[type+6]);
	}
}

int main()
{	
    // OpenCV
    CvCapture* capture = cvCaptureFromCAM( CV_CAP_ANY );
    if ( !capture )
    {
        fprintf( stderr, "ERROR: capture is NULL \n" );
        getchar();
        return -1;
    }
	
    // Ustawienia graficzne
	sf::RenderWindow renderWindow(sf::VideoMode(600, 600), "Chessboard", sf::Style::Close|sf::Style::Resize);
	sf::Event event;
	
	sf::Texture boardTexture;
	boardTexture.loadFromFile("data/board.png");
	sf::Sprite boardSprite(boardTexture);

	sf::Texture figuresTexture;
	figuresTexture.loadFromFile("data/figures.png");
	sf::Sprite figuresSprites[6*2];
	for(int color=0; color<2; color++)
	{
		for(int f=0; f<6; f++)
		{
			int id = color*6+f;
			figuresSprites[id].setTexture(figuresTexture);
			figuresSprites[id].setTextureRect(sf::IntRect(f*75, color*75, 75, 75));
		}
	}

    // Detektor planszy
    BoardDetection boardDetection;
    boardDetection.Init();
    
    // Detektor palcow
    FingerDetection fingerDetection;
    
	// Tworzenie planszy
	Board board;
    
    sf::Vector2f fingerPos(0,0);
    bool showFinger = false;
    
    sf::Clock clickClock;
    
    int lastHotRow=-1, lastHotCol=-1;

	// Glowna petla programu
	while(renderWindow.isOpen())
	{
		// Przejmowanie eventow
		while (renderWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				renderWindow.close();
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::D)
            {
                state = DETECT_BOARD;
                boardDetection.Reset();
            }
		}

        IplImage* frame = cvQueryFrame( capture );
        if (!frame)
        {
            fprintf( stderr, "ERROR: frame is null...\n" );
            getchar();
            break;
        }
        
        if(boardDetection.GetMask())
        {
            cvSet(frame, cvScalar(255,255,255), boardDetection.GetMask());
            cvShowImage("ROI", frame);
        }
        
		// Rysowanie
        if(state == NORMAL)
            renderWindow.clear(sf::Color::White);
        else
            renderWindow.clear(sf::Color::Black);
        
        UpdateView(renderWindow);
        
        if(state == NORMAL)
        {
            fingerDetection.Update(frame);
            DrawBoard(board, renderWindow, boardSprite, figuresSprites);
            
            sf::CircleShape c;
            c.setRadius(5.0f);
            c.setFillColor(sf::Color(255,0,0));
            sf::Vector2f f1 = fingerDetection.GetPos1();
            sf::Vector2f f2 = fingerDetection.GetPos2();
            
            bool lastShowFinger = showFinger;
            if(f1.x == 0 && f1.y==0)
                showFinger = false;
            else
                showFinger = true;
            
            f1 = boardDetection.CamToBoard(f1.y, f1.x);
            f2 = boardDetection.CamToBoard(f2.y, f2.x);
            
            f1 *= 600.0f; f1 -= sf::Vector2f(300, 300);
            f2 *= 600.0f; f2 -= sf::Vector2f(300, 300);
            
            if(showFinger)
                fingerPos = fingerPos*0.9f + f1*0.1f;
            if(lastShowFinger == false)
                fingerPos = f1;
            c.setPosition(fingerPos);
            if(showFinger)
                renderWindow.draw(c);
            
            if(showFinger)
            {
                if(clickClock.getElapsedTime().asSeconds() >= 2.0f)
                {
                    clickClock.restart();
                    // click!
                    std::cout << "click: "<<lastHotRow << "-" << lastHotCol<<"\n";
                } else
                {
                    sf::Vector2f fingerBoardSpace = fingerPos + sf::Vector2f(300, 300);
                    if(fingerBoardSpace.x < 0 || fingerBoardSpace.y < 0 ||
                            fingerBoardSpace.x > 600 || fingerBoardSpace.y >600)
                        clickClock.restart();
                    else
                    {
                        int currCol = int(fingerBoardSpace.x / 75.0f);
                        int currRow = int(fingerBoardSpace.y / 75.0f);
                        
                        if(currCol != lastHotCol || currRow != lastHotRow)
                        {
                            lastHotCol = currCol;
                            lastHotRow = currRow;
                            clickClock.restart();
                        }
                    }
                }
            } else
                clickClock.restart();
            
            //c.setPosition(f2);
            //renderWindow.draw(c);
        } else
        {
            if(boardDetection.Update(frame, renderWindow))
                state = NORMAL;
        }

		renderWindow.display();
        
        if ( (cvWaitKey(10) & 255) == 27 ) break;
	}

	return 0;
}

#endif
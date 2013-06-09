#include "Config.h"

//Zapomniałem o swoich palcach.

//WYKRYWANIE PALCÓW 1.0
//Binaryzuje obraz wykrywając kolor czerwony, i na tym zbinaryzowanym obrazie wykrywa kolorowe rzeczy na czubkach palców.
//*********** = ważne zmienne. Sądzę że obejdzie się bez ruszania reszty kodu.

//U mnie działa tak:
//Znośnie identyfikuje palec na współrzędnych:
//od (100,100) do (350,350)
//W praktyce jest to w przybliżeniu tak (pomiary bardzo niepewne)
//Przy odległości ok. 20-30 cm od kamerki macie pole do popisu około 20x20 cm, bądź troszkę większe

#include <iostream>
#ifdef _WIN32
#include <cv.h>
#include <highgui.h>
#else
#include <opencv/cv.h>
#include <opencv/highgui.h>
#endif
#include <fstream>

using namespace std;

IplImage* obraz1;



int palec1x = 0;
int palec1y = 0;
int palec2x = 0;
int palec2y = 0;

const int imheight=480;
const int imwidth=640;
const int helpsize=imwidth*imheight;									//możliwe że trzeba będzie jeszcze to powiększyć! INACZEJ MOŻE SIĘ SYYYYYYYYYYYYYYYYYYYYYYYYYYPAĆ!!!!

int tab_ind[imheight][imwidth];

int tabx[helpsize]; 
int taby[helpsize]; 

int tab_sort[helpsize];  //to jest taka tablica sklejeń, która dodatkowo liczy ilość pikseli.


//int tablica
//int tablica2 - rozmiary poszczeg. obiektów.
//potem dzielimy te palecnwsp przez ilość px
//i mamy śr x, śr y
//i na tamtym etapie mamy te x-y i y-i.
//i dla bezpieczeństwa wypiszemy.

//Wydobywamy odpowiedni kolor z obrazka, i binaryzujemy. I jeszcze erodujemy. Dwa razy. I dylatujemy też.
IplImage* Binaryzacja(IplImage* obraz_HSV){       

    IplImage* obraz_bin=cvCreateImage(cvGetSize(obraz_HSV),IPL_DEPTH_8U, 1);
	//AKTUALNIE WYKRYWANY KOLOR: Czerwony
	//Jeśli czujesz że zakres wyodrębnianych barw jest zbyt mały, możesz go zmienić w następnej linijce kodu.
    
    // rafal: boze, akurat czerwony jest w rangach H... zmieniam na NIEBIESKI
    //// H(60,100), S(50,255), V(50,255)
    float minH = 0; float maxH = 360;
    
    cvInRangeS(obraz_HSV, cvScalar(minH/2.0f, 0, 0), cvScalar(maxH/2.0f,255,50), obraz_bin);  //**********
	//IplImage* obraz_er=cvCreateImage(cvGetSize(obraz_HSV),IPL_DEPTH_8U, 1);
	//cvErode(obraz_bin, obraz_er, 0, 2);
	//IplImage* obraz_dyl=cvCreateImage(cvGetSize(obraz_HSV),IPL_DEPTH_8U, 1);
	//cvDilate(obraz_er, obraz_dyl, 0, 12);
    return obraz_bin;
	//Apropos cvErode i cvDilate: ostatni parametr to ILOŚĆ ITERACJI. 
	//Zwłaszcza przy erozji wypadałoby w fazie testowania pomanipulować. Mam zryty pokój, ale jak już kamerka będzie wskazywała na ekran kompa
	//który będzie całkowicie białoczarny, myślę że będzie można spokojnie zmniejszyć do 1 (a może nawet całkowicie wypierniczyć????), bo czerwonawych
	//rzeczy będzie w polu jej widzenia MNIEJ.
}

int getIndexValue(int i, int j)
{
	int value=0;

	int a=tab_ind[i-1][j-1];
	int b=tab_ind[i-1][j];
	int c=tab_ind[i-1][j+1];
	int d=tab_ind[i][j-1];
	

	if (a>0){	value=a;}
	if (b>0){	if (value>b) value=b;}
	if (c>0){	if (value>c) value=c;}
	if (d>0){	if (value>d) value=d;}
	

	return value;
}

int checkSurroundingIndexes(int i, int j, int value_to)
{
	int value_from=0;

	int a=tab_ind[i][j-1];
	int b=tab_ind[i][j+1];
	int c=tab_ind[i-1][j];
	int d=tab_ind[i-1][j];
	
	if (a!=0)	{	if (a!=value_to)	{	value_from=a;	}	}
	if (b!=0)	{	if (b!=value_to)	{	value_from=b;	}	}
	if (c!=0)	{	if (c!=value_to)	{	value_from=c;	}	}
	if (d!=0)	{	if (d!=value_to)	{	value_from=d;	}	}

	if (value_from==0)
	{
		value_from=value_to;
	}
	return value_from;
}


int test001()				//sprawdza ilość niezerowych elementów w tablicy sklejeń.
{
	int sum=0;
	for (int i=0;i<helpsize;i++)
	{
		if (tab_sort[i]>0)
		{
			sum++;
		}
	}
	return sum;
}

void indeksacja(IplImage* obraz_bin){
	//1. czyszczenie tablic

	for (int it1=0;it1<imheight;it1++)
	{
		for (int it2=0;it2<imwidth;it2++)
		{
			tab_ind[it1][it2]=0;
		}
	}
	for (int it3=0;it3<helpsize;it3++)
	{
		tabx[it3]=0;taby[it3]=0;tab_sort[it3]=0;
	}



	//2. Przejedź indeksacją

		int indeks=0;    
	
	CvScalar pixel2;
	CvScalar pixel;
	for (int ti = 1; ti < obraz_bin->height-1; ti++) {
    for (int tj = 1; tj < obraz_bin->width-1; tj++) {
     pixel = cvGet2D(obraz_bin, ti, tj);           // Here you have access to pixels values.
      if (pixel.val[0] == 255)						//białe!         
	  {
		  
		  int value=getIndexValue(ti,tj);
		  if (value==0)
		  {	//to znaczy że mamy nowy obiekt, bo w sąsiedztwie nie wykryto niczego o dziwnych kolorach.
			  indeks++;
			  tab_ind[ti][tj]=indeks;
			  tabx[indeks]=tabx[indeks]+ti;
			  taby[indeks]=taby[indeks]+tj;
			  tab_sort[indeks]++;
		  }
		  else
		  {
			  tab_ind[ti][tj]=value;
			  tabx[value]=tabx[value]+ti;
			  taby[value]=taby[value]+tj;
			  tab_sort[value]++;
		  }
	  }
	  else  //czarne - automatycznie 0.
	  {
		  tab_ind[ti][tj]=0;
	  }

    }  
	}

	//3. sklejanie


	for (int ti = 1; ti < obraz_bin->height-1; ti++) {
    for (int tj = 1; tj < obraz_bin->width-1; tj++) {
     pixel = cvGet2D(obraz_bin, ti, tj);           // Here you have access to pixels values.
      if (pixel.val[0] == 255)						//białe!         
	  {

		  int value_from=0;
		  int value_to=0;

		  value_to=tab_ind[ti][tj];
		  //value_from=getIndexValue(ti,tj);					//Uwaga: oże okazać się konieczne zrobienie nowej f-cji badającej CAŁE otoczenie piksela!
		  value_from=checkSurroundingIndexes(ti,tj,value_to);

		  if (value_to!=value_from)
			  //Czyli: w sąsiedztwie bieżącego piksela są piksele o innej wartości znacznika
		  {
			  tabx[value_to]=tabx[value_to]+tabx[value_from]; tabx[value_from]=0;
			  taby[value_to]=taby[value_to]+taby[value_from]; taby[value_from]=0;
			  tab_sort[value_to]=tab_sort[value_to]+tab_sort[value_from]; tab_sort[value_from]=0;
			  //
			  //Następny razem jak trafimy na coś z obszaru value_to, wartość tabx i taby się nie zmienią bo tabx[val_from] i taby[val_from] wynoszą 0.
		  }
	  }
	  else											//czarne!
	  {
		  //nic nie trzeba robić...
	  }
	}
	}
	

	//4. wybieramy 2 największe wartości z tab_sort (ilość px)
	
	
	
	int nw1=0;
	int nw2=0;
	int posnw1=0;
	int posnw2=0;


	for (int i=0;i<helpsize; i++)
	{
		if (tab_sort[i]>nw1) 
		{
			nw1=tab_sort[i];
			posnw1=i;
		}
		
	}
	for (int i=0;i<helpsize; i++)
	{
		if (tab_sort[i]>nw2) 
		{
			if (tab_sort[i]!=nw1)
				
			{
				nw2=tab_sort[i];
				posnw2=i;
			}
		}
			
			
	}

	//NIESŁYCHANIE WAŻNE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//TERAZ SPRAWDZAMY CZY OBA WYKRYTE OBSZARY SĄ DUŻE. JEŚLI NIE -> MAMY DO CZYNIENIA TYLKO Z JEDNYM, ZERUJEMY NW2 I DAJEMY TO NIŻEJ JAKO WARUNEK.
	//GENERALNIE SPRAWDZAMY ICH ROZMIAR, TJ. WARTOŚCI TAB_SORT[NW1] i TAB_SORT[NW2]
	//NIESŁYCHANIE WAŻNE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	//5. Wyliczamy współrzędne

	if (nw1>0)
	{
	palec1x=tabx[posnw1]/nw1;
	palec1y=taby[posnw1]/nw1;
	}
	else
	{
		palec1x=0; palec1y=0;
	}

		/*if (nw2>0)
	{
	palec2x=tabx[posnw2]/nw2;
	palec2y=taby[posnw2]/nw2;
	}
	else
	{
		palec2x=0; palec2y=0;
	}*/

		//I TUTAJ SĄ GOTOWE WSPÓŁRZĘDNE OBU PALCÓW.


		//POLIGON TESTOWY 4
		//cout<<"("<<palec1x<<","<<palec1y<<")  ("<<palec2x<<","<<palec2y<<")"<<endl;

}

void FindFingers(IplImage* frame)
{
    frame=cvCloneImage(frame); 
    //cvSmooth(frame, frame, CV_GAUSSIAN,3,3);
    IplImage* obraz_HSV = cvCreateImage(cvGetSize(frame), IPL_DEPTH_8U, 3);
    cvCvtColor(frame, obraz_HSV, CV_BGR2HSV);				
    IplImage* obraz_bin = Binaryzacja(obraz_HSV);  
	//cvSmooth(obraz_bin, obraz_bin, CV_GAUSSIAN,3,3); //?
	indeksacja(obraz_bin);  //znajdz palce
    
    cvShowImage("Binarized", obraz_bin);
    
    cvReleaseImage(&obraz_HSV);
	cvReleaseImage(&obraz_bin);
    cvReleaseImage(&frame);
}

#ifdef COMPILE_TEST_MIESZKO

int main(){

      CvCapture* capture =0;       
      capture = cvCaptureFromCAM(0);
      IplImage* frame=0;
      frame = cvQueryFrame(capture);           
      if(!frame) return -1;

      obraz1=cvCreateImage(cvGetSize(frame),IPL_DEPTH_8U, 3);
      cvZero(obraz1);   
      cvNamedWindow("Zbinaryzowane");
      cvNamedWindow("Oryginalny");
      cvNamedWindow("Dwa");

      while(true){
            frame = cvQueryFrame(capture);           
            if(!frame) break;
            
            FindFingers(frame, 0);

			//Przydatne.

            cvShowImage("Zbinaryzowane", obraz_bin);    

			cvReleaseImage(&obraz_HSV);
			cvReleaseImage(&obraz_bin);
                   
            cvReleaseImage(&frame);

            //Argument cvWaitKey to ilość milisekund 

            int c = cvWaitKey(100);  //***********
         
			//Warunek przerwania pętli. Aktualnie przerywa ją wciśnięcie esc.
			
            if((char)c == 27 ) {	//***********	
				break;      
			}

		}



      
      cvReleaseImage(&obraz1);
      cvReleaseCapture(&capture);     

      return 0;
}

 
#endif
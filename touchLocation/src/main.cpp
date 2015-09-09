#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <fstream>
#include "time.h"

using namespace std;
using namespace cv;

int frame=0;
int loc_x,loc_y;

void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
     if  ( event == EVENT_LBUTTONDOWN )
     {
		 loc_x = x;
		 loc_y = y;
         cout << "Left button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
     }
}

string getDate()
{
	time_t rawtime;
  struct tm * timeinfo;
  char buffer[80];

  time (&rawtime);
  timeinfo = localtime(&rawtime);

  strftime(buffer,80,"%d-%m-%Y_%I-%M-%S",timeinfo);
  std::string str(buffer);
  
  return str;
}

int main(int argc, char *argv[])
{
	int i=0;
	std::string path_to_experiments = "C:\\Users\\Henrique\\Desktop\\dataset\\data\\ws_white\\RGBuvMap\\";
	ofstream myfile;
	cout<<path_to_experiments+"touchLocation"+"_"+getDate()+".txt"<<endl;
	myfile.open(path_to_experiments+"touchLocation"+"_"+getDate()+".txt");

	//read frame from dataset
	while(true)
	{
		stringstream ss;
		ss << i++;
		string str = ss.str();
		cout<<path_to_experiments+str+".png"<<endl;
		Mat image = imread(path_to_experiments+str+".png");
		if( image.data )                              // Check for invalid input
		{
			
			//click on the point where the finger touches the table (if it occurs)
			//set the callback function for any mouse event
			imshow("My Window", image);
			setMouseCallback("My Window", CallBackFunc, NULL);	
			waitKey();

			//stores the x,y and the frame number 
			if(loc_x && loc_y != 0)
				myfile << frame << " " << loc_x << " " << loc_y << endl;
			
			loc_x = loc_y = 0;
			
			//enter to go to the next frame
			frame++;
		}
		else
		{			
			myfile.close();
			break;
		}
	}

	
	
	

	
	
	return 0;
	   
}



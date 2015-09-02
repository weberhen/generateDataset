#pragma once

#include <fstream> /**/
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include "DS325.h"

#include <stdio.h>  /* defines FILENAME_MAX */
#define WINDOWS
#ifdef WINDOWS
    #include <direct.h>
    #define GetCurrentDir _getcwd
#else
    #include <unistd.h>
    #define GetCurrentDir getcwd
#endif

using namespace cv;
using namespace std;

extern string verticesFloatingPoint_str;
extern string colorMap_str;
extern string confidenceMap_str;
extern string uvMap_str;

string createDirs(void);

template<typename T>
void saveToFile(InputArray _s, string fileName, int cont)
{
	std::ostringstream oss;
	oss << cont << ".txt";

	Mat s = _s.getMat();

	vector<Mat> channels(s.channels());
	split(s,channels);
	
	ofstream myfile;
	myfile.open (fileName+oss.str());
	
	for (int i = 0; i < s.rows;  i++){
		for (int j = 0; j < s.cols;  j++){
			for (int k = 0; k < s.channels();  k++){
				myfile << channels[k].at<T>(i,j)<<" ";
			}
			if(s.cols != 3)
				myfile<<endl;
		}
		if(s.cols == 3)
			myfile<<endl;
	}
	myfile.close();
}

void saveExperiment(Mat verticesFloatingPointArray, Mat depthMapFloatingPoint,Mat colorMap, Mat confMap, Mat uvMap);
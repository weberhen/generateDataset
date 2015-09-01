#pragma once

#include "DS325.h"
#include <stdlib.h>
#include <iostream>
#include <opencv2/core/core.hpp>

using namespace std;
using namespace cv;

namespace HandSegm{
	class ColorNode
	{

	private:
		static bool instanceFlag;
		static ColorNode *single;
		
		/*The color map. If captureConfiguration::compression is 
		DepthSense::COMPRESSION_TYPE_MJPEG, the output format is BGR, otherwise the 
		output format is YUY2. */
		Mat colorMap;
		
		ColorNode(void);

	public:
	
		static ColorNode* getInstance();

		void setColorMap(const DepthSense::Pointer< uint8_t >  &softdata);
		Mat getColorMap();
		
		~ColorNode(void){
			instanceFlag = false;
		}
	};
}


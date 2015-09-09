#pragma once

#include <iostream>
#include <opencv2/highgui/highgui.hpp>

#include "DS325.h"

using namespace std;
using namespace cv;

namespace HandSegm{
	class DepthNode
	{

	private:
		static bool instanceFlag;
		static DepthNode *single;
		
		/*The depth map in floating point format. This map represents the 
		cartesian depth of each pixel, expressed in meters. Saturated pixels 
		are given the special value -2.0. */
		Mat depthMapFloatingPoint;

		/*The vertices in floating point format. This map represents the 
		cartesian 3D coordinates of each pixel, expressed in meters. Saturated 
		pixels are given the special value -2.0. */
		Mat verticesFloatingPoint;

		/*Same of verticesFloatingPoint, but in array format [COLS*ROWS][3] */
		Mat verticesFloatingPointArray;

		/*The UV mapping. This map represents the normalized coordinates of 
		each pixel in the color map. Invalid pixels are given the special value
		-FLT_MAX. */
		Mat uvMap;
		
		/*the confidence map */
		Mat confidenceMap;

		Mat RGBuvmap;

		UV uv[240*320];

		DepthNode(void);

	public:
		
		static DepthNode* getInstance();

		void setDepthNode(DepthSense::DepthNode::NewSampleReceivedData data);

		void setDepthMapFloatingPoint(const Pointer< float >  &softdata);
		Mat getDepthMapFloatingPoint();

		void setVerticesFloatingPoint(const Pointer< DepthSense::FPVertex >  &softdata);
		Mat getVerticesFloatingPoint();

		void setUvMap(DepthSense::DepthNode::NewSampleReceivedData rec_data);
		
		void setConfMap(const Pointer< int16_t > &confidence);

		Mat getConfMap();

		Mat getVerticesFloatingPointArray();

		Mat getuvMap();

		Mat getRGBuvmap();

		void setRGBuvmap(Mat &uv);

		~DepthNode(void)
		{
			instanceFlag = false;
		}
	};
}
#include "DepthNode.hpp"
#include "opencv2/contrib/contrib.hpp"

HandSegm::DepthNode::DepthNode(void)
{
	depthMapFloatingPoint=Mat::zeros(ROWS,COLS,CV_32F);

	verticesFloatingPoint=Mat::zeros(ROWS,COLS,CV_32F);

	verticesFloatingPointArray=Mat::zeros(ROWS,COLS,CV_32F);

	confidenceMap=Mat::zeros(240, 320, CV_16S);

	RGBuvmap = Mat::zeros(ROWS,COLS,CV_8U);

}

bool HandSegm::DepthNode::instanceFlag = false;
HandSegm::DepthNode* HandSegm::DepthNode::single = NULL;

void HandSegm::DepthNode::setDepthNode(DepthSense::DepthNode::NewSampleReceivedData data){
	
	
	setDepthMapFloatingPoint(data.depthMapFloatingPoint);
	
	setVerticesFloatingPoint(data.verticesFloatingPoint);
	
	setUvMap(data);
	
	setConfMap(data.confidenceMap);

	setRGBuvmap(getuvMap());

}
/*pass depthmap (DS325) to Mat (openCV) in millimeters*/
void HandSegm::DepthNode::setDepthMapFloatingPoint(const Pointer< float >  &softdata)
{
	for(size_t i=0;i<ROWS;i++){
		for(size_t j=0;j<COLS;j++){
			depthMapFloatingPoint.at<float>(i,j)=softdata[i*COLS+j];
		}
	}
}

Mat HandSegm::DepthNode::getDepthMapFloatingPoint()
{
	return depthMapFloatingPoint.clone();
}

void HandSegm::DepthNode::setVerticesFloatingPoint(const Pointer< DepthSense::FPVertex >  &softdata)
{
	vector<Mat> channels(3);
  
	int c=0;
	while(c<3) channels[c++]=Mat::zeros(ROWS,COLS,CV_32F);

	for(size_t i=0;i<ROWS;i++){
		for(size_t j=0;j<COLS;j++){                
			channels[0].at<float>(i,j)=softdata[i*COLS+j].x;
			channels[1].at<float>(i,j)=softdata[i*COLS+j].y;
			channels[2].at<float>(i,j)=softdata[i*COLS+j].z;

			/*verticesFloatingPointArray.at<float>(i*COLS+j,0)=softdata[i*COLS+j].x;
			verticesFloatingPointArray.at<float>(i*COLS+j,1)=softdata[i*COLS+j].y;
			verticesFloatingPointArray.at<float>(i*COLS+j,2)=softdata[i*COLS+j].z;*/
		}
	}

	cv::merge(channels,verticesFloatingPoint);

}

Mat HandSegm::DepthNode::getVerticesFloatingPoint()
{
	return verticesFloatingPoint.clone();
}

void HandSegm::DepthNode::setUvMap(DepthSense::DepthNode::NewSampleReceivedData rec_data)
{
	
	for(int i=0;i<240;i++)
	{
		for(int j=0;j<320;j++)
		{
			uv[i*320+j]=rec_data.uvMap[i*320+j];		
		}
	}
}

void HandSegm::DepthNode::setConfMap(const Pointer< int16_t > &confidence)
{
	for (int i = 0; i < ROWS; i++)
		for (int j = 0; j < COLS; j++){
			confidenceMap.at<int16_t >(i,j) = confidence[i*COLS + j];
		}
}

Mat HandSegm::DepthNode::getConfMap()
{
	return confidenceMap.clone();
}

Mat HandSegm::DepthNode::getVerticesFloatingPointArray()
{
	return verticesFloatingPointArray.clone();
}

Mat HandSegm::DepthNode::getuvMap()
{
	Mat output;
	vector<Mat> channels(2);
	channels[0] = Mat(ROWS,COLS,CV_32FC1);
	channels[1] = Mat(ROWS,COLS,CV_32FC1);

	for (int i = 0; i < ROWS; i++)
		for (int j = 0; j < COLS; j++){
			channels[0].at<float>(i,j)=uv[i*320+j].u;
			channels[1].at<float>(i,j)=uv[i*320+j].v;
		}
	merge(channels,output);

	return output;
}

Mat HandSegm::DepthNode::getRGBuvmap()
{
	return RGBuvmap.clone();
}

void HandSegm::DepthNode::setRGBuvmap(Mat &uv)
{
	ColorNode *c = ColorNode::getInstance();
	Mat rgb = c->getColorMap();

	vector<Mat> channelsUV(3);
	vector<Mat> channelsRGB(3);
	vector<Mat> channelsRGBuvmap(3);
	split(uv,channelsUV);
	split(rgb,channelsRGB);
	
	for(int i=0;i<3;i++)
	{
		channelsRGBuvmap[i] = Mat(ROWS,COLS,CV_8UC1);
	}

	for(int i=0;i<ROWS;i++)
	{
		for(int j=0;j<COLS;j++)
		{
			if(channelsUV[0].at<float>(i,j)>0)
			{
				for(int c=0;c<3;c++)
				{
					int u = ROWS*channelsUV[1].at<float>(i,j);
					int v = COLS*channelsUV[0].at<float>(i,j);
					
					channelsRGBuvmap[c].at<uchar>(i,j) = channelsRGB[c].at<uint16_t>(u,v);
				}
			}
			else
			{
				for(int c=0;c<3;c++)
				{
					channelsRGBuvmap[c].at<uchar>(i,j) = 0;
				}
			}
		}
	}
	merge(channelsRGBuvmap,RGBuvmap);
		
}

	
HandSegm::DepthNode* HandSegm::DepthNode::getInstance()
{
    if(! instanceFlag)
    {
        single = new DepthNode();
        instanceFlag = true;
        return single;
    }
    else
    {
        return single;
    }
}
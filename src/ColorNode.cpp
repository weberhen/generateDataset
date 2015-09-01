#include "ColorNode.h"


HandSegm::ColorNode::ColorNode(void)
{
	colorMap=Mat::zeros(240,320,CV_8UC1);
}

bool HandSegm::ColorNode::instanceFlag = false;
HandSegm::ColorNode* HandSegm::ColorNode::single = NULL;

/*pass colorMap (DS325) to Mat (openCV) in BGR format*/
void HandSegm::ColorNode::setColorMap(const DepthSense::Pointer< uint8_t >  &softdata)
{
  vector<Mat> channels(3);

  for(size_t c=0;c<3;c++)
  {
    channels[c]=Mat::zeros(ROWS,COLS,CV_16U);
    for(size_t i=0;i<ROWS;i++){
      for(size_t j=0;j<COLS;j++){                
          channels[c].at<uint16_t>(i,j)=softdata[(i*2*COLS+j)*6+c];
        }
    }
  }

  cv::merge(channels,colorMap);
}

Mat HandSegm::ColorNode::getColorMap(){
	return colorMap.clone();
}

HandSegm::ColorNode* HandSegm::ColorNode::getInstance()
{
    if(! instanceFlag)
    {
        single = new ColorNode();
        instanceFlag = true;
        return single;
    }
    else
    {
        return single;
    }
}
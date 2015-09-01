#include <fstream> /**/
#include <opencv2/core/core.hpp>

using namespace cv;
using namespace std;

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
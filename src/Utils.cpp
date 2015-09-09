#include "Utils.h"
#include <Windows.h>
#include <iomanip>      // std::setprecision
#include "ColorNode.h"
#include "DepthNode.hpp"

string verticesFloatingPoint_str = "\\verticesFloatingPoint";
string colorMap_str = "\\colorMap";
string confidenceMap_str = "\\confidenceMap";
string uvMap_str = "\\uvMap";
string RGBuvMap_str = "\\RGBuvMap";

int frameCounter=0;
int experimentCounter = 0;
bool s_already_pressed=false;
bool new_experiment=true;

const int nFramesPerExperiment = 100;

vector <Mat> vec_verticesFloatingPointArray;
vector <Mat> vec_colorMap;
vector <Mat> vec_confMap;
vector <Mat> vec_uvMap;
vector <Mat> vec_RGBuvmap;

vector<string> name_dir;

std::wstring s2ws(const std::string& s)
{
    int len;
    int slength = (int)s.length() + 1;
    len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0); 
    wchar_t* buf = new wchar_t[len];
    MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
    std::wstring r(buf);
    delete[] buf;
    return r;
}

string createDirs(void)
{
	string root_data_dir = "data";
	
	//create data directory
	CreateDirectoryW(s2ws(root_data_dir).c_str(), NULL);

	string test_name;
	cout << "Enter the name of the experiment or `e` to exit: ";

	cin >> test_name;

	if(test_name != "e")
	{
		cout << "press `s` to start recording. " << endl;

		string verticesFloatingPoint_str_ext;
		string colorMap_str_ext;
		string confidenceMap_str_ext;
		string uvMap_str_ext;
		string RGBuvmap_str_ext;

		verticesFloatingPoint_str_ext = "data\\" + test_name + verticesFloatingPoint_str;
		colorMap_str_ext = "data\\" + test_name + colorMap_str;
		confidenceMap_str_ext = "data\\" + test_name + confidenceMap_str;
		uvMap_str_ext = "data\\" + test_name + uvMap_str;
		RGBuvmap_str_ext = "data\\" + test_name + RGBuvMap_str;

		CreateDirectoryW(s2ws("data\\"+test_name).c_str(), NULL);
		CreateDirectoryW(s2ws(verticesFloatingPoint_str_ext).c_str(), NULL);
		CreateDirectoryW(s2ws(colorMap_str_ext).c_str(), NULL);
		CreateDirectoryW(s2ws(confidenceMap_str_ext).c_str(), NULL);
		CreateDirectoryW(s2ws(uvMap_str_ext).c_str(), NULL);
		CreateDirectoryW(s2ws(RGBuvmap_str_ext).c_str(), NULL);
	}

	return test_name;
}

void saveExperiment(Mat &verticesFloatingPoint, Mat &depthMapFloatingPoint,Mat &colorMap, Mat &confMap, Mat &uvMap, Mat &RGBuvmap)
{
	char cCurrentPath[FILENAME_MAX];
	GetCurrentDir(cCurrentPath, sizeof(cCurrentPath));
	string working_path(cCurrentPath);
	working_path+=+"\\data\\";
	
	HandSegm::DepthNode *dep = HandSegm::DepthNode::getInstance();
	
	if(new_experiment)
	{
		name_dir.push_back(createDirs());
		new_experiment = false;
	}

	imshow("rgbuvmap",RGBuvmap);
	imshow("dep->getDepthMapFloatingPoint()",depthMapFloatingPoint);
	imshow("dep->getConfMap()",confMap);
	
	if(waitKey(1) == 's' || s_already_pressed == true)
	{
		if(!s_already_pressed)
		{
			cout << "Recording..." << endl;
		}
		s_already_pressed = true;

		vec_verticesFloatingPointArray.push_back(verticesFloatingPoint);
		vec_colorMap.push_back(colorMap);
		vec_confMap.push_back(confMap);
		vec_uvMap.push_back(uvMap);
		vec_RGBuvmap.push_back(RGBuvmap);

		frameCounter++;
	}

	if(frameCounter == nFramesPerExperiment)
	{
		cout << "Recording done." << endl;
		frameCounter = 0;
		s_already_pressed = false;
		experimentCounter++;
		new_experiment = true;
		destroyAllWindows();
	}

	if(name_dir.back() == "e")
	{
		destroyAllWindows();

		cout << "Recording complete." << endl;
		cout << "Saving " << experimentCounter << "experiments to disk..." << endl;
		
		for(int i=0;i<experimentCounter;i++)
		{
			cout<<"Saving experiment `" << name_dir[i] << "`" << endl;
			
			for(int j=0;j<nFramesPerExperiment;j++)
			{
				saveToFile<float>(vec_verticesFloatingPointArray[i*nFramesPerExperiment+j], working_path+"\\"+name_dir[i]+verticesFloatingPoint_str+"\\", j);
				saveToFile<int16_t>(vec_colorMap[i*nFramesPerExperiment+j], working_path+name_dir[i]+colorMap_str+"\\", j); 
				saveToFile<int16_t>(vec_confMap[i*nFramesPerExperiment+j], working_path+name_dir[i]+confidenceMap_str+"\\", j); 
				saveToFile<float>(vec_uvMap[i*nFramesPerExperiment+j], working_path+name_dir[i]+uvMap_str+"\\", j); 
				std::ostringstream oss;
				oss << j << ".png";
				imwrite( working_path+name_dir[i]+RGBuvMap_str+"\\"+oss.str(),vec_RGBuvmap[i*nFramesPerExperiment+j]);
				cout<< std::setprecision(3) << ((float)j/(float)nFramesPerExperiment)*100<<"%"<<endl;
			}
		}
		cout << "Saving complete." << endl;
		Sleep(1000);
		exit( 0 );
	}
}
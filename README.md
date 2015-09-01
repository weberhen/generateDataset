+-----------------------+
|Hand Segmentation code |
+-----------------------+

To run the code, it is necessary:

- OpenCV 2.4.9
- DepthSenseSDK-1.5.0.1205 or higher

----------------------
Using Visual Studio 2010 win 32

There are some environment variables that must be set if the Visual Studio Project will be used, which are:

SOFTKINETICINCLUDE----------------(C:\Program Files (x86)\SoftKinetic\DepthSenseSDK\include)
SOFTKINETICLIB-------------------------(C:\Program Files (x86)\SoftKinetic\DepthSenseSDK\lib)
OPENCVINCLUDE-----------------------(C:\opencv\build\include)
OPENCVLIB--------------------------------(C:\opencv\build\x86\vc10\lib)

The paths in parenthesis are just an example. You must adapt them according to your computer.

To compile the code from VS, just double click the "HP_Project.sln" file and then add the code to the VS project (in release mode).
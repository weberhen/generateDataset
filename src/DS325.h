#pragma once

// SoftKinetic DepthSense SDK
//
// COPYRIGHT AND CONFIDENTIALITY NOTICE - SOFTKINETIC CONFIDENTIAL
// INFORMATION
//
// All rights reserved to SOFTKINETIC SENSORS NV (a
// company incorporated and existing under the laws of Belgium, with
// its principal place of business at Boulevard de la Plainelaan 15,
// 1050 Brussels (Belgium), registered with the Crossroads bank for
// enterprises under company number 0811 341 454 - "Softkinetic
// Sensors").
//
// The source code of the SoftKinetic DepthSense Camera Drivers is
// proprietary and confidential information of Softkinetic Sensors NV.
//
// For any question about terms and conditions, please contact:
// info@softkinetic.com Copyright (c) 2002-2013 Softkinetic Sensors NV
#define ROWS 240
#define COLS 320

//#define WRITE_IMG

#include <stdlib.h>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <DepthSense.hxx>

using namespace cv;
using namespace std;
using namespace DepthSense;

#include "ColorNode.h"
#include "DepthNode.hpp"
#include "Utils.h"

extern Context g_context;
extern DepthNode g_dnode;
extern ColorNode g_cnode;

extern bool g_bDeviceFound;

extern ProjectionHelper* g_pProjHelper;
extern StereoCameraParameters g_scp;

/*----------------------------------------------------------------------------*/
static void onNewColorSample (ColorNode obj, ColorNode::NewSampleReceivedData data);

/*----------------------------------------------------------------------------*/
static void onNewDepthSample (DepthNode obj, DepthNode::NewSampleReceivedData data);

/*----------------------------------------------------------------------------*/
void configureDepthNode();

/*----------------------------------------------------------------------------*/
void configureColorNode();

/*----------------------------------------------------------------------------*/
void configureNode(Node node);

/*----------------------------------------------------------------------------*/
void onNodeConnected(Device device, Device::NodeAddedData data);

/*----------------------------------------------------------------------------*/
void onNodeDisconnected(Device device, Device::NodeRemovedData data);

/*----------------------------------------------------------------------------*/
void onDeviceConnected(Context context, Context::DeviceAddedData data);

/*----------------------------------------------------------------------------*/
void onDeviceDisconnected(Context context, Context::DeviceRemovedData data);
#include "DS325.h"

Context g_context;
DepthNode g_dnode;
ColorNode g_cnode;

uint32_t g_aFrames = 0;
uint32_t g_cFrames = 0;
uint32_t g_dFrames = 0;

bool g_bDeviceFound = false;

ProjectionHelper* g_pProjHelper = NULL;
StereoCameraParameters g_scp;

/*----------------------------------------------------------------------------*/
// New color sample event handler
static void onNewColorSample (ColorNode obj, ColorNode::NewSampleReceivedData data){	
	
	/******initializing singleton classes******/
	HandSegm::ColorNode *col;
	col=HandSegm::ColorNode::getInstance();
	/******************************************/

	col->setColorMap(data.colorMap);
}

int cont=0;

/*----------------------------------------------------------------------------*/
// New depth sample event handler
static void onNewDepthSample (DepthNode obj, DepthNode::NewSampleReceivedData data){
	
	/******initializing singleton classes******/
	HandSegm::DepthNode *dep = HandSegm::DepthNode::getInstance();
		
	HandSegm::ColorNode *col = HandSegm::ColorNode::getInstance();
	
	/******************************************/

	dep->setDepthNode(data);

	imshow("dep->getDepthMapFloatingPoint()",dep->getDepthMapFloatingPoint());

	//imshow("dep->getUvMapRGB()",dep->getUvMapRGB());

	imshow("dep->getConfMap()",dep->getConfMap());
	
	const string path = "C:\\Users\\Henrique\\Desktop\\dataset\\data\\";
	
	saveToFile<float>(dep->getVerticesFloatingPointArray(), path+"\\verticesFloatingPoint\\", cont);
	saveToFile<int16_t>(col->getColorMap(), path+"\\colorMap\\", cont);
	saveToFile<int16_t>(dep->getConfMap(), path+"\\confidenceMap\\", cont);
	saveToFile<float>(dep->getuvMap(), path+"\\uvMap\\", cont);

	cont++;
	waitKey(3);
}

/*----------------------------------------------------------------------------*/
void configureDepthNode()
{
    g_dnode.newSampleReceivedEvent().connect(&onNewDepthSample);

    DepthNode::Configuration config = g_dnode.getConfiguration();
    config.frameFormat = FRAME_FORMAT_QVGA;
    config.framerate = 25;
    config.mode = DepthNode::CAMERA_MODE_CLOSE_MODE;
    config.saturation = true;

	g_dnode.setEnableDepthMap(true);
	g_dnode.setEnableVertices(true);
    g_dnode.setEnableDepthMapFloatingPoint(true);
	g_dnode.setEnableVerticesFloatingPoint(true);
	g_dnode.setEnableUvMap(true);
	g_dnode.setEnableConfidenceMap(true);
	g_dnode.setEnablePhaseMap(true);
  
    try 
    {
        g_context.requestControl(g_dnode,0);

        g_dnode.setConfiguration(config);
    }
    catch (ArgumentException& e)
    {
        printf("Argument Exception: %s\n",e.what());
    }
    catch (UnauthorizedAccessException& e)
    {
        printf("Unauthorized Access Exception: %s\n",e.what());
    }
    catch (IOException& e)
    {
        printf("IO Exception: %s\n",e.what());
    }
    catch (InvalidOperationException& e)
    {
        printf("Invalid Operation Exception: %s\n",e.what());
    }
    catch (ConfigurationException& e)
    {
        printf("Configuration Exception: %s\n",e.what());
    }
    catch (StreamingException& e)
    {
        printf("Streaming Exception: %s\n",e.what());
    }
    catch (TimeoutException&)
    {
        printf("TimeoutException\n");
    }

}

/*----------------------------------------------------------------------------*/
void configureColorNode()
{
    // connect new color sample handler
    g_cnode.newSampleReceivedEvent().connect(&onNewColorSample);

    ColorNode::Configuration config = g_cnode.getConfiguration();
    config.frameFormat = FRAME_FORMAT_VGA;
    config.compression = COMPRESSION_TYPE_MJPEG;
    config.powerLineFrequency = POWER_LINE_FREQUENCY_50HZ;
    config.framerate = 25;

    g_cnode.setEnableColorMap(true);

    try 
    {
        g_context.requestControl(g_cnode,0);

        g_cnode.setConfiguration(config);
    }
    catch (ArgumentException& e)
    {
        printf("Argument Exception: %s\n",e.what());
    }
    catch (UnauthorizedAccessException& e)
    {
        printf("Unauthorized Access Exception: %s\n",e.what());
    }
    catch (IOException& e)
    {
        printf("IO Exception: %s\n",e.what());
    }
    catch (InvalidOperationException& e)
    {
        printf("Invalid Operation Exception: %s\n",e.what());
    }
    catch (ConfigurationException& e)
    {
        printf("Configuration Exception: %s\n",e.what());
    }
    catch (StreamingException& e)
    {
        printf("Streaming Exception: %s\n",e.what());
    }
    catch (TimeoutException&)
    {
        printf("TimeoutException\n");
    }
}

/*----------------------------------------------------------------------------*/
void configureNode(Node node)
{
    if ((node.is<DepthNode>())&&(!g_dnode.isSet()))
    {
        g_dnode = node.as<DepthNode>();
        configureDepthNode();
        g_context.registerNode(node);
    }

    if ((node.is<ColorNode>())&&(!g_cnode.isSet()))
    {
        g_cnode = node.as<ColorNode>();
        configureColorNode();
        g_context.registerNode(node);
    }

}

/*----------------------------------------------------------------------------*/
void onNodeConnected(Device device, Device::NodeAddedData data)
{
    configureNode(data.node);
}

/*----------------------------------------------------------------------------*/
void onNodeDisconnected(Device device, Device::NodeRemovedData data)
{
    if (data.node.is<ColorNode>() && (data.node.as<ColorNode>() == g_cnode))
        g_cnode.unset();
    if (data.node.is<DepthNode>() && (data.node.as<DepthNode>() == g_dnode))
        g_dnode.unset();
    printf("Node disconnected\n");
}

/*----------------------------------------------------------------------------*/
void onDeviceConnected(Context context, Context::DeviceAddedData data)
{
    if (!g_bDeviceFound)
    {
        data.device.nodeAddedEvent().connect(&onNodeConnected);
        data.device.nodeRemovedEvent().connect(&onNodeDisconnected);
        g_bDeviceFound = true;
    }
}

/*----------------------------------------------------------------------------*/
void onDeviceDisconnected(Context context, Context::DeviceRemovedData data)
{
    g_bDeviceFound = false;
    printf("Device disconnected\n");
}

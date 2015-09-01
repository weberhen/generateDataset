#include "DS325.h"

using namespace std;

int main (int argc, char** argv)
{
	g_context = Context::create("localhost");

    g_context.deviceAddedEvent().connect(&onDeviceConnected);
    g_context.deviceRemovedEvent().connect(&onDeviceDisconnected);

    // Get the list of currently connected devices
    vector<Device> da = g_context.getDevices();

    // We are only interested in the first device
    if (da.size() >= 1)
    {
        g_bDeviceFound = true;

        da[0].nodeAddedEvent().connect(&onNodeConnected);
        da[0].nodeRemovedEvent().connect(&onNodeDisconnected);

        vector<Node> na = da[0].getNodes();
        
        printf("Found %u nodes\n",na.size());
        
        for (int n = 0; n < (int)na.size();n++)
            configureNode(na[n]);
    }

    g_context.startNodes();

    g_context.run();

    g_context.stopNodes();

    if (g_cnode.isSet()) g_context.unregisterNode(g_cnode);
    if (g_dnode.isSet()) g_context.unregisterNode(g_dnode);

    if (g_pProjHelper)
        delete g_pProjHelper;

    return 0;
}
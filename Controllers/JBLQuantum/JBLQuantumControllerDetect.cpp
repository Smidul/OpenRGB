#include "Detector.h"
#include "JBLQuantumController.h"
#include "RGBController_JBLQuantum.h"
#include "ResourceManager.h"
#include <hidapi.h>

static bool jbl_device_registered = false;

void DetectJBLQuantum(hid_device_info *info, const std::string &name)
{
    if (info->interface_number != 5)
    {
        return;
    }

    if (info->usage_page != 0xFF13)
    {
        return;
    }

    if (jbl_device_registered)
    {
        return;
    }

    hid_device *dev = hid_open_path(info->path);
    if (dev)
    {
        JBLQuantumController *controller = new JBLQuantumController(dev, info->path);
        RGBController_JBLQuantum *rgb_controller = new RGBController_JBLQuantum(controller);
        ResourceManager::get()->RegisterRGBController(rgb_controller);

        jbl_device_registered = true;
    }
}

REGISTER_HID_DETECTOR("JBL Quantum", DetectJBLQuantum, 0x0ECB, 0x2088);

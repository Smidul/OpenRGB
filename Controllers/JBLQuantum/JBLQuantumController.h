#pragma once
#include "RGBController.h"
#include <hidapi.h>
#include <string>
#include <vector>

class JBLQuantumController
{
public:
    JBLQuantumController(hid_device *dev_handle, const char *path);
    ~JBLQuantumController();

    std::string GetDeviceLocation();
    std::string GetSerialString();

    void SetLEDs(std::vector<RGBColor> colors);

private:
    hid_device *dev;
    std::string location;
};

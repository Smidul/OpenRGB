#pragma once
#include "RGBController.h"
#include "JBLQuantumController.h"

class RGBController_JBLQuantum : public RGBController
{
public:
    RGBController_JBLQuantum(JBLQuantumController *controller_ptr);
    ~RGBController_JBLQuantum();

    void SetupZones() override;
    void ResizeZone(int zone, int new_size) override;
    void DeviceUpdateLEDs() override;
    void UpdateZoneLEDs(int zone) override;
    void UpdateSingleLED(int led) override;
    void DeviceUpdateMode() override;

private:
    JBLQuantumController *controller;
};

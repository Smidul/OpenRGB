#include "RGBController_JBLQuantum.h"

RGBController_JBLQuantum::RGBController_JBLQuantum(JBLQuantumController *controller_ptr)
{
    controller = controller_ptr;
    name = "JBL Quantum 910 Wireless";
    vendor = "JBL";
    type = DEVICE_TYPE_HEADSET;
    description = "JBL Quantum Headset Device";
    location = controller->GetDeviceLocation();
    mode Direct;
    Direct.name = "Direct";
    Direct.flags = MODE_FLAG_HAS_PER_LED_COLOR;
    Direct.color_mode = MODE_COLORS_PER_LED;
    modes.push_back(Direct);

    SetupZones();
}

RGBController_JBLQuantum::~RGBController_JBLQuantum()
{
    delete controller;
}

void RGBController_JBLQuantum::SetupZones()
{
    // Create 4 generic zones for the headset
    for (int i = 0; i < 4; i++)
    {
        zone new_zone;
        new_zone.name = "Zone " + std::to_string(i + 1);
        new_zone.type = ZONE_TYPE_SINGLE;
        new_zone.leds_min = 1;
        new_zone.leds_max = 1;
        new_zone.leds_count = 1;
        new_zone.matrix_map = NULL;
        zones.push_back(new_zone);

        led new_led;
        new_led.name = "LED " + std::to_string(i + 1);
        leds.push_back(new_led);
    }
    SetupColors();
}

void RGBController_JBLQuantum::ResizeZone(int zone, int new_size) {}

void RGBController_JBLQuantum::DeviceUpdateLEDs()
{
    controller->SetLEDs(colors);
}

void RGBController_JBLQuantum::UpdateZoneLEDs(int zone)
{
    DeviceUpdateLEDs();
}

void RGBController_JBLQuantum::UpdateSingleLED(int led)
{
    DeviceUpdateLEDs();
}

void RGBController_JBLQuantum::DeviceUpdateMode() {}

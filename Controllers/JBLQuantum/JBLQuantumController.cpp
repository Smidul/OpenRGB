#include "JBLQuantumController.h"
#include <thread>
#include <chrono>

#define JBL_REPORT_BRIGHTNESS 0x4C
#define JBL_REPORT_COLOR 0x4D
#define JBL_REPORT_ENABLE 0x40
#define JBL_REPORT_COMMIT 0x4B

using namespace std::chrono_literals;

JBLQuantumController::JBLQuantumController(hid_device *dev_handle, const char *path)
{
    dev = dev_handle;
    location = path;
}

JBLQuantumController::~JBLQuantumController()
{
    hid_close(dev);
}

std::string JBLQuantumController::GetDeviceLocation()
{
    return location;
}

std::string JBLQuantumController::GetSerialString()
{
    return "";
}

void JBLQuantumController::SetLEDs(std::vector<RGBColor> colors)
{
    for (int zone = 0; zone < 4; zone++)
    {
        // 1. Brightness Packet
        unsigned char brightness_packet[4] = {0};
        brightness_packet[0] = JBL_REPORT_BRIGHTNESS; // 0x4C
        brightness_packet[1] = zone;
        brightness_packet[2] = 0x64; // 100% Brightness (Hex 64)
        brightness_packet[3] = 0x01; // Enable Flag

        hid_send_feature_report(dev, brightness_packet, 4);
        std::this_thread::sleep_for(5ms);

        // 2. Colour Packet
        unsigned char color_packet[8] = {0};
        color_packet[0] = JBL_REPORT_COLOR; // 0x4D
        color_packet[1] = zone;
        color_packet[2] = 0x00;

        RGBColor current_color = colors[zone % colors.size()];
        color_packet[3] = RGBGetRValue(current_color);
        color_packet[4] = RGBGetGValue(current_color);
        color_packet[5] = RGBGetBValue(current_color);

        color_packet[6] = 0x01; // Static Mode
        color_packet[7] = 0x00;

        hid_send_feature_report(dev, color_packet, 8);
        std::this_thread::sleep_for(5ms);
    }

    // 3. Commit packet
    unsigned char commit_packet[2] = {0};
    commit_packet[0] = JBL_REPORT_COMMIT; // 0x4B
    commit_packet[1] = 0x01;

    hid_send_feature_report(dev, commit_packet, 2);
    std::this_thread::sleep_for(5ms);
}

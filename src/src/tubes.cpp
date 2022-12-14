#include "tubes.h"

void tubes::setup()
{
    // serial.listDevices();
	// vector <ofSerialDeviceInfo> deviceList = serial.getDeviceList();
    int baud = 9600;
    serial.setup(1, 115200);
// auto deviceDescriptors = ofx::IO::SerialDeviceUtils::listDevices();

//     if (!deviceDescriptors.empty())
//     {
//         ofLogNotice("ofApp::setup") << "Connected Devices: ";
//         for (auto deviceDescriptor: deviceDescriptors)
//         {
//             ofLogNotice("ofApp::setup") << "\t" << deviceDescriptor;
//         }

//         // Choose a device.
//         auto deviceDescriptor = deviceDescriptors[0];
        
//         // Connect to the first matching device.
//         bool success = device.setup(deviceDescriptor, 115200);

//         if (success)
//         {
//             ofLogNotice("ofApp::setup") << "Successfully setup " << deviceDescriptor;
//         }
//         else
//         {
//             ofLogNotice("ofApp::setup") << "Unable to setup " << deviceDescriptor;
//         }
//     }
//     else
//     {
//         ofLogNotice("ofApp::setup") << "No devices connected.";
//     }    

}

void tubes::sendKey(int valString)
{
   
    std::cout<<"SEnd: "<<valString<<std::endl;
    unsigned char b1, b2;
    b1 = valString & 255;
    b2 = valString >> 8 & 255;
    std::cout<<"Bytes :"<<b1<<" , "<<b2<<std::endl;
    serial.writeByte(b1); // LSB
	serial.writeByte(b2); // MSB

    //ofx::IO::ByteBuffer textBuffer(valString);

    //device.writeBytes(valString);
    //device.writeByte('\n');

}

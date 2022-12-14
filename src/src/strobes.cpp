#include "strobes.h"

void strobes::setup()
{
    ard.connect("/dev/ttyUSB0", 57600);
    ard.sendFirmwareVersionRequest();

    for(int i = 0; i < 6; i++)
    {
        strobe aux;
        strobes.push_back(aux);
    }
    bSetupArduino = false;
    int timeout = 0;
    strobeShutdown = true;
    ofLogNotice() << ard.getFirmwareName(); 
    ofLogNotice() << "firmata v" << ard.getMajorFirmwareVersion() << "." << ard.getMinorFirmwareVersion();
	}

void strobes::setupArduino(const int & version)
{
    ofLogNotice() << ard.getFirmwareName(); 
    ofLogNotice() << "firmata v" << ard.getMajorFirmwareVersion() << "." << ard.getMinorFirmwareVersion();
    
    // remove listener because we don't need it anymore
    ard.sendDigitalPinMode(2, ARD_OUTPUT);
    ard.sendDigitalPinMode(3, ARD_OUTPUT);
    ard.sendDigitalPinMode(4, ARD_OUTPUT);
    ard.sendDigitalPinMode(5, ARD_OUTPUT);
    ard.sendDigitalPinMode(6, ARD_OUTPUT);
    ard.sendDigitalPinMode(7, ARD_OUTPUT);
    strobePin[0] = 2;
    strobePin[1] = 3;
    strobePin[2] = 4;
    strobePin[3] = 5;
    strobePin[4] = 6;
    strobePin[5] = 7;
    bSetupArduino = true;
    std::cout<<"Strobes setup completed"<<std::endl;
}

void strobes::updateStrobe(int strobe, float value)
{
    strobes[strobe].updateInterval(ofMap(value, 0, 1.0, 0.0, 1.0));
}

void strobes::shutdownStrobes(bool state)
{
    strobeShutdown = state;
}

void strobes::updateArduino()
{
    ard.update();
    if(bSetupArduino)
    {
        for(int i = 0; i < 6; i++)
        {
            strobes[i].update();
            if(strobes[i].strobeOn && !strobeShutdown) 
            {
                ard.sendDigital(strobePin[i], ARD_HIGH);
            }
            else
            {
                ard.sendDigital(strobePin[i], ARD_LOW);
            }
        }
    }
}
   
#include "ofMain.h"
#include "ofxSerial.h"
class SerialMessage
{
public:
    SerialMessage(): fade(0)
    {
    }

    SerialMessage(const std::string& _message,
                  const std::string& _exception,
                  int _fade):
        message(_message),
        exception(_exception),
        fade(_fade)
    {
    }

    std::string message;
    std::string exception;
    int fade;
};

class tubes
{
public:
    void setup();
    void sendKey(int valString);

    ofxIO::BufferedSerialDevice device;

    std::vector<SerialMessage> serialMessages;

    ofSerial serial;


};
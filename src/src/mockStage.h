#include "ofMain.h"

// struct ledStrips
// {
//     glm::vec2 position;
//     int length;
    
// }
class mockStage
{
public:
    void setup();
    void updateLeds();
    void updateStrips(vector<float> channels);
    void draw();

private:
    vector <int> ledTubes;
    vector<float> ledStrips;
};
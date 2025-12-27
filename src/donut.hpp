#ifndef DONUT
#define DONUT

#include <vector>
using namespace std;

pair<vector<vector<float>>, vector<vector<float>>> generateDonutPoints (const float& R1, const float& R2, float& deltaAngle1, float& deltaAngle2, const int& N);
void rotateDonutPoints (vector<vector<float>>& DonutPoints, vector<vector<float>>& normalVectors, const vector<vector<float>>& rotationMatrix);
void drawFrame(vector<vector<float>>& screen, vector<vector<float>>& depth, 
               const vector<float>& LIGHTING_DIRECTION,
               vector<vector<float>>& DonutPoints, vector<vector<float>>& normalVectors,
               const float& R1, const float& R2, const string& ascii);

#endif

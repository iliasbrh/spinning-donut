#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <assert.h>
#include <donut.hpp>
#include <linear_algebra.hpp>

using namespace std;

pair<vector<vector<float>>, vector<vector<float>>> generateDonutPoints (const float& R1, const float& R2, float& deltaAngle1, float& deltaAngle2, const int& N) {
    vector<vector<float>> rotationGenerationMatrix = {
        {cos(deltaAngle2), -sin(deltaAngle2), 0},
        {sin(deltaAngle2), cos(deltaAngle2), 0},
        {0, 0, 1}};

    vector<vector<float>> donutPoints;
    vector<vector<float>> normalVectors;

    for (int i=0; i<N; ++i) {
        donutPoints.push_back({R1+R2*cos(deltaAngle1 * i), 0, R2*sin(deltaAngle1 * i)});
        normalVectors.push_back({R2*cos(deltaAngle1 * i), 0, R2*sin(deltaAngle1 * i)});
    }
    for (int i=0; i<N-1; ++i)
        for (int j=i*N; j<(i+1)*N; ++j) {
            donutPoints.push_back(linearTransform(rotationGenerationMatrix, donutPoints[j]));
            normalVectors.push_back(linearTransform(rotationGenerationMatrix, normalVectors[j]));
        }

    return {donutPoints, normalVectors};
}


void rotateDonutPoints (vector<vector<float>>& donutPoints, vector<vector<float>>& normalVectors, const vector<vector<float>>& rotationMatrix) {
    int length = donutPoints.size();
    for (int i=0; i<length; ++i) {
        donutPoints[i] = linearTransform(rotationMatrix, donutPoints[i]);
        normalVectors[i] = linearTransform(rotationMatrix, normalVectors[i]);
    }
}


void drawFrame(vector<vector<float>>& screen, vector<vector<float>>& depth, 
               const vector<float>& LIGHTING_DIRECTION,
               vector<vector<float>>& donutPoints, vector<vector<float>>& normalVectors,
               const float& R1, const float& R2, const string& ascii) {
    // reset screen
    int SCREENPOINTS_X = screen[0].size();
    int SCREENPOINTS_Y = screen.size();
    for (int i=0; i<SCREENPOINTS_Y; ++i)
        for (int j=0; j<SCREENPOINTS_X; ++j) {
            screen[i][j] = 0;
            depth[i][j] = 100;
        }
    
        
    // get light of each screen pixel
    float step_x = 2*(R1+R2) / SCREENPOINTS_X;
    float step_y = 2*(R1+R2) / SCREENPOINTS_Y;

    int x, y;
    int length = donutPoints.size();
    for (int i=0; i<length; ++i) {
        // les points se baladent dans [-4, 4] en x y z
        // on veut discrétiser [-4, 4] en x y pour screenpoints_x points en x et pour screenpoints_y en y
        // pour ça on a la variable step
        // on divise par step la coordonnée, on prend la partie entière et tada
        vector<float> proj = projection(donutPoints[i]);
        x = (proj[0]+R1+R2-0.001) / step_x;
        y = (proj[1]+R1+R2-0.001) / step_y;

        if (donutPoints[i][2] < depth[y][x]) {
            depth[y][x] = donutPoints[i][2];
            screen[y][x] = (dotProduct(normalVectors[i], LIGHTING_DIRECTION) + 1) / 2;
        }
    }
    

    // colorize each pixel with ascii
    int DISCRETE_COLORS = ascii.length();
    int color_index;
    string res = "";
    for (int i=0; i<SCREENPOINTS_Y; ++i) {
        for (int j=0; j<SCREENPOINTS_X; ++j) {
            color_index = DISCRETE_COLORS * screen[i][j];
            res += ascii[color_index];
        }
        res += "\n";
    }
    cout << "\033[" << 31 << "m";
    cout << "\x1b[H" << res;
    
}






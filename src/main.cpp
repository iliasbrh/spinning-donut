#include <thread>
#include <iostream>
#include <vector>
#include <cmath>
#include <donut.hpp>
#include <linear_algebra.hpp>

using namespace std;

// ---------- Parameters ----------
// to initialize donut points
constexpr int N = 200;
constexpr float circle = 2 * M_PI;
constexpr float R1 = 3.;
constexpr float R2 = 1.;

float deltaAngle1 = circle / N;
float deltaAngle2 = circle / N;


// to animate
float deltaAngleAnimation = 0.05;
constexpr int TARGET_FPS = 20;
constexpr chrono::seconds delta_time(1/TARGET_FPS);

vector<vector<float>> rotationAnimationMatrix = { 
    {cos(deltaAngleAnimation), 0, -sin(deltaAngleAnimation)}, 
    {0, 1, 0}, 
    {sin(deltaAngleAnimation), 0, cos(deltaAngleAnimation)}};

vector<vector<float>> base_change = { // randomly generated orthogonal matrix
    {0.2672612419f,  0.8728715609f,  0.4082482905f},
    {0.5345224838f,  0.2182178902f, -0.8164965809f},
    {0.8017837257f, -0.4364357805f,  0.4082482905f}};
vector<vector<float>> base_change_inverted = {
    {0.2672612419f, 0.53452248390f, 0.8017837257f},
    {0.8728715609f, 0.21821789026f, -0.436435780f},
    {0.4082482904f, -0.8164965809f, 0.4082482904}};
vector<vector<float>> randomizedRotationMatrix = matrixMultiplication(matrixMultiplication(base_change, rotationAnimationMatrix), base_change_inverted);


// to color
vector<float> LIGHTING_DIRECTION = normalize({1, 1, -1});


// to render
constexpr int SCREENPOINTS_X = 70;
constexpr int SCREENPOINTS_Y = 30;
constexpr float step_x = 2*(R1+R2) / SCREENPOINTS_X;
constexpr float step_y = 2*(R1+R2) / SCREENPOINTS_Y;
vector<vector<float>> screen(SCREENPOINTS_Y, vector<float>(SCREENPOINTS_X, 0));
vector<vector<float>> depth(SCREENPOINTS_Y, vector<float>(SCREENPOINTS_X, 100));

const string ascii = " `.-_^;<!cj2dB%@";

// ----------------------------------------


int main() {
    auto [donutPoints, normalVectors] = generateDonutPoints(R1, R2, deltaAngle1, deltaAngle2, N);
    

    while (true) {
        this_thread::sleep_for(delta_time);
        rotateDonutPoints(donutPoints, normalVectors, randomizedRotationMatrix);
        drawFrame(screen, depth, LIGHTING_DIRECTION, donutPoints, normalVectors, R1, R2, ascii);
    }

    return 0;
}
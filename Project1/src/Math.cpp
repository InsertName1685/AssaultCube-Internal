#include<cmath>
#include "Math.h"

#define _USE_MATH_DEFINES
#define M_PI 3.14159265358979323846


bool Math::worldToScreen(vec_3 pos, vec_2& screen, viewMatrix matrix, int windowWidth, int windowHeight) {

    vec_4 clipCoords;
    clipCoords.x = pos.x * matrix.matrix[0] + pos.y * matrix.matrix[4] + pos.z * matrix.matrix[8] + matrix.matrix[12];
    clipCoords.y = pos.x * matrix.matrix[1] + pos.y * matrix.matrix[5] + pos.z * matrix.matrix[9] + matrix.matrix[13];
    clipCoords.z = pos.x * matrix.matrix[2] + pos.y * matrix.matrix[6] + pos.z * matrix.matrix[10] + matrix.matrix[14];
    clipCoords.w = pos.x * matrix.matrix[3] + pos.y * matrix.matrix[7] + pos.z * matrix.matrix[11] + matrix.matrix[15];

    if (clipCoords.w < 0.001f) {
        return false;
    }


    vec_3 NDC;
    NDC.x = clipCoords.x / clipCoords.w;
    NDC.y = clipCoords.y / clipCoords.w;
    NDC.z = clipCoords.z / clipCoords.w;

    screen.x = (windowWidth / 2 * NDC.x) + (NDC.x + windowWidth / 2);
    screen.y = -(windowHeight / 2 * NDC.y) + (NDC.y + windowHeight / 2);

    return true;
}

bool Math::lookAt(vec_3 cameraPos, vec_3 target, vec_2& rotation) // needs a vec 2 as we are not gona rotate the camera on the z axis
{

    vec_3 delta;    // Find distance between myself and nearest enemy
    delta.x = (target.x - cameraPos.x);
    delta.y = (target.y - cameraPos.z);
    delta.z = (target.z - cameraPos.y);
    float yaw = atan2f(delta.y, delta.x) * 180 / M_PI;         // Find angle for x direction

    float hyp = sqrt(delta.x * delta.x + delta.y * delta.y);   // Find angle for y direction
    float pitch = atan2f(delta.z, hyp) * 180 / M_PI;

    //pitch + 90; // Assault Cube mechanics
    yaw += 90;
    rotation.x = yaw;
    rotation.y = pitch;
    return true;
}


float Math::Magnitude(vec_2 from, vec_2 to) {
    float deltaX = to.x - from.x;
    float deltaY = to.y - from.y;

    return sqrt((deltaX * deltaX) + (deltaY * deltaY));
}

float Math::Magnitude3(vec_3 from, vec_3 to) {
    
    float deltaX = to.x - from.x;
    float deltaY = to.y - from.y;
    float deltaZ = to.z - from.z;
    return sqrt((deltaX * deltaX) + (deltaY * deltaY)  +  (deltaZ * deltaZ));
}

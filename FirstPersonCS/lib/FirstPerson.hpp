#pragma once
#include<QtCore>
#include<QtGui>
#include<vector>
#include<cmath>

struct dda {
    float RayStartX = 0;
    float RayStartY = 0;
    float RayAngel = 0;
    float RayEndX = 0;
    float RayEndY = 0 ;
    float Raylength = 0;
    float Raylength3D = 0;
    bool HorizontalHit = false;
    bool VerticalHit = false;
};

class Map;
class Display3D;

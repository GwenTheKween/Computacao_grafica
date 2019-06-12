#ifndef STRUCTS_H
#define STRUCTS_H

#include <vector>
#include <QPoint>

#define DEFAULTMINX 0
#define DEFAULTMAXX 800
#define DEFAULTMINY 0
#define DEFAULTMAXY 600
#define DEFAULTMINZ -1
#define DEFAULTMAXZ 10

using namespace std;

typedef struct Edge {
    int yMax;
    int x;
    float slope;
    int deltaX;
    int deltaY;
} Edge;

typedef struct Polygon {
    vector<vector<float> > vertices;
    double color[4];
} Polygon;

enum ShadingMethods {
    FLAT    = 0,
    GOURAUD = 1,
    PHONG   = 2
};

#endif // STRUCTS_H

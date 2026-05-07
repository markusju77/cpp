// Language: C++
// Usage: Compile with `g++ pixel_glut.cpp -o pixel_glut -lglut -lGL -lGLU` on Linux
//        On Windows with FreeGLUT, link against opengl32 and glut32 libraries.
/**
 * plus key to increase initial speed
 * minus key to decrease initial speed
 * up arrow to increase angle
 * down arrow to decrease angle
 * enter key to launch projectile

 Author: Markus Juhala
 */
#include <windows.h>
#include <mmsystem.h>
#include <GL/glut.h>
#include <fstream>
#include <vector>
#include <cmath>
#include <iostream>
#include <chrono>
#include <thread>
#include <stack>
#include "physic2.h"
#include "sound.h"
#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"     // must be after the #define
#pragma comment(lib, "winmm.lib")
using namespace std;

// Window dimensions
const int width=1536;
const int height=864;
int window_width;
int window_height;
int angle = 0;
int angle2 = 0;
int initialSpeed = 10;
int initialSpeed2 = 10;
int tower1_x = 10;
int tower2_x = 0.8 * width;
const int towerHeight = 30;
const int towerWidth = 20;
const int tower2Height = 30;
int towerCannon = 10;
int towerBaseY = 0;
int tower2BaseY = 0;
int towerCannonY2 = 5;
int tower_projectile=10;
int turn=1; // 1 = player one, 2 = player two
bool player1_hit = false;
bool player2_hit = false;
bool gameOver = false;
std::string statusMessage = "";
int player1Score = 0;
int player2Score = 0;
bool tower1_alive = true;
bool tower2_alive = true;
bool starField = false;
bool cannonFiring = false;
float cannonTimer = 0.0f;
float cannonDelay = 0.5f; // 500 ms ennen ammusta


struct Color{
    float r, g, b, a;
};

struct Point {
    int x=0, y=0;
    Color color;
    bool occupied = false;
    Point() = default;
    Point(int xx, int yy) : x(xx), y(yy), color{1.0f,1.0f,1.0f,1.0f}, occupied(false) {}
};
struct Brush {
    int w,h;
    std::vector<Color> px; // filled from file
};
vector<Point> stars;
Brush brush;
Brush towerBrush;

//Point obstacles [width][height];
Point obstacles [height][width]; // Note: [y][x] for easier access
Point goalArea1 [height][width];
Point goalArea2 [height][width];
Point scoreBoard[350][width]; 
// Grid size
//const int ROWS = 66;
//const int COLS = 250;
constexpr int ROWS = 66;
constexpr int COLS = 250;
const float CELL_SIZE = 0.2f;
Color towerColor = {0.6f, 0.6f, 0.6f, 1.0f}; // Gray color
#define SND_MEMORY 0x0004
std::vector<char> wavData;

void loadWavToMemory() {
    std::ifstream file("cannon2.wav", std::ios::binary);
    wavData = std::vector<char>(std::istreambuf_iterator<char>(file), {});
}


// very minimal 24‑bit BMP loader
bool loadBMP(const char *path, int &outW, int &outH,
             std::vector<uint8_t> &outRGB)        // RGB triples, row‑major, top‑left first
{
    FILE *f = fopen(path, "rb");
    if (!f) return false;
    uint8_t hdr[54];
    if (fread(hdr, 1, 54, f) != 54) { fclose(f); return false; }
    outW = *(int*)&hdr[18];
    outH = *(int*)&hdr[22];
    int bpp = *(short*)&hdr[28];
    if (bpp != 24) { fclose(f); return false; }

    int rowBytes = ((outW * 3 + 3) / 4) * 4;   // padded scan‑line size
    std::vector<uint8_t> buf(rowBytes * outH);
    for (int y = 0; y < outH; ++y) {
        if (fread(&buf[y * rowBytes], 1, rowBytes, f) != (size_t)rowBytes) {
            fclose(f);
            return false;
        }
    }
    fclose(f);

    // copy into outRGB flipping vertically and switching B<->R
    outRGB.resize(outW * outH * 3);
    for (int y = 0; y < outH; ++y) {
        int srcRow = (outH - 1 - y) * rowBytes;      // bottom‑up -> top‑down
        int dstRow = y * outW * 3;
        for (int x = 0; x < outW; ++x) {
            outRGB[dstRow + x*3 + 0] = buf[srcRow + x*3 + 2];  // R
            outRGB[dstRow + x*3 + 1] = buf[srcRow + x*3 + 1];  // G
            outRGB[dstRow + x*3 + 2] = buf[srcRow + x*3 + 0];  // B
        }
    }
    return true;
}

void initBrush(const char *filename)
{
    int w,h,ch;
    unsigned char *data = stbi_load(filename,&w,&h,&ch,4);   // force RGBA
    if (!data) {
        std::cerr<<"couldn't load "<<filename<<"\n";
        return;
    }

    brush.w = w;
    brush.h = h;
    brush.px.resize(w*h);

    // copy bytes → float, keep order exactly as returned
    for(int y=0;y<h;++y){
        for(int x=0;x<w;++x){
            int bi = (y*w + x)*4;            // byte index in data[]
            int ii = y*w + x;                // index in brush.px
            brush.px[ii].r = data[bi+0]/255.0f;
            brush.px[ii].g = data[bi+1]/255.0f;
            brush.px[ii].b = data[bi+2]/255.0f;
            brush.px[ii].a = data[bi+3]/255.0f;
        }
    }

    stbi_image_free(data);

    std::cout<<"brush "<<w<<"×"<<h<<" loaded from "<<filename<<"\n";
}

void initTowerBrush(const char *filename)
{
    int w,h,ch;
    unsigned char *data = stbi_load(filename,&w,&h,&ch,4);   // force RGBA
    if (!data) {
        std::cerr<<"couldn't load tower brush "<<filename<<"\n";
        return;
    }

    towerBrush.w = w;
    towerBrush.h = h;
    towerBrush.px.resize(w*h);

    // copy bytes → float, keep order exactly as returned
    for(int y=0;y<h;++y){
        for(int x=0;x<w;++x){
            int bi = (y*w + x)*4;            // byte index in data[]
            int ii = y*w + x;                // index in towerBrush.px
            towerBrush.px[ii].r = data[bi+0]/255.0f;
            towerBrush.px[ii].g = data[bi+1]/255.0f;
            towerBrush.px[ii].b = data[bi+2]/255.0f;
            towerBrush.px[ii].a = data[bi+3]/255.0f;
        }
    }

    stbi_image_free(data);

    std::cout<<"tower brush "<<w<<"×"<<h<<" loaded from "<<filename<<"\n";
}

inline bool inBounds(int x, int y){
    return x >= 0 && x < width && y >= 0 && y < height;
}

static void drawText(const char* text, int x, int y){
    glRasterPos2i(x, y);
    while (*text){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *text++);
    }
}

void drawScoreBoardBackground(){
    const int barHeight = 90;
    int w = (window_width > 0 ? window_width : width);
    int h = (window_height > 0 ? window_height : height);

    glColor4f(0.0f, 0.0f, 0.0f, 0.55f);
    glBegin(GL_QUADS);
        glVertex2i(0, h);
        glVertex2i(w, h);
        glVertex2i(w, h - barHeight);
        glVertex2i(0, h - barHeight);
    glEnd();
}

void drawScoreBoard(){
    drawScoreBoardBackground();

    int h = (window_height > 0 ? window_height : height);
    char buf[128];
    glColor3f(1.0f, 1.0f, 1.0f);

    sprintf(buf, "Player 1 angle (arrow up and down): %d", angle);
    drawText(buf, 10, h-20);
    sprintf(buf, "Player 1 speed (+ or -): %d", initialSpeed);
    drawText(buf, 10, h-40);

    sprintf(buf, "Player 2 angle (arrow up and down): %d", angle2);
    drawText(buf, 410, h-20);
    sprintf(buf, "Player 2 speed (+ or -): %d", initialSpeed2);
    drawText(buf, 410, h-40);

    if (!statusMessage.empty()){
        int w = (window_width > 0 ? window_width : width);
        int h = (window_height > 0 ? window_height : height);
        drawText(statusMessage.c_str(), w/2 - 80, h - 100);
    }

    if (gameOver){
        const char *result = "";
        if (player1_hit) result = "Player 1 wins!";
        else if (player2_hit) result = "Player 2 wins!";
        else result = "Game Over";

        int w = (window_width > 0 ? window_width : width);
        int h = (window_height > 0 ? window_height : height);
        drawText(result, w/2 - 80, h - 60);
        drawText("Press R to reset", w/2 - 80, h - 40);
    }
}

void paintTowerBrushAtLocation(int centerX, int baseY, Point goalArea[][1536])
{
    if (towerBrush.w == 0 || towerBrush.h == 0) {
        std::cout << "Tower brush not loaded\n";
        return;
    }

    std::cout << "Painting tower at centerX=" << centerX << " baseY=" << baseY << " brush size=" << towerBrush.w << "x" << towerBrush.h << " (scaled 0.5x)\n";
    
    int painted = 0;
    int scaledW = towerBrush.w / 2;
    int scaledH = towerBrush.h / 2;
    
    // Paint tower at half scale
    for(int dy = 0; dy < scaledH; ++dy) {
        for(int dx = 0; dx < scaledW; ++dx) {
            int x = centerX + dx - scaledW / 2;  // center horizontally at half size
            int y = baseY + dy;                  // draw upward from baseY
            
            if (!inBounds(x, y)) continue;
            
            // Sample from doubled source coordinates (scale source 2x)
            int src_dx = dx * 2;
            int src_dy = dy * 2;
            int by = towerBrush.h - 1 - src_dy;  // flip image vertically
            
            Color c = towerBrush.px[by * towerBrush.w + src_dx];
            if (c.a < 0.1f) continue;  // skip transparent pixels
            
            obstacles[y][x].color = c;
            obstacles[y][x].occupied = true;
            goalArea[y][x].occupied = true;  // Mark as goal area
            painted++;
        }
    }
    std::cout << "Tower painted " << painted << " pixels\n";
}

Point calculateBezierPoint(float t, Point p0, Point p1, Point p2, Point p3) {
    float u = 1.0f - t;
    float tt = t * t;
    float uu = u * u;
    float uuu = uu * u;
    float ttt = tt * t;

    Point p;
    p.x = static_cast<int>(uuu * p0.x + 3 * uu * t * p1.x + 3 * u * tt * p2.x + ttt * p3.x);
    p.y = static_cast<int>(uuu * p0.y + 3 * uu * t * p1.y + 3 * u * tt * p2.y + ttt * p3.y);

    return p;
}

   

std::vector<Point> generateBezierCurve(Point p0, Point p1, Point p2, Point p3, int numPoints) {
    std::vector<Point> curvePoints;
    for (int i = 0; i < numPoints; ++i) {
        // Calculate t value from 0.0 to 1.0
        float t = static_cast<float>(i) / static_cast<float>(numPoints - 1);
        Point p = calculateBezierPoint(t, p0, p1, p2, p3);
        curvePoints.push_back(p);
    }
    return curvePoints;
}

void drawPixel(int x, int y){
    glEnable(GL_POINT_SMOOTH);       // Enable smoothing for points
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    // Draw single pixel
    glBegin(GL_POINTS);
        glVertex2i(x, y); // Pixel position (x, y)
    glEnd();

}

void drawStars(){
    if (stars.empty()) {
        // Generate star positions once
        for (int i = 0; i < 200; ++i) {
            int x = rand() % (window_width > 0 ? window_width : width);
            int y = rand() % (window_height > 0 ? window_height : height);
            stars.push_back(Point(x, y));
        }
    }

    glColor3f(1.0f, 1.0f, 1.0f);
    for (const Point &p : stars) {
        drawPixel(p.x, p.y);
    }
}

// No longer needed, but kept for reference
void drawStarsInVector(){
    // unchanged; old style
}

void drawObstacleDot(int x, int y){
    // Set pixel color (Red)
    glColor3f(100.0f / 255.0f, 30.0f / 255.0f, 30.0f / 255.0f);
    drawPixel(x-2,y);

    //glColor3f(165.0f / 255.0f, 42.0f / 255.0f, 42.0f / 255.0f);
    drawPixel(x-1,y);
    //glColor3f(1.0f, 1.0f, 1.0f);
    glColor3f(165.0f / 255.0f, 42.0f / 255.0f, 42.0f / 255.0f);
    drawPixel(x,y);
        
    drawPixel(x+1,y);
    drawPixel(x,y-1);
    drawPixel(x,y+1);

    glColor3f(100.0f / 255.0f, 30.0f / 255.0f, 30.0f / 255.0f);
    drawPixel(x,y+2);
}

void drawObstacleLine(int x, int y){
    while(x < width){
        drawObstacleDot(x,y);
        x+=2;    
    }
}

void drawObstacle(int x, int y){
    while(y > 0){
        drawObstacleLine(x,y);
        y-=2;    
    }
}

/*
inline bool inBounds(int x, int y){
    return x >= 0 && x < width && y >= 0 && y < height;
}
*/
void paintWithBrush(int cx,int cy){
    for(int dy=0; dy<brush.h; ++dy){
        for(int dx=0; dx<brush.w; ++dx){
            int x = cx + dx - brush.w/2;
            int y = cy + dy - brush.h/2;
            if (!inBounds(x,y)) continue;
            Color c = brush.px[dy*brush.w + dx];
            if (c.a < 0.1f) continue;          // skip transparent
            obstacles[y][x].color = c;
            obstacles[y][x].occupied = true;
        }
    }
}

inline void markObstaclePixel(int x, int y, const Color &c){
    //cout << "Marking obstacle pixel at (" << x << "," << y << ")" << endl;
    //cout << "Color RGBA: (" << c.r << "," << c.g << "," << c.b << "," << c.a << ")" << endl;
    if(!inBounds(x,y)) return;
    obstacles[y][x].x = x;
    obstacles[y][x].y = y;
    obstacles[y][x].color = c;
    obstacles[y][x].occupied = true;
    // Avoid immediate GL drawing or console I/O here; drawing is done in drawObstacles()
}

void bresenhamLineAllDirections(int x0, int y0, int x1, int y1, const Color &c) {
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    int err = dx - dy;
    cout << "Drawing AllDirectionsBresenham line from (" << x0 << "," << y0 << ") to (" << x1 << "," << y1 << ")" << endl;
    
    while(true) {
        markObstaclePixel(x0, y0, c);

        if (x0 == x1 && y0 == y1) break;

        int e2 = 2 * err;
        if (e2 >= -dy) { // Käytä dy, ei dx kuten kommentoiduissa osissa oli
            err -= dy;
            x0 += sx;
        }
        if (e2 <= dx) { // Käytä dx, ei dy kuten kommentoiduissa osissa oli
            err += dx;
            y0 += sy;
        }
    }
}

void bresenhamLine(int x0, int y0, int x1, int y1, const Color &c){
    // Oletetaan tässä yksinkertaistetussa esimerkissä, että x0 < x1 ja |dx| >= |dy|.
    // Täydellinen toteutus vaatisi suuntien ja oktanttien käsittelyn.

    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int p = 2 * dy - dx;
    int const1 = 2 * dy;
    int const2 = 2 * (dy - dx); // Korjattu laskenta
    cout << "Drawing Bresenham line from (" << x0 << "," << y0 << ") to (" << x1 << "," << y1 << ")" << endl;
    
    // Määritä suunta y-akselilla
    int y_step = (y0 < y1) ? 1 : -1;

    int x = x0;
    int y = y0;
    
    markObstaclePixel(x, y, c);

    while(x < x1){
        x++;
        if(p < 0) {
            p += const1;
        }
        else {
            y += y_step; // Käytä määritettyä suuntaa
            p += const2; // Käytä korjattua const2
        }
        markObstaclePixel(x, y, c);
    }
}

// Bresenham line between two integer points (marks obstacles + draws)
/*
void bresenhamLine(int x0, int y0, int x1, int y1, const Color &c){
    int dx = abs(x0 - x1);
    int dy = abs(y0 - y1);
    int p = 2 * dy - dx;
    int const1 = 2 * dy;
    int const2 = 2 * (dy + dx);
    glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
    cout << "Drawing Bresenham line from (" << x0 << "," << y0 << ") to (" << x1 << "," << y1 << ")" << endl;
    int x=0;
    int y=0;
    int x_end=0;

    if(x0 > x1){
        x=x1;
        y=y1;
        x_end=x0;  
    } else {
        x=x0;
        y=y0;
        x_end=x1;  
    }
    //drawPixel(x,y);
    markObstaclePixel(x,y,c);
    while(x < x_end){
        
        markObstaclePixel(x0, y0, c);
        if (x0 == x1 && y0 == y1) break;
       // int e2 = 2 * err;
       // if (e2 >= dy) { err += dy; x0 += sx; }
       // if (e2 <= dx) { err += dx; y0 += sy; }
        x++;
        if(p < 0) p = p + const1;
        else {
            y += 1;
            p = p + const2;
        }
        markObstaclePixel(x, y, c);
        //drawPixel(x,y);
    }
}
*/
/*
void drawPattern(int x, int y){
    if(obstacles[y][x] == 1){ // Use [y][x] to match [ROWS][COLS] declaration
        drawObstacleDot(x,y);
    }
}

void drawPattern2(int x, int y){
    // Calculate the Y index by subtracting the current Y from the maximum ROWS index (65)
    int flippedY = ROWS - 1 - y; 
    
    // Ensure we don't access out of bounds accidentally (safety check)
    if (x >= 0 && x < COLS && flippedY >= 0 && flippedY < ROWS) {
        if(obstacles[flippedY][x] == 1){ 
            drawObstacleDot(x,y); // Draw at the actual screen Y coordinate
        }
    }
}

// [ROWS][COLS]    66        250
void drawPeaks(int endx, int endy){
    int x,y=0;
    while(y < endy){
        while (x < endx){
            drawPattern(x,y);
            x++;
        }
    y++;
    x=0;
    }

}


*/

void drawBezierToObstacles(){
    Point p0 = {0, (int) (0.2*height)};
    Point p1 = {(int) (0.33 * width), (int) (0.02 * height)};
    Point p2 = {(int) (0.66 * width), (int) (0.38 * height)};
    Point p3 = {(int)(1 * width), (int) (0.2 * height)};
    int numberOfPoints = width * 2;
    std::vector<Point> bezierPoints = generateBezierCurve(p0, p1, p2, p3, numberOfPoints);
    //Color curveColor = {1.0f, 0.0f, 0.0f, 1.0f};
    for (size_t i = 1; i < bezierPoints.size(); ++i) {
        //Point prev = bezierPoints[i-1];
        Point cur  = bezierPoints[i];
        cur.color = {1.0f, 0.0f, 0.0f, 1.0f};
        if (inBounds(cur.x, cur.y)) {
            obstacles[cur.y][cur.x]=cur;
            obstacles[cur.y][cur.x].occupied = true;
        }
        // use Bresenham to fill the gap between samples
       // bresenhamLine(prev.x, prev.y, cur.x, cur.y, curveColor);
    }
}

void drawObstacleToObstacles(){
    int y2=0;
    for (int x = 0; x < width; ++x) {
        //y2=y;
        for (int y = 0; y < height; ++y) {
            if (obstacles[y][x].occupied) {
                Point p;
                // propagate column downward into obstacles array (no GL here)

                for(y2=y; y2 > 0; --y2){
                    if (!inBounds(x, y2)) break;
                    p.x = x;
                    p.y = y2;
                    p.color = obstacles[y][x].color;
                    //p.color = {1.0f, 0.0f, 0.0f, 1.0f};
                    obstacles[y2][x] = p;
                    obstacles[y2][x].occupied = true;
                    //drawPixel(x, y2);
                    //cout << "y2:" << y2;
                    //y2++;
                }
                //y2=y;
            }
        }
    }    
}



void drawObstacles(){
    // Batch draw all occupied obstacle pixels in one GL_POINTS call
    glBegin(GL_POINTS);
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (obstacles[y][x].occupied) {
                glColor4f(obstacles[y][x].color.r, obstacles[y][x].color.g, obstacles[y][x].color.b, obstacles[y][x].color.a);
                glVertex2i(x, y);
            }
        }
    }
    glEnd();
}

// Origocentric circle

void explode(int cx, int cy, int r){
    int r2 = r * r;
    Color color = {0.0f, 0.0f, 0.0f, 1.0f};
    bool tower1_once = false;
    bool tower2_once = false;

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {

            int dx = x - cx;
            int dy = y - cy;
            
            if (dx*dx + dy*dy <= r2) {
                //cout << "Explode checking pixel (" << x << "," << y << ") with dx=" << dx << ", dy=" << dy << endl;
                if(goalArea1[y][x].occupied){
                    if(!tower1_once) {
                        std::cout << "Goal hit! Player two" << std::endl;
                        statusMessage = "Goal hit! Player two";
                    }                   
                    glutPostRedisplay();
                    tower1_once = true;
                    tower1_alive = false;
                    player2_hit = true;
                    player2Score++;
                    gameOver = true;            
                }                
                if(goalArea2[y][x].occupied){
                    if(!tower2_once) {
                        std::cout << "Goal hit! Player one" << std::endl;
                        statusMessage = "Goal hit! Player one";
                    }
                    glutPostRedisplay();
                    tower2_once = true;
                    tower2_alive = false;
                    player1_hit = true;
                    player1Score++;
                    gameOver = true;             
                }                
                obstacles[y][x].occupied = false;
                obstacles[y][x].color = color;
                
            }
        }
    }
}

// After an explosion, let pixels above fall down into the cleared space.
// Only settle columns in the given x-range (clamped to window).
void settleTerrainRange(int x0, int x1){
    if(x0 < 0) x0 = 0;
    if(x1 >= width) x1 = width - 1;

    for(int x = x0; x <= x1; ++x){
        std::vector<Point> stack;
        // collect occupied pixels in column (bottom to top), excluding tower pixels
        for(int y = 0; y < height; ++y){
            if(obstacles[y][x].occupied && !goalArea1[y][x].occupied && !goalArea2[y][x].occupied) {
                stack.push_back(obstacles[y][x]);
            }
        }
        // clear non-tower pixels in column
        for(int y = 0; y < height; ++y){
            if(!goalArea1[y][x].occupied && !goalArea2[y][x].occupied) {
                obstacles[y][x].occupied = false;
            }
        }
        // place settled pixels at bottom (above towers)
        for(int y = 0; y < height; ++y){
            if(y < (int)stack.size()){
                obstacles[y][x] = stack[y];
                obstacles[y][x].y = y;
                obstacles[y][x].occupied = true;
            }
        }
    }
}

inline int surfaceYAtX(int x){
    // return the topmost occupied pixel Y for column x (or 0 if none)
    if(!inBounds(x,0)) return 0;
    for(int y = height - 1; y >= 0; --y){
        if(obstacles[y][x].occupied) return y;
    }
    return 0;
}

void drawTower_one(){
    int towerBaseX = tower1_x;
    towerBaseY = surfaceYAtX(towerBaseX);
    paintTowerBrushAtLocation(towerBaseX, towerBaseY, goalArea1);
}

void drawTower_two(){
    int towerBaseX = tower2_x;
    tower2BaseY = surfaceYAtX(towerBaseX);
    paintTowerBrushAtLocation(towerBaseX, tower2BaseY, goalArea2);
}


// --- Non-blocking projectile state and timer-based animation ---
static bool projActive = false;
static bool projStarted = false;
static double proj_px = 0.0, proj_py = 0.0;
static double proj_vx = 0.0, proj_vy = 0.0;
static bool goalHit = false;  // Flag to track if goal has been hit this round
//static bool player1_hit = false;  // Flag for player 1 winning
//static bool player2_hit = false;  // Flag for player 2 winning
// physics timestep in seconds per update (kept for tuning)
static double proj_dt = 0.016; // default ~16ms
// Scale between physics meters and screen pixels. Adjust to tune flight.
static const double PIXELS_PER_METER = 25.0; // 50 pixels == 1 meter
int projIntervalMs = 16;         // timer interval hint (ms)
double timeScale = 1.0;          // 1.0 normal, >1 faster, <1 slower

void updateProjectile(double dtSec);

// Idle-driven updater (runs each frame)
void idle();

// Start a non-blocking projectile animation from `startX`.
void startProjectile(int angleDeg, int initialSpeed, int startX, int startY = -1){
    
    if (projActive) return; // already running
    double angleRad = angleDeg * M_PI / 180.0;
    // Convert initial speed (m/s) to pixels/s using PIXELS_PER_METER
    proj_vx = initialSpeed * std::cos(angleRad) * PIXELS_PER_METER;
    proj_vy = initialSpeed * std::sin(angleRad) * PIXELS_PER_METER;
    proj_px = static_cast<double>(startX);
    // Use provided startY if given, otherwise calculate from surface
    if (startY >= 0) {
        proj_py = static_cast<double>(startY);
    } else {
        proj_py = static_cast<double>(surfaceYAtX(startX)) + 8.0; // slightly above surface
    }
    projActive = true;
    projStarted = true;
    goalHit = false;  // Reset goal hit flag for new projectile
    player1_hit = false;
    player2_hit = false;
    // compute physics timestep in seconds from projIntervalMs and timeScale
    proj_dt = (double)projIntervalMs / 1000.0 * timeScale;
    
}

// Timer callback advances projectile, checks collision, triggers explosion and redisplay.
void updateProjectile(double dtSec){
    if (!projActive) return;
    // clamp dt to avoid huge steps (prevents tunneling)
    if (dtSec <= 0.0) dtSec = proj_dt;
    if (dtSec > 0.05) dtSec = 0.05;

    // compute next position using pixel velocities (pixels/s)
    double nextx = proj_px + proj_vx * dtSec;
    double nexty = proj_py + proj_vy * dtSec;

    // apply gravity (convert to pixels/s^2)
    proj_vy -= (g * PIXELS_PER_METER) * dtSec;

    // sample the segment to avoid tunneling
    int steps = static_cast<int>(std::ceil(std::fmax(std::fabs(nextx - proj_px), std::fabs(nexty - proj_py))));
    if (steps < 1) steps = 1;

    for (int i = 0; i <= steps; ++i) {
        double f = static_cast<double>(i) / steps;
        int sx = static_cast<int>(std::lround(proj_px + (nextx - proj_px) * f));
        int sy = static_cast<int>(std::lround(proj_py + (nexty - proj_py) * f));
        if (!inBounds(sx, sy)) continue;
        if (obstacles[sy][sx].occupied) {
            int er = 25;
            explode(sx, sy, er);
            PlaySound(TEXT("explosion.wav"), NULL, SND_FILENAME | SND_ASYNC);
            Sleep(500);
        //    settleTerrainRange(sx - er, sx + er);
            glutPostRedisplay();
            projActive = false;
            //cout << "Projectile hit an obstacle at (" << sx << "," << sy << ")" << endl;
            
            
            return;
        }
        
        
    }

    proj_px = nextx;
    proj_py = nexty;

    // stop if out of view
    int drawx = static_cast<int>(std::lround(proj_px));
    int drawy = static_cast<int>(std::lround(proj_py));
    if (!inBounds(drawx, drawy)) {
        projActive = false;
        glutPostRedisplay();
        return;
    }
}

void updateProjectile2(double dtSec){
    if (!projActive) return;
    // clamp dt to avoid huge steps (prevents tunneling)
    if (dtSec <= 0.0) dtSec = proj_dt;
    if (dtSec > 0.05) dtSec = 0.05;

    // compute next position using pixel velocities (pixels/s)
    double nextx = proj_px - proj_vx * dtSec;
    double nexty = proj_py + proj_vy * dtSec;

    // apply gravity (convert to pixels/s^2)
    proj_vy -= (g * PIXELS_PER_METER) * dtSec;

    // sample the segment to avoid tunneling
    int steps = static_cast<int>(std::ceil(std::fmax(std::fabs(nextx - proj_px), std::fabs(nexty - proj_py))));
    if (steps < 1) steps = 1;

    for (int i = 0; i <= steps; ++i) {
        double f = static_cast<double>(i) / steps;
        int sx = static_cast<int>(std::lround(proj_px - (proj_px - nextx) * f));
        int sy = static_cast<int>(std::lround(proj_py + (nexty - proj_py) * f));
        if (!inBounds(sx, sy)) continue;
        if (obstacles[sy][sx].occupied) {
            int er = 25;
            explode(sx, sy, er);
            PlaySound(TEXT("explosion.wav"), NULL, SND_FILENAME | SND_ASYNC);
            Sleep(500);
        //    settleTerrainRange(sx - er, sx + er);
            glutPostRedisplay();
            projActive = false;
            //cout << "Projectile hit an obstacle at (" << sx << "," << sy << ")" << endl;
            
            
            return;
        }
        
        
    }

    proj_px = nextx;
    proj_py = nexty;

    // stop if out of view
    int drawx = static_cast<int>(std::lround(proj_px));
    int drawy = static_cast<int>(std::lround(proj_py));
    if (!inBounds(drawx, drawy)) {
        projActive = false;
        glutPostRedisplay();
        return;
    }
}

void idle(){
    // Delta time laskenta
    static auto last = std::chrono::steady_clock::now();
    auto now = std::chrono::steady_clock::now();
    double dtSec = std::chrono::duration<double>(now - last).count();
    last = now;

    // -----------------------------------------
    // 1) TYKIN LAUKAISUVIIVE (korvaa Sleep)
    // -----------------------------------------
    /*
    if (cannonFiring) {
        cannonTimer += dtSec;

        if (cannonTimer >= cannonDelay) {
            cannonFiring = false;   // laukaisuviive ohi

            // Nyt luodaan ammus täsmälleen oikealla hetkellä
            if(turn == 1 && !player1_hit && !player2_hit){
                float angle_radians = angle * M_PI / 180.0f;
                int cannonLength = 25;

                int endX = tower1_x + (int)(cannonLength * cos(angle_radians)) + 10;
                int endY = towerBaseY + towerHeight - 5 + (int)(cannonLength * sin(angle_radians));

                if (!projActive) startProjectile(angle, initialSpeed, endX, endY);

            } else if(!player1_hit && !player2_hit){
                float angle_radians = angle2 * M_PI / 180.0f;
                int cannonLength = 25;

                int endX = tower2_x - (int)(cannonLength * cos(angle_radians)) - 10;
                int endY = tower2BaseY + tower2Height - 5 + (int)(cannonLength * sin(angle_radians));

                if (!projActive) startProjectile(angle2, initialSpeed2, endX, endY);
            }
        }
    }
        */
    // -----------------------------------------
    // 2) NORMAALI PROJEKTIIILI/FYSIIKKA
    // -----------------------------------------
    if (projActive) {
        if(turn == 1){
            updateProjectile(dtSec * timeScale);
        } else {
            updateProjectile2(dtSec * timeScale);
        }
        glutPostRedisplay();
    } 
    else {
        // Vuoronvaihto
        if(turn == 1 && projStarted && !player1_hit && !player2_hit){
            cout << "Switching to player two turn" << endl;
            statusMessage = "Player two's turn!";
            turn = 2;
            projStarted = false;
        } 
        else if (turn == 2 && projStarted && !player1_hit && !player2_hit){
            cout << "Switching to player one turn" << endl;
            statusMessage = "Player one's turn!";
            turn = 1;
            projStarted = false;
        }
        else {
            if(!gameOver && (player1_hit || player2_hit)){
                cout << "It's a tie!" << endl;
                if(player1_hit) cout << "Player one wins!" << endl;
                if(player2_hit) cout << "Player two wins!" << endl;

                projActive = false;
                projStarted = false;
                gameOver = true;
            }
        }

        // Pieni lepo kun ei ole animaatiota
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}


void launch(int angleDeg, int initialSpeed){
    // Convert launch angle to radians and set local velocities
    double angleRad = angleDeg * M_PI / 180.0;
    double pvx = initialSpeed * std::cos(angleRad);
    double pvy = initialSpeed * std::sin(angleRad);

    double dt = 0.05; // smaller time step for more reliable collision sampling

    // Start slightly above the surface at x = 0
    double px = 10.0; // starting X (pixels)
    double py = static_cast<double>(surfaceYAtX(static_cast<int>(px))) + 8.0; // start above surface

    // Step the projectile, sampling along each step to avoid tunneling
    while (true) {
        double nextx = px + pvx * dt;
        double nexty = py + pvy * dt;

        // gravity affects vertical velocity
        pvy -= g * dt;

        // Sample along the segment from (px,py) to (nextx,nexty)
        int steps = static_cast<int>(std::ceil(std::fmax(std::fabs(nextx - px), std::fabs(nexty - py))));
        if (steps < 1) steps = 1;

        bool hit = false;
        for (int i = 0; i <= steps; ++i) {
            double f = static_cast<double>(i) / steps;
            int sx = static_cast<int>(std::lround(px + (nextx - px) * f));
            int sy = static_cast<int>(std::lround(py + (nexty - py) * f));

            if (!inBounds(sx, sy)) continue;
            if (obstacles[sy][sx].occupied) {
                // hit obstacle: explode at contact point and stop
                int er = 25;
                // clear the crater first, then let terrain settle into it
                explode(sx, sy, er);
             //   settleTerrainRange(sx - er, sx + er);
                // immediate redraw so the crater is visible right away
                //drawObstacles();
                //glFlush();
                //glutSwapBuffers();
                
                hit = true;
                break;
            }
        }

        // advance projectile
        px = nextx;
        py = nexty;

        // draw projectile if still in window
        int drawx = static_cast<int>(std::lround(px));
        int drawy = static_cast<int>(std::lround(py));
        if (!inBounds(drawx, drawy)) break;

        glColor3f(1.0f, 1.0f, 0.0f); // Yellow
        drawPixel(drawx, drawy);
        // draw to back buffer; present only on explosion or final display

        if (hit){
            //explode(drawx, drawy, 12);
            break;
        } 

        // small sleep to visualise
        std::this_thread::sleep_for(std::chrono::duration<double>(0.06) );
    }
}

void drawCannon(float angle) {
    if (!tower1_alive) return;
    int towerBaseX = tower1_x;
    float angle_radians = angle * M_PI / 180.0f;
    
    int cannonLength = 17;
    int endX = towerBaseX + (int)(cannonLength * cos(angle_radians));
    int endY = towerBaseY + towerHeight - 5 + (int)(cannonLength * sin(angle_radians));
    tower_projectile = endX;
    // Draw cannon directly with OpenGL (do not write into obstacles array)
    glColor3f(towerColor.r, towerColor.g, towerColor.b);
    glBegin(GL_LINES);
        glVertex2i(towerBaseX, towerBaseY + towerHeight - 5);
        glVertex2i(endX, endY);
    glEnd();
}

void drawCannon2(float angle) {
    if (!tower2_alive) return;
    int towerBaseX = tower2_x;
    float angle_radians = angle * M_PI / 180.0f;
    
    int cannonLength = 17;
    int endX = towerBaseX - (int)(cannonLength * cos(angle_radians));
    int endY = tower2BaseY + tower2Height - 5 + (int)(cannonLength * sin(angle_radians));
    tower_projectile = endX;
    // Draw cannon directly with OpenGL
    //glColor3f(1.0f, 1.0f, 1.0f); // White
    glColor3f(towerColor.r, towerColor.g, towerColor.b);
    glBegin(GL_LINE_STRIP);
    
    glVertex2i(towerBaseX, tower2BaseY + tower2Height - 5);
    glVertex2i(endX, endY);
    glEnd();
}

void floodFillPattern(int sx,int sy)
{
    if (brush.w == 0 || brush.h == 0) {
        std::cout << "Brush not loaded, skipping flood fill\n";
        return;
    }
    std::stack<Point> stack;
    stack.push({sx,sy});
    int filled = 0;

    while(!stack.empty()){
        Point p = stack.top(); stack.pop();
        int x = p.x, y = p.y;
        if(!inBounds(x,y)) continue;
        if(obstacles[y][x].occupied) continue;

        int bx = (x - sx) % brush.w; if (bx<0) bx+=brush.w;
        int by = (y - sy) % brush.h; if (by<0) by+=brush.h;
        Color c = brush.px[by*brush.w + bx];
        if(c.a < 0.1f) continue;

        obstacles[y][x].color = c;
        obstacles[y][x].occupied = true;
        filled++;

        stack.push({x+1,y}); stack.push({x-1,y});
        stack.push({x,y+1}); stack.push({x,y-1});
    }
    std::cout << "Flood filled " << filled << " pixels\n";
}

// brush already loaded, brush.w/brush.h >0
// (brush.px is row-major RGBA as before)

void fillRectWithBrush(int x0, int y0, int x1, int y1)
{
    if (brush.w == 0 || brush.h == 0) {
        std::cout << "Brush not loaded, skipping rect fill\n";
        return;
    }
    if (x0 > x1) std::swap(x0,x1);
    if (y0 > y1) std::swap(y0,y1);

    for (int y = y0; y <= y1; ++y) {
        for (int x = x0; x <= x1; ++x) {
            if (!inBounds(x,y)) continue;
            // only apply brush to already-occupied pixels (existing terrain)
            if (!obstacles[y][x].occupied) continue;
            
            // compute corresponding coordinates inside the brush (tile pattern)
            int bx = (x - x0) % brush.w;
            if (bx < 0) bx += brush.w;
            int by = (y - y0) % brush.h;
            if (by < 0) by += brush.h;

            Color c = brush.px[by * brush.w + bx];
            if (c.a < 0.1f) continue;           // skip transparent pixels

            obstacles[y][x].color    = c;
        }
    }
    std::cout << "Rect filled from (" << x0 << "," << y0 << ") to (" << x1 << "," << y1 << ")\n";
}

// Display callback function
// Try this!!
void display() {
    glClear(GL_COLOR_BUFFER_BIT); // Clear the screen with background color
    // Terrain/obstacles are initialized once (initWorld). Just draw them here.
    drawStars();
    drawObstacles();
    
    // Draw the cannon at current angle
    drawCannon(angle);
    drawCannon2(angle2);
    // start the non-blocking projectile once
    //if (!projStarted) startProjectile(70, 10, 10);

    // draw projectile when active
    if (projActive) {
        int pdx = static_cast<int>(std::lround(proj_px));
        int pdy = static_cast<int>(std::lround(proj_py));
        if (inBounds(pdx, pdy)){
            glColor3f(1.0f, 1.0f, 0.0f);
            // draw projectile as a single vertex (batch already used for obstacles)
            glBegin(GL_POINTS);
            glVertex2i(pdx, pdy);
            glEnd();
        }
    }
    drawScoreBoard();
    // present frame
    glutSwapBuffers();
}

void keys(unsigned char key, int x, int y){
    cout << "Key pressed: " << (int)key << endl;
    switch(key){
        case 27: // ESC
            shutdownAudio();
            exit(0);
            break;
        // Arrow keys are handled in specialKeys() via glutSpecialFunc
        case 13: // Enter
            cout << "Enter pressed" << endl;
            statusMessage = "";
            playCannon();   // ääni lähtee heti, nollaviiveellä

            //if (!wavData.empty()) {
            //    PlaySound((LPCSTR)wavData.data(), NULL, SND_MEMORY | SND_ASYNC);
            //}
            cannonFiring = true;
            cannonTimer = 0.0f;
            //Sleep(500);
            // launch a projectile from the cannon tip (endX, endY)
            if(turn == 1 && player1_hit == false && player2_hit == false){
                cout << "Player one launching at angle: " << angle << " speed: " << initialSpeed << endl;
                int towerBaseX = tower1_x;
                float angle_radians = angle * M_PI / 180.0f;
                int cannonLength = 25;
                int endX = towerBaseX + (int)(cannonLength * cos(angle_radians)) + 10;  // Extra offset to avoid tower collision
                int endY = towerBaseY + towerHeight - 5 + (int)(cannonLength * sin(angle_radians));
                if (!projActive) startProjectile(angle, initialSpeed, endX, endY);
                
            }else if(player1_hit == false && player2_hit == false){
                cout << "Player two launching at angle: " << angle2 << " speed: " << initialSpeed2 << endl;
                int towerBaseX = tower2_x;
                float angle_radians = angle2 * M_PI / 180.0f;
                int cannonLength = 25;
                int endX = towerBaseX - (int)(cannonLength * cos(angle_radians)) - 10;  // Extra offset to avoid tower collision
                int endY = tower2BaseY + tower2Height - 5 + (int)(cannonLength * sin(angle_radians));
                if (!projActive) startProjectile(angle2, initialSpeed2, endX, endY);
                
            }
            
            break;
        case '+':
        case '=':
            if(turn == 1 && player1_hit == false && player2_hit == false){
                initialSpeed += 1;
                cout << "player 1 speed increased: " << initialSpeed << endl;
            }else if(player1_hit == false && player2_hit == false){
                initialSpeed2 += 1;
                cout << "player 2 speed increased: " << initialSpeed2 << endl;
            }
            glutPostRedisplay();
            break;
        case '-':
            if(turn == 1 && player1_hit == false && player2_hit == false){
                initialSpeed -= 1;
                if(initialSpeed < 1) initialSpeed = 1;
            }else if(player1_hit == false && player2_hit == false){
                initialSpeed2 -= 1;
                if(initialSpeed2 < 1) initialSpeed2 = 1;
            }
            cout << "speed changed: " << (turn == 1 ? initialSpeed : initialSpeed2) << endl;
            glutPostRedisplay();
            break;
        case 'r':
        case 'R':
            cout << "Resetting game state" << endl;
            // Reset all game state variables to initial conditions
            projActive = false;
            projStarted = false;
            goalHit = false;
            player1_hit = false;
            player2_hit = false;
            turn = 1;
            initialSpeed = 10;
            initialSpeed2 = 10;
            player1Score = 0;
            player2Score = 0;
            tower1_alive = true;
            tower2_alive = true;
            gameOver = false;
            statusMessage = "Game reset. Player one starts.";
            
            // Reinitialize terrain and obstacles
            for (int y = 0; y < height; ++y) {
                for (int x = 0; x < width; ++x) {
                    obstacles[y][x].occupied = false;
                    obstacles[y][x].color = {0.0f, 0.0f, 0.0f, 1.0f};
                    goalArea1[y][x].occupied = false;
                    goalArea2[y][x].occupied = false;
                }
            }
            drawBezierToObstacles();
            drawObstacleToObstacles();
            
             fillRectWithBrush(0, 0, width, height);
             drawStars();
             drawTower_one();
             drawTower_two();
             drawScoreBoardBackground();
             drawScoreBoard();
             
             glutPostRedisplay();
             break;
        default:
            break;
    }
}

// Special key handler for arrow keys and function keys
void specialKeys(int key, int x, int y){

    switch(key){
       /*case ' ':
            cout << "Spacebar pressed (special)" << endl;
            // launch a new projectile from left edge
            if (!projActive) startProjectile(70, 10, 10);
            break;*/
        case GLUT_KEY_UP:
            if(turn == 1 && player1_hit == false && player2_hit == false){
                if(angle < 90){
                    playElevation();
                    angle+=1;
                    cout << "Up arrow pressed (special) angle: " << angle << endl;
                    glutPostRedisplay(); // Request a redraw
                }
            }else if(player1_hit == false && player2_hit == false){
                if(angle2 < 90){
                    playElevation();
                    angle2+=1;
                    cout << "Up arrow pressed (special) angle2: " << angle2 << endl;
                    glutPostRedisplay(); // Request a redraw
                }
            }
            // Example action: launch a projectile when up is pressed
           // if (!projActive) startProjectile(70, 12, 10);
            break;
        case GLUT_KEY_DOWN:
            if(turn == 1 && player1_hit == false && player2_hit == false){
                if(angle > 0){
                    playElevation();
                    angle-=1;
                    cout << "Down arrow pressed (special)" << angle << endl;
                    glutPostRedisplay(); // Request a redraw
                }
            }else if(player1_hit == false && player2_hit == false){
                if(angle2 > 0){
                    playElevation();
                    angle2-=1;
                    cout << "Down arrow pressed (special) angle2: " << angle2 << endl;
                    glutPostRedisplay(); // Request a redraw
                }
            }
            
            break;
        default:
            break;
    }
}

// Window reshape callback
void reshape(int w, int h) {
    window_width = w;
    window_height = h;

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    cout << "Reshape called with width: " << w << ", height: " << h << endl;
    // Set coordinate system to match window pixels
    gluOrtho2D(0, w, 0, h);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv); // Initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    
    glutInitWindowSize(width, height);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Single Pixel with GLUT");
    glutFullScreen();

    int window_width = glutGet(GLUT_WINDOW_WIDTH);
    int window_height = glutGet(GLUT_WINDOW_HEIGHT);
   
    std::cout << "Window size: " << window_width << "x" << window_height << std::endl;
    // Set background color (black)
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glPointSize(1.0f);
    //PlaySound(TEXT("cannon2.wav"), NULL, SND_FILENAME | SND_ASYNC);
    //std::this_thread::sleep_for(std::chrono::milliseconds(200));
    //PlaySound(NULL, 0, 0);
    //loadWavToMemory();
    initAudio();
    
    // Configure point smoothing once
    glEnable(GL_POINT_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    // Register callback functions
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);

    // Initialize terrain/obstacles once before entering main loop
    // (these routines only populate the obstacles array; they don't issue GL draws)
    drawBezierToObstacles();
    drawObstacleToObstacles();
    
    
    int cx = 100;
    int cy = surfaceYAtX(cx);
    int radius = 25;
    //explode(cx, cy, radius);
    settleTerrainRange(cx - radius, cx + radius);
    
    // Load brush before filling
    initBrush("bricks.bmp");
    initTowerBrush("torni.bmp");
    
    statusMessage = "Welcome to Pixel Artillery! Player one starts.";
    
    // Fill large rect to cover terrain (but not towers)
    fillRectWithBrush(0, 0, width, height);
    // place towers before filling silhouette so they are not covered
    drawStars();
    drawTower_one();
    drawTower_two();
    drawScoreBoardBackground();
    drawScoreBoard();
    glutKeyboardFunc(keys);
    glutSpecialFunc(specialKeys);
    // Enter the GLUT main loop
    glutMainLoop();

    return 0;
}
#include <iostream> // cout
#include <iomanip> // setw
#include <math.h> // sqrt
#include <chrono>
#include <thread>

/**
* New improved version of the physics2 engine!
* This one calculates the time of the throwing arc!
 */

using namespace std;
/*
// Horizontal position
int x=0;
// Vertical position
int y=0;
// Horizontal velocity
double vx=0;
// Vertical velocity
double vy=0;
// Mass
double m=0;
//Acceleration
double ax, ay;  // Acceleration (m/s^2)
// These are the mass of the particles m1, m2
int m1=80;
int m2=40;
// Time variables
double t=0.0;
double sleep_duration = 0.06;

// acceleration due gravity (M/s) of Earth
const double g=9.81;
// Speed of the object
// initial speed in m/s
double initial_speed=50.0;

double speed(double distance, double time){

return (distance / time);
}

double calculateAngle(double vx, double vy) {
    return std::atan2(vy, vx) * 180.0 / M_PI;
}

int main(void){
    x = 100;
	y = 1983;
    double launchAngle = 68.0;
    // Convert launch angle to radians
    double angleRad = launchAngle * M_PI / 180.0;
    vx = initial_speed * std::cos(angleRad);
    vy = initial_speed * std::sin(angleRad);
    double dt = 0.1; // time step (seconds)
    //auto lastFrameTime = std::chrono::high_resolution_clock::now();
    //timeScale = 0.2; // 20% speed
    std::cout << "Time\tX\tY\tAngle" << std::endl;

    while (y >= 1983) {  // Stop when projectile hits the ground, detect the hit with some function!
        
        double angle = calculateAngle(vx, vy);
        if (angle >= 89.9999) vx = 0; 
        std::cout << t << "\t" << x << "\t" << y << "\t" << angle << "" << std::endl;

        // Update positions
        x += vx * dt;
        y += vy * dt;

        // Update vertical velocity due to gravity
        vy -= g * dt;

        // Increment time
        t += dt;
        std::this_thread::sleep_for(std::chrono::duration<double>(sleep_duration));        
    }
}*/
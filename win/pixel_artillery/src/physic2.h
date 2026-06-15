#include <iostream> // cout
#include <iomanip> // setw
#include <math.h> // sqrt
#include <chrono>
#include <thread>

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
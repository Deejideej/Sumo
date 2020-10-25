//These libraries are needed for the script to function
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Player object
class Player {
    public:
        double x, y, direction;
        Player(double, double, double);
        double rad () {return (direction) * (M_PI/180);};
};

Player::Player (double a, double b, double c) {
    x = a;
    y = b;
    direction = c;
}


//Detection object
class Detection {
public:
    double distance, direction;
    Detection(double, double);
    void SetValues(double, double);
    double absDir (double oDir) {return direction + oDir;};
    double x (double playerOffsetX = 0, double oDir = 0) {return (distance * cos((direction + oDir) * (M_PI/180))) + playerOffsetX;};
    double y (double playerOffsetY = 0, double oDir = 0) {return (distance * sin((direction + oDir) * (M_PI/180))) + playerOffsetY;};

};

Detection::Detection (double a, double b) {
    distance = a;
    direction = b;
}

void Detection::SetValues (double a, double b) {
    distance = a;
    direction = b;
}

//This function prints the current state of the plane to the console, unnessasary in arduino as it is only for human interface
void printToConsole(bool plane[100][100]) {
    for(size_t y = 0; y < 100; y++) {
        char line[200];
        for(size_t x = 0; x < 100; x++) {
            if(plane[x][y]) {
                line[x * 2] = '0';
                line[x * 2 - 1] = '0';
            } else {
                line[x * 2] = ' ';
                line[x * 2 - 1] = ' ';
            }
        }
        std::cout << line << std::endl;
    }
}

//This function draws a circle, it is also unnessasary in arduino
int circle(int x, double r, double h, double k, int mod) {
    int newY = (int)(k + mod * sqrt(pow(r, 2) - pow(x - h, 2)) + 0.5 * mod);
    if (newY != -2147483648) {
        return newY;
    } else {
        return 0;
    }
}

//This function simply checks if a point with coordinates (x,y) falls inside a circle with radius r and a centre at (h,k)
bool checkIfInsideArena(double x, double y, double r, double h, double k) {
    return (pow(x - h, 2) + pow(y - k, 2) < pow(r, 2));
}


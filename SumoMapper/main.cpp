#include <iostream>
#include <math.h>
#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>


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

class Detection {
public:
    double distance, direction;
    Detection(double, double);
    double absDir (double oDir) {return direction + oDir;};
    double x (double playerOffsetX = 0, double oDir = 0) {return (distance * cos((direction + oDir) * (M_PI/180))) + playerOffsetX;};
    double y (double playerOffsetY = 0, double oDir = 0) {return (distance * sin((direction + oDir) * (M_PI/180))) + playerOffsetY;};

};

Detection::Detection (double a, double b) {
        distance = a;
        direction = b;
}

void printToConsole(bool plane[100][100]) {
    for(size_t y = 0; y < 100; y++) {
        for(size_t x = 0; x < 100; x++) {
            if(plane[x][y]) {
                std::cout << "##";
            } else {
                std::cout << "  ";
            }
        }
        std::cout << std::endl;
    }
}

int circle(int x, double r, double h, double k, int mod) {
    int newY = (int)(k + mod * sqrt(pow(r, 2) - pow(x - h, 2)) + 0.5 * mod);
    if (newY != -2147483648) {
        return newY;
    } else {
        return 0;
    }
}

bool checkIfInsideArena(double x, double y, double r, double h, double k) {
    return (pow(x - h, 2) + pow(y - k, 2) > pow(r, 2));
}

int main()
{
    //Initialise random
    srand(time(NULL));

    int frame;

    //Set radius and offset (r, h, k)
    double radius = 38;
    double h = 50;
    double k = 50;

    //Set size of drawable plane, make this larger if needed
    bool plane[100][100] = { {false} };

    //Initialise player
    Player self(50, 50, 270);

    //Create fake detection
    Detection enemy(rand() % 61, rand() % 361);

    while (true) {

        //Clear plane data
        for(size_t y = 0; y < 100; y++) {
            for(size_t x = 0; x < 100; x++) {
                plane[x][y] = false;
            }
        }

        //Draw the arena
        for (int x = 0; x < 100; x++) {
            plane[x][circle(x, radius, h, k, 1)] = true;
            plane[x][circle(x, radius, h, k, -1)] = true;
        }

        //Check if the detected object is inside the arena
        if (!checkIfInsideArena(enemy.x(self.x, self.direction), enemy.y(self.y, self.direction), radius, h, k)) {
            plane[(int)enemy.x(self.x, self.direction)][(int)enemy.y(self.y, self.direction)] = true;
        }



        //Draw the player, and draw a circle around the player
        //plane[(int)self.x][(int)self.y] = true;

        for (int x = 0; x < 100; x++) {
            plane[x][circle(x, 8, self.x, self.y, 1)] = true;
            plane[x][circle(x, 8, self.x, self.y, -1)] = true;
        }
        //plane[(int)(self.x+3*cos(self.rad()))][(int)(self.x+3*sin(self.rad()))] = true;
        self.x = self.x + 3*cos(self.rad());
        self.y = self.y + 3*sin(self.rad());

        //Print state of plane to console
        system("cls");
        std::cout << "frame: " << frame << " coordinates: " << self.x << ", " << self.y;
        printToConsole(plane);
        frame++;
    }
    return 0;
}

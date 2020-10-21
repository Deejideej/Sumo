/*
This code is meant to be both a practical implementation and digital representation of the robot sumo arena.
*/

//These libraries are needed for the script to function
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Remove these for arduino
#include <iostream>

//Le classes
#include <classy.h>


//This function prints the current state of the plane to the console, unnessasary in arduino as it is only for human interface
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

int main()
{
    //Initialise rng
    srand(time(NULL));

    //Set radius and offset (r, h, k)
    double radius = 38;
    double h = 50;
    double k = 50;

    //Set size of drawable plane, make this larger if needed
    bool plane[100][100] = { {false} };

    //Initialise player
    Player self(50, 50, 270);

    //Create fake detection
    Detection enemy(rand() % 31, rand() % 361);

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
        if (checkIfInsideArena(enemy.x(self.x, self.direction), enemy.y(self.y, self.direction), radius, h, k)) {
            plane[(int)enemy.x(self.x, self.direction)][(int)enemy.y(self.y, self.direction)] = true;
        }

        //Draw the player, and draw a circle around the player
        //plane[(int)self.x][(int)self.y] = true;

        for (int x = 0; x < 100; x++) {
            plane[x][circle(x, 8, self.x, self.y, 1)] = true;
            plane[x][circle(x, 8, self.x, self.y, -1)] = true;
        }

        self.x = self.x + 3*cos(self.rad());
        self.y = self.y + 3*sin(self.rad());

        //Print state of plane to console
        system("cls");
        std::cout << "coordinates: " << self.x << ", " << self.y;
        printToConsole(plane);
    }
    return 0;
}

/*
This code is meant to be both a practical implementation and digital representation of the robot sumo arena.
*/

//Remove these for arduino
#include <iostream>

//Le classes
#include <classy.h>

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

    //Create fake detection - testing only
    //Detection enemy(rand() % 31, rand() % 361);

    //Initialise detection, assumes ultrasonic is already pointing towards enemy
    Detection enemy(/*ultrasonic detection*/2, /*servo detection*/2);
    Detection newEnemy(/*ultrasonic detection*/2, /*servo detection*/2);

    while (true) {

        /*
        newEnemy.SetValues(ultrasonic detection, servo detection)
        */
        //Clear plane data - redundant in arduino
        for(size_t y = 0; y < 100; y++) {
            for(size_t x = 0; x < 100; x++) {
                plane[x][y] = false;
            }
        }

        //Check if the detected object is inside the arena, if so, set new enemy to the enemy variable. This enemy variable is what the robot uses to make its decisions
        if (checkIfInsideArena(newEnemy.x(self.x, self.direction), newEnemy.y(self.y, self.direction), radius, h, k)) {
            //plane[(int)enemy.x(self.x, self.direction)][(int)enemy.y(self.y, self.direction)] = true;
            enemy = newEnemy;
        }


        //Draw the arena - redundunt in arduino
        for (int x = 0; x < 100; x++) {
            plane[x][circle(x, radius, h, k, 1)] = true;
            plane[x][circle(x, radius, h, k, -1)] = true;
        }

        //Draw the player, and draw a circle around the player - redundant in arduino
        for (int x = 0; x < 100; x++) {
            plane[x][circle(x, 8, self.x, self.y, 1)] = true;
            plane[x][circle(x, 8, self.x, self.y, -1)] = true;
        }

        self.x = self.x + 3*cos(self.rad());
        self.y = self.y + 3*sin(self.rad());

        //Print state of plane to console - redundant in arduino
        system("cls");
        std::cout << "coordinates: " << self.x << ", " << self.y;
        printToConsole(plane);

    }
    return 0;
}

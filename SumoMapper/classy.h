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
    double absDir (double oDir) {return direction + oDir;};
    double x (double playerOffsetX = 0, double oDir = 0) {return (distance * cos((direction + oDir) * (M_PI/180))) + playerOffsetX;};
    double y (double playerOffsetY = 0, double oDir = 0) {return (distance * sin((direction + oDir) * (M_PI/180))) + playerOffsetY;};

};

Detection::Detection (double a, double b) {
        distance = a;
        direction = b;
}

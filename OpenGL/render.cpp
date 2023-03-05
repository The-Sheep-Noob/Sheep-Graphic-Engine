#include "program.h"
#include "settings.h"


Square* testing;
Square* lightning;
Rectangle* a_square;
Circle* circle;
Circle* circle2;


void Program::onStartup()
{

    testing = new Square();
    testing->setColors(50);
    testing->Size = (height > width ? height : width);
    testing->setPositions(350);

    lightning = new Square();
    lightning->Size = 300;
    lightning->A = 0;
    lightning->setPositions(350);
    lightning->Texture = "Lightning.png";
    lightning->setColorsTexture(0, 200, 200, 255);

    a_square = new Rectangle();
    a_square->setPositions(0, 0);
    a_square->setSizes(0, 25);
    a_square->setColors(255, 255, 255,100);
    a_square->Transform_from_middle = false;

    circle = new Circle();
    circle->Size = 400;
    circle->Transform_from_middle = false;
    circle->setPositions(height - circle->Size,width - circle->Size);
    circle->setColors(0, 0, 200 , 100);

    circle2 = new Circle();
    circle2->Size = 700;
    circle2->setPositions(350 , 350);
    circle2->setColors(0, 0, 200, 100);
}

void Program::onUpdate()
{
    lightning->setRotations(0, lightning->Y_rotate + 1, 0);
    a_square->X_size += 3;
    if (a_square->X_size > width) {
        a_square->X_size = 0;
    }
}


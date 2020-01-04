#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <cstdlib>

//limites da tela
#define WIDTH 800
#define HEIGHT 600
#define SPEED 1


int main()
{
    sf::ConvexShape nave;
    nave.setPointCount(4);
    nave.setPoint(0, sf::Vector2f(-10,-10));
    nave.setPoint(1, sf::Vector2f(0,20));
    nave.setPoint(2, sf::Vector2f(10,-10));
    nave.setPoint(3, sf::Vector2f(0,0));

    sf::RenderWindow Window(sf::VideoMode(WIDTH, HEIGHT), "Asteroids");
    float rotateTax = 0, lastInputR = 0, inputW = 0;
    float throttlex = 0, throttley = 0, angle = nave.getRotation();

    nave.setFillColor(sf::Color::Transparent);
    nave.setOutlineThickness(1);
    nave.setOutlineColor(sf::Color::White);
    nave.setPosition(WIDTH/2,HEIGHT/2);

    //game loop
    while (Window.isOpen())
    {

        sf::Event event;
        while (Window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                Window.close();

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            {
                throttlex = sin((angle)*3.14159265/180);
                throttley = cos((angle+90)*3.14159265/180);
                angle = nave.getRotation();
            }

            if (event.type == sf::Event::KeyPressed)
            {
                switch(event.key.code)
                {
                    case(sf::Keyboard::Left): rotateTax = -0.6; lastInputR = -1; break;
                    case(sf::Keyboard::Right): rotateTax = 0.6; lastInputR = 1; break;
                }
            }

            if (event.type == sf::Event::KeyReleased)
            {
                switch(event.key.code)
                {
                    case(sf::Keyboard::Left): lastInputR==-1?rotateTax = 0:rotateTax = 0.6; break;
                    case(sf::Keyboard::Right): lastInputR==1?rotateTax = 0:rotateTax = -0.6; break;
                }
            }
        }
        nave.rotate(rotateTax);
        printf("x: %f y: %f \n",sin((angle)*3.14159265/1800),cos((angle+90)*3.14159265/1800));
        nave.move( sin((angle)*-3.14159265/180)*throttlex, sin((angle+90)*3.14159265/180)*throttley);

        Window.clear();
        Window.draw(nave);
        Window.display();
    }

    return EXIT_SUCCESS;
}

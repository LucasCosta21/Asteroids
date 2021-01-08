////////////////////////////////////////////////
    /* Autor: Lucas Assunção Costa
       Data de criação: 03/01/2020
       Asteroids: ver 0.1        */
////////////////////////////////////////////////

//DEPENDÊNCIAS
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <cstdlib>
#include <ctime>

//MACROS E CONSTANTES
#define WIDTH 800
#define HEIGHT 600
#define SPEED 1
#define modulo(d) ((d)<0?d*-1:d)

int main()
{
    srand(time(NULL));
    int auxMeteoros[15], auxTiros[10], qtdMun = 9;

    sf::ConvexShape nave;
    nave.setPointCount(4);
    nave.setPoint(0, sf::Vector2f(-10,-20));
    nave.setPoint(1, sf::Vector2f(0,10));
    nave.setPoint(2, sf::Vector2f(10,-20));
    nave.setPoint(3, sf::Vector2f(0,-10));
    nave.setFillColor(sf::Color::Transparent);
    nave.setOutlineThickness(1);
    nave.setOutlineColor(sf::Color::White);
    nave.setPosition(WIDTH/2,HEIGHT/2);

    std::vector<sf::CircleShape> meteoros(15);
    for(int i=0;i<15;i++)
    {
        auxMeteoros[i] = 0;
        meteoros[i].setPointCount(7);
        meteoros[i].setRadius((rand()%20)+20);
        meteoros[i].setFillColor(sf::Color::Transparent);
        meteoros[i].setOutlineThickness(1);
        meteoros[i].setOutlineColor(sf::Color::White);
        meteoros[i].setPosition(-40,-40);
        meteoros[i].setOrigin(meteoros[i].getRadius(),meteoros[i].getRadius());
    }

    std::vector<sf::ConvexShape> tiros(10);
    for(int i=0;i<10;i++)
    {
        auxTiros[i] = 0;
        tiros[i].setPointCount(4);
        tiros[i].setPoint(0,sf::Vector2f(-1,-2));
        tiros[i].setPoint(1,sf::Vector2f(-1,2));
        tiros[i].setPoint(2,sf::Vector2f(1,2));
        tiros[i].setPoint(3,sf::Vector2f(1,-2));
        tiros[i].setFillColor(sf::Color::White);
        tiros[i].setPosition(300+(10*i),(10*i)+300);
        tiros[i].setOrigin(meteoros[i].getRadius(),meteoros[i].getRadius());
    }

    sf::RenderWindow Window(sf::VideoMode(WIDTH, HEIGHT), "Asteroids");
    Window.setFramerateLimit(350);

    float rotateTax = 0, lastInputR = 0, inputW = 0, dificuldade = 0.2;
    float throttlex = 0, throttley = 0, angle = nave.getRotation(), atirou = 0;

    while (Window.isOpen())
    {
        sf::Event event;
        while (Window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                Window.close();

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            {
                angle = nave.getRotation();
                throttlex += sin((angle)*3.14159265/180)/10;
                throttley += cos((angle)*3.14159265/180)/10;
            }

            if(throttlex > 0.5)
            {
                throttlex = 0.5;
            }
            if(throttley > 0.5)
            {
                throttley = 0.5;
            }

            if (event.type == sf::Event::KeyPressed)
            {
                switch(event.key.code)
                {
                    case(sf::Keyboard::Left): rotateTax = -0.6; lastInputR = -1; break;
                    case(sf::Keyboard::Right): rotateTax = 0.6; lastInputR = 1; break;
                    case(sf::Keyboard::Space): qtdMun>0?atirou = 1:true; break;
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
        nave.move( sin((angle)*-3.14159265/180)*modulo(throttlex),
                   sin((angle+90)*3.14159265/180)*modulo(throttley));

        if(nave.getPosition().x>800){nave.setPosition(0,nave.getPosition().y);}
        if(nave.getPosition().x<0){nave.setPosition(800,nave.getPosition().y);}
        if(nave.getPosition().y>600){nave.setPosition(nave.getPosition().x,0);}
        if(nave.getPosition().y<0){nave.setPosition(nave.getPosition().x,600);}

        for(int i=0;i<15;i++)
        {
            if(auxMeteoros[i]==0)
            {
                int x = rand()%2;
                int y = rand()%2;

                if(x == 0)
                {
                    if(y == 0)
                    {
                        meteoros[i].setPosition((rand()%800),-40);
                        meteoros[i].setRotation((rand()%90)-45);
                    }else
                    {
                        meteoros[i].setPosition((rand()%800),600);
                        meteoros[i].setRotation((rand()%90)+135);
                    }
                }else
                {
                    if(y == 0)
                    {
                        meteoros[i].setPosition(-40,rand()%600);
                        meteoros[i].setRotation((rand()%90)+225);
                    }else
                    {
                        meteoros[i].setPosition(800,rand()%600);
                        meteoros[i].setRotation((rand()%90)+45);
                    }
                }
            auxMeteoros[i] = 1;
            }else if(auxMeteoros[i]==1)
            {
                if(meteoros[i].getPosition().x>800 || meteoros[i].getPosition().x<-40
                   || meteoros[i].getPosition().y>600 || meteoros[i].getPosition().y<-40)
                {
                    auxMeteoros[i] = 0;
                }
            }

            meteoros[i].move( sin((meteoros[i].getRotation())*-3.14159265/180)*dificuldade,
                              sin((meteoros[i].getRotation()+90)*3.14159265/180)*dificuldade);
        }

        printf("origem nave : %d %d\n", nave.getOrigin().x,nave.getOrigin().y);

        if(atirou == 1)
        {
            atirou = 0;

            for(int i = 0; i < 10; i++)
            {
                if(auxTiros[i] == 0)
                {
                    if(nave.getRotation()<270 && nave.getRotation()>90)
                    {
                        nave.getRotation()>180?tiros[i].setPosition(nave.getPosition().x,nave.getPosition().y)
                        :tiros[i].setPosition(nave.getPosition().x,nave.getPosition().y);
                    }else
                    {
                        nave.getRotation()>180?tiros[i].setPosition(nave.getPosition().x,nave.getPosition().y)
                        :tiros[i].setPosition(nave.getPosition().x,nave.getPosition().y);
                    }

                    tiros[i].setRotation(nave.getRotation());
                    auxTiros[i] = 1;
                    qtdMun--;
                    break;
                }
            }
        }

        for(int i=0;i<10;i++)
        {
            if(auxTiros[i] == 1)
            {
                tiros[i].move(sin((tiros[i].getRotation())*-3.14159265/180)*0.7,
                               sin((tiros[i].getRotation()+90)*3.14159265/180)*0.7);
            }

            if((tiros[i].getPosition().x>800 || tiros[i].getPosition().x<-40
               || tiros[i].getPosition().y>600 || tiros[i].getPosition().y<-40)
               && auxTiros[i] == 1)
            {
                qtdMun++;
                auxTiros[i] = 0;
            }
        }

        Window.clear();
        Window.draw(nave);
        for(int i=0; i<15 ; i++)
        {
            Window.draw(meteoros[i]);
        }
        for(int i=0;i<10;i++)
        {
            if(auxTiros[i] == 1)
            {
                Window.draw(tiros[i]);
            }
        }
        Window.display();
    }

    return EXIT_SUCCESS;
}

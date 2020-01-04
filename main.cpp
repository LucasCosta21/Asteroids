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

////////////////////////////////////////////////
////////////////////////////////////////////////
////////////////////////////////////////////////
////////////////////////////////////////////////
////////////////////////////////////////////////

//Main function
int main()
{
    srand(time(NULL));
    int aux[30];

    //DEFINIÇÕES
    //Criação da nave
    sf::ConvexShape nave;
    nave.setPointCount(4);
    nave.setPoint(0, sf::Vector2f(-10,-10));
    nave.setPoint(1, sf::Vector2f(0,20));
    nave.setPoint(2, sf::Vector2f(10,-10));
    nave.setPoint(3, sf::Vector2f(0,0));
    nave.setFillColor(sf::Color::Transparent);
    nave.setOutlineThickness(1);
    nave.setOutlineColor(sf::Color::White);
    nave.setPosition(WIDTH/2,HEIGHT/2);

    //Criação dos meteoros
    std::vector<sf::CircleShape> meteoros(30);
    for(int i=0;i<30;i++)
    {
        aux[i] = 0;
        meteoros[i].setPointCount(7);
        meteoros[i].setRadius((rand()%20)+20);
        meteoros[i].setFillColor(sf::Color::Transparent);
        meteoros[i].setOutlineThickness(1);
        meteoros[i].setOutlineColor(sf::Color::White);
        meteoros[i].setPosition(-40,-40);
    }

    //Renderização da janela
    sf::RenderWindow Window(sf::VideoMode(WIDTH, HEIGHT), "Asteroids");

    //Variáveis de lógica do jogo
    float rotateTax = 0, lastInputR = 0, inputW = 0, dificuldade = 0.2;
    float throttlex = 0, throttley = 0, angle = nave.getRotation();

    ////////////////////////////////////////////////
    ////////////////////////////////////////////////
    ////////////////////////////////////////////////
    ////////////////////////////////////////////////
    ////////////////////////////////////////////////

    //game loop
    while (Window.isOpen())
    {
        ////////////////////////////////////////////////
        ////////////////////////////////////////////////
        ////////////////////////////////////////////////
        ////////////////////////////////////////////////

        //INPUT
        sf::Event event;
        while (Window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                Window.close();

            //Controle de aceleração da nave
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            {
                angle = nave.getRotation();
                throttlex += sin((angle)*3.14159265/180)/10;
                throttley += cos((angle)*3.14159265/180)/10;
            }

            if(throttlex > 1)
            {
                throttlex = 1;
            }
            if(throttley > 1)
            {
                throttley = 1;
            }

            //Controle de rotação da nave
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

        ////////////////////////////////////////////////
        ////////////////////////////////////////////////
        ////////////////////////////////////////////////
        ////////////////////////////////////////////////
        ////////////////////////////////////////////////

        //MOVIMENTAÇÃO
        nave.rotate(rotateTax);
        printf("x: %f y: %f \n",sin((nave.getRotation())*3.14159265/180),sin((nave.getRotation()+90)*3.14159265/180));
        nave.move( sin((angle)*-3.14159265/180)*modulo(throttlex), sin((angle+90)*3.14159265/180)*modulo(throttley));

        if(nave.getPosition().x>800){nave.setPosition(0,nave.getPosition().y);}
        if(nave.getPosition().x<0){nave.setPosition(800,nave.getPosition().y);}
        if(nave.getPosition().y>600){nave.setPosition(nave.getPosition().x,0);}
        if(nave.getPosition().y<0){nave.setPosition(nave.getPosition().x,600);}

        for(int i=0;i<15;i++)
        {
            if(aux[i]==0)
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
            aux[i] = 1;
            }else if(aux[i]==1)
            {
                if(meteoros[i].getPosition().x>800 || meteoros[i].getPosition().x<-40 || meteoros[i].getPosition().y>600 || meteoros[i].getPosition().y<-40)
                {
                    aux[i] = 0;
                }
            }

            meteoros[i].move( sin((meteoros[i].getRotation())*-3.14159265/180)*dificuldade, sin((meteoros[i].getRotation()+90)*3.14159265/180)*dificuldade);
        }

        ////////////////////////////////////////////////
        ////////////////////////////////////////////////
        ////////////////////////////////////////////////
        ////////////////////////////////////////////////
        ////////////////////////////////////////////////

        //RENDERIZAÇÃO
        Window.clear();
        Window.draw(nave);
        for(int i=0; i<15 ; i++)
        {
            Window.draw(meteoros[i]);
        }
        Window.display();
    }

    return EXIT_SUCCESS;
}

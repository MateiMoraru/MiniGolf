#include <iostream>
#include <chrono>
#include <SFML/Graphics.hpp>
#include "ball.h"
#include "walls.h"
#define WIDTH 1200
#define HEIGHT 800

int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "MiniGolf!");
    window.setFramerateLimit(60);

    sf::Font Arial;
    if(!Arial.loadFromFile("res/Arial.ttf"))
    {
        std::cout << "Failed to load font!" << std::endl;
        return -1;
    }
    sf::Text TextFps;
    TextFps.setFont(Arial);
    TextFps.setString(" ");
    TextFps.setPosition(10, 30);

    Ball ball = Ball(sf::Vector2f(200, 400));
    Walls walls = Walls();

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
            if(event.type == sf::Event::KeyPressed)
                switch(event.key.code)
                {
                    case sf::Keyboard::W:
                        break;
                    case sf::Keyboard::S:
                        break;
                    case sf::Keyboard::A:
                        break;
                    case sf::Keyboard::D:
                        break;
                }
            if(event.type == sf::Event::MouseButtonPressed)
            {
                if(event.mouseButton.button == sf::Mouse::Left)
                {
                    ball.mousePressed();
                }
            }
            else if(event.type == sf::Event::MouseButtonReleased)
            {
                if(event.mouseButton.button == sf::Mouse::Left)
                {
                    ball.mouseReleased();
                }   
            }
        }
   
        window.clear(sf::Color(23, 107, 12));
        ball.draw(window);
        ball.update(window);
        walls.draw(window, ball);
        window.draw(TextFps);
        window.display();
        TextFps.setString(std::to_string(ball.getVelocity().x) + " " + std::to_string(ball.getVelocity().y));
    }
}


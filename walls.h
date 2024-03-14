#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class Walls
{
    private:
        // replace std::pair<sf::Vector> with VertexArray(sf::LineStrip, 2)
        std::vector<sf::VertexArray> walls;

    public:
        Walls()
        {
            sf::VertexArray line(sf::LinesStrip, 2);
            line[0].position = sf::Vector2f(100, 100);
            line[1].position = sf::Vector2f(500, 300);
            walls.push_back(line);

        }    

        void draw(sf::RenderWindow &window, Ball &ball)
        {
            for(int i = 0; i < walls.size(); i++)
            {
                sf::VertexArray line = walls[i];
                
                sf::Vector2f pos1 = sf::Vector2f(line[0].position.x, line[0].position.y);
                sf::Vector2f pos2 = sf::Vector2f(line[1].position.x, line[1].position.y);
                if(ball.intersectsLine(pos1, pos2))
                {
                    ball.reverseVelocity();
                }
                window.draw(line); 
            }
        }
};

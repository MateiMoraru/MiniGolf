#include <SFML/Graphics.hpp>
#include <math.h>

class Ball
{
    private:
        sf::Vector2f position;
        int size;
        sf::CircleShape ball;
        sf::Vector2f velocity;
        sf::Vector2f force;
        sf::Vector2f drag;
        bool mouseDown = false;
        bool selected = false;

    public:
        Ball(sf::Vector2f pos)
        {
            position = pos;
            size = 15;
            ball.setRadius(size);
            ball.setPosition(pos);
        }
        
        void draw(sf::RenderWindow &window)
        {
            window.draw(ball);
            
            if(selected)
                drawDrag(window);
        }
        
        void drawDrag(sf::RenderWindow &window)
        {
            sf::VertexArray triangle(sf::Triangles, 3);

            float dy = (drag.y - (position.y + size)) / 100;
            float dx = (drag.x - (position.x + size)) / 100;

            // Still figuring out how trigonometry works
            triangle[0].position = drag;
            triangle[1].position = sf::Vector2f(position.x + size / 2, position.y + 2);
            triangle[2].position = sf::Vector2f(position.x + size / 2 + cos(dx) * 10, position.y + size * 2 - 2 - sin(dy));


            triangle[0].color = sf::Color(186, 71, 84, 100);
            triangle[1].color = sf::Color(122, 18, 30, 200);
            triangle[2].color = sf::Color(122, 18, 30, 200);

            window.draw(triangle);
        }

        void update(sf::RenderWindow &window)
        {
            sf::Vector2i mousePixel = sf::Mouse::getPosition(window);
            sf::Vector2f mousePosition = window.mapPixelToCoords(mousePixel);

            if(mouseDown)
            {
                if(contains(mousePosition))
                {
                    selected = true;
                }
                if(selected)
                    drag = mousePosition;
            }
            else
            {
                if(selected)
                {
                    calculateForce();
                    velocity.x += force.x;
                    velocity.y += force.y;
                    selected = false;
                }
            }


            if(abs(velocity.x) < 0.001)
                velocity.x = 0;
            else
                velocity.x -= 0.1 * (velocity.x / abs(velocity.x));
            if(abs(velocity.y) < 0.001)
                velocity.y = 0;
            else
                velocity.y -= 0.1 * (velocity.y / abs(velocity.y));

            position.x += velocity.x;
            position.y += velocity.y;

            if(position.x + size > window.getSize().x || position.x < 0)
            {
                velocity.x *= -1;
                position.x += velocity.x;
            }
            if(position.y + size > window.getSize().y || position.y < 0)
            {
                velocity.y *= -1;
                position.y += velocity.y;
            }

            ball.setPosition(position);
        }

        void calculateForce()
        {
            force.x = -(drag.x - position.x + size) / 30;
            force.y = -(drag.y - position.y + size) / 30;
            std::cout << force.x << ' ' << force.y << std::endl;
        }
        
        bool contains(sf::Vector2f pos)
        {
            return distance(pos) <= size;
        }

        float distance(sf::Vector2f pos)
        {
            float a = pos.x - (position.x + size);
            float b = pos.y - (position.y + size);
            a *= a;
            b *= b;
            return sqrt(a + b);
        }

        void mousePressed()
        {
            mouseDown = true;
        }

        void mouseReleased()
        {
            mouseDown = false;
        }
};

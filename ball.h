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
            float a = drag.x - position.x;
            float b = drag.y - position.y;
            float c = sqrt(a * a + b * b);
            a /= c;
            b /= c;
            force.x = -a * 5 * c / 100;
            force.y = -b * 5 * c / 100;
            std::cout << force.x << ' ' << force.y << std::endl;
        }

        bool intersectsLine(sf::Vector2f start, sf::Vector2f end)
        {
            float x1 = start.x, y1 = start.y, x2 = end.x, y2 = end.y;
            float cx = position.x + size, cy = position.y + size;
            float r = size;
            bool inside1 = contains(sf::Vector2f(x1,y1));
            bool inside2 = contains(sf::Vector2f(x2,y2));
            if (inside1 || inside2) return true;

            float distX = x1 - x2;
            float distY = y1 - y2;
            float len = sqrt( (distX*distX) + (distY*distY) );

            float dot = ( ((cx-x1)*(x2-x1)) + ((cy-y1)*(y2-y1)) ) / pow(len,2);

            float closestX = x1 + (dot * (x2-x1));
            float closestY = y1 + (dot * (y2-y1));

            bool onSegment = linePoint(x1,y1,x2,y2, closestX,closestY);
            if (!onSegment) return false;
            distX = closestX - cx;
            distY = closestY - cy;
            float distance = sqrt( (distX*distX) + (distY*distY) );

            if (distance <= r) {
                return true;
            }
            return false;
        }

        bool contains(sf::Vector2f pos)
        {
            return distance(pos) <= size;
        }

        bool linePoint(float x1, float y1, float x2, float y2, float px, float py)
        {
            float d1 = distance(sf::Vector2f(x1,y1));
            float d2 = distance(sf::Vector2f(x2,y2));

            float lineLen = dist(sf::Vector2f(x1,y1), sf::Vector2f(x2,y2));

            float buffer = 0.1;    // higher # = less accurate

            if (d1+d2 >= lineLen-buffer && d1+d2 <= lineLen+buffer) {
                return true;
            }
            return false;
        }

        float dist(sf::Vector2f pos1, sf::Vector2f pos2)
        {
            float a = pos1.x - pos2.x;
            float b = pos1.y - pos2.y;
            
            return sqrt(a * a + b * b);
        }

        float distance(sf::Vector2f pos)
        {
            float a = pos.x - (position.x + size);
            float b = pos.y - (position.y + size);
            a *= a;
            b *= b;
            return sqrt(a + b);
        }

        void reverseVelocity()
        {
            velocity.x *= -1;
            velocity.y *= -1;
        }

        void mousePressed()
        {
            mouseDown = true;
        }

        void mouseReleased()
        {
            mouseDown = false;
        }

        sf::Vector2f getVelocity()
        {
            return velocity;
        }
};

#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
int main()
{
    sf::RenderWindow window({640,480}, "GAME");
    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        window.display();
    }
    return 0;
}

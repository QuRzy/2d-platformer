#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
void checkCollision(sf::RectangleShape& player, const sf::RectangleShape& cube, bool& isGround, bool& isJump, float& countJump)
{
    if(player.getGlobalBounds().intersects(cube.getGlobalBounds()))
    {
        int i = -1;
        int min = 10000;
        if(abs((player.getPosition().x+player.getSize().x) - cube.getPosition().x) < min)
        {
            min = abs((player.getPosition().x+player.getSize().x) - cube.getPosition().x);
            i = 0;
        }
        if(abs(player.getPosition().x - (cube.getPosition().x + cube.getSize().x)) < min)
        {
            min = abs(player.getPosition().x - (cube.getPosition().x + cube.getSize().x));
            i = 1;
        }
        if(abs( (player.getPosition().y+player.getSize().y) - cube.getPosition().y ) < min)
        {
            min = abs( (player.getPosition().y+player.getSize().y) - cube.getPosition().y );
            i = 2;
        }
        if(abs( player.getPosition().y - (cube.getPosition().y + cube.getSize().y) ) < min)
        {
            min = abs( player.getPosition().y - (cube.getPosition().y + cube.getSize().y) );
            i = 3;
        }
        switch (i) {
            case 0:
                player.setPosition(cube.getPosition().x - player.getSize().x, player.getPosition().y);
                break;
            case 1:
                player.setPosition(cube.getPosition().x + cube.getSize().x, player.getPosition().y);
                break;
            case 2:
                player.setPosition(player.getPosition().x, cube.getPosition().y - player.getSize().y);
                isGround = true;
                break;
            case 3:
                player.setPosition(player.getPosition().x, cube.getPosition().y + cube.getSize().y);
                isJump = false;
                countJump = 15;
                break;
        }
    }
}
int main()
{
    sf::RenderWindow window({640,480}, "GAME");
    sf::Clock clock;
    sf::RectangleShape player;
    player.setSize({32, 32});
    player.setPosition(window.getSize().x / 2,window.getSize().y / 2);
//    window.setFramerateLimit(60);
    char map[][21] = {
            "11111111111111111111",
            "10000000000000000001",
            "10000000000000000001",
            "10000000000000000001",
            "10000000000000000001",
            "10000000000000000001",
            "10000000000000000001",
            "10011100000000000001",
            "10000000000000000001",
            "10000010000000000001",
            "10000011111000000001",
            "10000000000000011101",
            "10000000000000000001",
            "11110000000000000001",
            "11111111111111111111"

    };
    bool isJump = false;
    float countJump = 15;
    bool isGround = false;
    float countFall = 1.f;
    while(window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();
        deltaTime *= 60;
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
        }
        sf::Vector2f lastPos = player.getPosition();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            player.move(-8.f * deltaTime, 0);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            player.move(8.f * deltaTime, 0);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && isGround)
            isJump = true;
        if(isJump)
        {
            if(countJump > 0) {
                player.move(0, -countJump * deltaTime);
                countJump -= 1 * deltaTime;
            }
            else
            {
                countJump = 15;
                isJump = false;
            }
        }
        if(!isJump && !isGround)
        {
            player.move(0, countFall * deltaTime);
            if(countFall < 8.f)
            {
                countFall += 1.f * deltaTime;
            }
        }
        else{
            countFall = 1;
        }
        isGround = false;

        window.clear();
        for(int i = 0;  i < 15; ++i)
        {
            for(int j = 0; map[i][j] != '\0'; ++j)
            {
                if(map[i][j] != '1')
                    continue;
                sf::RectangleShape cube;
                cube.setSize({32, 32});
                cube.setFillColor(sf::Color::Blue);
                cube.setPosition(j * 32, i * 32);
                window.draw(cube);
                checkCollision(player, cube, isGround, isJump, countJump);

            }
        }
        window.draw(player);
        window.display();
    }
    return 0;
}
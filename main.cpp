#include <iostream>
#include<cstdlib>
#include <SFML/Graphics.hpp>

using namespace std;

#define WINDOWX 800
#define WINDOWY 800

#define SNAKESIZE 20

void Log(string);
void CheckBoundaries(sf::RectangleShape&);

int main() {
	cout << "Hello, Snake" << endl;

    sf::RenderWindow window(sf::VideoMode(WINDOWX, WINDOWY), "SFML works!");

    sf::Vector2f headSize(SNAKESIZE, SNAKESIZE);
    sf::Vector2f UpVector(0, -SNAKESIZE);
    sf::Vector2f DownVector(0, SNAKESIZE);
    sf::Vector2f RightVector(SNAKESIZE, 0);
    sf::Vector2f LeftVector(-SNAKESIZE, 0);

    sf::Vector2f moveVector = RightVector;

    sf::RectangleShape snakeHead(headSize);
    sf::CircleShape apple(10.f);
    apple.setFillColor(sf::Color(250, 50, 10));
    apple.setOutlineThickness(1.f);
    apple.setOutlineColor(sf::Color(250, 150, 100));
    snakeHead.setFillColor(sf::Color::Green);

    sf::Clock gameClock;
    sf::Clock updateClock;
    sf::Time timeElapsed;
    sf::Time colorElapsed;

    int score = 0;
    int frameCount = 0;
    bool IsInputAllowed = true;
    bool IsMoving = false;

    // Providing a seed value
    srand((unsigned)time(NULL));

    //// Get a random number
    //int random = rand();

    float num, dec, numcpy;
    int n, last;
    cout << "Input number :";
    cin >> num;
    numcpy = num;
    dec = num - floor(num);
    num = numcpy;
    n = floor(num);
    if (n % 10 < 5)
    {
        n = (n / 10) * 10;
    }
    else if (n % 10 == 5)
    {
        if (dec > 0)
            n = (((n + 10) / 10) * 10);
        else
            n = (n / 10) * 10;
    }
    else
    {
        n = (((n + 10) / 10) * 10);
    }

    sf::Vector2f appleVector(, rand() % WINDOWY);
    apple.setPosition(appleVector);
    cout << "apple position " << apple.getPosition().x << ", " << apple.getPosition().y << endl;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        timeElapsed = updateClock.getElapsedTime();

        /*colorElapsed = gameClock.getElapsedTime();
        if (colorElapsed.asMilliseconds() % 100 == 0)
        {
            snakeHead.setFillColor(sf::Color::Red);
        }
        else
        {
            snakeHead.setFillColor(sf::Color::Black);
        }*/

        // Update function
        if (timeElapsed.asMilliseconds() >= 200)
        {
            updateClock.restart();

            snakeHead.move(moveVector);
            CheckBoundaries(snakeHead);
            frameCount++;

            //cout << "frame number: " << frameCount << endl;
        }

        // Input function
        if (event.type == sf::Event::KeyPressed && IsInputAllowed)
        {
            //cout << "printing keycode " << event.key.code << endl;

            IsInputAllowed = false;
            IsMoving = true;

            if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up) // UP
            {
                moveVector = UpVector;
                snakeHead.move(moveVector);
            }

            if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down) // DOWN
            {
                moveVector = DownVector;
                snakeHead.move(moveVector);
            }

            if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right) // RIGHT
            {
                moveVector = RightVector;
                snakeHead.move(moveVector);
            }

            if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left) // LEFT
            {
                moveVector = LeftVector;
                snakeHead.move(moveVector);
            }

            // keyboard not working??
            if (event.key.code == sf::Keyboard::Escape)
            {
                Log("Trying to quit!");
                return 0;
            }

            CheckBoundaries(snakeHead);
        }

        if (event.type == sf::Event::KeyReleased && IsMoving)
        {
            IsInputAllowed = true;
            IsMoving = false;
        }

        window.clear();
        window.draw(snakeHead);
        window.draw(apple);
        window.display();
    }

	return 0;
}

void CheckBoundaries(sf::RectangleShape& object) {
    if (object.getPosition().x < 0 || object.getPosition().x >= WINDOWX)
    {
        if (object.getPosition().x < 0)
        {
            object.setPosition(sf::Vector2f(WINDOWX - SNAKESIZE, object.getPosition().y));
        }
        else
        {
            object.setPosition(sf::Vector2f(0, object.getPosition().y));
        }
    }

    if (object.getPosition().y < 0 || object.getPosition().y >= WINDOWY)
    {
        if (object.getPosition().y < 0)
        {
            object.setPosition(sf::Vector2f(object.getPosition().x, WINDOWY - SNAKESIZE));
        }
        else
        {
            object.setPosition(sf::Vector2f(object.getPosition().x, 0));
        }
    }
}

void Log(string logMessage) {
    cout << "[LOG] " << logMessage << endl;
}
/// <summary>
/// @author Peter Lowe
/// @date May 2019
///
/// you need to change the above lines or lose marks
/// </summary>

#include "Game.h"
#include <iostream>



/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ 800U, 600U, 32U }, "SFML Game" },
	m_exitGame{false} //when true game will exit
{
	setupFontAndText(); // load font 
	setupSprite(); // load texture
}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but mthod needs to be here
/// </summary>
Game::~Game()
{
}


/// <summary>
/// main game loop
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
void Game::run()
{	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
#ifdef _DEBUG
			render(); // want to debug drawing while stepping through code
#endif // _DEBUG

		}
		render(); // as many as possible
	}
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if ( sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}
	}
}


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	if (t_deltaTime.asMilliseconds() != 16)
	{
		std::cout << "time warp" << std::endl; // expecting 60 fps of action
	}
	if (m_exitGame)
	{
		m_window.close();
	}
	move();
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::White);
	m_window.draw(m_welcomeMessage);
	
	for (int i = 0; i < m_snakeLenght; i++)
	{
		m_snakeTail.setPosition(m_tail[i]);
		m_window.draw(m_snakeTail);
	}
	m_window.draw(m_snakeBody);
	m_window.display();
}

void Game::move()
{
	float speed = 2.0f;
	switch (m_direction)
	{
	case Direction::Up:		
		m_snakeBody.move(0.0f, -speed);
		break;
	case Direction::Right:           		
		m_snakeBody.move(speed, 0.0f);
		break;
	case Direction::Down:		
		m_snakeBody.move(0.0f, speed);
		break;
	case Direction::Left:		
		m_snakeBody.move(-speed, 0.0f);
		break;
	default:
		break;
	}
	switch (m_tailDirections[m_snakeLenght - 1])
	{
	case Direction::Up:
		m_tail[m_snakeLenght - 1].y -= speed;
		break;
	case Direction::Down:
		m_tail[m_snakeLenght - 1].y += speed;
		break;
	case Direction::Right:
		m_tail[m_snakeLenght - 1].x += speed;
		break;
	case Direction::Left:
		m_tail[m_snakeLenght - 1].x -= speed;
		break;
	default:
		break;
	}

	if (static_cast<int>(m_snakeBody.getPosition().x) % 32 == 0 &&
		static_cast<int>(m_snakeBody.getPosition().y) % 32 == 0)
	{
		checkDirection();
	}
}

void Game::checkDirection()
{


	if (m_snakeBody.getPosition().x > 733 && m_snakeBody.getPosition().y < 65)
	{
		m_direction = Direction::Down;
	}
	if (m_snakeBody.getPosition().y > 533 && m_snakeBody.getPosition().x > 733)
	{		
		m_direction = Direction::Left;
	}
	if (m_snakeBody.getPosition().x < 65 && m_snakeBody.getPosition().y > 533)
	{
		m_direction = Direction::Up;
	}
	if (m_snakeBody.getPosition().y < 65 && m_snakeBody.getPosition().x < 65)
	{
		m_direction = Direction::Right;
	}
	
	for (int i = m_snakeLenght; i > 0; i--)
	{
		m_tail[i] = m_tail[i - 1];
		m_tailDirections[i] = m_tailDirections[i - 1];
	}
	m_tail[0] = m_snakeBody.getPosition();
	m_tailDirections[0] = m_direction;
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setupFontAndText()
{
	if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}
	m_welcomeMessage.setFont(m_ArialBlackfont);
	m_welcomeMessage.setString("Snake");
	m_welcomeMessage.setPosition(40.0f, 40.0f);
	m_welcomeMessage.setCharacterSize(30U);
	m_welcomeMessage.setOutlineColor(sf::Color::Red);
	m_welcomeMessage.setFillColor(sf::Color::Black);
	m_welcomeMessage.setOutlineThickness(1.0f);

}

/// <summary>
/// load the texture and setup the sprite for the logo
/// </summary>
void Game::setupSprite()
{
	if (!m_logoTexture.loadFromFile("ASSETS\\IMAGES\\SFML-LOGO.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading logo" << std::endl;
	}
	m_logoSprite.setTexture(m_logoTexture);
	m_logoSprite.setPosition(300.0f, 180.0f);

	m_snakeBody.setFillColor(sf::Color::Green);
	m_snakeBody.setSize(sf::Vector2f{ 32.0f,32.0f });
	m_snakeBody.setPosition(64.0f, 64.0f);

	m_snakeTail.setFillColor(sf::Color::Blue);
	m_snakeTail.setSize(sf::Vector2f{ 32.0f,32.0f });
	m_snakeTail.setPosition(-64.0f, -64.0f);
}

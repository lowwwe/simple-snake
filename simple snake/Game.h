/// <summary>
/// author Pete Lowe May 2022
/// Snake
/// </summary>
#ifndef GAME_HPP
#define GAME_HPP 
/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the endif at the bottom
/// </summary>
#include <SFML/Graphics.hpp>

const int MAX_LENGHT = 20;

enum class Direction
{
	Up,
	Right,
	Down,
	Left
};


class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

private:
	
	
	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	void move();
	void checkDirection();
	
	void setupFontAndText();
	void setupSprite();

	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_welcomeMessage; // text used for message on screen
	sf::Texture m_logoTexture; // texture used for sfml logo
	sf::Sprite m_logoSprite; // sprite used for sfml logo
	bool m_exitGame; // control exiting game
	sf::RectangleShape m_snakeBody; // square for sanke
	sf::RectangleShape m_snakeTail;// square for snake tail
	Direction m_direction{ Direction::Right };// diresction snake is heading
	int m_snakeLenght{15};
	sf::Vector2f m_tail[MAX_LENGHT];
	Direction m_tailDirections[MAX_LENGHT];


};

#endif // !GAME_HPP



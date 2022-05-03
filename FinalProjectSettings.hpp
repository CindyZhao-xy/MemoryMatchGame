/*
* File name : FinalProjectSettings.hpp
* Course : CST8219_S20_Cplusplus Programming
* Final Project Template
* Student : Xinyi Zhao
* Stud.ID : 040953633
* Professor : Eric Torunski, Mariusz Makos
* Due Date : August-07-2020
* Lab Section : 303
*/
#pragma once

#include <iostream>

/* Three SFML hpp files */
#include <SFML/Graphics.hpp>
#include "SFML/Window.hpp"
#include <SFML/Audio.hpp>

/* include hpp file */
#include "FinalProjectSettings.hpp"

/* set namespace */
using namespace std;
using namespace sf;

namespace FinalProject {
const string arrayOfImage[10] = { 
/* Store the pictures */		"bird1.png",
								"bird2.png",
								"bird3.png",
								"bird4.png",
								"bird5.png",
								"bird6.png",
								"bird7.png",
								"bird8.png",
								"bird9.png",
								"bird10.png" };
class Cards {
public:
	/* the cards all show the same back of the card */
		string showBack;
	Cards(int i) {
		showBack = arrayOfImage[i];
	}
}; // // End of Cards

///////////////////////////////////////////////////////////////

class GameSettings {
public:
	typedef struct Position {
		/* From left to right */
		float Axis_x; 
		/* From top to button */
		float Axis_y;
		
		/* set <double> point_x, point_y */
		Position(double point_x, double point_y) 
		{
				this->Axis_x = point_x;
				this->Axis_y = point_y;
		} // End of Position(double, double)
	}ImagePosition; // struct -> ImagePosition
		
	/* Global variables */
	int flip,click,matched;

	/* 2 array for store 20 pictures */
	int clicking[20] = {};
	int matching[20] = {};

	/* Global variables -> SFML */

	/* sf::Sprite */
	sf::Sprite gameSettings;
	sf::Sprite quitGame;
	sf::Sprite sprite;
	sf::Sprite spritesArray[20];

	/* sf::Texture */
	sf::Texture Texture_game;
	sf::Texture Texture_quit;
	
	/* sf:: Sound */
	sf::SoundBuffer buffer;
	sf::Sound sound;

	/*sf:: window */
	sf::RenderWindow window;

	/* Global variables -> vector<> */
	vector<ImagePosition>positions;
	vector<Cards>cardsBoard;

	/* friend bool class for two cards */
	friend bool operator==(const Cards& card_1, const Cards& card_2);

	GameSettings() :window(sf::VideoMode(1000, 800), "Memory Matching Game ___ BY:Xinyi Zhao") 
	{
		/* initialize */
		flip = 0;
		matched = 0;
		click = 0;
			for (int i = 0; i < 20; i++) {
				clicking[i] = 0;
				matching[i] = 0;
			}		
	} // End of GameSettings

	/* Set random position of cards */
	void temporayRandom(){
		float px = 50;
		float py = 50;

		/* Set the pictures as random positions */
		for (int y = 0; y < 2; y++)
			for (int x = 0; x < 10; x++)
			cardsBoard.push_back(Cards(x));
			random_shuffle(cardsBoard.begin(), cardsBoard.end());
			/* rows -> 5*/
			for (int a = 0; a < 5; a++){
				/* columns -> 4 */
				for (int b = 0; b < 4; b++){
					positions.push_back(Position(px, py));
					px += 220.0;
				}
				px = 50.0;
				py += 120.0;
			}
		}// End of temporaryRandom

		/* Display and load all images */
	void draw(){
		sf::Texture texture;
			for (int i = 0; i < 20; i++){
				sprite.setPosition(positions[i].Axis_x, positions[i].Axis_y);
				spritesArray[i] = sprite;
				if (clicking[i] == 1 || matching[i] == 1){
					if (matching[i] == 1) {
						texture.loadFromFile("nothing.jpg"); // blank file
						sprite.setTexture(texture);
					}
					else {
						texture.loadFromFile(cardsBoard[i].showBack);
						sprite.setTexture(texture);
					}
				}
				else {
					/* green peakcock -> the original back image */
					texture.loadFromFile("original.jpg");
					sprite.setTexture(texture);
				}
				window.draw(sprite);
			}
		} // End of draw

	/* if the two cards are matching */
	void pair(int i){
		/* initialize */
			flip = 0;
			int ring = 0;
			for (int a = 0; a < 20; a++){
				/* check if the two cards are matching */
				if (clicking[a] == 1 && a != i){
					if (cardsBoard[i] == cardsBoard[a]) {
						matching[i] = 1;
						matching[a] = 1;
						matched++;
						ring = 1;
					}
					else {
						clicking[i] = 0;
						clicking[a] = 0;
					}
				}
				else if (clicking[a] == 1 && a == i) {
					clicking[i] = 0;
					clicking[a] = 0;
				}
			}// End of for loop

			/* if not matching -> play the wrong.wav file */
			if (!ring) {
				if (!buffer.loadFromFile("wrong.wav"))
					cerr << "Fail to load sound";
				sound.setBuffer(buffer);
				sound.play();
			}
			/* otherwise -> matching -> play the correct.wav */
			else{
				if (!buffer.loadFromFile("correct.wav"))
					cerr << "Unable to load the sounding";
				sound.setBuffer(buffer);
				sound.play();			
			}
		} // End of pair
		
		void isClicked() {
			sf::Vector2i localPosition = sf::Mouse::getPosition(window);
			sf::Vector2f floatPosition(localPosition.x, localPosition.y);
			sf::Texture texture;			
			for (int i = 0; i < 20; i++) {			
				if (spritesArray[i].getGlobalBounds().contains(floatPosition)){					
					sprite.setPosition(positions[i].Axis_x, positions[i].Axis_y);
					texture.loadFromFile(cardsBoard[i].showBack);
					sprite.setTexture(texture);
					clicking[i] = 1;
					window.draw(sprite);
					flip++;
					click++;
					/* if two cards turn to front */
					if (flip == 2){	
						window.clear();
						/* call draw function to display */
						draw();
						window.display();

						/* show 1 seconds */
						sleep(milliseconds(1000));
						pair(i);
					}			
					break;
				}
			}
		} // End of isCliecked 

	void win()
		{
			Text message;
			Sprite win;
			Texture winTexture;
			string text;
			//////////////////////////////////
			text = "Clicked " + click;
			text += " times to finish the game! ";
			win.setPosition(50,50);
			winTexture.loadFromFile("win.png");
			win.setTexture(winTexture);
			//////////////////////////////////
			text = "Clicked " + click;
			gameSettings.setPosition(80, 400);
			Texture_game.loadFromFile("newGame.png");
			gameSettings.setTexture(Texture_game);
			window.draw(gameSettings);
			//////////////////////////////////
			text = "Clicked " + click;
			quitGame.setPosition(300, 400);
			Texture_quit.loadFromFile("quit.png");
			quitGame.setTexture(Texture_quit);
			window.draw(quitGame);
			//////////////////////////////////
			text = "Clicked " + click;
			message.setString(text);
			message.setFillColor(Color::White);
			message.setPosition(Vector2f(50, 300));
			//////////////////////////////////
			text = "Clicked " + click;
			window.draw(win);
			window.draw(message);
			window.display();			
		} // End of win

		int doAgain() {		
			sf::Vector2i localPosition = sf::Mouse::getPosition(window);
			sf::Vector2f floatPosition(localPosition.x, localPosition.y);
			if (gameSettings.getGlobalBounds().contains(floatPosition))
				return 1; // true
			else
				return 0; // false
			/* show 1 seconds */
			sleep(milliseconds(1000));
		}
		int quitG() {
			sf::Vector2i localPosition = sf::Mouse::getPosition(window);
			sf::Vector2f floatPosition(localPosition.x, localPosition.y);
			if (quitGame.getGlobalBounds().contains(floatPosition))
				return 1; // false
			else
				return 0; // true			
		} // End of quitG
	}; // End of GameSettings
bool operator==(const Cards& card1, const Cards& card2) {
		if (card1.showBack != card2.showBack)
			return 0; // false
		else
			return 1; // true
} // End of operator==
}; // End of namespace FinalProject





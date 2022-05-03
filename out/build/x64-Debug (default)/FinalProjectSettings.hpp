
#pragma once
#include <iostream>
#include "FinalProjectSettings.hpp"
#include <SFML/Graphics.hpp>
#include "SFML/Window.hpp"
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;

namespace FinalProject {
	const string imageArray[10] = { "bird1.png",
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
		string hidden;
		
		Cards(int i) {
			hidden = imageArray[i];
		}
	};

	class Game {
	public:
		typedef struct Coordinates {
			float x, y;
			Coordinates(double px, double py) {
				x = px;
				y = py;

			}

		}Coord;
		
		int flips ;
		int clicks;
		int clickflag[20] = {};
		int findflag[20] = {};
		int found;
		Sprite game;
		Texture gameT;
		Sprite quit;
		Texture quitT;
		SoundBuffer buffer;
		Sound sound;
		vector<Coord>coordinates;
		Sprite sprites[20];
		vector<Cards>cardsDeck;
		Sprite sprite;
		RenderWindow window;

		friend bool operator==(const Cards& card1, const Cards& card2);

		Game() :window(sf::VideoMode(800, 800), "Hello World") {
			flips = 0;
			found = 0;
			clicks = 0;
			for (int i = 0; i < 20; i++) {
				clickflag[i] = 0;
				findflag[i] = 0;

			}
			
		}

		void staging()
		{
			float px = 50;
			float py = 0;

			for (int y = 0; y < 2; y++)
				for (int x = 0; x < 10; x++)
					cardsDeck.push_back(Cards(x));
			random_shuffle(cardsDeck.begin(), cardsDeck.end());

			for (int a = 0; a < 5; a++)
			{
				for (int b = 0; b < 4; b++)
				{
					coordinates.push_back(Coordinates(px, py));
					px += 200.0;
				}
				px = 50.0;
				py += 100.0;
			}

		}//set position array,

		void draw()
		{

			Texture texture;
			for (int i = 0; i < 20; i++)
			{
				
				sprite.setPosition(coordinates[i].x, coordinates[i].y);
				sprites[i] = sprite;
				if (clickflag[i] == 1 || findflag[i] == 1)
				{
					if (findflag[i] == 1) {
						texture.loadFromFile("nothing.jpg");
						sprite.setTexture(texture);
					}
					else {
						texture.loadFromFile(cardsDeck[i].hidden);
						sprite.setTexture(texture);
					}
				}
				else {
					texture.loadFromFile("original.jpg");
					sprite.setTexture(texture);
				}
				window.draw(sprite);

			}//layout all sprites;
			


		}


	void compare(int i)
		{
			flips = 0;

			int soundflag = 0;
			for (int a = 0; a < 20; a++)
			{
				// check if the two cards are the same
				if (clickflag[a] == 1 && a != i)
				{
					if (cardsDeck[i] == cardsDeck[a]) {
						findflag[i] = 1;
						findflag[a] = 1;
						found++;
						soundflag = 1;
					}

					else {
						clickflag[i] = 0;
						clickflag[a] = 0;
					}
				}
				else if (clickflag[a] == 1 && a == i) {
					clickflag[i] = 0;
					clickflag[a] = 0;


				}

			}//end of for loop

			if (!soundflag) {
				if (!buffer.loadFromFile("wrong.wav"))
					printf("Unable to load sound resource!");

				sound.setBuffer(buffer);

				sound.play();
				

			}
			else
			{
				if (!buffer.loadFromFile("correct.wav"))
					printf("Unable to load sound resource!");

				sound.setBuffer(buffer);

				sound.play();
				
			}



		}//use to set flags;
		
		void isClicked() {
			Vector2i localPosition = sf::Mouse::getPosition(window);
			Vector2f floatPosition(localPosition.x, localPosition.y);
			Texture texture;
			
			for (int i = 0; i < 20; i++) {
				
				if (sprites[i].getGlobalBounds().contains(floatPosition))
				{
					
					sprite.setPosition(coordinates[i].x, coordinates[i].y);
					texture.loadFromFile(cardsDeck[i].hidden);
					sprite.setTexture(texture);
					clickflag[i] = 1;
					window.draw(sprite);
					flips++;
					clicks++;
					// if 2 cards are selected
					if (flips == 2)
					{
						window.clear();
						draw();
						
						
						window.display();
						//pause for 3 sec
						sleep(milliseconds(3000));
						compare(i);
					}
					
					break;
				}




			}






		}//function to perform after sprite is clicked
	void congrats()
		{
			Text clicktxt;
			Sprite win;
			Texture winT;
			string text;
			text = "It takes you " + clicks;
			text += " times to finish the game! ";
			//window.clear();
			//win.setScale(Vector2f(50,50));
			win.setPosition(50,50);
			winT.loadFromFile("win.jpg");
			win.setTexture(winT);
			game.setPosition(50, 200);
			gameT.loadFromFile("newGame.png");
			game.setTexture(gameT);
			window.draw(game);
			quit.setPosition(200, 200);
			quitT.loadFromFile("qquit.png");
			quit.setTexture(quitT);
			window.draw(quit);
			clicktxt.setString(text);
			clicktxt.setFillColor(Color::White);
			clicktxt.setPosition(Vector2f(50, 300));
			window.draw(win);
			window.draw(clicktxt);
			window.display();
			

			
			
		}
		int doAgain() {
			
			Vector2i localPosition = sf::Mouse::getPosition(window);
			Vector2f floatPosition(localPosition.x, localPosition.y);
			
			
			if (game.getGlobalBounds().contains(floatPosition))
				return 1;
			else
				return 0;

			sleep(milliseconds(5000));
		}
		int quitG() {

			Vector2i localPosition = sf::Mouse::getPosition(window);
			Vector2f floatPosition(localPosition.x, localPosition.y);


			if (quit.getGlobalBounds().contains(floatPosition))
				return 1;
			else
				return 0;


			
		}

	};
bool operator==(const Cards& card1, const Cards& card2) {

		if (card1.hidden != card2.hidden)
			return 0;
		else
			return 1;
	}


	};





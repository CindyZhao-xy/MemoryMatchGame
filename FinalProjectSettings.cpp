/*
* File name : FinalProjectSettings.cpp
* Course : CST8219_S20_Cplusplus Programming
* Final Project Template
* Student : Xinyi Zhao
* Stud.ID : 040953633
* Professor : Eric Torunski, Mariusz Makos
* Due Date : August-07-2020
* Lab Section : 303
*/

#include "FinalProjectSettings.hpp"

/* Three SFML hpp files */
#include <SFML/Graphics.hpp>
#include "SFML/Window.hpp"
#include <SFML/Audio.hpp>

/* namespace */
using namespace std;
using namespace sf;
using namespace FinalProject;

/* Global variables */
sf::Event event;
sf::SoundBuffer buffer;
sf::Sound sound;

int main(int argc, char** argv) {
    int startGame = 0;
    do {
        startGame = 0;
        GameSettings game;
        game.temporayRandom();
        /* window open */
        while (game.window.isOpen()){
            game.window.clear();
            game.draw();
            /* display */
            game.window.display();
                if (game.matched == 10) {
                    game.window.clear();  
                    /* if file fail to load */
                        if (!buffer.loadFromFile("birdsWaveFile.wav"))
                            cerr << "Fail to load sound!";
                        sound.setBuffer(buffer);
                        sound.play();
                    while (1) {
                        game.win();
                        while (game.window.pollEvent(event)) {
                            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left){
                                startGame = game.doAgain();
                                if (game.quitG()) {
                                    game.window.close();
                                    startGame = 0;
                                    exit(0);
                                }
                            }
                        }
                        if (startGame == 1)
                            break;
                    }
                }
            while (game.window.pollEvent(event)){
                if (event.type == Event::Closed)
                    game.window.close();

                else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
                    game.isClicked();
            }
            if (startGame == 1)
                game.window.close();
        }      
    } while (startGame == 1);
    return 0;
} // End of main

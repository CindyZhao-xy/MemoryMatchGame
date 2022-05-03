
#include "FinalProjectSettings.hpp"
#include <SFML/Graphics.hpp>
#include "SFML/Window.hpp"
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;
using namespace FinalProject;

sf::Event event;
sf::SoundBuffer buffer;
sf::Sound sound;


int main(int argc, char** argv) {
    int startflag = 0;

    do {
        startflag = 0;
        Game game;
        game.staging();

        while (game.window.isOpen())
        {
            game.window.clear();
            game.draw();
            game.window.display();
            
                if (game.found == 10) {

                    game.window.clear();
                    
                        if (!buffer.loadFromFile("cheer.wav"))
                            printf("Unable to load sound resource!");

                        sound.setBuffer(buffer);

                        sound.play();
                    while (1) {
                        game.congrats();
                        while (game.window.pollEvent(event)) {
                            if (event.type == sf::Event::MouseButtonPressed &&
                                event.mouseButton.button == Mouse::Left){
                                startflag = game.doAgain();
                                if (game.quitG()) {
                                    game.window.close();
                                    startflag = 0;
                                    exit(0);
                                }
                            }
                        }
                        if (startflag == 1)
                            break;
                    }

                }

            while (game.window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    game.window.close();

                else if (event.type == sf::Event::MouseButtonPressed &&
                    event.mouseButton.button == Mouse::Left)
                    game.isClicked();

            }
            if (startflag == 1)
                game.window.close();
        }
        
    } while (startflag == 1);
    return 0;
}

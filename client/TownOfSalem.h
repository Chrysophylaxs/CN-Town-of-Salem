#ifndef TOS_TOWNOFSALEM_H
#define TOS_TOWNOFSALEM_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Chat.h"
#include "Caret.h"
#include "Client.h"
#include "Interface.h"
#include "Graveyard.h"
#include "Minibox.h"
#include "Rolecard.h"
#include "Rolelist.h"
#include "Townies.h"
#include "Will.h"

class TownOfSalem {
private:
    sf::RenderWindow window;
    sf::Texture dayTexture;
    sf::Texture nightTexture;
    sf::Sprite background;
    sf::Music morningMusic;
    sf::Music discussionMusic;
    sf::Music votingMusic;
    sf::Music nightMusic;
    sf::Music waitingMusic;
    Chat chat;
    Caret caret;
    Client client;
    Graveyard graveyard;
    Interface intrface;
    Minibox minibox;
    Rolecard rolecard;
    Rolelist rolelist;
    Role role;
    Townies townies;
    Will will;
    bool mini;
    bool usingWill;
    bool mute;
    bool mafia = false;
    bool dead = false;
    bool haunt = false;
    bool music = true;
    bool jailed = false;
    std::string buffer;
    std::string name;
    std::string phase;

    void handleInput(sf::Event &event);
    void handleKey(sf::Event &event);
    void handleScrollwheel(sf::Event &event);
    void handleMouseClick();
    void handleIncomingMessage();
    void toggleMinibox();
    void toggleMusic();
    void sendWill();
    void toggleWill();
    void draw();

public:
    TownOfSalem();
    ~TownOfSalem();
    void run();
};

#endif // TOS_TOWNOFSALEM_H
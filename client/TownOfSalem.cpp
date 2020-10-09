#include "TownOfSalem.h"

TownOfSalem::TownOfSalem() : window(sf::VideoMode(1920, 1016), "Town of Salem") {
    morningMusic.openFromFile("DayMusic.wav");
    discussionMusic.openFromFile("DiscussionMusic.wav");
    votingMusic.openFromFile("VotingMusic.wav");
    nightMusic.openFromFile("NightMusic.wav");
    waitingMusic.openFromFile("LobbyMusic.wav");
    morningMusic.setLoop(true);
    discussionMusic.setLoop(true);
    votingMusic.setLoop(true);
    nightMusic.setLoop(true);
    waitingMusic.setLoop(true);
    dayTexture.loadFromFile("background.jpg");
    nightTexture.loadFromFile("nightbackground.jpg");
    background.setTexture(dayTexture);
    mini = true;
    mute = false;
    usingWill = false;
    mafia = false;
    minibox.setText("Enter your name here:");
    client.setup();
    intrface.setPhase("Waiting...");
    role.setRole("Empty");
    rolecard.setRole(role);
    waitingMusic.play();
}

TownOfSalem::~TownOfSalem() {
    client.shutdown();
}

void TownOfSalem::sendWill() {
    std::string temp = "WILL ";
    for (int i = 0; i < 15; ++i) {
        temp += will.lines.at(i);
        temp += '\n';
    }
    client.sendMsg(temp);
}

void TownOfSalem::handleInput(sf::Event &event) {
    char letter = static_cast<char>(event.text.unicode);
    if (letter == 13 && (!buffer.empty() || usingWill)) {
        if (!name.empty()) {
            if (!usingWill) {
                if (buffer == "/fill") {
                    client.sendMsg("FILL\n");
                }
                else if (buffer == "/start") {
                    client.sendMsg("START\n");
                }
                else {
                    client.sendMsg("SEND " + buffer + '\n');
                }
            }
            else {
                caret.down();
                caret.on();
            }
        }
        else {
            int error = client.login(buffer);
            if (error == 1) {
                minibox.setText("In use, try again!");
            }
            else if (error == 0) {
                name = buffer;
                caret.chat();
                intrface.setName(name);
                toggleMinibox();
            }
            else {
                exit(1);
            }
        }
        buffer.clear();
        caret.reset();
    }
    else if (letter > 31 && letter < 127) {
        if (!mini) {
            if (!usingWill) {
                if (buffer.size() < 50) {
                    buffer.insert(caret.getPos(), 1, letter);
                    caret.right();
                }
            }
            else {
                if (will.lines.at(caret.getHeight()).size() < 50) {
                    will.lines.at(caret.getHeight()).insert(caret.getPos(), 1, letter);
                    caret.right();
                }
                else if (will.lines.at(caret.getHeight()).size() == 50){
                    caret.down();
                }
            }
        }
        else {
            if (buffer.size() < 16) {
                if (letter == ' ') {
                    buffer.insert(caret.getPos(), 1, '_');
                }
                else {
                    buffer.insert(caret.getPos(), 1, letter);
                }

                caret.right();
            }
        }
    }
    else if (letter == '\b') {
        if (!usingWill) {
            if (caret.getPos() != 0) {
                buffer.erase(buffer.begin() + caret.getPos() - 1);
                caret.left();
            }
        }
        else if (usingWill) {
            if (caret.getPos() != 0) {
                will.lines.at(caret.getHeight()).erase(will.lines.at(caret.getHeight()).begin() + caret.getPos() - 1);
                caret.left();
            }
        }
    }
    if (!mini && !usingWill) {
        chat.input(buffer);
    }
    else {
        minibox.input(buffer);
    }
}

void TownOfSalem::handleKey(sf::Event &event) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        if (caret.getPos() != 0) {
            caret.left();
        }
        caret.on();
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        if (!usingWill) {
            if (caret.getPos() != buffer.size()) {
                caret.right();
            }
            caret.on();
        }
        else {
            if(caret.getPos() != will.lines.at(caret.getHeight()).size()){
                caret.right();
            }
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        if (caret.getHeight() != 0) {
            caret.up();
        }
        caret.on();
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
        if (caret.getHeight() != 14){
            caret.down();

        }
        caret.on();
    }
    else if (event.key.code == sf::Keyboard::Escape) {
        window.close();
    }
}

void TownOfSalem::handleScrollwheel(sf::Event &event){
    if (event.mouseWheel.delta > 0) {
        chat.up();
    }
    else {
        chat.down();
    }
}

void TownOfSalem::handleMouseClick() {
    if (townies.showBoxes) {
        for (int i = 0; i < townies.clickboxes.size(); i++){
            if (townies.clickboxes.at(i).getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)){
                if (townies.clicked.at(i) == true){
                    townies.clicked.at(i) = false;
                    townies.clickboxes.at(i).setFillColor(sf::Color(sf::Color(50, 50, 50, 210)));
                    client.sendMsg("CANCEL\n");
                }
                else if (townies.checkSelected()) {
                    int j = townies.clearSelected();
                    townies.clickboxes.at(i).setFillColor(sf::Color(sf::Color(242, 224, 124, 180)));
                    townies.clicked.at(i) = true;
                    if (phase == "VOTING") {
                        client.sendMsg("VOTE " + std::to_string(i) + "\n");
                    }
                    else if (phase == "NIGHT") {
                        client.sendMsg("NIGHTABILITY " + std::to_string(i) + "\n");
                    }
                }
                else {
                    townies.clickboxes.at(i).setFillColor(sf::Color(sf::Color(242, 224, 124, 180)));
                    townies.clicked.at(i) = true;
                    if (phase == "VOTING") {
                        client.sendMsg("VOTE " + std::to_string(i) + "\n");
                    }
                    else if (phase == "NIGHT") {
                        client.sendMsg("NIGHTABILITY " + std::to_string(i) + "\n");
                    }
                }
            }
        }
    }
    if (intrface.jail) {
        for (int i = 0; i < intrface.jailboxes.size(); i++){
            if (intrface.jailboxes.at(i).getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)){
                if (intrface.clicked.at(i) == true){
                    intrface.clicked.at(i) = false;
                    intrface.jailboxes.at(i).setFillColor(sf::Color(sf::Color(50, 50, 50, 210)));
                    client.sendMsg("CANCELJAIL\n");
                }
                else if (intrface.checkSelected()) {
                    int j = intrface.clearSelected();
                    intrface.jailboxes.at(i).setFillColor(sf::Color(sf::Color(242, 224, 124, 180)));
                    intrface.clicked.at(i) = true;
                    client.sendMsg("JAIL " + std::to_string(i) + "\n");
                }
                else {
                    intrface.jailboxes.at(i).setFillColor(sf::Color(sf::Color(242, 224, 124, 180)));
                    intrface.clicked.at(i) = true;
                    client.sendMsg("JAIL " + std::to_string(i) + "\n");
                }
            }
        }
    }
    if (intrface.willBox.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)){
        toggleWill();
    }
    if (intrface.musicBox.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)){
        toggleMusic();
    }
    if (intrface.leaveBox.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)){
        window.close();
    }
    if (!dead) {
        if (intrface.dayAbilityBox.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)){
            if (role.roleName == "Mayor" && phase != "NIGHT") {
                client.sendMsg("REVEAL\n");
            }
            if (role.roleName == "Jailor" && phase != "NIGHT") {
                intrface.jail = !intrface.jail;
            }
        }
        if (intrface.showJudge){
            if (intrface.innoBox.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
                client.sendMsg("INNO\n");
                intrface.judgingOff();
            }
            if (intrface.guiltyBox.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)){
                client.sendMsg("GUILTY\n");
                intrface.judgingOff();
            }
        }
    }
}

void TownOfSalem::handleIncomingMessage() {
    std::string msg = client.receive();
    if (msg.substr(0, 5) == "ALIVE") {
        msg = msg.erase(0, 6);
        std::vector<std::string> alive;
        std::string temp;
        for (int i = 0; i < msg.size(); i++) {
            if (msg.at(i) == ' ') {
                alive.push_back(temp);
                temp.clear();
            }
            else {
                temp.push_back(msg.at(i));
            }
        }
        alive.push_back(temp);
        temp.clear();
        townies.setup(alive);
        intrface.setTownies(alive);
    }
    else if (msg.substr(0, 7) == "NEWROLE") {
        std::string temp;
        int index = 8;
        while (index < msg.size() && !isspace(msg.at(index))) {
            temp += msg.at(index);
            index++;
        }
        role.setRole(temp);
        rolecard.setRole(role);
        chat.push("You have become a " + temp);
    }
    else if (msg.substr(0, 4) == "ROLE") {
        std::string temp;
        int index = 5;
        while (index < msg.size() && !isspace(msg.at(index))) {
            temp += msg.at(index);
            index++;
        }
        minibox.setText("Your role:");
        minibox.input(temp);
        toggleMinibox();
        role.setRole(temp);
        rolecard.setRole(role);
        mute = true;
        caret.off();
        if (temp == "Godfather" || temp == "Mafioso" || temp == "Blackmailer" || temp == "Janitor" || temp == "Consigliere" || temp == "Consort" || temp == "Framer") {
            mafia = true;
        }
    }
    else if (msg == "START\n") {
        toggleMinibox();
        mute = false;
        caret.on();
    }
    else if (msg == "DAY\n") {
        townies.clickboxesOff();
        intrface.setPhase("Day");
        phase = "DISCUSSION";
        waitingMusic.stop();
    }
    else if (msg == "NIGHT\n") {
        intrface.judgingOff();
        background.setTexture(nightTexture);
        if (!dead || haunt) {
            int tmp = townies.clearSelected();
            townies.clickboxesOn();
            haunt = false;
        }
        intrface.jail = false;
        intrface.setPhase("Night");
        phase = "NIGHT";
        votingMusic.stop();
        nightMusic.play();
    }
    else if (msg == "MORNING\n") {
        background.setTexture(dayTexture);
        townies.clickboxesOff();
        intrface.setPhase("Morning");
        phase = "MORNING";
        jailed = false;
        nightMusic.stop();
        morningMusic.play();
    }
    else if (msg == "DISCUSSION\n") {
        intrface.setPhase("Discussion");
        phase = "DISCUSSION";
        morningMusic.stop();
        discussionMusic.play();
    }
    else if (msg == "VOTING\n") {
        if (!dead) {
            int tmp = townies.clearSelected();
            townies.clickboxesOn();
        }
        intrface.setPhase("Voting");
        phase = "VOTING";
        discussionMusic.stop();
        votingMusic.play();
    }
    else if (msg == "DEFENSE\n") {
        if (!dead) {
            townies.clickboxesOff();
        }
        intrface.setPhase("Defense");
        phase = "DEFENSE";
    }
    else if (msg == "JUDGING\n") {
        if (!dead) {
            townies.clickboxesOff();
            intrface.judgingOn();
        }
        intrface.setPhase("Judging");
        phase = "JUDGING";
    }
    else if (msg.substr(0, 4) == "WILL") {
        msg = msg.erase(0, 5);
        std::string temp;
        for (int i = 0; i < msg.size(); ++i) {
            if (msg.at(i) == '\n') {
                chat.push(temp);
                Sleep(50);
                temp = "";
            }
            else {
                temp += msg.at(i);
            }
        }
    }
    else if (msg == "MUTE\n") {
        mute = true;
        caret.off();
    }
    else if (msg == "UNMUTE\n") {
        mute = false;
        caret.on();
    }
    else if (msg.substr(0, 6) == "TARGET") {
        msg = msg.erase(0, 7);
        role.attributes1 = "Attributes: Your target is " + msg;
        rolecard.setRole(role);
    }
    else if (msg.substr(0, 5) == "MAFIA"){
        std::vector<std::string> inputMafia;
        std::string tempMafia;
        int index = 6;
        while (index < msg.size()){
            if (msg.at(index) != ' ') {
                tempMafia += msg.at(index);
                index++;
            }
            else {
                inputMafia.push_back(tempMafia);
                tempMafia.clear();
                index++;
            }
        }
        townies.setMafia(inputMafia, mafia);
    }
    else if (msg.substr(0, 9) == "RESURRECT") {
        std::string temp;
        int index = 10;
        while (index < msg.size() && !isspace(msg.at(index))) {
            temp += msg.at(index);
            index++;
        }
        if (temp == name) {
            chat.push("You have been resurrected by a retributionist!");
        }
        else {
            chat.push(temp + " has been resurrected by a retributionist!");
        }
        graveyard.remove(temp);
        dead = false;
    }
    else if (msg == "HAUNT\n") {
        haunt = true;
    }
    else if (msg == "JAILED\n") {
        jailed = true;
    }
    else if (msg == "REQUESTWILL\n") {
        dead = true;
        mute = true;
        sendWill();
    }
    else if (msg.substr(0, 5) == "DEATH") {
        std::string player;
        std::string role;
        int i = 6;
        while(msg.at(i) != ' ') {
            player += msg.at(i);
            i++;
        }
        while(i < msg.size() - 1) {
            i++;
            role += msg.at(i);
        }
        graveyard.push(player, role);
    }
    else if (msg == "WIN\n") {
        chat.push("You win! Thank you for playing");
        chat.push("You should now exit the game.");
        mute = true;
    }
    else if (msg == "LOSS\n") {
        chat.push("You've lost, better luck next time! Thank you for playing");
        chat.push("You should now exit the game.");
        mute = true;
    }
    else {
        chat.push(msg);
    }
}

void TownOfSalem::draw() {
    window.clear();
    window.draw(background);
    if (mini) {
        minibox.draw(window);
    }
    else {
        chat.draw(window);
        graveyard.draw(window);
        intrface.draw(window);
        rolecard.draw(window);
        rolelist.draw(window);
        townies.draw(window);
        if (usingWill){
            will.draw(window);
        }
    }
    caret.draw(window);
    window.display();
}

void TownOfSalem::run() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (!mute || usingWill || ((dead || jailed || mafia || role.roleName == "Medium" || role.roleName == "Jailor") && phase == "NIGHT")) {
                if (event.type == sf::Event::TextEntered) {
                    handleInput(event);
                    caret.on();
                }
                else if (event.type == sf::Event::KeyPressed) {
                    handleKey(event);
                }
            }
            if (client.poll() == 1) {
                handleIncomingMessage();
            }
            else if (event.type == sf::Event::MouseWheelMoved) {
                handleScrollwheel(event);
            }
            else if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                handleMouseClick();
            }
        }
        if (client.poll() == 1) {
            handleIncomingMessage();
        }
        if (!mute || usingWill || ((dead || mafia || role.roleName == "Medium") && phase == "NIGHT")) {
            caret.tick();
        }
        draw();
    }
}

void TownOfSalem::toggleMinibox() {
    mini = !mini;
}

void TownOfSalem::toggleWill() {
    caret.reset();
    if (!usingWill){
        caret.will();
    }
    else if (usingWill){
        caret.chat();
    }
    usingWill = !usingWill;
}

void TownOfSalem::toggleMusic() {
    if (music) {
        morningMusic.setVolume(0);
        discussionMusic.setVolume(0);
        votingMusic.setVolume(0);
        nightMusic.setVolume(0);
        waitingMusic.setVolume(0);
        music = false;
    }
    else {
        morningMusic.setVolume(100);
        discussionMusic.setVolume(100);
        votingMusic.setVolume(100);
        nightMusic.setVolume(100);
        waitingMusic.setVolume(100);
        music = true;
    }
}
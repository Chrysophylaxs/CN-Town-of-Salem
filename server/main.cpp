#include <winsock2.h>
#include <thread>
#include <iostream>
#include <ctime>
#include <vector>

struct player {
    bool winCondition = false;
    int voting = 1;
    bool rb = false;
    bool bm = false;
    bool ability = true;
    int attack = 0;
    int defense = 0;
    bool framed = false;
    bool cleaned = false;
    bool doused = false;
    bool alive = true;
    bool jailed = false;
    std::string killer;
    std::string defender;
};

bool stop = false;
int counter = 1;
int exeTarget = -2;
int jailee = -2;
sockaddr_in server{}, client{}, recipient{};
int addrLength = sizeof(sockaddr_in);

// Client info
const int maxClients = 15;
std::vector<std::string> clientName(maxClients);
std::vector<SOCKET> clientSocket(maxClients);

std::vector<std::string> roles(maxClients);
std::vector<int> nightAbilities(maxClients);
std::vector<int> votes = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
std::vector<int> judging(maxClients, 0);
std::vector<int> totalVotes(maxClients, 0);
std::vector<player> players(maxClients);
std::string phase;
int majority;

std::vector<int> deadPlayers;
std::string will;

void sendToEveryone(std::string msg) {
    const char *buf = msg.c_str();
    for (int i = 0; i < maxClients; i++) {
        if (clientSocket.at(i) == 0) {
            continue;
        }
        int bytesSent = send(clientSocket.at(i), buf, (int)msg.size(), 0);
        getpeername(clientSocket.at(i), (sockaddr *)&recipient, &addrLength);
        std::cout << inet_ntoa(recipient.sin_addr) << ":" << ntohs(recipient.sin_port);
        if (bytesSent == SOCKET_ERROR) {
            std::cout << " <- Error sending message, code:" << WSAGetLastError() << std::endl;
        }
        else {
            std::cout << " <- " << msg;
        }
    }
    Sleep(500);
}

void sendToDead(std::string msg) {
    const char *buf = msg.c_str();
    for (int i = 0; i < maxClients; i++) {
        if (clientSocket.at(i) == 0 || (players.at(i).alive && roles.at(i) != "Medium")) {
            continue;
        }
        int bytesSent = send(clientSocket.at(i), buf, (int)msg.size(), 0);
        getpeername(clientSocket.at(i), (sockaddr *)&recipient, &addrLength);
        std::cout << inet_ntoa(recipient.sin_addr) << ":" << ntohs(recipient.sin_port);
        if (bytesSent == SOCKET_ERROR) {
            std::cout << " <- Error sending message, code:" << WSAGetLastError() << std::endl;
        }
        else {
            std::cout << " <- " << msg;
        }
    }
    Sleep(500);
}

void sendToMafia(std::string msg) {
    const char *buf = msg.c_str();
    for (int i = 0; i < maxClients; i++) {
        if (clientSocket.at(i) != 0) {
            if (roles.at(i) == "Godfather" || roles.at(i) == "Mafioso" || roles.at(i) == "Blackmailer" || roles.at(i) == "Janitor" || roles.at(i) == "Consigliere" || roles.at(i) == "Consort" || roles.at(i) == "Framer") {
                int bytesSent = send(clientSocket.at(i), buf, (int)msg.size(), 0);
                getpeername(clientSocket.at(i), (sockaddr *)&recipient, &addrLength);
                std::cout << inet_ntoa(recipient.sin_addr) << ":" << ntohs(recipient.sin_port);
                if (bytesSent == SOCKET_ERROR) {
                    std::cout << " <- Error sending message, code:" << WSAGetLastError() << std::endl;
                }
                else {
                    std::cout << " <- " << msg;
                }
            }
        }
    }
    Sleep(500);
}

void sendToIndex(std::string msg, int index) {
	const char *buf = msg.c_str();
	if (index >= 0) {
        if (clientSocket.at(index) != 0) {
            int bytesSent = send(clientSocket.at(index), buf, (int)msg.size(), 0);
            getpeername(clientSocket.at(index), (sockaddr *)&recipient, &addrLength);
            std::cout << inet_ntoa(recipient.sin_addr) << ":" << ntohs(recipient.sin_port);
            if (bytesSent == SOCKET_ERROR) {
                std::cout << " <- Error sending message, code:" << WSAGetLastError() << std::endl;
            }
            else {
                std::cout << " <- " << msg;
            }
        }
	}
    Sleep(500);
}

void sendToJail(std::string msg) {
    const char *buf = msg.c_str();
    for (int i = 0; i < maxClients; i++) {
        if (clientSocket.at(i) != 0) {
            if (roles.at(i) == "Jailor") {
                int bytesSent = send(clientSocket.at(i), buf, (int)msg.size(), 0);
                getpeername(clientSocket.at(i), (sockaddr *)&recipient, &addrLength);
                std::cout << inet_ntoa(recipient.sin_addr) << ":" << ntohs(recipient.sin_port);
                if (bytesSent == SOCKET_ERROR) {
                    std::cout << " <- Error sending message, code:" << WSAGetLastError() << std::endl;
                }
                else {
                    std::cout << " <- " << msg;
                }
            }
        }
    }
    sendToIndex(msg, jailee);
    Sleep(500);
}

int getRandomTownie() {
    while (true) {
        int i = rand() % 15;
        if (roles.at(i) == "Investigator" || roles.at(i) == "Doctor" || roles.at(i) == "Bodyguard" || roles.at(i) == "Spy" || roles.at(i) == "Sheriff" || roles.at(i) == "Retributionist" || roles.at(i) == "Medium" || roles.at(i) == "Lookout" || roles.at(i) == "Escort" || roles.at(i) == "Veteran" || roles.at(i) == "Vigilante") {
            return i;
        }
    }
}

void showDeathsAndWills() {
    for (int i = 0; i < deadPlayers.size(); ++i) {
        will.clear();
        if (clientSocket.at(i) != 0) {
            sendToIndex("REQUESTWILL\n", deadPlayers.at(i));
        }
        Sleep(5000);
        sendToEveryone(clientName.at(deadPlayers.at(i)) + " has died.");
        Sleep(3000);
        sendToEveryone("They were killed by a " + players.at(deadPlayers.at(i)).killer);
        Sleep(2000);
        if (players.at(deadPlayers.at(i)).cleaned) {
            sendToEveryone("We could not determine their role.");
            sendToMafia("As a member of the mafia, you secretly know that their role was " + roles.at(deadPlayers.at(i)));
            sendToEveryone("DEATH " + clientName.at(deadPlayers.at(i)) + " Cleaned");
        }
        else {
            sendToEveryone("Their role was " + roles.at(deadPlayers.at(i)));
            sendToEveryone("DEATH " + clientName.at(deadPlayers.at(i)) + " " + roles.at(deadPlayers.at(i)));
        }
        Sleep(2000);

        if (roles.at(deadPlayers.at(i)) == "Godfather" || roles.at(deadPlayers.at(i)) == "Mafioso" || roles.at(deadPlayers.at(i)) == "Janitor" || roles.at(deadPlayers.at(i)) == "Consigliere" || roles.at(deadPlayers.at(i)) == "Consort" || roles.at(deadPlayers.at(i)) == "Blackmailer" || roles.at(deadPlayers.at(i)) == "Framer") {
            int rm = -1;
            if (roles.at(deadPlayers.at(i)) == "Godfather") {
                bool maf = false;
                for (int j = 0; j < maxClients; ++j) {
                    if ((roles.at(j) == "Janitor" || roles.at(j) == "Consigliere" || roles.at(j) == "Consort" || roles.at(j) == "Blackmailer" || roles.at(j) == "Framer") && players.at(j).alive) {
                        rm = j;
                    }
                    else if (roles.at(j) == "Mafioso" && players.at(j).alive) {
                        roles.at(j) = "Godfather";
                        sendToIndex("NEWROLE Godfather", j);
                        maf = true;
                    }
                }
                if (!maf && rm != -1) {
                    roles.at(rm) = "Mafioso";
                    sendToIndex("NEWROLE Mafioso", rm);
                }
            }
            if (roles.at(deadPlayers.at(i)) == "Mafioso") {
                bool gf = false;
                for (int j = 0; j < maxClients; ++j) {
                    if (roles.at(j) == "Godfather"  && players.at(j).alive) {
                        gf = true;
                    }
                    else if ((roles.at(j) == "Janitor" || roles.at(j) == "Consigliere" || roles.at(j) == "Consort" || roles.at(j) == "Blackmailer" || roles.at(j) == "Framer") && players.at(j).alive) {
                        rm = j;
                    }
                }
                if (!gf & rm != -1) {
                    roles.at(rm) = "Mafioso";
                    sendToIndex("NEWROLE Mafioso", rm);
                }
            }
            std::string temp = "MAFIA ";
            for (int j = 0; j < maxClients; j++) {
                if (roles.at(j) == "Godfather" || roles.at(j) == "Mafioso" || roles.at(j) == "Blackmailer" || roles.at(j) == "Janitor" || roles.at(j) == "Consigliere" || roles.at(j) == "Consort" || roles.at(j) == "Framer") {
                    if (players.at(j).alive) {
                        temp += clientName.at(j);
                        temp += "(";
                        temp += roles.at(j);
                        temp += ") ";
                    }
                }
            }
            sendToMafia(temp);
        }
        else if (deadPlayers.at(i) == exeTarget) {
            int j;
            for (j = 0; j < maxClients; ++j) {
                if (roles.at(j) == "Executioner") {
                    break;
                }
            }
            sendToIndex("You have target has died, you have become a jester!", j);
            sendToIndex("NEWROLE Jester", j);
            roles.at(j) = "Jester";
        }

        if (!will.empty() && !players.at(deadPlayers.at(i)).cleaned) {
            sendToEveryone("We found a last will next to their body:");
            Sleep(1000);
            sendToEveryone(will);
        }
        else {
            sendToEveryone("We could not find a last will.");
        }
    }
}

void nightLogic() {
    for (int i = 0; i < maxClients; ++i) {
        players.at(i).rb = false;
        players.at(i).bm = false;
        if (roles.at(i) == "Godfather" || roles.at(i) == "Arsonist" || roles.at(i) == "Serialkiller" || roles.at(i) == "Werewolf" || roles.at(i) == "Executioner") {
            players.at(i).defense = 1;
        }
        else {
            players.at(i).defense = 0;
        }
        players.at(i).attack = 0;
        players.at(i).framed = false;
        players.at(i).jailed = false;
        players.at(i).cleaned = false;
        players.at(i).defender = "";
    }
    if (jailee >= 0) {
        players.at(jailee).jailed = true;
        players.at(jailee).defense = 2;
        players.at(jailee).rb = true;
    }
    for (int i = 0; i < maxClients; ++i) {
        if (!players.at(i).alive && roles.at(i) != "Jester") {
            continue;
        }
        if (players.at(i).rb) {
            nightAbilities.at(i) = -1;
        }

        if (roles.at(i) == "Consort" && !players.at(i).jailed) {
            if (nightAbilities.at(i) != -1) {
                if (roles.at(nightAbilities.at(i)) == "Serialkiller") {
                    players.at(i).attack = 1;
                    players.at(i).killer = "Serialkiller";
                }
                else {
                    players.at(nightAbilities.at(i)).rb = true;
                }
            }
            else if (nightAbilities.at(i) == jailee) {
                sendToIndex("Someone tried to roleblock you, but you were in Jail last night!", jailee);
            }
        }

        else if (roles.at(i) == "Escort" && !players.at(i).jailed) {
            if (nightAbilities.at(i) != -1) {
                if (roles.at(nightAbilities.at(i)) == "Serialkiller") {
                    players.at(i).attack = 1;
                    players.at(i).killer = "Serialkiller";
                }
                else {
                    players.at(nightAbilities.at(i)).rb = true;
                }
            }
            else if (nightAbilities.at(i) == jailee) {
                sendToIndex("Someone tried to roleblock you, but you were in Jail last night!", jailee);
            }
        }

        else if (roles.at(i) == "Arsonist" && !players.at(i).rb) {
            if (nightAbilities.at(i) != -1) {
                if (i == nightAbilities.at(i)) {
                    for (int j = 0; j < maxClients; j++) {
                        if (players.at(j).doused) {
                            players.at(j).attack = 3;
                            players.at(j).killer = "Arsonist";
                        }
                    }
                }
                else {
                    players.at(nightAbilities.at(i)).doused = true;
                }
            }
        }

        else if (roles.at(i) == "Blackmailer" && !players.at(i).rb) {
            if (nightAbilities.at(i) != -1) {
                players.at(nightAbilities.at(i)).bm = true;
            }
        }

        else if (roles.at(i) == "Bodyguard" && !players.at(i).rb) {
            if (nightAbilities.at(i) != -1) {
                players.at(nightAbilities.at(i)).defense = 2;
                players.at(nightAbilities.at(i)).defender = "Bodyguard";
            }
        }

        else if (roles.at(i) == "Doctor" && !players.at(i).rb) {
            if (nightAbilities.at(i) != -1) {
                players.at(nightAbilities.at(i)).defense = 2;
                players.at(nightAbilities.at(i)).defender = "Doctor";
            }
        }

        else if (roles.at(i) == "Framer" && !players.at(i).rb) {
            if (nightAbilities.at(i) != -1) {
                players.at(nightAbilities.at(i)).framed = true;
            }
        }
        else if (roles.at(i) == "Godfather" && !players.at(i).rb) {
            if (nightAbilities.at(i) != -1) {
                players.at(nightAbilities.at(i)).attack = 1;
                players.at(nightAbilities.at(i)).killer = "Godfather";
            }
        }
        else if (roles.at(i) == "Jailor" && !players.at(i).rb) {
            if (nightAbilities.at(i) != -1) {
                players.at(nightAbilities.at(i)).attack = 3;
                players.at(nightAbilities.at(i)).killer = "Jailor";
            }
        }
        else if (roles.at(i) == "Janitor" && !players.at(i).rb) {
            if (nightAbilities.at(i) != -1) {
                players.at(nightAbilities.at(i)).cleaned = true;
            }
        }
        else if (roles.at(i) == "Jester" && !players.at(i).rb) {
            if (nightAbilities.at(i) != -1) {
                if (players.at(nightAbilities.at(i)).winCondition) {
                    players.at(nightAbilities.at(i)).attack = 3;
                    players.at(nightAbilities.at(i)).killer = "Jester";
                }
            }
        }
        else if (roles.at(i) == "Mafioso" && !players.at(i).rb) {
            if (nightAbilities.at(i) != -1) {
                players.at(nightAbilities.at(i)).attack = 1;
                players.at(nightAbilities.at(i)).killer = "Mafioso";
            }
        }
        else if (roles.at(i) == "Retributionist" && !players.at(i).rb) {
            if (nightAbilities.at(i) != -1 && !players.at(nightAbilities.at(i)).alive && players.at(i).ability) {
                players.at(nightAbilities.at(i)).alive = true;
                sendToEveryone("RESURRECT " + clientName.at(nightAbilities.at(i)));
                std::string temp = "MAFIA ";
                for (int i = 0; i < maxClients; i++) {
                    if (roles.at(i) == "Godfather" || roles.at(i) == "Mafioso" || roles.at(i) == "Blackmailer" || roles.at(i) == "Janitor" || roles.at(i) == "Consigliere" || roles.at(i) == "Consort" || roles.at(i) == "Framer") {
                        temp += clientName.at(i);
                        temp += "(";
                        temp += roles.at(i);
                        temp += ") ";
                    }
                }
                sendToMafia(temp);
                players.at(i).ability = false;
            }
        }
        else if (roles.at(i) == "Serialkiller" && !players.at(i).rb) {
            if (nightAbilities.at(i) != -1) {
                players.at(nightAbilities.at(i)).attack = 1;
                players.at(nightAbilities.at(i)).killer = "Serialkiller";
            }
        }
        else if (roles.at(i) == "Vigilante" && !players.at(i).rb) {
            if (nightAbilities.at(i) != -1) {
                players.at(nightAbilities.at(i)).attack = 1;
                players.at(nightAbilities.at(i)).killer = "Vigilante";
            }
        }
        else if (roles.at(i) == "Werewolf" && !players.at(i).rb) {
            if (nightAbilities.at(i) != -1 && counter % 2 == 0) {
                players.at(nightAbilities.at(i)).attack = 2;
                players.at(nightAbilities.at(i)).killer = "Werewolf";
                if (!players.at(nightAbilities.at(i)).jailed) {
                    sendToIndex("You attacked someone.", i);
                }
                for (int j = 0; j < maxClients; j++) {
                    if (nightAbilities.at(j) == nightAbilities.at(i) && j != i) {
                        players.at(j).attack = 2;
                        players.at(j).killer = "Werewolf";
                        sendToIndex("You attacked someone.", i);
                    }
                }
            }
        }
    }
    for (int i = 0; i < maxClients; ++i) {
        if (!players.at(i).alive) {
            continue;
        }
        if (nightAbilities.at(i) != -1) {
            if (players.at(nightAbilities.at(i)).jailed && roles.at(i) != "Jailor") {
                sendToIndex("You could not perform your ability, because your target was in Jail last night!", i);
                continue;
            }
        }

        if (nightAbilities.at(i) != -1) {
            if (roles.at(i) == "Bodyguard" && !players.at(i).rb) {
                if (players.at(nightAbilities.at(i)).attack > 0 && players.at(nightAbilities.at(i)).attack < 3) {
                    for (int j = 0; j < maxClients; ++j) {
                        if (roles.at(j) == players.at(nightAbilities.at(i)).killer) {
                            players.at(j).attack = 2;
                            players.at(j).killer = "Bodyguard";
                            players.at(i).attack = 1;
                            players.at(i).killer = players.at(nightAbilities.at(i)).killer;
                            break;
                        }
                    }
                }
            }
        }


        if (roles.at(i) == "Veteran" && !players.at(i).jailed) {
            if (i == nightAbilities.at(i)) {
                players.at(i).defense = 1;
                for (int j = 0; j < maxClients; j++) {
                    if (j == i) {
                        continue;
                    }
                    if (nightAbilities.at(j) == i && j != i) {
                        players.at(j).attack = 2;
                        players.at(j).killer = "Veteran";
                        sendToIndex("You shot someone that visited you last night!", i);
                    }
                }
            }
        }

        if (nightAbilities.at(i) != -1) {
            if (roles.at(i) == "Sheriff" && !players.at(i).rb) {
                if (players.at(nightAbilities.at(i)).framed) {
                    sendToIndex("Your target is a member of the mafia!", i);
                }
                else if (roles.at(nightAbilities.at(i)) == "Serialkiller") {
                    sendToIndex("Your target is a Serial Killer!", i);
                }
                else if (roles.at(nightAbilities.at(i)) == "Werewolf" && counter % 2 == 0) {
                    sendToIndex("Your target is a Werewolf!", i);
                }
                else if (roles.at(nightAbilities.at(i)) == "Mafioso") {
                    sendToIndex("Your target is a member of the mafia!", i);
                }
                else if (roles.at(nightAbilities.at(i)) == "Blackmailer") {
                    sendToIndex("Your target is a member of the mafia!", i);
                }
                else if (roles.at(nightAbilities.at(i)) == "Consigliere") {
                    sendToIndex("Your target is a member of the mafia!", i);
                }
                else if (roles.at(nightAbilities.at(i)) == "Consort") {
                    sendToIndex("Your target is a member of the mafia!", i);
                }
                else if (roles.at(nightAbilities.at(i)) == "Framer") {
                    sendToIndex("Your target is a member of the mafia!", i);
                }
                else if (roles.at(nightAbilities.at(i)) == "Janitor") {
                    sendToIndex("Your target is a member of the mafia!", i);
                }
                else {
                    sendToIndex("Your target is not suspicious!", i);
                }
            }

            if (roles.at(i) == "Investigator" && !players.at(i).rb) {
                if (players.at(nightAbilities.at(i)).framed || roles.at(nightAbilities.at(i)) == "Framer" || roles.at(nightAbilities.at(i)) == "Jester") {
                    sendToIndex("Your target could be a Framer or a Jester!", i);
                }
                else if (players.at(nightAbilities.at(i)).doused || roles.at(nightAbilities.at(i)) == "Bodyguard" || roles.at(nightAbilities.at(i)) == "Godfather" || roles.at(nightAbilities.at(i)) == "Arsonist") {
                    sendToIndex("Your target could be a Bodyguard, Godfather or Arsonist!", i);
                }
                else if (roles.at(nightAbilities.at(i)) == "Doctor" || roles.at(nightAbilities.at(i)) == "Serialkiller" || roles.at(nightAbilities.at(i)) == "Lookout") {
                    sendToIndex("Your target could be a Doctor, Serial Killer or Lookout!", i);
                }
                else if (roles.at(nightAbilities.at(i)) == "Sheriff" || roles.at(nightAbilities.at(i)) == "Executioner" || roles.at(nightAbilities.at(i)) == "Werewolf") {
                    sendToIndex("Your target could be a Sheriff, Executioner or Werewolf!", i);
                }
                else if (roles.at(nightAbilities.at(i)) == "Vigilante" || roles.at(nightAbilities.at(i)) == "Veteran" || roles.at(nightAbilities.at(i)) == "Mafioso") {
                    sendToIndex("Your target could be a Vigilante, Veteran or Mafioso!", i);
                }
                else if (roles.at(nightAbilities.at(i)) == "Spy" || roles.at(nightAbilities.at(i)) == "Jailor" || roles.at(nightAbilities.at(i)) == "Blackmailer") {
                    sendToIndex("Your target could be a Spy, Blackmailer or Jailor!", i);
                }
                else if (roles.at(nightAbilities.at(i)) == "Investigator" || roles.at(nightAbilities.at(i)) == "Mayor" || roles.at(nightAbilities.at(i)) == "Consigliere") {
                    sendToIndex("Your target could be an Investigator, Consigliere or Mayor!", i);
                }
                else if (roles.at(nightAbilities.at(i)) == "Escort" || roles.at(nightAbilities.at(i)) == "Consort") {
                    sendToIndex("Your target could be an Escort or a Consort!", i);
                }
                else if (roles.at(nightAbilities.at(i)) == "Retributionist" || roles.at(nightAbilities.at(i)) == "Medium" || roles.at(nightAbilities.at(i)) == "Janitor") {
                    sendToIndex("Your target could be a Medium, Janitor or Retributionist!", i);
                }
            }

            if (roles.at(i) == "Consigliere" && !players.at(i).rb) {
                if (players.at(nightAbilities.at(i)).doused) {
                    sendToIndex("Your target is an Arsonist!", i);
                }
                else {
                    sendToIndex("Your target is a " + roles.at(nightAbilities.at(i)), i);
                }
            }

            if (roles.at(i) == "Spy" && !players.at(i).rb) {
                if (players.at(nightAbilities.at(i)).attack > 0) {
                    sendToIndex("Your target was attacked by a " + players.at(nightAbilities.at(i)).killer, i);
                }
                else if (players.at(nightAbilities.at(i)).rb) {
                    sendToIndex("Someone occupied your target's night. They were role blocked!", i);
                }
                else if (players.at(nightAbilities.at(i)).rb) {
                    sendToIndex("Someone threatened to reveal your target's secrets. They were blackmailed!", i);
                }
                for (int j = 0; j < maxClients; ++j) {
                    if (roles.at(j) == "Godfather" || roles.at(j) == "Mafioso" || roles.at(j) == "Janitor" || roles.at(j) == "Consigliere" || roles.at(j) == "Consort" || roles.at(j) == "Blackmailer" || roles.at(j) == "Framer") {
                        if (nightAbilities.at(j) != -1) {
                            sendToIndex("A member of the mafia visited: " + clientName.at(nightAbilities.at(j)), i);
                            Sleep(10);
                        }
                    }
                }
            }

            if (roles.at(i) == "Lookout" && !players.at(i).rb) {
                for (int j = 0; j < maxClients; ++j) {
                    if (nightAbilities.at(j) == nightAbilities.at(i) && nightAbilities.at(j) != -1) {
                        sendToIndex("Your target was visited by: " + clientName.at(nightAbilities.at(j)), i);
                    }
                }
            }
        }
    }
    for (int i = 0; i < maxClients; ++i) {
        if (!players.at(i).alive) {
            continue;
        }

        if (players.at(i).rb && !players.at(i).jailed) {
            if (roles.at(i) == "Escort" || roles.at(i) == "Consort" || roles.at(i) == "Veteran") {
                sendToIndex("Someone tried to roleblock you, but you are immune!", i);
            }
            else {
                sendToIndex("Someone occupied your night, you were roleblocked!", i);
            }
        }

        if (players.at(i).bm && players.at(i).jailed) {
            sendToIndex("Someone tried to blackmail you, but you were in Jail last night!", i);
            players.at(i).bm = false;
        }
        else if (players.at(i).bm) {
            sendToIndex("Someone threatened to reveal your secrets, you were blackmailed!", i);
        }

        if (players.at(i).attack > 0 && players.at(i).jailed && players.at(i).killer != "Jailor") {
            sendToIndex("Someone tried to attack you, but you were in Jail last night!", i);
        }
        else if (players.at(i).attack > 0) {
            if (players.at(i).attack > players.at(i).defense) {
                players.at(i).alive = false;
                sendToIndex("You were attacked by a " + players.at(i).killer + ", you have died!", i);
                deadPlayers.push_back(i);
            }
            else if (players.at(i).defender.empty()) {
                sendToIndex("You were attacked, but your defense was too strong!", i);
                for (int j = 0; j < maxClients; ++j) {
                    if (nightAbilities.at(j) == i && players.at(i).killer == roles.at(j)) {
                        sendToIndex("Your target's defense was too strong to kill!", j);
                    }
                }
            }
            else if (players.at(i).defender == "Doctor") {
                sendToIndex("You were attacked, but someone nursed you back to health!", i);
            }
            else if (players.at(i).defender == "Bodyguard") {
                sendToIndex("You were attacked, but someone fought of your attacker!", i);
            }
        }
    }
}

void checkWin() {
    int town = 0, maf = 0, nk = 0;
    for (int i = 0; i < maxClients; ++i) {
        if (players.at(i).alive) {
            if (roles.at(i) == "Godfather" || roles.at(i) == "Mafioso" || roles.at(i) == "Janitor" || roles.at(i) == "Consigliere" || roles.at(i) == "Consort" || roles.at(i) == "Blackmailer" || roles.at(i) == "Framer") {
                maf = 1;
            }
            else if (roles.at(i) == "Serialkiller" || roles.at(i) == "Werewolf" || roles.at(i) == "Arsonist") {
                nk = 1;
            }
            else if (roles.at(i) != "Executioner" && roles.at(i) != "Jester") {
                town = 1;
            }
        }
    }
    if (maf + nk + town < 2) {
        for (int i = 0; i < maxClients; ++i) {
            if (players.at(i).alive) {
                if (roles.at(i) == "Godfather" || roles.at(i) == "Mafioso" || roles.at(i) == "Janitor" || roles.at(i) == "Consigliere" || roles.at(i) == "Consort" || roles.at(i) == "Blackmailer" || roles.at(i) == "Framer") {
                    if (maf) {
                        players.at(i).winCondition = true;
                    }
                }
                else if (roles.at(i) == "Serialkiller" || roles.at(i) == "Werewolf" || roles.at(i) == "Arsonist") {
                    if (nk) {
                        players.at(i).winCondition = true;
                    }
                }
                else if (roles.at(i) != "Executioner" && roles.at(i) != "Jester") {
                    if (town) {
                        players.at(i).winCondition = true;
                    }
                }
            }
        }
        for (int i = 0; i < maxClients; ++i) {
            if (players.at(i).winCondition) {
                sendToIndex("WIN\n", i);
            }
            else {
                sendToIndex("LOSS\n", i);
            }
            stop = true;
        }
    }
}

void dayNightCycle() {
    sendToEveryone("DAY\n");
    Sleep(10000);
    while (!stop) {
        for (int i = 0; i < maxClients; ++i) {
            nightAbilities.at(i) = -1;
        }
        sendToEveryone("MUTE\n");
        phase = "night";
        sendToEveryone("NIGHT\n");
        sendToIndex("You have been hauled off to jail!", jailee);
        sendToIndex("JAILED\n", jailee);
        Sleep(35000);
        nightLogic();
        for (int i = 0; i < maxClients; ++i) {
            if (players.at(i).jailed) {
                players.at(i).jailed = false;
                break;
            }
        }
        sendToEveryone("MORNING\n");
        counter++;
        phase = "morning";
        showDeathsAndWills();
        deadPlayers.clear();
        will.clear();
        checkWin();
        sendToEveryone("UNMUTE\n");
        Sleep(1000);
        phase = "discussion";
        sendToEveryone("DISCUSSION\n");
        Sleep(30000);
		majority = 0;
		for (int i = 0; i < maxClients; ++i) {
			if (clientSocket.at(i) > 0 && players.at(i).alive) {
				majority++;
			}
		}
		majority += 2;
		majority /= 2;
        phase = "voting";
		sendToEveryone("VOTING\n");
		Sleep(15000);
		for (int i = 0; i < maxClients; ++i) {
		    if (votes.at(i) != -1) {
                totalVotes.at(votes.at(i)) += players.at(i).voting;
		    }
		}
        for (int i = 0; i < maxClients; ++i) {
            if (totalVotes.at(i) >= majority && players.at(i).alive) {
                sendToEveryone(clientName.at(i) + " has been voted up by the town.\n");
                sendToEveryone("MUTE\n");
                sendToIndex("UNMUTE\n", i);
                phase = "defense";
                sendToEveryone("DEFENSE\n");
                Sleep(15000);
                sendToEveryone("UNMUTE\n");
                phase = "judging";
                sendToEveryone("JUDGING\n");
                Sleep(15000);
                int total = 0;
                for (int j = 0; j < maxClients; ++j) {
                    if (judging.at(j) == 1) {
                        sendToEveryone(clientName.at(j) + " has voted GUILTY.\n");
                        total += players.at(j).voting;

                    }
                    else if (judging.at(j) == 0) {
                        sendToEveryone(clientName.at(j) + " has abstained.\n");
                    }
                    else {
                        sendToEveryone(clientName.at(j) + " has voted INNOCENT.\n");
                        total -= players.at(j).voting;
                    }
                    judging.at(j) = 0;
                }
                if (total > 0) {
                    if (roles.at(i) == "Jester") {
                        sendToEveryone("The Jester will get his revenge from the grave!\n");
                        sendToIndex("You have successfully gotten yourself lynched!", i);
                        sendToIndex("HAUNT\n", i);
                        players.at(i).winCondition = true;
                    }
                    if (i == exeTarget) {
                        int j;
                        for (j = 0; j < maxClients; ++j) {
                            if (roles.at(j) == "Executioner") {
                                break;
                            }
                        }
                        players.at(j).winCondition = true;
                        sendToIndex("You have successfully gotten your target lynched!", j);
                    }
                    players.at(i).killer = "Lynch";
                    players.at(i).alive = false;
                    deadPlayers.push_back(i);
                    showDeathsAndWills();
                    deadPlayers.clear();
                    will.clear();
                    checkWin();
                }
            }
        }
		for (int i = 0; i < maxClients; ++i) {
			votes.at(i) = -1;
			totalVotes.at(i) = 0;
		}
		Sleep(5000);
    }
}

// Server
int main() {
	// General Variables
	WSADATA wsaData;
	srand(time(nullptr));
    std::thread cycle;

	// Roles
	roles.at(0) = "Jailor"; roles.at(1) = "TI"; roles.at(2) = "TI";
    roles.at(3) = "TP"; roles.at(4) = "TK"; roles.at(5) = "TS";
    roles.at(6) = "RT"; roles.at(7) = "RT"; roles.at(8) = "RT";
    roles.at(9) = "Godfather"; roles.at(10) = "Mafioso"; roles.at(11) = "RM";
    roles.at(12) = "RM"; roles.at(13) = "NE"; roles.at(14) = "NK";
    std::vector<std::string> TI = {"Investigator", "Sheriff", "Lookout", "Spy"};
    std::vector<std::string> TP = {"Doctor", "Bodyguard"};
    std::vector<std::string> TK = {"Vigilante", "Veteran"};
    std::vector<std::string> TS = {"Escort", "Medium", "Mayor", "Retributionist"};
    std::vector<std::string> RT = {"Investigator", "Sheriff", "Lookout", "Spy", "Doctor", "Bodyguard", "Escort", "Medium", "Mayor", "Retributionist"};
    std::vector<std::string> RM = {"Blackmailer", "Consigliere", "Consort", "Framer", "Janitor"};
    std::vector<std::string> NE = {"Jester", "Executioner"};
    std::vector<std::string> NK = {"Serialkiller", "Werewolf", "Arsonist"};

	// Server variables
	SOCKET serverSocketTCP, incomingSocket, temp;

	// Variables for select
	fd_set readfds;

	// Variables for sending and receiving
	int bytes, bytesSent;
	const int bufSize = 2048;
	auto *buffer = new char[bufSize + 1];

	// Response codes
	std::string response;
	const char* SEND_OK = "SEND-OK\n";
	const char* UNKNOWN = "UNKNOWN\n";
	const char* IN_USE = "INUSE\n";
	const char* BUSY = "BUSY\n";
	const char* BAD_RQST_HDR = "BAD-RQST-HDR\n";
	const char* BAD_RQST_BODY = "BAD-RQST-BODY\n";
	const char* SERVER_ERROR = "SERVER-ERROR\n";

	// Initializing clients to zero
	for (int i = 0; i < maxClients; i++) {
		clientSocket.at(i) = 0; // TCP
	}

	// Initializing WSA
	std::cout << "Initialising WSA...";
	int wsaError = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (wsaError != 0) {
		std::cout << " > Failed Initialising. Code: " << wsaError << std::endl;
		return 1;
	}
	std::cout << " > Initialised." << std::endl;

	// Creating server TCP socket
	std::cout << "Creating socket...";
	serverSocketTCP = socket(AF_INET, SOCK_STREAM, 0); // TCP
	if (serverSocketTCP == INVALID_SOCKET) {
		std::cout << " > Failed Creating. Code: " << WSAGetLastError() << std::endl;
		return 1;
	}
	std::cout << " > Socket created." << std::endl;

	// Setting server address and port
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("192.168.0.120");
	//server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(8888);

	// Binding socket to server address and port
	std::cout << "Binding socket...";
	if (bind(serverSocketTCP, (sockaddr*)&server, addrLength) == SOCKET_ERROR) {
		std::cout << " > Failed Binding. Code: " << WSAGetLastError() << std::endl;
		return 1;
	}
	std::cout << " > Socket bound." << std::endl;

	// Setting TCP to listen for connections
	listen(serverSocketTCP, SOMAXCONN);
	std::cout << "Listening for incoming connections." << std::endl;
	std::cout << "===================================" << std::endl;

	// Loop until stop
	while (!stop) {
		// Set Server and Client sockets to be selected
		FD_ZERO(&readfds);
		FD_SET(serverSocketTCP, &readfds);

		for (int i = 0; i < maxClients; i++) {
			if (clientSocket.at(i) > 0) {
				FD_SET(clientSocket.at(i), &readfds);
			}
		}

		// Select
		if (select(0, &readfds, nullptr, nullptr, nullptr) == SOCKET_ERROR) {
			std::cout << "Failed Selecting. Code: " << WSAGetLastError() << std::endl;
			stop = true;
		}
		// TCP Socket is set: Incoming connection
		else if (FD_ISSET(serverSocketTCP, &readfds)) {
			// Accept connection
			incomingSocket = accept(serverSocketTCP, (sockaddr*)&client, &addrLength);
			std::cout << inet_ntoa(client.sin_addr) << ":" << ntohs(client.sin_port);
			if (incomingSocket == INVALID_SOCKET) {
				std::cout << " -> Failed Accepting connection. Code: " << WSAGetLastError() << std::endl;
				continue;
			}

			// Check if there are already maxClients
			int num = 0;
			while (num < maxClients && !clientName.at(num).empty()) {
				num++;
			}
			if (num == maxClients) {
				// Server is busy
				bytesSent = send(incomingSocket, BUSY, (int)strlen(BUSY), 0);
				if (bytesSent == SOCKET_ERROR) {
					std::cout << " <- Error sending message, code:" << WSAGetLastError() << std::endl;
				}
				else {
					std::cout << " <- BUSY" << std::endl;
				}
				closesocket(incomingSocket);
			}
			else {
				clientSocket.at(num) = incomingSocket;
				std::cout << " -> Connected." << std::endl;
			}
		}
		// Something happened on a Client Socket (TCP)
		else {
			// Loop through all client sockets
			for (int num = 0; num < maxClients; num++) {
				// Check if it is in use
				if (clientSocket.at(num) == 0) {
					continue;
				}
				temp = clientSocket.at(num);
				// Check if something happened
				if (FD_ISSET(temp, &readfds)) {
					// Logging
					getpeername(temp, (sockaddr*)&client, &addrLength);
					std::cout << inet_ntoa(client.sin_addr) << ":" << ntohs(client.sin_port);
					// Receive message
					bytes = recv(temp, buffer, bufSize, 0);
					// Something went wrong
					if (bytes == SOCKET_ERROR) {
						// Check if they abruptly disconnected
						if (WSAGetLastError() == WSAECONNRESET) {
							std::cout << " -> Unexpectedly Disconnected." << std::endl;
							closesocket(temp);
							clientSocket.at(num) = 0;
							clientName.at(num) = "";
						}
						else {
							std::cout << " -> Failed Receiving. Code: " << WSAGetLastError() << std::endl;
						}
					}
					// Check if they disconnected
					else if (bytes == 0) {
						std::cout << " -> Disconnected." << std::endl;

						closesocket(temp);
						clientSocket.at(num) = 0;
						clientName.at(num) = "";
					}
					// Process the message
					else {
						buffer[bytes] = '\0';
						std::string msg = buffer;
						std::cout << " -> " << msg;
						// Handshake
						if (msg.size() > 5 && msg.substr(0, 5) == "LOGIN") {
							if (msg.size() > 6) {
								// Check if they already logged in
								if (!clientName.at(num).empty()) {
									response = BAD_RQST_HDR;
								}
								else {
									// Extract name from message
									std::string name;
									int index = 6;
									while (index < msg.size() && !isspace(msg.at(index))) {
										name += msg.at(index);
										index++;
									}
									// Check if it is already being used
									bool inuse = false;
                                    for (int i = 0; i < maxClients; i++) {
                                        if (name == clientName.at(i)) {
                                            inuse = true;
                                            break;
                                        }
                                    }
									// Set appropriate response
									if (inuse) {
										response = IN_USE;
									}
									else {
                                        response = "HELLO " + name + "\n";
                                        const char *buf = response.c_str();
                                        bytesSent = send(temp, buf, (int)response.size(), 0);
                                        std::cout << inet_ntoa(client.sin_addr) << ":" << ntohs(client.sin_port);
                                        if (bytesSent == SOCKET_ERROR) {
                                            std::cout << " <- Error sending message, code:" << WSAGetLastError() << std::endl;
                                        }
                                        else {
                                            std::cout << " <- " << response;
                                        }

                                        clientName.at(num) = name;
                                        response = "ALIVE";
                                        for (int i = 0; i < maxClients; i++) {
                                            if (!clientName.at(i).empty()) {
                                                response += " ";
                                                response += clientName.at(i);
                                            }
                                        }
                                        response += "\n";
									}
								}
							}
							// No name
							else {
								response = BAD_RQST_BODY;
							}
                            // Send response
                            sendToEveryone(response);
						}
						// Send a message
						else if (msg.size() > 4 && msg.substr(0, 4) == "SEND") {
						    response = clientName.at(num) + ": " + msg.erase(0, 5);
                            // Send response
                            if (phase == "night" && (num == jailee || roles.at(num) == "Jailor") && players.at(num).alive) {
                                sendToJail(response);
                            }
                            else if (phase == "night" && (roles.at(num) == "Godfather" || roles.at(num) == "Mafioso" || roles.at(num) == "Blackmailer" || roles.at(num) == "Janitor" || roles.at(num) == "Consigliere" || roles.at(num) == "Consort" || roles.at(num) == "Framer") && players.at(num).alive) {
                                sendToMafia(response);
                            }
                            else if (players.at(num).alive && phase != "night") {
                                if (!players.at(num).bm) {
                                    sendToEveryone(response);
                                }
                            }
                            else {
                                sendToDead(response);
                            }
						}
						else if (msg == "FILL\n") {
                            for (int i = 0; i < maxClients; i++) {
                                if (clientName.at(i).empty()) {
                                    clientName.at(i) = "Bot" + std::to_string(i + 1);
                                }
                            }

                            response = "ALIVE";
                            for (int j = 0; j < maxClients; j++) {
                                if (!clientName.at(j).empty()) {
                                    response += " ";
                                    response += clientName.at(j);
                                }
                            }
                            response += "\n";
                            // Send response
                            sendToEveryone(response);
						}
						else if (msg == "START\n") {
                            int currentIndex = maxClients, randomIndex;
                            std::string temporaryValue;
                            while (currentIndex != 0) {
                                randomIndex = rand() % maxClients;
                                currentIndex -= 1;

                                temporaryValue = roles.at(currentIndex);
                                roles.at(currentIndex) = roles.at(randomIndex);
                                roles.at(randomIndex) = temporaryValue;
                            }

                            for (int i = 0; i < maxClients; i++) {
                                if (roles.at(i) == "TI") roles.at(i) = TI.at(rand() % 4);
                                if (roles.at(i) == "TP") roles.at(i) = TP.at(rand() % 2);
                                if (roles.at(i) == "TK") roles.at(i) = TK.at(rand() % 2);
                                if (roles.at(i) == "TS") roles.at(i) = TS.at(rand() % 4);
                                if (roles.at(i) == "RT") roles.at(i) = RT.at(rand() % 10);
                                if (roles.at(i) == "RM") roles.at(i) = RM.at(rand() % 5);
                                if (roles.at(i) == "NE") roles.at(i) = NE.at(rand() % 2);
                                if (roles.at(i) == "NK") roles.at(i) = NK.at(rand() % 3);
                                roles.at(0) = "Godfather";
                                roles.at(1) = "Investigator";
                                if (clientSocket.at(i) > 0) {
                                    response = "ROLE ";
                                    response += roles.at(i);
                                    response += '\n';
                                    const char *buf = response.c_str();
                                    bytesSent = send(clientSocket.at(i), buf, (int)response.size(), 0);
                                    getpeername(clientSocket.at(i), (sockaddr *)&recipient, &addrLength);
                                    std::cout << inet_ntoa(recipient.sin_addr) << ":" << ntohs(recipient.sin_port);
                                    if (bytesSent == SOCKET_ERROR) {
                                        std::cout << " <- Error sending message, code:" << WSAGetLastError() << std::endl;
                                    }
                                    else {
                                        std::cout << " <- " << response;
                                    }
                                }
                            }
                            // Assigning exe target
                            for (int i = 0; i < maxClients; i++) {
                                std::cout << roles.at(i) << ',';
                                if (roles.at(i) == "Executioner") {
                                    exeTarget = getRandomTownie();
                                    sendToIndex("TARGET " + clientName.at(exeTarget), i);
                                }
                            }
                            std::string temp = "MAFIA ";
                            for (int i = 0; i < maxClients; i++) {
                                if (roles.at(i) == "Godfather" || roles.at(i) == "Mafioso" || roles.at(i) == "Blackmailer" || roles.at(i) == "Janitor" || roles.at(i) == "Consigliere" || roles.at(i) == "Consort" || roles.at(i) == "Framer") {
                                    temp += clientName.at(i);
                                    temp += "(";
                                    temp += roles.at(i);
                                    temp += ") ";
                                }
                            }
                            sendToMafia(temp);

                            std::cout << std::endl;

                            Sleep(5000);
                            response = "START\n";
                            cycle = std::thread{dayNightCycle};
                            Sleep(100);
                            // Send response
                            sendToEveryone(response);
						}
						else if (msg == "CANCEL\n") {
							if (phase == "voting") {
                                votes.at(num) = -1;
                                response = clientName.at(num) + " has cancelled their vote.\n";
                                // Send response
                                sendToEveryone(response);
							}
							else if (phase == "night") {
							    nightAbilities.at(num) = -1;
                                sendToIndex("You have changed your mind.\n", num);
							}
						}
						else if (msg.substr(0, 4) == "VOTE") {
							int index = 5;
							std::string tmp;
							while (index < msg.size() && !isspace(msg.at(index))) {
								tmp += msg.at(index);
								index++;
							}
							int vote = std::stoi(tmp);
							votes.at(num) = vote;
							response = clientName.at(num) + " has voted against " + clientName.at(vote) + '\n';
                            // Send response
                            sendToEveryone(response);
						}
						else if (msg == "GUILTY\n") {
							judging.at(num) = 1;
							response = clientName.at(num) + " has voted.\n";
                            // Send response
                            sendToEveryone(response);
						}
						else if (msg == "INNO\n") {
                            judging.at(num) = -1;
							response = clientName.at(num) + " has voted.\n";
                            // Send response
                            sendToEveryone(response);
						}
                        else if (msg.substr(0, 12) == "NIGHTABILITY") {
                            int index = 13;
                            std::string tmp;
                            while (index < msg.size() && !isspace(msg.at(index))) {
                                tmp += msg.at(index);
                                index++;
                            }
                            int ability = std::stoi(tmp);
                            nightAbilities.at(num) = ability;
                            sendToIndex("You have decided to target " + clientName.at(ability) + " tonight.", num);
                        }
                        else if (msg == "CANCELJAIL\n") {
                            jailee = -2;
                            sendToIndex("You have changed your mind.", num);
                        }
                        else if (msg.substr(0, 4) == "JAIL") {
                            int index = 5;
                            std::string tmp;
                            while (index < msg.size() && !isspace(msg.at(index))) {
                                tmp += msg.at(index);
                                index++;
                            }
                            jailee = std::stoi(tmp);
                            if (jailee == num) {
                                sendToIndex("You cannot jail yourself!", num);
                            }
                            else {
                                sendToIndex("You have decided to jail " + clientName.at(jailee) + " tonight.", num);
                            }
                        }
                        else if (msg.substr(0, 4) == "WILL") {
                            will = msg;
                        }
                        else if (msg == "REVEAL\n") {
                            if (roles.at(num) == "Mayor" && players.at(num).ability) {
                                players.at(num).voting = 3;
                                players.at(num).ability = false;
                                response = clientName.at(num) + " has revealed themselves as the Mayor!";
                                sendToEveryone(response);
                            }
                        }
						else {
							response = BAD_RQST_HDR;
                            // Send response
                            sendToIndex(response, num);
						}
					} // received bytes is an actual message
				} // clientSocket.at(num) is set
			} // loop through clientSocket
		} // serverSockets are not set
	} // loop until stop

	// Cleaning up
	for (int i = 0; i < maxClients; i++) {
		if (clientSocket.at(i) > 0) {
			closesocket(clientSocket.at(i));
		}
	}
	closesocket(serverSocketTCP);
	FD_ZERO(&readfds);

	delete[] buffer;
	WSACleanup();

	cycle.join();

	std::cout << " > Shut down." << std::endl;

	return 0;
}
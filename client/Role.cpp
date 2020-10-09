#include "Role.h"

void Role::setArsonist() {
    alignment = "Alignment: Neutral Killing";
    ability1 = "You may Douse someone in gas";
    ability2 = "or ignite Doused targets..";
    attributes1 = "Select yourself to ignite";
    attributes2 = "the already doused targets";
    goal = "Live to see everyone burn.";
    attack = "Attack: Unstoppable";
    defense = "Defense: Basic";
    AttValue = 3;
    DefValue = 1;
    DayAbility = false;
};

void Role::setBlackmailer() {
    alignment = "Alignment: Mafia Support";
    ability1 = "Choose someone to blackmail at night";
    ability2 = "";
    attributes1 = "blackmailed targets can't talk";
    attributes2 = "You can hear whispers of others";
    goal = "Kill all non-mafias.";
    attack = "Attack: None";
    defense = "Defense: None";
    AttValue = 0;
    DefValue = 0;
    DayAbility = false;
};

void Role::setBodyguard() {
    alignment = "Alignment: Town Protective";
    ability1 = "Heal one person each night.";
    ability2 = "you will fight with the attacker";
    attributes1 = "You can protect yourself once.";
    attributes2 = "You kill your targets attacker";
    goal = "Lynch every criminal and evildoer.";
    attack = "Attack: None";
    defense = "Defense: None";
    AttValue = 0;
    DefValue = 0;
    DayAbility = false;
};

void Role::setConsigliere() {
    alignment = "Alignment: Mafia Support";
    ability1 = "Check someones exact";
    ability2 = "role every night";
    attributes1 = "";
    attributes2 = "";
    goal = "Kill all non-mafias.";
    attack = "Attack: None";
    defense = "Defense: None";
    DefValue = 0;
    DayAbility = false;
};

void Role::setConsort() {
    alignment = "Alignment: Mafia Support";
    ability1 = "Distract someone each night";
    ability2 = "";
    attributes1 = "Distraction blocks";
    attributes2 = "target from doing anything at night";
    goal = "Kill all non-mafias.";
    attack = "Attack: None";
    defense = "Defense: None";
    AttValue = 0;
    DefValue = 0;
    DayAbility = false;
};

void Role::setDoctor() {
    alignment = "Alignment: Town Protective";
    ability1 = "Heal one person each night.";
    ability2 = "This prevents them from dying.";
    attributes1 = "You can heal yourself once. ";
    attributes2 = "You will know if your target is attacked.";
    goal = "Lynch every criminal and evildoer.";
    attack = "Attack: None";
    defense = "Defense: None";
    AttValue = 0;
    DefValue = 0;
    DayAbility = false;
};

void Role::setEscort() {
    alignment = "Alignment: Town Support";
    ability1 = "Distract someone each night";
    ability2 = "";
    attributes1 = "Distraction blocks";
    attributes2 = "target from doing anything at night";
    goal = "Lynch every criminal and evildoer.";
    attack = "Attack: None";
    defense = "Defense: None";
    AttValue = 0;
    DefValue = 0;
    DayAbility = false;
};

void Role::setExecutioner() {
    alignment = "Alignment: Neutral Evil";
    ability1 = "Trick the town ";
    ability2 = "into lynching your target";
    attributes1 = "Your target: <>";
    attributes2 = "You become Jester if unsuccessful at lynching";
    goal = "Get your target lynched at any cost.";
    attack = "Attack: None";
    defense = "Defense: Basic";
    AttValue = 0;
    DefValue = 1;
    DayAbility = false;
};

void Role::setFramer() {
    alignment = "Alignment: Mafia Support";
    ability1 = "Choose someone to";
    ability2 = "frame at night";
    attributes1 = "if your target is investigated";
    attributes2 = "they will appear as a mafia member";
    goal = "Kill all non-mafias.";
    attack = "Attack: None";
    defense = "Defense: None";
    AttValue = 0;
    DefValue = 0;
    DayAbility = false;
};

void Role::setGodfather() {
    alignment = "Alignment: Mafia Killing";
    ability1 = "Choose to attack a player at night";
    ability2 = "if mafioso can't attack you will attack";
    attributes1 = "Mafioso will attack your target";
    attributes2 = " instead. Sheriff thinks you're a Townie";
    goal = "Kill all non-mafias.";
    attack = "Attack: Basic";
    defense = "Defense: Basic";
    AttValue = 1;
    DefValue = 1;
    DayAbility = false;
};

void Role::setInvestigator() {
    alignment = "Alignment: Town Invest";
    ability1 = "Investigate one person each";
    ability2 = "night for a clue to their role";
    attributes1 = "";
    attributes2 = "";
    goal = "Lynch every criminal and evildoer.";
    attack = "Attack: None";
    defense = "Defense: None";
    AttValue = 0;
    DefValue = 0;
    DayAbility = false;
};

void Role::setJailor() {
    alignment = "Alignment: Town Killing";
    ability1 = "Choose someone to jail";
    ability2 = "during the day";
    attributes1 = "you can talk to your prisoner ";
    attributes2 = "at night and decide to execute them";
    goal = "Lynch every criminal and evildoer.";
    attack = "Attack: Unstoppable";
    defense = "Defense: None";
    AttValue = 3;
    DefValue = 0;
    DayAbility = true;
};

void Role::setJanitor() {
    alignment = "Alignment: Mafia Support";
    ability1 = "Choose a person to";
    ability2 = "clean at night";
    attributes1 = "3 cleans, remove targets will and role";
    attributes2 = "you will be able to see the will and role";
    goal = "Kill all non-mafias.";
    attack = "Attack: None";
    defense = "Defense: None";
    AttValue = 0;
    DefValue = 0;
    DayAbility = false;
};

void Role::setJester() {
    alignment = "Alignment: Neutral Evil";
    ability1 = "Trick the town into lynching yourself";
    ability2 = "";
    attributes1 = "Haunt someone at night ";
    attributes2 = "when you get lynched.";
    goal = "Get yourself lynched at any cost.";
    attack = "Attack: None";
    defense = "Defense: None";
    AttValue = 0;
    DefValue = 0;
    DayAbility = false;
};

void Role::setLookout() {
    alignment = "Alignment: Town Invest";
    ability1 = "Choose a target to watch at night to";
    ability2 = "see who visits them";
    attributes1 = "";
    attributes2 = "";
    goal = "Lynch every criminal and evildoer.";
    attack = "Attack: None";
    defense = "Defense: None";
    AttValue = 0;
    DefValue = 0;
    DayAbility = false;
};

void Role::setMafioso() {
    alignment = "Alignment: Mafia Killing";
    ability1 = "Carry out the Godfathers order";
    ability2 = "and attack someone at night";
    attributes1 = "You can attack even without ";
    attributes2 = "orders.";
    goal = "Kill all non-mafias.";
    attack = "Attack: Basic";
    defense = "Defense: None";
    AttValue = 1;
    DefValue = 0;
    DayAbility = false;
};

void Role::setMayor() {
    alignment = "Alignment: Town Support";
    ability1 = "You can reveal yourself as";
    ability2 = "The mayor of the town";
    attributes1 = "Revealing triples your voting power";
    attributes2 = "You cannot be healed or whisper/receive whispers";
    goal = "Lynch every criminal and evildoer.";
    attack = "Attack: None";
    defense = "Defense: None";
    AttValue = 0;
    DefValue = 0;
    DayAbility = true;
};

void Role::setMedium() {
    alignment = "Alignment: Town Support";
    ability1 = "Speak to the dead when living";
    ability2 = "Speak to the living once when dead";
    attributes1 = "you may speak anonymously to the dead";
    attributes2 = "and once to the living during the night";
    goal = "Lynch every criminal and evildoer.";
    attack = "Attack: None";
    defense = "Defense: None";
    AttValue = 0;
    DefValue = 0;
    DayAbility = true;
};

void Role::setRetributionist() {
    alignment = "Alignment: Town Support";
    ability1 = "You may revive a dead town member";
    ability2 = "Once and once only";
    attributes1 = "You may resurrect only";
    attributes2 = "one dead player.";
    goal = "Lynch every criminal and evildoer.";
    attack = "Attack: None";
    defense = "Defense: None";
    AttValue = 0;
    DefValue = 0;
    DayAbility = true;
};

void Role::setSerialKiller() {
    alignment = "Alignment: Neutral Killing";
    ability1 = "You may choose to attack";
    ability2 = "a player at night";
    attributes1 = "kills roleblockers and kills";
    attributes2 = "the jailor when jailed";
    goal = "Kill the mafia and town.";
    attack = "Attack: Basic";
    defense = "Defense: Basic";
    AttValue = 1;
    DefValue = 1;
    DayAbility = false;
};

void Role::setSheriff() {
    alignment = "Alignment: Town Invest";
    ability1 = "Check a person each night";
    ability2 = "to see if they're suspicious";
    attributes1 = "Mafia (except Godfather), Werewolf";
    attributes2 = "(during full moon) and Serial Killer are suspicious";
    goal = "Lynch every criminal and evildoer.";
    attack = "Attack: None";
    defense = "Defense: None";    AttValue = 0;
    DefValue = 0;
    DayAbility = false;
};

void Role::setSpy() {
    alignment = "Alignment: Town Invest";
    ability1 = "You may bug a person";
    ability2 = "to see what happens with them at night";
    attributes1 = "you will see who the mafia visits";
    attributes2 = "at night.";
    goal = "Lynch every criminal and evildoer.";
    attack = "Attack: None";
    defense = "Defense: None";
    AttValue = 0;
    DefValue = 0;
    DayAbility = false;
};

void Role::setVeteran() {
    alignment = "Alignment: Town Killing";
    ability1 = "You may choose to go on alert";
    ability2 = "at night.(3 times max)";
    attributes1 = "If you alert you gain basic defense ";
    attributes2 = "and will attack everyone who visits";
    goal = "Lynch every criminal and evildoer.";
    attack = "Attack: Powerful";
    defense = "Defense: None";
    AttValue = 2;
    DefValue = 0;
    DayAbility = false;
};

void Role::setVigilante() {
    alignment = "Alignment: Town Killing";
    ability1 = "You may choose to shoot someone ";
    ability2 = "at night.(3 times max)";
    attributes1 = "If you shoot a townie you will";
    attributes2 = "commit seppuku.";
    goal = "Lynch every criminal and evildoer.";
    attack = "Attack: None";
    defense = "Defense: None";
    AttValue = 1;
    DefValue = 0;
    DayAbility = false;
};

void Role::setWerewolf() {
    alignment = "Alignment: Neutral Killing";
    ability1 = "You may choose to rampage";
    ability2 = "at a player during full moon";
    attributes1 = "attacks everyone who visits";
    attributes2 = "target";
    goal = "Kill the mafia and town.";
    attack = "Attack: Powerful";
    defense = "Defense: Basic";
    AttValue = 2;
    DefValue = 1;
    DayAbility = false;
};

void Role::setEmpty() {
    alignment = "Alignment: Undefined";
    ability1 = "You may choose a player";
    ability2 = "at night and perform your ability";
    attributes1 = "Undefined";
    attributes2 = "Other attributes";
    goal = "depends on your alignment.";
    attack = "Attack: unknown";
    defense = "Defense: unknown";
    AttValue = 0;
    DefValue = 0;
    DayAbility = false;
}

void Role::setRole(std::string input){
    roleName = input;
    if (input == "Arsonist") {
        setArsonist();
    }

    else if (input == "Blackmailer") {
        setBlackmailer();
    }

    else if (input == "Bodyguard") {
        setBodyguard();
    }
    else if (input == "Consigliere") {
        setConsigliere();
    }

    else if (input == "Consort") {
        setConsort();
    }

    else if (input == "Doctor") {
        setDoctor();
    }

    else if (input == "Escort") {
        setEscort();
    }

    else if (input == "Executioner") {
        setExecutioner();
    }

    else if (input == "Framer") {
        setFramer();
    }

    else if (input == "Godfather") {
        setGodfather();
    }

    else if (input == "Investigator") {
        setInvestigator();
    }

    else if (input == "Jailor") {
        setJailor();
    }

    else if (input == "Janitor") {
        setJanitor();
    }

    else if (input == "Jester") {
        setJester();
    }

    else if (input == "Lookout") {
        setLookout();
    }

    else if (input == "Mafioso") {
        setMafioso();
    }

    else if (input == "Mayor") {
        setMayor();
    }

    else if (input == "Medium") {
        setMedium();
    }

    else if (input == "Retributionist") {
        setRetributionist();
    }

    else if (input == "SerialKiller") {
        setSerialKiller();
    }

    else if (input == "Sheriff") {
        setSheriff();
    }

    else if (input == "Spy") {
        setSpy();
    }

    else if (input == "Veteran") {
        setVeteran();
    }

    else if (input == "Vigilante") {
        setVigilante();
    }

    else if (input == "Werewolf") {
        setWerewolf();
    }

    else if (input == "Empty") {
        setEmpty();
    }
};
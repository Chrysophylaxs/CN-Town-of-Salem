#ifndef TOS_ROLE_H
#define TOS_ROLE_H

#include <string>

class Role {
public:
    void setArsonist();
    void setBlackmailer();
    void setBodyguard();
    void setConsigliere();
    void setConsort();
    void setDoctor();
    void setEscort();
    void setExecutioner();
    void setFramer();
    void setGodfather();
    void setInvestigator();
    void setJailor();
    void setJanitor();
    void setJester();
    void setLookout();
    void setMafioso();
    void setMayor();
    void setMedium();
    void setRetributionist();
    void setSerialKiller();
    void setSheriff();
    void setSpy();
    void setVeteran();
    void setVigilante();
    void setWerewolf();
    void setEmpty();

    void setRole(std::string input);
    std::string roleName;
    std::string alignment;
    std::string ability1;
    std::string ability2;
    std::string attributes1;
    std::string attributes2;
    std::string goal;
    std::string attack;
    std::string defense;
    int AttValue;
    int DefValue;
    bool DayAbility;
};

#endif // TOS_ROLE_H



#include"Character.hpp"

Character::Character(){
    description = "unknown";
    hp = 1;
    currentPosition = 0;
}
void Character::setCharacter(string desc, int h, Room* currentPos){
    description = desc;
    hp = h;
    currentPosition = currentPos;
}
void Character::addPartner(Character* part){
    partner.push_back(part);
}
vector<string> Character::getCharacterStatus(){
    vector<string> ret;
    ret.push_back(description);
    ret.push_back(to_string(hp));
    ret.push_back(currentPosition->getRoomStatus()[0]);
    ret.push_back(to_string(partner.size()));
    for(size_t it=0; it<partner.size(); it++){
        ret.push_back(partner[it]->getCharacterStatus()[0]);
    }
    return ret;
}
bool Character::goRoom(string exit){
    Room* room = currentPosition->getExit(exit);
    if(!room)
        return false;
    currentPosition = room;
    for(size_t it=0; it<partner.size(); it++)
        partner[it]->goRoom(exit);
    return true;
}
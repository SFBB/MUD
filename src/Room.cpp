#include"Room.hpp"

Room::Room(string desc){
    description = desc;
    exits[description] = this;
}
void Room::setDescription(string desc){
    description = desc;
}
void Room::setExit(string exit, Room* room){
    exits[exit] = room;
}
vector<string> Room::getRoomStatus(){
    exits.erase(description);
    vector<string> ret;
    ret.push_back(description);
    ret.push_back(to_string(exits.size()));
    map<string, Room*>::iterator it;
    for(it=exits.begin(); it!=exits.end(); it++){
        ret.push_back(it->first);
    }
    exits[description] = this;
    return ret;
}
Room* Room::getExit(string exit){
    return exits[exit];
} 
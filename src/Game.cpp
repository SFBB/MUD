#include"Game.hpp"

void Game::intiialMap(){
    static Room lobby("Lobby"), square("Square"), dinningHall("Dinning Hall"), bedroom("Bedroom"), basement("Basement"), bedroom_1("Bedroom_1"), bedroom_2("Bedroom_2"), bedroom_3("Bedroom_3");

    roomInMap[lobby.getRoomStatus()[0]] = &lobby;
    lobby.setExit("east", &dinningHall);
    roomInMap[square.getRoomStatus()[0]] = &square;
    square.setExit("west_1", &dinningHall);
    square.setExit("west_2", &bedroom_3);
    roomInMap[dinningHall.getRoomStatus()[0]] = &dinningHall;
    dinningHall.setExit("west", &lobby);
    dinningHall.setExit("east", &square);
    dinningHall.setExit("up", &bedroom);
    dinningHall.setExit("down", &basement);
    dinningHall.setExit("north", &bedroom_1);
    dinningHall.setExit("south", &bedroom_3);
    roomInMap[bedroom.getRoomStatus()[0]] = &bedroom;
    bedroom.setExit("down", &dinningHall);
    bedroom.setExit("north", &bedroom_2);
    roomInMap[basement.getRoomStatus()[0]] = &basement;
    basement.setExit("up_1", &dinningHall);
    basement.setExit("up_2", &bedroom_1);
    roomInMap[bedroom_1.getRoomStatus()[0]] = &bedroom_1;
    bedroom_1.setExit("up", &bedroom_2);
    bedroom_1.setExit("south", &dinningHall);
    bedroom_1.setExit("down", &basement);
    roomInMap[bedroom_2.getRoomStatus()[0]] = &bedroom_2;
    bedroom_2.setExit("south", &bedroom);
    bedroom_2.setExit("down", &bedroom_1);
    roomInMap[bedroom_3.getRoomStatus()[0]] = &bedroom_3;
    bedroom_3.setExit("north", &dinningHall);
    bedroom_3.setExit("east", &square);    
    
    start = &lobby;
    end = &lobby;
    prision = randomPosition();
}
Room* Game::randomPosition(){
    int roomNumbers = roomInMap.size();
    int roomID = rand()%roomNumbers;
    vector<Room*> rooms;
    map<string, Room*>::iterator it;
    for(it=roomInMap.begin(); it!=roomInMap.end(); it++)
        rooms.push_back(it->second);
    while(rooms[roomID] == start){
        roomID = rand()%roomNumbers;
    }
    return rooms[roomID];
}
string Game::randomDirection(string curRoom){
    vector<string> roomStatus = roomInMap[curRoom]->getRoomStatus();
    vector<string> exits;
    exits.push_back(roomStatus[0]);
    for(size_t it=2; it<roomStatus.size(); it++)
        exits.push_back(roomStatus[it]);
    int exitNum = exits.size();
    int roomID = rand()%exitNum;
    return exits[roomID];
}
void Game::initialCharacter(){
    static Character player, princess, monster;
    characterInMap["Player"] = &player;
    player.setCharacter("Player", 1, start);
    characterInMap["Princess"] = &princess;
    princess.setCharacter("Princess", 1, prision);
    characterInMap["Monster"] = &monster;
    monster.setCharacter("Monster", 1, randomPosition());
    monster.setCharacter("Monster", 1, roomInMap["Square"]);
}
string Game::setHelp(){
    string ret = "";
    ret += "\"go + exit name\" to go to next room.\n";
    ret += "\"stay\" to stay at current room.\n";
    ret += "\"bye\" to exit this game.\n";
    return ret;
}
string Game::setDiaglogue(Character* player, Character* monster){
    string ret = "";
    if(player->getCharacterStatus()[2] == monster->getCharacterStatus()[2]){
        ret += player->getCharacterStatus()[0]+": Oh, monster!\n";
    }
    if(roomInMap[player->getCharacterStatus()[2]] == prision && player->getCharacterStatus()[3] == "0"){
        ret += characterInMap["Princess"]->getCharacterStatus()[0]+": Help me! Help me, please!\n";
        ret += player->getCharacterStatus()[0]+": Oh, princess!\n";
    }
    return ret;
}
string Game::setDescription(){
    Character* player = characterInMap["Player"];
    string ret = "";
    vector<string> playerStatus = player->getCharacterStatus();
    vector<string> roomStatus = roomInMap[player->getCharacterStatus()[2]]->getRoomStatus();
    ret += playerStatus[0];
    ret += " is in ";
    ret += roomStatus[0];
    ret += " with ";
    ret += playerStatus[3];
    ret += " partners";
    for(size_t it=4; it<playerStatus.size()-1; it++)
        ret += " "+playerStatus[it];
    if(4 < playerStatus.size()-1)
        ret += ", " + playerStatus[playerStatus.size() - 1];
    else if(4 == playerStatus.size()-1)
        ret += " " + playerStatus[playerStatus.size() - 1];
    ret += ".\n";
    ret += "This room has " + roomStatus[1] + " exits:";
    for(size_t it=2; it<roomStatus.size()-1; it++)
        ret += " " + roomStatus[it];
    if(2 < roomStatus.size()-1)
        ret += ", " + roomStatus[roomStatus.size()-1];
    else if(2 == roomStatus.size()-1)
        ret += " " + roomStatus[roomStatus.size()-1];
    ret += "?\n";
    return ret;
}
Game::Game(){
    start = 0;
    end = 0;
    prision = 0;
    intiialMap();
    initialCharacter();
}
Room* Game::getRoom(string room){
    return roomInMap[room];
}
string Game::retHelp(){
    return setHelp();
}
string Game::retDialogue(){
    return  setDiaglogue(characterInMap["Player"], characterInMap["Monster"]);
}
string Game::retDescription(){
    return setDescription();
}
bool Game::moveCharacter(string character, string exit){
    if(exit == "Random")
        exit = randomDirection(characterInMap[character]->getCharacterStatus()[2]);
    return (characterInMap[character]->goRoom(exit));
}
bool Game::checkWinOrLose(){
    bool checkPoint_win = (roomInMap[characterInMap["Player"]->getCharacterStatus()[2]] == end && roomInMap[characterInMap["Princess"]->getCharacterStatus()[2]] == end);
    bool checkPoint_lose = characterInMap["Player"]->getCharacterStatus()[2] == characterInMap["Monster"]->getCharacterStatus()[2];
    if(checkPoint_win)
        cout<<"Congratulations! You saved princess and got away with monster!\n";
    if(checkPoint_lose)
        cout << "You lost this game!\n";
    return checkPoint_win || checkPoint_lose;    
}
bool Game::checkKeyPointAndDo(){
    bool checkPoint_1 = characterInMap["Player"]->getCharacterStatus()[2] == characterInMap["Monster"]->getCharacterStatus()[2];
    bool checkPoint_2 = roomInMap[characterInMap["Player"]->getCharacterStatus()[2]] == prision && characterInMap["Player"]->getCharacterStatus()[3] == "0";
    if(checkPoint_1){
        cout<<"If you want to attack or go away? [y/n]?:\n";
        string input;
        while(1){
            getline(cin, input);
            if(input == "y"){
                cout<<"You stupid guy! You are dead! Game over!\n";
                break;
            }
            else if(input == "n"){
                cout<<"Coward! You cannot get away! You are dead! Game over!\n";
                break;
            }
            else
                cout<<"What? Please reinput!\n"<<"Btw, you have only two choice [y/n]?:\n";
        }
        return checkPoint_1;
    }
    if(checkPoint_2){
        cout<<"Princess is in prision! Do you want to save her? [y/n]?:\n";
        string input;
        while(1){
            getline(cin, input);
            if(input == "y"){
                characterInMap["Player"]->addPartner(characterInMap["Princess"]);
                cout<<"You have saved princess!\n";
                break;
            }
            else if(input == "n"){
                cout<<"You left!\n";
                break;
            }
            else
                cout<<"What? Please reinput!\n"<<"Btw, you have only two choice [y/n]?:\n";                
        }
    }
    return checkPoint_1 || checkPoint_2;
}
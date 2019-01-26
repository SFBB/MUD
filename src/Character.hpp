#ifndef _CHARACTER_HPP_
#define _CHARACTER_HPP_

#include"Room.hpp"
#include<stdlib.h>


class Character{
private:
    string description; //记录角色的名称
    int hp; //记录角色的生命值
    vector<Character*> partner; //存储与角色一起行进的同伴
    Room* currentPosition;  //记录该角色目前所处的房间位置
public:
    Character();    //构造函数
    void setCharacter(string desc, int h, Room* currentPos);    //设置该角色的名称，生命值，当前所处的位置
    void addPartner(Character* part);   //为该角色添加一名共同行进的同伴
    vector<string> getCharacterStatus();    //得到该角色的状态，按照名称，生命值，所处的房间名称，拥有的共同行进的同伴的数量以及这些同伴的名称返回
    bool goRoom(string exit);   //控制该角色从某一个入口进入到某个房间
};

#endif // !_CHARACTE_HPP_R
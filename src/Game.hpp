#ifndef _GAME_HPP_
#define _GAME_HPP_

#include"Room.hpp"
#include"Character.hpp"
#include<vector>
#include<cstdlib>
#include<stdlib.h>

class Game{
private:
    Room* start;    //记录游戏所设置的起点位置
    Room* end;  //记录游戏所设置的重点位置
    Room* prision;  //记录游戏所设置的监狱位置
    map<string, Character*> characterInMap; //存储所有在该地图中的角色，string为角色名称，Character*为相应的角色
    map<string, Room*> roomInMap;   //存储所有在该地图中的房间，string为房间名称，Character*为相应的房间
    void intiialMap();  //初始化地图，地图的描绘在这里完成
    Room* randomPosition(); //生成地图中现有房间中的任意一个房间
    string randomDirection(string curRoom); //生成当前房间的随机出口(含本房间)
    void initialCharacter();    //初始化角色，角色的描绘在这里完成
    string setHelp();  //设定帮助信息
    string setDiaglogue(Character* player, Character* monster);    //设定对话信息以及对话会如何由角色间的状态触发
    string setDescription();   //设定描述信息，包含玩家的状态与房间的信息
public:
    Game(); //构造函数
    Room* getRoom(string room); //通过房间名称得到相应的房间
    string retHelp();   //返回帮助信息
    string retDialogue();   //返回对话信息
    string retDescription();    //返回描述信息
    bool moveCharacter(string character, string exit);  //通过角色名称和入口名称来移动相应的角色进入相应的房间
    bool checkWinOrLose();  //判断游戏是赢是输
    bool checkKeyPointAndDo();  //检查角色是否到达关键点并触发相应的互动
};

#endif // !_GAME_HPP_
#ifndef _ROOM_HPP_
#define _ROOM_HPP_

#include<iostream>
#include<vector>
#include<map>
#include<cstdlib>
using namespace std;

class Room{
private:
    string description; //记录房间的名称
    map<string, Room*> exits;   //string为出口的名称，Room*为该出口通向的房间，这个变量存储该房间所有的出口
public:
    Room(string desc);  //初始化一个房间，同时初始化房间的名称
    void setDescription(string desc);   //修改房间的名称
    void setExit(string exit, Room* room);  //设定该房间的出口
    vector<string> getRoomStatus(); //得到该房间的描述，按照房间名称，出口数量(不含本房间)以及这些出口的名称返回
    Room* getExit(string exit); //得到出口指向的房间
};

#endif  // !_ROOM_HPP_
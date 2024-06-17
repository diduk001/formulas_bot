
#include <iostream>
#ifndef TELEGRAMBOT_GROUP_H
#define TELEGRAMBOT_GROUP_H


class Group {
    std::string group_name;
    int64_t tg_id;
    int64_t owner_id;
    
public:
    Group();

   ~Group();

    void set_group_name(std::string name){
        this->group_name=name;
    }

    void set_tg_id(int64_t id){
        this->tg_id=id;
    }

    void set_owner_id(int64_t id){
        this->owner_id=id;
    }


    std::string get_group_name(){
        return this->group_name;
    }

    int64_t get_tg_id(){
        return this->tg_id;
    }

    int64_t get_owner_id(){
        return this->owner_id;
    }
};


#endif //TELEGRAMBOT_GROUP_H

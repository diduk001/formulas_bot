#include <iostream>
#ifndef BOT_GROUP_H
#define BOT_GROUP_H

class Group{
    private:
        std::string group_name;
        int tg_id;
        int64_t owner_id;
    public:
        Group():group_name(""),tg_id(0),owner_id(0) {}
       ~Group(){}

        void set_group_name(std::string name){
            this->group_name=name;
        }

        void set_tg_id(int id){
            this->tg_id=id;
        }

        void set_owner_id(int64_t user_id){
            this->owner_id=user_id;
        }

        std::string get_group_name(){
            return this->group_name;
        }

        int get_tg_id(){
            return this->tg_id;
        }

        int64_t get_owner_if(){
            return this->owner_id;
        }
};

#endif //BOT_GROUP_H
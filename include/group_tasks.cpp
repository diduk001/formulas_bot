#include <tgbot/tgbot.h>
#include <stdio.h>
#include <unordered_map>
#include <vector>
#include <string>
#include "group.h"
#include <sqlite3.h>

enum class Group_State{NONE, WAITING_FOR_GROUP_NAME,WAITING_FOR_NEW_GROUP_NAME};

std::unordered_map<int64_t, Group_State> userStates;
std::unordered_map<int64_t, Group> userGroup;

void setState(int64_t userId, Group_State state) {
    userStates[userId] = state;
}

Group_State getState(int64_t userId) {
    if (userStates.find(userId) == userStates.end()) {
        return Group_State::NONE;
    }
    return userStates[userId];
}


int main(){
    TgBot::Bot bot("...");

    //КЛАВИАТУРА для ответа да/нет 1
    TgBot::InlineKeyboardMarkup::Ptr keyboardYesNo1(new TgBot::InlineKeyboardMarkup); // создали инлайновую клавиатуру
    std::vector<TgBot::InlineKeyboardButton::Ptr> buttons1; // создали вектор с набором кнопок, которые будут там храниться
    TgBot::InlineKeyboardButton::Ptr AnswerYes1(new TgBot::InlineKeyboardButton); // создание самой кнопки
    AnswerYes1->text = "Да"; // как кнопка будет подписана у пользователя
    AnswerYes1->callbackData = "Yes1"; // то, что возвращает кнопка в бота при нажатии
    AnswerYes1->url="https://t.me/yapi_test_bot?startgroup=1";
    buttons1.push_back(AnswerYes1); // заталкиваем кнопки в вектор
    TgBot::InlineKeyboardButton::Ptr AnswerNo1(new TgBot::InlineKeyboardButton); // создание самой кнопки
    AnswerNo1->text = "Нет"; // как кнопка будет подписана у пользователя
    AnswerNo1->callbackData = "No1"; // то, что возвращает кнопка в бота при нажатии
    buttons1.push_back(AnswerNo1); // заталкиваем кнопки в вектор
    keyboardYesNo1->inlineKeyboard.push_back(buttons1); // заталкиваем вектор в клавиатуру
    
    //КЛАВИАТУРА для ответа да/нет 2
    TgBot::InlineKeyboardMarkup::Ptr keyboardYesNo2(new TgBot::InlineKeyboardMarkup); 
    std::vector<TgBot::InlineKeyboardButton::Ptr> buttons2; 
    TgBot::InlineKeyboardButton::Ptr AnswerYes2(new TgBot::InlineKeyboardButton); 
    AnswerYes2->text = "Да";
    AnswerYes2->callbackData = "Yes2";
    buttons2.push_back(AnswerYes2);
    TgBot::InlineKeyboardButton::Ptr AnswerNo2(new TgBot::InlineKeyboardButton);
    AnswerNo2->text = "Нет"; 
    AnswerNo2->callbackData = "No2";
    buttons2.push_back(AnswerNo2); 
    keyboardYesNo2->inlineKeyboard.push_back(buttons2); 

    //КЛАВИАТУРА для присоединения к группе
    TgBot::InlineKeyboardMarkup::Ptr keyboardJoin(new TgBot::InlineKeyboardMarkup);
    std::vector<TgBot::InlineKeyboardButton::Ptr> buttons3;
    TgBot::InlineKeyboardButton::Ptr JoinGroup(new TgBot::InlineKeyboardButton);
    JoinGroup->text="Присоединиться к группе.";
    JoinGroup->callbackData="JoinGroup";
    //int64_t chatId;
    //JoinGroup->url="https://t.me/yapi_test_bot?start="+std::to_string(chatId);
    buttons3.push_back(JoinGroup);
    keyboardJoin->inlineKeyboard.push_back(buttons3);


    bot.getEvents().onCallbackQuery([&bot, &keyboardYesNo1,&keyboardYesNo2](TgBot::CallbackQuery::Ptr query){
    if (query->data == "Yes1") { // так мы определяем какая кнопка была нажата
        bot.getApi().sendMessage(query->message->chat->id,"Группа создана.");
        //вернуться в меню
    }
    else if(query->data=="No1"){
        bot.getApi().sendMessage(query->message->chat->id,"Группа создана.");
        //вернуться в меню
    }
    else if (query->data == "Yes2") { // так мы определяем какая кнопка была нажата
        //удаление группы из базы данных
        bot.getApi().sendMessage(query->message->chat->id,"Группа удалена.");
        //вернуться в меню
    }
    else if(query->data=="No2"){
        //тут должно возвращаться в изначальное меню с кнопочками групп
        //вернуться в меню
    }
    else if(query->data=="JoinGroup"){
        //добавляем в базу данных пользователя, которых нажал на кнопочку
        int64_t userId=query->message->from->id;
    }  
    });

    bot.getEvents().onCommand("start", [&bot](TgBot::Message::Ptr message){
        if (message->chat->type==TgBot::Chat::Type::Group){
            bot.getApi().sendMessage(message->chat->id,"Привет, я бот, который поможет тебе структурировать всю информацию о твоих учебных предметах. \nНажимай на кнопку, и я добавлю тебя в группу, где будет храниться вся информация.");
            int64_t tg_id=message->chat->id;
            int64_t userId=message->from->id;
            userGroup[userId].set_tg_id(tg_id);
            TgBot::InlineKeyboardMarkup::Ptr keyboardJoin(new TgBot::InlineKeyboardMarkup);
            std::vector<TgBot::InlineKeyboardButton::Ptr> buttons3;
            TgBot::InlineKeyboardButton::Ptr JoinGroup(new TgBot::InlineKeyboardButton);
            JoinGroup->text="Присоединиться к группе.";
            JoinGroup->callbackData="JoinGroup";
            JoinGroup->url="https://t.me/yapi_test_bot?start="+std::to_string(tg_id);
            buttons3.push_back(JoinGroup);
            keyboardJoin->inlineKeyboard.push_back(buttons3);
            bot.getApi().sendMessage(message->chat->id,"Нажми на кнопочку и тебя добавят в группу.",false,0,keyboardJoin);
        }
    });
 
    bot.getEvents().onCommand("create_group",[&bot](TgBot::Message::Ptr message){
        int64_t userId=message->chat->id;
        userGroup[userId].set_owner_id(userId);
        bot.getApi().sendMessage(userId, "Введите название группы:");
        setState(userId,Group_State::WAITING_FOR_GROUP_NAME);
    });

    bot.getEvents().onCommand("exit_group",[&bot,&keyboardYesNo2](TgBot::Message::Ptr message){
        int64_t userId=message->chat->id;
        int64_t ownerId;
        //берем ownerId из базы данных, и userId=message->chat->id
        //Затем сравниваем ownerId и userId: Если они не равны, тогда удаляем эту группу из списка пользователя, если же равны, тогда еще раз
        //спросим точно хотите ли вы удалить группу, в которой являетесь админом
        if (ownerId!=userId){
            //удаление группы из базы данных
            bot.getApi().sendMessage(userId,"Группа удалена.");
            //вернуться в меню группы
        }
        else{
            bot.getApi().sendMessage(userId,"Вы точно хотите удалить группу, в которой являетесь владельцем?",false,0,keyboardYesNo2);
        } 
    });

    bot.getEvents().onCommand("edit_group",[&bot](TgBot::Message::Ptr message){
        int64_t userId=message->chat->id;
        int64_t ownerId;
        // Мы также сравниваем ownerId из базы данных и userId, если они равны, то пишем: введите new name, иначе если вы не админ - вы лохи
        if (ownerId==userId){
            bot.getApi().sendMessage(userId,"Введите новое название группы: ");
            setState(userId,Group_State::WAITING_FOR_NEW_GROUP_NAME);
            // в базу данных запрос на изменение имени группы
        }
        else{
            bot.getApi().sendMessage(userId,"Вы не являетесь админом группы.");
            //вернуться в меню группы
        }
    });

    bot.getEvents().onAnyMessage([&bot,&keyboardYesNo1](TgBot::Message::Ptr message){
        int64_t userId=message->chat->id;
        Group_State state=getState(userId);

        if (state==Group_State::WAITING_FOR_GROUP_NAME)
        {
            //запись названия в базу данных
            printf("Name of group: %s\n",message->text.c_str());
            userGroup[userId].set_group_name(message->text);
            bot.getApi().sendMessage(userId,"Название группы сохранено.");
            bot.getApi().sendMessage(userId,"Хотите ли вы добавить бота в чат?",false,0, keyboardYesNo1);
            setState(userId,Group_State::NONE);
            //вернуться в меню группы
        }
        else if (state==Group_State::WAITING_FOR_NEW_GROUP_NAME){
            //вводим значит new name и изменяем в базе данных
            userGroup[userId].set_group_name(message->text);
            bot.getApi().sendMessage(userId,"Новое имя группы сохранено.");
            setState(userId,Group_State::NONE);
            //вернуться в меню группы
        }
        else {
            printf("User wrote %s\n", message->text.c_str());
            if (StringTools::startsWith(message->text, "/start") ||
                StringTools::startsWith(message->text, "/create_group") ||
                StringTools::startsWith(message->text, "/exit_group") ||
                StringTools::startsWith(message->text, "/edit_group")){
                return;
            }
        }
    });

    try {
        printf("Bot username: %s\n", bot.getApi().getMe()->username.c_str());
        TgBot::TgLongPoll longPoll(bot);
        while (true){
            printf("Long poll started\n");
            longPoll.start();
        }
    } catch (TgBot::TgException& e) {
        printf("error: %s\n", e.what());
    }
    return 0;
}   

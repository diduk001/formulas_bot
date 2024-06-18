//
// Created by Stepan Didurenko on 05.06.2024.
//

#ifndef INCLUDE_CONSTANTS_H_
#define INCLUDE_CONSTANTS_H_

#include <string>

namespace consts {
// TODO(diduk001): проверять регексом в compile-time
constexpr char TOKEN[] = "...";
constexpr char DB_NAME[] = "../chinook.db";
}  // namespace consts

namespace messages {
constexpr char HI[] = "Hi!";
constexpr char CreatedGroup[] = "Группа создана.";
constexpr char DeletedGroup[] = "Группа удалена.";
constexpr char JoinChat[] =
    "Привет, я бот, который поможет тебе структурировать всю информацию о "
    "твоих учебных предметах. \nНажимай на кнопку, и я добавлю тебя в группу, "
    "где будет храниться вся информация.";
constexpr char ButtonToJoinGroup[] =
    "Нажми на кнопочку и тебя добавят в группу.";
constexpr char PrintGroupName[] = "Введите название группы:";
constexpr char PrintNewGroupName[] = "Введите новое название группы:";
constexpr char AdminDeleteGroup[] =
    "Вы точно хотите удалить группу, в которой являетесь владельцем?";
constexpr char NoAdminGroup[] = "Вы не являетесь админом группы.";
constexpr char SavedNameGroup[] = "Имя группы сохранено.";
constexpr char SavedNewNameGroup[] = "Новое имя группы сохранено.";
constexpr char QuestJoinBot[] = "Хотите ли вы добавить бота в чат?";
}  // namespace messages

namespace button_names {
constexpr char Yes[] = "Да";
constexpr char No[] = "Нет";
constexpr char GroupJoin[] = "Присоединиться к группе.";
}  // namespace button_names

namespace button_datas {
constexpr char GroupYes1[] = "Yes1";
constexpr char GroupNo1[] = "No1";
constexpr char GroupYes2[] = "Yes2";
constexpr char GroupNo2[] = "No2";
constexpr char JoinGroup[] = "JoinGroup";
}  // namespace button_datas

namespace urls {
constexpr char UrlForStartGroup[] = "https://t.me/yapi_test_bot?startgroup=1";
constexpr char UrlForChatWithBot[] = "https://t.me/yapi_test_bot?start=";
}  // namespace urls

namespace db_queries {
constexpr char basic_where_from_customers[] =
    "SELECT FirstName FROM customers WHERE Country=?";
}

#endif  // INCLUDE_CONSTANTS_H_

//
// Created by Stepan Didurenko on 05.06.2024.
//

#ifndef INCLUDE_CONSTANTS_H_
#define INCLUDE_CONSTANTS_H_

#include <string>
#include <utility>

namespace consts {
// TODO(diduk001): проверять регексом в compile-time
constexpr char TOKEN[] = "...";
constexpr char DB_NAME[] = "../chinook.db";
}  // namespace consts

namespace messages {
constexpr char HI[] = "Hi!";
constexpr char CreatedGroup[] = "Группа создана.";
constexpr char DeletedGroup[] = "Группа удалена.";
constexpr char PrintGroupName[] = "Введите название группы:";
constexpr char PrintNewGroupName[] = "Введите новое название группы:";
constexpr char SavedNameGroup[] = "Имя группы сохранено.";
constexpr char SavedNewNameGroup[] = "Новое имя группы сохранено.";
constexpr char MENU[] = "Меню.";
}  // namespace messages

namespace button_names {
constexpr char create_group[] = "Создать группу";
constexpr char edit_group[] = "Изменить имя группы";
constexpr char delete_group[] = "Удалить группу";
}  // namespace button_names

namespace button_datas {
constexpr char create_group[] = "create_group";
constexpr char edit_group[] = "edit_group";
constexpr char delete_group[] = "delete_group";
}  // namespace button_datas

namespace commands {
constexpr char START[] = "start";
constexpr char CREATEGROUP[] = "create_group";
constexpr char DELETEGROUP[] = "delete_group";
constexpr char EDITGROUP[] = "edit_group";
}  // namespace commands

namespace keyboards {
// create group
TgBot::InlineKeyboardButton::Ptr create_group(new TgBot::InlineKeyboardButton{
    button_names::create_group, {}, button_datas::create_group});
const TgBot::InlineKeyboardMarkup::Ptr create_group_keyboard(
    new TgBot::InlineKeyboardMarkup);

// edit group
TgBot::InlineKeyboardButton::Ptr edit_group(new TgBot::InlineKeyboardButton{
    button_names::edit_group, {}, button_datas::edit_group});
const TgBot::InlineKeyboardMarkup::Ptr edit_group_keyboard(
    new TgBot::InlineKeyboardMarkup);
// delete group
TgBot::InlineKeyboardButton::Ptr delete_group(new TgBot::InlineKeyboardButton{
    button_names::delete_group, {}, button_datas::delete_group});
const TgBot::InlineKeyboardMarkup::Ptr delete_group_keyboard(
    new TgBot::InlineKeyboardMarkup);

void init_keyboards() {
  create_group_keyboard->inlineKeyboard = {{std::move(create_group)}};
  delete_group_keyboard->inlineKeyboard = {{std::move(delete_group)}};
  edit_group_keyboard->inlineKeyboard = {{std::move(edit_group)}};
}
}  // namespace keyboards

namespace db_queries {
constexpr char basic_where_from_customers[] =
    "SELECT FirstName FROM customers WHERE Country=?";
}

#endif  // INCLUDE_CONSTANTS_H_

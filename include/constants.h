//
// Created by Stepan Didurenko on 05.06.2024.
//

#ifndef INCLUDE_CONSTANTS_H_
#define INCLUDE_CONSTANTS_H_

#include <string>
#include <utility>

namespace consts {
// TODO(diduk001): проверять регексом в compile-time
constexpr char token[] = "7041771878:AAF4sXHwXYmFLGfE5BFMjcvRt5KBGPlTtEw";
constexpr char dbName[] = "../chinook.db";
}  // namespace consts

namespace messages {
constexpr char welcomeMessage[] = "Привет!";
constexpr char createdGroup[] = "Группа создана.";
constexpr char deletedGroup[] = "Группа удалена.";
constexpr char enterGroupName[] = "Введите название группы:";
constexpr char enterNewGroupName[] = "Введите новое название группы:";
constexpr char groupNameSaved[] = "Имя группы сохранено.";
constexpr char newGroupNameSaved[] = "Новое имя группы сохранено.";
constexpr char MenuTitle[] = "Меню.";
}  // namespace messages

namespace button_names {
constexpr char createGroup[] = "Создать группу";
constexpr char editGroup[] = "Изменить имя группы";
constexpr char deleteGroup[] = "Удалить группу";
}  // namespace button_names

namespace button_data {
constexpr char createGroup[] = "createGroup";
constexpr char editGroup[] = "editGroup";
constexpr char deleteGroup[] = "deleteGroup";
}  // namespace button_data

namespace commands {
constexpr char start[] = "start";
constexpr char create_group[] = "create_group";
constexpr char delete_group[] = "delete_group";
constexpr char edit_group[] = "edit_group";
}  // namespace commands

namespace keyboards {
// create group
TgBot::InlineKeyboardButton::Ptr createGroup(new TgBot::InlineKeyboardButton{
    button_names::createGroup, {}, button_data::createGroup});
const TgBot::InlineKeyboardMarkup::Ptr createGroupKeyboard(
    new TgBot::InlineKeyboardMarkup);

// edit group
TgBot::InlineKeyboardButton::Ptr editGroup(new TgBot::InlineKeyboardButton{
    button_names::editGroup, {}, button_data::editGroup});
const TgBot::InlineKeyboardMarkup::Ptr editGroupKeyboard(
    new TgBot::InlineKeyboardMarkup);
// delete group
TgBot::InlineKeyboardButton::Ptr deleteGroup(new TgBot::InlineKeyboardButton{
    button_names::deleteGroup, {}, button_data::deleteGroup});
const TgBot::InlineKeyboardMarkup::Ptr deleteGroupKeyboard(
    new TgBot::InlineKeyboardMarkup);

void init_keyboards() {
  createGroupKeyboard->inlineKeyboard = {{std::move(createGroup)}};
  deleteGroupKeyboard->inlineKeyboard = {{std::move(deleteGroup)}};
  editGroupKeyboard->inlineKeyboard = {{std::move(editGroup)}};
}
}  // namespace keyboards

namespace db_queries {}

#endif  // INCLUDE_CONSTANTS_H_

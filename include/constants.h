//
// Created by Stepan Didurenko on 05.06.2024.
//

#ifndef INCLUDE_CONSTANTS_H_
#define INCLUDE_CONSTANTS_H_

#include <tgbot/tgbot.h>

#include <regex>
#include <string>
#include <unordered_set>
#include <utility>

namespace consts {
// TODO(diduk001): проверять регексом в compile-time
constexpr char token[] = "7041771878:AAF4sXHwXYmFLGfE5BFMjcvRt5KBGPlTtEw";
constexpr char dbName[] = "../chinook.db";
}  // namespace consts

namespace messages {
// making
constexpr char disciplineMakingNew[] = "Вы создаете новую дисциплину";
constexpr char disciplineMakingCanceled[] = "Создание дисциплины отменено";
constexpr char disciplineIsSaved[] = "Дисциплина сохранена в базе данных";
// description
constexpr char disciplineHaveNoDescription[] = "В дисциплине не будет описания";
constexpr char checkDiscipline[] = "Информация записана правильно?";
// enter
constexpr char disciplineEnterName[] = "Введите название дисциплины";
constexpr char disciplineEnterFullName[] = "Введите ФИ(О) преподавателя";
constexpr char disciplineEnterEmail[] = "Введите почту преподавателя";
constexpr char disciplineEnterDescription[] = "Введите описания предмета";
// saved
constexpr char disciplineProfessorNameSaved[] = "Имя преподавателя сохранено";
constexpr char disciplineNameSaved[] = "Название дисциплины сохранено";
constexpr char disciplineEmailSaved[] = "Электронная почта сохранена";
constexpr char disciplineSaved[] = "Данные записаны правильно?";
// wrong
constexpr char disciplineWrongNameLength[] =
    "Неправильная длина дисциплины\nДлина должна быть более:";
constexpr char disciplineWrongFullName[] = "Неправильный формат ввода ФИ(О)";
constexpr char disciplineWrongEmail[] =
    "Проверьте правильность ввода почты, впишите ее еще раз";
constexpr char disciplineWrongDescription[] =
    "Максимальная длина для описания {}";

constexpr char discipline_what_want_to_do[] = "Что вы хотите сделать?";
constexpr char welcomeMessage[] = "Привет!";
constexpr char createdGroup[] = "Группа создана.";
constexpr char deletedGroup[] = "Группа удалена.";
constexpr char enterGroupName[] = "Введите название группы:";
constexpr char enterNewGroupName[] = "Введите новое название группы:";
constexpr char groupNameSaved[] = "Имя группы сохранено.";
constexpr char newGroupNameSaved[] = "Новое имя группы сохранено.";
constexpr char MenuTitle[] = "Меню.";
}  // namespace messages

namespace commands {
constexpr char start[] = "start";
constexpr char create_group[] = "create_group";
constexpr char delete_group[] = "delete_group";
constexpr char edit_group[] = "edit_group";
constexpr char make_discipline[] = "make_discipline";

const std::unordered_set<std::string> commands({start, create_group,
                                                delete_group, edit_group,
                                                make_discipline});
}  // namespace commands

namespace db_queries {}

namespace regular_expressions {
const std::regex pattern(
    R"(\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Z|a-z]{2,}\b)");
}

namespace button_names {
constexpr char makeDiscipline[] = "Создать дисциплину";
constexpr char stopMakingDiscipline[] = "Прервать создание дисциплины";
constexpr char buttonYes[] = "Да";
constexpr char buttonNo[] = "Нет";
constexpr char dontAddDescription[] = "Не добавлять описание";
constexpr char createGroup[] = "Создать группу";
constexpr char editGroup[] = "Изменить имя группы";
constexpr char deleteGroup[] = "Удалить группу";
}  // namespace button_names

namespace button_data {
constexpr char makeDiscipline[] = "makeDiscipline";
constexpr char stopMakingDiscipline[] = "stopMakingDiscipline";
constexpr char disciplineConfirmed[] = "disciplineConfirmed";
constexpr char disciplineNotConfirmed[] = "disciplineNotConfirmed";
constexpr char dontAddDescription[] = "dontAddDescription";
constexpr char createGroup[] = "createGroup";
constexpr char editGroup[] = "editGroup";
constexpr char deleteGroup[] = "deleteGroup";
}  // namespace button_data

namespace standard_text {
constexpr char description_standard[] = "Отсутствует";
}

namespace lengths {
size_t max_discipline_name_length = 40;
size_t min_discipline_name_length = 1;
size_t minimal_space_count_in_name = 1;
size_t max_description_len = 500;
}  // namespace lengths

namespace keyboards {
// making discipline
TgBot::InlineKeyboardButton::Ptr make_discipline(
    new TgBot::InlineKeyboardButton{
        button_names::makeDiscipline,
        {},
        button_data::makeDiscipline,
    });
const TgBot::InlineKeyboardMarkup::Ptr making_discipline_keyboard(
    new TgBot::InlineKeyboardMarkup);

TgBot::InlineKeyboardButton::Ptr stop_making_discipline(
    new TgBot::InlineKeyboardButton{
        button_names::stopMakingDiscipline,
        {},
        button_data::stopMakingDiscipline,
    });
const TgBot::InlineKeyboardMarkup::Ptr stop_making_discipline_keyboard(
    new TgBot::InlineKeyboardMarkup);

TgBot::InlineKeyboardButton::Ptr discipline_confirmation_yes(
    new TgBot::InlineKeyboardButton{
        button_names::buttonYes,
        {},
        button_data::disciplineConfirmed,
    });
TgBot::InlineKeyboardButton::Ptr discipline_confirmation_no(
    new TgBot::InlineKeyboardButton{
        button_names::buttonNo,
        {},
        button_data::disciplineNotConfirmed,
    });
const TgBot::InlineKeyboardMarkup::Ptr discipline_confirmation_keyboard(
    new TgBot::InlineKeyboardMarkup);

TgBot::InlineKeyboardButton::Ptr dont_add_description(
    new TgBot::InlineKeyboardButton{
        button_names::dontAddDescription,
        {},
        button_data::dontAddDescription,
    });
const TgBot::InlineKeyboardMarkup::Ptr dont_add_description_keyboard(
    new TgBot::InlineKeyboardMarkup);

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
  making_discipline_keyboard->inlineKeyboard = {{std::move(make_discipline)}};
  stop_making_discipline_keyboard->inlineKeyboard = {
      {std::move(stop_making_discipline)}};
  discipline_confirmation_keyboard->inlineKeyboard = {
      {std::move(discipline_confirmation_yes),
       std::move(discipline_confirmation_no)}};
  dont_add_description_keyboard->inlineKeyboard = {
      {std::move(dont_add_description)}};
  createGroupKeyboard->inlineKeyboard = {{std::move(createGroup)}};
  deleteGroupKeyboard->inlineKeyboard = {{std::move(deleteGroup)}};
  editGroupKeyboard->inlineKeyboard = {{std::move(editGroup)}};
}

}  // namespace keyboards
#endif  // INCLUDE_CONSTANTS_H_

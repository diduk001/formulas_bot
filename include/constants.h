//
// Created by Stepan Didurenko on 05.06.2024.
//

#ifndef INCLUDE_CONSTANTS_H_
#define INCLUDE_CONSTANTS_H_

#include <string>
#include <regex>
#include <tgbot/tgbot.h>

namespace consts {
// TODO(diduk001): проверять регексом в compile-time
constexpr char TOKEN[] = "...";
constexpr char DB_NAME[] = "../chinook.db";
}  // namespace consts
namespace messages {
constexpr char HI[] = "Здарова шершень";
// making
constexpr char discipline_making_new[] = "Вы создаете новую дисциплину";
constexpr char discipline_making_canceled[] = "Создание дисциплины отменено";
constexpr char discipline_is_saved[] = "Дисциплина сохранена в базе данных";
//description
constexpr char discipline_have_no_description[] = "В дисциплине не будет описания";
constexpr char discipline_is_correct_description[] = "Информация записана правильно?";
// enter
constexpr char discipline_enter_name[] = "Введите название дисциплины";
constexpr char discipline_enter_full_name[] = "Введите ФИ(О) преподавателя";
constexpr char discipline_enter_email[] = "Введите почту преподавателя";
constexpr char discipline_enter_description[] = "Введите описания предмета";
// saved
constexpr char discipline_professor_name_saved[] = "Имя преподавателя сохранено";
constexpr char discipline_name_saved[] = "Название дисциплины сохранено";
constexpr char discipline_email_saved[] = "Электронная почта сохранена";
constexpr char discipline_saved[] = "Проверьте правильность данных:";
// wrong
constexpr char discipline_wrong_name_length[] = "Неправильная длина дисциплины\nДлина должна быть более: ";
constexpr char discipline_wrong_full_name[] = "Неправильный формат ввода ФИ(О)";
constexpr char discipline_wrong_email[] = "Проверьте правильность ввода почты, впишите ее еще раз";
constexpr char discipline_wrong_describe[] = "Максимальная длина для описания {}";

constexpr char discipline_what_want_to_do[] = "Что вы хотите сделать?";
}

namespace db_queries {
constexpr char basic_where_from_customers[] =
    "SELECT FirstName FROM customers WHERE Country=?";
}

namespace regular_expressions {
const std::regex pattern(R"(\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Z|a-z]{2,}\b)");
}

namespace button_names {
constexpr char make_discipline[] = "Создать дисциплину";
constexpr char stop_making_discipline[] = "Прервать создание дисциплины";
constexpr char button_yes[] = "Да";
constexpr char button_no[] = "Нет";
constexpr char dont_add_description[] = "Не добавлять описание";
}

namespace button_data {
constexpr char make_discipline[] = "make discipline";
constexpr char stop_making_discipline[] = "stop making discipline";
constexpr char correct_description_yes[] = "description is correct";
constexpr char correct_description_no[] = "description is not correct";
constexpr char dont_add_description[] = "dont add";
}

namespace standard_text {
constexpr char description_standard[] = "Отсутствует";
}

namespace lengths {
size_t max_discipline_name_length = 40;
size_t min_discipline_name_length = 1;
size_t minimal_space_count_in_PHIO = 1;
size_t max_description_len = 500;
}

namespace keyboards {
// making discipline
TgBot::InlineKeyboardButton::Ptr make_discipline(new TgBot::InlineKeyboardButton{
    button_names::make_discipline,
    {},
    button_data::make_discipline,
});
const TgBot::InlineKeyboardMarkup::Ptr making_discipline_keyboard(new TgBot::InlineKeyboardMarkup);

void init_keyboards() {
  making_discipline_keyboard->inlineKeyboard = {{std::move(make_discipline)}};
}

}
#endif  // INCLUDE_CONSTANTS_H_

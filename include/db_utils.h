#ifndef INCLUDE_DB_UTILS_H_
#define INCLUDE_DB_UTILS_H_

#include <sqlite3.h>

#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "constants.h"

namespace db {
sqlite3 *db_conn;

void init_conn() {
  // TODO(diduk001): придумать, как тут использовать std::unique_ptr
  int rc = sqlite3_open(consts::dbName, &db_conn);
  if (rc != SQLITE_OK) {
    sqlite3_close(db_conn);
    throw std::runtime_error("Error while connecting db");
  }
}

void close_conn() { sqlite3_close(db_conn); }

TgBot::InlineKeyboardMarkup::Ptr make_MainMenuKeyboard(const TgBot::Bot &bot) {
  // открываем бд

  // Создаем запрос который даст нам имена всех груп пользователя
  // В соответствии с запросом берем из бд имена и конвертируем их в кнопки
  const TgBot::InlineKeyboardMarkup::Ptr MenuKeyboard(
      new TgBot::InlineKeyboardMarkup);
  /*
  while (sqlite3_step(statement) == SQLITE_ROW) {
      TgBot::InlineKeyboardButton::Ptr GroupButton(new
  TgBot::InlineKeyboardButton); GroupButton->text = reinterpret_cast<const char
  *>(sqlite3_column_text(statement, 1)); GroupButton->callbackData=
  std::to_string(sqlite3_column_int(statement, 0)); MenuKeyboard->inlineKeyboard
  = {{std::move(GroupButton)}};
  }*/

  MenuKeyboard->inlineKeyboard = {{std::move(keyboards::createGroup)}};

  // закрываем бд
  return MenuKeyboard;
}

}  // namespace db

#endif  // INCLUDE_DB_UTILS_H_

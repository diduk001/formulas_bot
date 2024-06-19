#include <tgbot/tgbot.h>

#include <cstdio>

#include "../include/constants.h"
#include "../include/db_utils.h"
#include "../include/group.h"
#include "../include/state_utils.h"
using keyboards::create_group_keyboard;
using keyboards::delete_group_keyboard;
using keyboards::edit_group_keyboard;

int main() {
  keyboards::init_keyboards();
  db::init_conn();

  TgBot::Bot bot(consts::TOKEN);

  // Stepan's piece

  bot.getEvents().onCallbackQuery(
      [&bot, create_group_keyboard, delete_group_keyboard,
       edit_group_keyboard](TgBot::CallbackQuery::Ptr query) {
        if (query->data == button_datas::create_group) {
          int64_t userId = query->message->chat->id;
          getGroup(userId)->set_owner_id(userId);
          bot.getApi().sendMessage(userId, messages::PrintGroupName);
          setState(userId, Group_State::WAITING_FOR_GROUP_NAME);
        } else if (query->data == button_datas::delete_group) {
          int64_t userId = query->message->chat->id;
          // удаление группы из базы данных
          bot.getApi().sendMessage(userId, messages::DeletedGroup);
        } else if (query->data == button_datas::edit_group) {
          int64_t userId = query->message->chat->id;
          bot.getApi().sendMessage(userId, messages::PrintNewGroupName);
          setState(userId, Group_State::WAITING_FOR_NEW_GROUP_NAME);
        }
      });

  bot.getEvents().onCommand(
      commands::START, [&bot](TgBot::Message::Ptr message) {
        if (message->chat->type == TgBot::Chat::Type::Private) {
          bot.getApi().sendMessage(message->chat->id, messages::HI);
        }
      });

  bot.getEvents().onCommand(
      commands::CREATEGROUP,
      [&bot, create_group_keyboard](TgBot::Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id, messages::MENU, nullptr,
                                 nullptr, create_group_keyboard);
      });

  bot.getEvents().onCommand(
      commands::DELETEGROUP,
      [&bot, delete_group_keyboard](TgBot::Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id, messages::MENU, nullptr,
                                 nullptr, delete_group_keyboard);
      });

  bot.getEvents().onCommand(
      commands::EDITGROUP,
      [&bot, edit_group_keyboard](TgBot::Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id, messages::MENU, nullptr,
                                 nullptr, edit_group_keyboard);
      });

  bot.getEvents().onAnyMessage([&bot](TgBot::Message::Ptr message) {
    int64_t userId = message->chat->id;
    Group_State state = getState(userId);

    switch (state) {
      case Group_State::WAITING_FOR_GROUP_NAME:
        // запись названия в базу данных
        printf("Name of group: %s\n", message->text.c_str());
        getGroup(userId)->set_group_name(message->text);
        bot.getApi().sendMessage(userId, messages::SavedNameGroup);
        bot.getApi().sendMessage(userId, messages::CreatedGroup);
        setState(userId, Group_State::NONE);
        // вернуться в меню группы
        break;
      case Group_State::WAITING_FOR_NEW_GROUP_NAME:
        // вводим значит new name и изменяем в базе данных
        getGroup(userId)->set_group_name(message->text);
        bot.getApi().sendMessage(userId, messages::SavedNewNameGroup);
        setState(userId, Group_State::NONE);
        // вернуться в меню группы
        break;
      default:
        printf("User wrote %s\n", message->text.c_str());
        break;
    }
  });

  try {
    printf("Bot username: %s\n", bot.getApi().getMe()->username.c_str());
    TgBot::TgLongPoll longPoll(bot);
    while (true) {
      printf("Long poll started\n");
      longPoll.start();
    }
  } catch (TgBot::TgException& e) {
    printf("error: %s\n", e.what());
  }

  return 0;
}

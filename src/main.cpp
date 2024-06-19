#include <tgbot/tgbot.h>

#include <cstdio>

#include "../include/constants.h"
#include "../include/db_utils.h"
#include "../include/group.h"
#include "../include/state.h"

int main() {
  keyboards::init_keyboards();
  const auto& createGroupKeyboard = keyboards::createGroupKeyboard;
  const auto& deleteGroupKeyboard = keyboards::deleteGroupKeyboard;
  const auto& editGroupKeyboard = keyboards::editGroupKeyboard;

  db::init_conn();

  TgBot::Bot bot(consts::token);

  bot.getEvents().onCallbackQuery(
      [&bot, createGroupKeyboard, deleteGroupKeyboard,
       editGroupKeyboard](const TgBot::CallbackQuery::Ptr& query) {
        int64_t userId = query->message->chat->id;
        if (query->data == button_data::createGroup) {
          getGroup(userId)->set_owner_id(userId);
          bot.getApi().sendMessage(userId, messages::enterGroupName);
          setGroupState(userId, GroupState::WAITING_FOR_GROUP_NAME);
        } else if (query->data == button_data::deleteGroup) {
          // удаление группы из базы данных
          bot.getApi().sendMessage(userId, messages::deletedGroup);
        } else if (query->data == button_data::editGroup) {
          bot.getApi().sendMessage(userId, messages::enterNewGroupName);
          setGroupState(userId, GroupState::WAITING_FOR_NEW_GROUP_NAME);
        }
      });

  bot.getEvents().onCommand(
      commands::start, [&bot](const TgBot::Message::Ptr& message) {
        if (message->chat->type == TgBot::Chat::Type::Private) {
          bot.getApi().sendMessage(message->chat->id, messages::welcomeMessage);
        }
      });

  bot.getEvents().onCommand(
      commands::create_group,
      [&bot, createGroupKeyboard](const TgBot::Message::Ptr& message) {
        bot.getApi().sendMessage(message->chat->id, messages::MenuTitle,
                                 nullptr, nullptr, createGroupKeyboard);
      });

  bot.getEvents().onCommand(
      commands::delete_group,
      [&bot, deleteGroupKeyboard](const TgBot::Message::Ptr& message) {
        bot.getApi().sendMessage(message->chat->id, messages::MenuTitle,
                                 nullptr, nullptr, deleteGroupKeyboard);
      });

  bot.getEvents().onCommand(
      commands::edit_group,
      [&bot, editGroupKeyboard](const TgBot::Message::Ptr& message) {
        bot.getApi().sendMessage(message->chat->id, messages::MenuTitle,
                                 nullptr, nullptr, editGroupKeyboard);
      });

  bot.getEvents().onAnyMessage([&bot](const TgBot::Message::Ptr& message) {
    int64_t userId = message->chat->id;
    GroupState state = getGroupState(userId);

    switch (state) {
      case GroupState::WAITING_FOR_GROUP_NAME:
        // запись названия в базу данных
        printf("Name of group: %s\n", message->text.c_str());
        getGroup(userId)->set_group_name(message->text);
        bot.getApi().sendMessage(userId, messages::groupNameSaved);
        bot.getApi().sendMessage(userId, messages::createdGroup);
        setGroupState(userId, GroupState::NONE);
        // вернуться в меню группы
        break;
      case GroupState::WAITING_FOR_NEW_GROUP_NAME:
        // вводим значит new name и изменяем в базе данных
        getGroup(userId)->set_group_name(message->text);
        bot.getApi().sendMessage(userId, messages::newGroupNameSaved);
        setGroupState(userId, GroupState::NONE);
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

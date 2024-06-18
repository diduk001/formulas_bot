#include <tgbot/tgbot.h>

#include <cstdio>

#include "../include/constants.h"
#include "../include/db_utils.h"
#include "../include/models/group.h"
#include "../include/state_utils.h"

std::unordered_map<int64_t, Group> userGroup;

int main() {
  db::init_conn();

  TgBot::Bot bot(consts::TOKEN);
  
  bot.getEvents().onAnyMessage([&bot](TgBot::Message::Ptr message) {
    printf("User wrote %s\n", message->text.c_str());
    if (StringTools::startsWith(message->text, '/'+commands::START)) {
      return;
    }
    const auto query_result = db::basic_where(message->text);
    bot.getApi().sendMessage(message->chat->id,
                             std::to_string(query_result.size()));
    for (const std::string& res : query_result) {
      bot.getApi().sendMessage(message->chat->id, res);
    }
  });

  // Stepan's piece

  // КЛАВИАТУРА для ответа да/нет 1
  TgBot::InlineKeyboardMarkup::Ptr keyboardYesNo1(
      new TgBot::InlineKeyboardMarkup);
  std::vector<TgBot::InlineKeyboardButton::Ptr> buttons1;
  TgBot::InlineKeyboardButton::Ptr AnswerYes1(new TgBot::InlineKeyboardButton);
  AnswerYes1->text = button_names::Yes;
  AnswerYes1->callbackData = button_datas::GroupYes1;
  AnswerYes1->url = urls::UrlForStartGroup;
  buttons1.emplace_back(AnswerYes1);
  TgBot::InlineKeyboardButton::Ptr AnswerNo1(new TgBot::InlineKeyboardButton);
  AnswerNo1->text = button_names::No;
  AnswerNo1->callbackData = button_datas::GroupNo1;
  buttons1.emplace_back(AnswerNo1);
  keyboardYesNo1->inlineKeyboard.push_back(buttons1);

  // КЛАВИАТУРА для ответа да/нет 2
  TgBot::InlineKeyboardMarkup::Ptr keyboardYesNo2(
      new TgBot::InlineKeyboardMarkup);
  std::vector<TgBot::InlineKeyboardButton::Ptr> buttons2;
  TgBot::InlineKeyboardButton::Ptr AnswerYes2(new TgBot::InlineKeyboardButton);
  AnswerYes2->text = button_names::Yes;
  AnswerYes2->callbackData = button_datas::GroupYes2;
  buttons2.emplace_back(AnswerYes2);
  TgBot::InlineKeyboardButton::Ptr AnswerNo2(new TgBot::InlineKeyboardButton);
  AnswerNo2->text = button_names::No;
  AnswerNo2->callbackData = button_datas::GroupNo2;
  buttons2.emplace_back(AnswerNo2);
  keyboardYesNo2->inlineKeyboard.push_back(buttons2);

  bot.getEvents().onCallbackQuery([&bot, &keyboardYesNo1, &keyboardYesNo2](
                                      TgBot::CallbackQuery::Ptr query) {
    if (query->data == button_datas::GroupYes1) {
      bot.getApi().sendMessage(query->message->chat->id,
                               messages::CreatedGroup);
      // вернуться в меню
    } else if (query->data == button_datas::GroupNo1) {
      bot.getApi().sendMessage(query->message->chat->id,
                               messages::CreatedGroup);
      // вернуться в меню
    } else if (query->data == button_datas::GroupYes2) {
      // удаление группы из базы данных
      bot.getApi().sendMessage(query->message->chat->id,
                               messages::DeletedGroup);
      // вернуться в меню
    } else if (query->data == button_datas::GroupNo2) {
      // тут должно возвращаться в изначальное меню с кнопочками групп
      // вернуться в меню
    } else if (query->data == button_datas::JoinGroup) {
      // добавляем в базу данных пользователя, которых нажал на кнопочку
    }
  });

  bot.getEvents().onCommand(commands::START, [&bot](TgBot::Message::Ptr message) {
    if (message->chat->type == TgBot::Chat::Type::Group) {
      bot.getApi().sendMessage(message->chat->id, messages::JoinChat);
      int64_t tg_id = message->chat->id;
      int64_t userId = message->from->id;
      userGroup[userId].set_tg_id(tg_id);
      TgBot::InlineKeyboardMarkup::Ptr keyboardJoin(
          new TgBot::InlineKeyboardMarkup);
      std::vector<TgBot::InlineKeyboardButton::Ptr> buttons3;
      TgBot::InlineKeyboardButton::Ptr JoinGroup(
          new TgBot::InlineKeyboardButton);
      JoinGroup->text = button_names::GroupJoin;
      JoinGroup->callbackData = button_datas::JoinGroup;
      JoinGroup->url = urls::UrlForChatWithBot + std::to_string(tg_id);
      buttons3.emplace_back(JoinGroup);
      keyboardJoin->inlineKeyboard.push_back(buttons3);
      bot.getApi().sendMessage(message->chat->id, messages::ButtonToJoinGroup,
                               NULL, 0, keyboardJoin);
    } else if (message->chat->type == TgBot::Chat::Type::Private) {
      bot.getApi().sendMessage(message->chat->id, messages::HI);
    }
  });

  bot.getEvents().onCommand(
      commands::CREATEGROUP, [&bot](TgBot::Message::Ptr message) {
        int64_t userId = message->chat->id;
        userGroup[userId].set_owner_id(userId);
        bot.getApi().sendMessage(userId, messages::PrintGroupName);
        setState(userId, Group_State::WAITING_FOR_GROUP_NAME);
      });

  bot.getEvents().onCommand(
      commands::EXITGROUP, [&bot, &keyboardYesNo2](TgBot::Message::Ptr message) {
        int64_t userId = message->chat->id;
        int64_t ownerId = -1;
        // берем ownerId из базы данных, и userId=message->chat->id
        // Затем сравниваем ownerId и userId: Если они не равны, тогда удаляем
        // эту группу из списка пользователя, если же равны, тогда еще раз
        // спросим точно хотите ли вы удалить группу, в которой являетесь
        // админом
        if (ownerId != userId) {
          // удаление группы из базы данных
          bot.getApi().sendMessage(userId, messages::DeletedGroup);
          // вернуться в меню группы
        } else {
          bot.getApi().sendMessage(userId, messages::AdminDeleteGroup, NULL, 0,
                                   keyboardYesNo2);
        }
      });

  bot.getEvents().onCommand(commands::EDITGROUP, [&bot](TgBot::Message::Ptr message) {
    int64_t userId = message->chat->id;
    int64_t ownerId = -1;
    // Мы также сравниваем ownerId из базы данных и userId, если они равны, то
    // пишем: введите new name, иначе если вы не админ - вы лохи
    if (ownerId == userId) {
      bot.getApi().sendMessage(userId, messages::PrintNewGroupName);
      setState(userId, Group_State::WAITING_FOR_NEW_GROUP_NAME);
      // в базу данных запрос на изменение имени группы
    } else {
      bot.getApi().sendMessage(userId, messages::NoAdminGroup);
      // вернуться в меню группы
    }
  });

  bot.getEvents().onAnyMessage(
      [&bot, &keyboardYesNo1](TgBot::Message::Ptr message) {
        int64_t userId = message->chat->id;
        Group_State state = getState(userId);

        if (state == Group_State::WAITING_FOR_GROUP_NAME) {
          // запись названия в базу данных
          printf("Name of group: %s\n", message->text.c_str());
          userGroup[userId].set_group_name(message->text);
          bot.getApi().sendMessage(userId, messages::SavedNameGroup);
          bot.getApi().sendMessage(userId, messages::QuestJoinBot, NULL, 0,
                                   keyboardYesNo1);
          setState(userId, Group_State::NONE);
          // вернуться в меню группы
        } else if (state == Group_State::WAITING_FOR_NEW_GROUP_NAME) {
          // вводим значит new name и изменяем в базе данных
          userGroup[userId].set_group_name(message->text);
          bot.getApi().sendMessage(userId, messages::SavedNewNameGroup);
          setState(userId, Group_State::NONE);
          // вернуться в меню группы
        } else {
          printf("User wrote %s\n", message->text.c_str());
          if (StringTools::startsWith(message->text, '/'+commands::START) ||
              StringTools::startsWith(message->text, '/'+commands::CREATEGROUP) ||
              StringTools::startsWith(message->text, '/'+commands::EXITGROUP) ||
              StringTools::startsWith(message->text, '/'+commands::EDITGROUP)) {
            return;
          }
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

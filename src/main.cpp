#include <tgbot/tgbot.h>

#include <format>

#include <cstdio>

#include "../include/constants.h"
#include "../include/db_utils.h"
#include "../include/state.h"
#include "../include/utils.h"

using keyboards::making_discipline_keyboard;
using keyboards::stop_making_discipline_keyboard;
using keyboards::discipline_confirmation_keyboard;
using keyboards::dont_add_description_keyboard;

int main() {
  keyboards::init_keyboards();
  db::init_conn();

  TgBot::Bot bot(consts::TOKEN);
  bot.getEvents().onCallbackQuery([&bot, &stop_making_discipline_keyboard,
                                   &discipline_confirmation_keyboard,
                                   &dont_add_description_keyboard](
                                      const TgBot::CallbackQuery::Ptr& query) {
    int64_t userId = query->message->chat->id;
    if (query->data == button_data::make_discipline) {
      bot.getApi().sendMessage(userId, messages::discipline_making_new);
      bot.getApi().sendMessage(userId, messages::discipline_enter_name, nullptr,
                               nullptr, stop_making_discipline_keyboard);
      setState(userId, State::WAITING_FOR_NAME);
    } else if (query->data == button_data::stop_making_discipline) {
      bot.getApi().sendMessage(userId, messages::discipline_making_canceled);
      setState(userId, State::NONE);
      eraseStateAndSubject(userId);
    } else if (query->data == button_data::discipline_confirmation_no) {
      bot.getApi().sendMessage(userId, messages::discipline_enter_name, nullptr,
                               nullptr, stop_making_discipline_keyboard);
      setState(userId, State::WAITING_FOR_NAME);
    } else if (query->data == button_data::discipline_confirmation_yes) {
      bot.getApi().sendMessage(userId, messages::discipline_is_saved);
    } else if (query->data == button_data::dont_add_description) {
      bot.getApi().sendMessage(userId,
                               messages::discipline_have_no_description);
      getSubject(userId)->set_description(standard_text::description_standard);
      bot.getApi().sendMessage(userId, getSubject(userId)->print_all());
      bot.getApi().sendMessage(
          userId, messages::discipline_is_correct_description, nullptr, nullptr,
          discipline_confirmation_keyboard);
      setState(userId, State::NONE);
    }
  });

  bot.getEvents().onCommand("start", [&bot, making_discipline_keyboard](
                                         const TgBot::Message::Ptr& message) {
    bot.getApi().sendMessage(message->chat->id,
                             messages::discipline_what_want_to_do, nullptr,
                             nullptr, making_discipline_keyboard);
  });

  bot.getEvents().onCommand(
      "make_discipline", [&bot, stop_making_discipline_keyboard](
                             const TgBot::Message::Ptr& message) {
        int64_t userId = message->chat->id;
        bot.getApi().sendMessage(userId, messages::discipline_making_new,
                                 nullptr, nullptr,
                                 stop_making_discipline_keyboard);
        setState(userId, State::WAITING_FOR_NAME);
      });

  bot.getEvents().onAnyMessage([&bot, stop_making_discipline_keyboard,
                                discipline_confirmation_keyboard,
                                dont_add_description_keyboard](
                                   const TgBot::Message::Ptr& message) {
    int64_t userId = message->chat->id;
    State state = getState(userId);

    switch (state) {
      case State::WAITING_FOR_NAME:
        if (message->text.length() <= lengths::max_discipline_name_length &&
            message->text.length() >= lengths::min_discipline_name_length) {
          getSubject(userId)->set_subject_name(message->text);
          bot.getApi().sendMessage(userId, messages::discipline_name_saved,
                                   nullptr, nullptr);
          setState(userId, State::WAITING_FOR_PROFESSOR_NAME);
          bot.getApi().sendMessage(userId, messages::discipline_enter_full_name,
                                   nullptr, nullptr,
                                   stop_making_discipline_keyboard);
        } else {
          bot.getApi().sendMessage(userId,
                                   messages::discipline_wrong_name_length);
        }
        break;
      case State::WAITING_FOR_PROFESSOR_NAME:
      {
        int16_t spaceCount =
            std::count(message->text.begin(), message->text.end(), ' ');
        if (spaceCount >= lengths::minimal_space_count_in_name) {
          getSubject(userId)->set_professor_name(message->text);
          bot.getApi().sendMessage(
              userId, messages::discipline_professor_name_saved, nullptr, nullptr,
              stop_making_discipline_keyboard);
          setState(userId, State::WAITING_FOR_PROFESSOR_EMAIL);
          bot.getApi().sendMessage(userId, messages::discipline_enter_email,
                                   nullptr, nullptr);
        } else {
          bot.getApi().sendMessage(userId, messages::discipline_wrong_full_name);
        }
      }
      break;
      case State::WAITING_FOR_PROFESSOR_EMAIL:
        if (utils::isValidEmail(message->text)) {
          getSubject(userId)->set_professor_email(message->text);
          bot.getApi().sendMessage(userId, messages::discipline_email_saved,
                                   nullptr, nullptr,
                                   stop_making_discipline_keyboard);
          setState(userId, State::WAITING_FOR_DESCRIPTION);
          bot.getApi().sendMessage(userId, messages::discipline_enter_description,
                                   nullptr, nullptr,
                                   dont_add_description_keyboard);
        } else {
          bot.getApi().sendMessage(userId, messages::discipline_wrong_email);
        }
        break;
      case State::WAITING_FOR_DESCRIPTION:
        if (message->text.length() < lengths::max_description_len) {
          getSubject(userId)->set_description(message->text);
          bot.getApi().sendMessage(userId, messages::discipline_saved, nullptr,
                                   nullptr, discipline_confirmation_keyboard);
          bot.getApi().sendMessage(userId, getSubject(userId)->print_all());
          bot.getApi().sendMessage(userId, messages::discipline_saved, nullptr,
                                   nullptr, discipline_confirmation_keyboard);
          setState(userId, State::NONE);
        } else {
          bot.getApi().sendMessage(
              userId, std::format(messages::discipline_wrong_describe,
                                  lengths::max_description_len));
        }
        break;
      default:
        printf("User wrote %s\n", message->text.c_str());
        if (StringTools::startsWith(message->text, "/start") ||
            StringTools::startsWith(message->text, "/make_discipline")) {
          return;
        }
        break;
    }
  });

  bot.getEvents().onAnyMessage([&bot](const TgBot::Message::Ptr& message) {
    printf("User wrote %s\n", message->text.c_str());
    if (StringTools::startsWith(message->text, "/start")) {
      return;
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

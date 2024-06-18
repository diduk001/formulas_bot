#include <tgbot/tgbot.h>

#include <cstdio>
#include "../include/constants.h"
#include "../include/db_utils.h"
using namespace keyboards;

int main() {
  keyboards::init_keyboards();
  db::init_conn();

  TgBot::Bot bot(consts::TOKEN);
  bot.getEvents().onCommand("start", [&bot, &making_discipline_keyboard](TgBot::Message::Ptr message) {
    bot.getApi().sendMessage(message->chat->id, messages::HI, nullptr, nullptr, making_discipline_keyboard);
  });
  bot.getEvents().onAnyMessage([&bot](const TgBot::Message::Ptr& message) {
    printf("User wrote %s\n", message->text.c_str());
    if (StringTools::startsWith(message->text, "/start")) {
      return;
    }
    const auto query_result = db::basic_where(message->text);
    bot.getApi().sendMessage(message->chat->id,
                             std::to_string(query_result.size()));
    for (const std::string& res : query_result) {
      bot.getApi().sendMessage(message->chat->id, res);
    }
    return;
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

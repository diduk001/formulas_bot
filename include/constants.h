//
// Created by Stepan Didurenko on 05.06.2024.
//

#ifndef FORMULAS_BOT_CONSTANTS_H
#define FORMULAS_BOT_CONSTANTS_H

#include <string>

namespace consts {
    const std::string TOKEN = "7041771878:AAEtRcUXq5mzxGg0imb52ucMR-o4rKDdeYA";
    const std::string DB_NAME = "../chinook.db";
}

namespace messages {
    const std::string HI = "Hi!";
}

namespace db_queries {
    const std::string basic_where_from_customers = "SELECT FirstName FROM customers WHERE Country=?";
}

#endif //FORMULAS_BOT_CONSTANTS_H

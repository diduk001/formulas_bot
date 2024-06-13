//
// Created by Stepan Didurenko on 05.06.2024.
//

#ifndef INCLUDE_CONSTANTS_H_
#define INCLUDE_CONSTANTS_H_

#include <string>

namespace consts {
// TODO(diduk001): проверять регексом в compile-time
constexpr char TOKEN[] = "...";
constexpr char DB_NAME[] = "../chinook.db";
}  // namespace consts

namespace messages {
constexpr char HI[] = "Hi!";
}

namespace db_queries {
constexpr char basic_where_from_customers[] =
    "SELECT FirstName FROM customers WHERE Country=?";
}

#endif  // INCLUDE_CONSTANTS_H_

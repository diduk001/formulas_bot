//
// Created by Stepan Didurenko on 05.06.2024.
//

#ifndef FORMULAS_BOT_CONSTANTS_H
#define FORMULAS_BOT_CONSTANTS_H

#include <string>

namespace consts {
    const std::string TOKEN = "...";
    const std::string DB_NAME = "../chinook.db";
}

namespace messages {
    const std::string HI = "Hi!";
}

namespace db_queries {
    //Select
    const std::string basic_where_from_customers = "SELECT FirstName FROM customers WHERE Country=?";
    const std::string basic_where_from_element = "SELECT * FROM Element WHERE element_id = ?";

    //Create
    const std::string create_table_user = "CREATE TABLE IF NOT EXISTS user (user_id INTEGER PRIMARY KEY, tg_id INTEGER)";
    const std::string create_table_group = "CREATE TABLE IF NOT EXISTS `group` (group_id INTEGER PRIMARY KEY,"
                                           " group_name TEXT, tg_id INTEGER, owner_id INTEGER, FOREIGN KEY (owner_id) REFERENCES user (user_id))";
    const std::string create_table_subject = "CREATE TABLE IF NOT EXISTS subject (subject_id INTEGER PRIMARY KEY, subject_name TEXT, group_id INTEGER,"
                                             " description TEXT, professor_name TEXT, professor_email TEXT, FOREIGN KEY (group_id) REFERENCES `group` (group_id))";
    const std::string create_table_element = "CREATE TABLE IF NOT EXISTS element (element_id INTEGER PRIMARY KEY, name TEXT, subject_id INTEGER, value REAL,"
                                             " block INTEGER, description TEXT, FOREIGN KEY (subject_id) REFERENCES subject (subject_id))";
    const std::string create_table_map = "CREATE TABLE IF NOT EXISTS map (map_id INTEGER PRIMARY KEY, user_id INTEGER, subject_id INTEGER, "
                                         "FOREIGN KEY (user_id) REFERENCES user (user_id)), FOREIGN KEY (subject_id) REFERENCES subject (subject_id))";
}

#endif //FORMULAS_BOT_CONSTANTS_H

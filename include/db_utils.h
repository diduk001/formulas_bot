#ifndef FORMULAS_TMP_DB_UTILS_H
#define FORMULAS_TMP_DB_UTILS_H

#include <sqlite3.h>
#include <memory>
#include <stdexcept>
#include "constants.h"
#include <vector>

namespace db {
    sqlite3 *db_conn;

    void init_conn() {
        // TODO: было бы прикольно придумать, как тут использовать std::unique_ptr
        int rc = sqlite3_open(consts::DB_NAME.c_str(), &db_conn);
        if (rc != SQLITE_OK) {
            sqlite3_close(db_conn);
            throw std::runtime_error("Error while connecting db");
        }
    }

    std::vector<std::string> basic_where(const std::string &clause_value) {
        sqlite3_stmt *statement;
        int rc = sqlite3_prepare_v2(db_conn, db_queries::basic_where_from_customers.c_str(), -1, &statement, 0);
        if (rc != SQLITE_OK) {
            sqlite3_close(db_conn);
            throw std::runtime_error("Error while preparing statement. Error code = " + std::to_string(rc));
        }

        sqlite3_bind_text(statement, 1, clause_value.c_str(), -1, SQLITE_STATIC);

        std::vector<std::string> result;
        while (sqlite3_step(statement) == SQLITE_ROW) {
            const unsigned char* result_value = sqlite3_column_text(statement, 0);
            result.emplace_back(reinterpret_cast<const char*>(result_value));
        }
        sqlite3_finalize(statement);
        return result;
    }

    void close_conn() {
        sqlite3_close(db_conn);
    }

    void create_working_db() {
        //Table user
        sqlite3_stmt *statement;
        int rc = sqlite3_prepare_v2(db_conn, db_queries::create_table_user.c_str(), -1, &statement, 0);
        if (rc != SQLITE_OK) {
            sqlite3_close(db_conn);
            throw std::runtime_error("Error while preparing statement. Error code = " + std::to_string(rc));
        }
        sqlite3_step(statement);

        //Table group
        sqlite3_stmt *statement;
        int rc = sqlite3_prepare_v2(db_conn, db_queries::create_table_group.c_str(), -1, &statement, 0);
        if (rc != SQLITE_OK) {
            sqlite3_close(db_conn);
            throw std::runtime_error("Error while preparing statement. Error code = " + std::to_string(rc));
        }
        sqlite3_step(statement);

        //Table subject
        sqlite3_stmt *statement;
        int rc = sqlite3_prepare_v2(db_conn, db_queries::create_table_subject.c_str(), -1, &statement, 0);
        if (rc != SQLITE_OK) {
            sqlite3_close(db_conn);
            throw std::runtime_error("Error while preparing statement. Error code = " + std::to_string(rc));
        }
        sqlite3_step(statement);

        //Table element
        int rc = sqlite3_prepare_v2(db_conn, db_queries::create_table_element.c_str(), -1, &statement, 0);
        sqlite3_stmt *statement;
        if (rc != SQLITE_OK) {
            sqlite3_close(db_conn);
            throw std::runtime_error("Error while preparing statement. Error code = " + std::to_string(rc));
        }
        sqlite3_step(statement);

        sqlite3_finalize(statement);
    }
}

#endif //FORMULAS_TMP_DB_UTILS_H

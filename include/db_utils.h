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

    void insert_element(const std::string &name, size_t subject_id, float coef, bool is_blocking, const std::string& description) {
        sqlite3_stmt *statement;
        int rc = sqlite3_prepare_v2(db_conn, query.c_str(), -1, &statement, 0);
        if (rc != SQLITE_OK) {
            sqlite3_close(db_conn);
            throw std::runtime_error("Error while preparing statement. Error code = " + std::to_string(rc));
        }

        sqlite3_bind_text(statement, 1, name.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_int64(statement, 2, subject_id, -1, SQLITE_STATIC);
        sqlite3_bind_double(statement, 3, coef, -1, SQLITE_STATIC);
        sqlite3_bind_int(statement, 4, (is_blocking ? true : false), -1, SQLITE_STATIC);
        sqlite3_bind_text(statement, 5, description.c_str(), -1, SQLITE_STATIC);

        sqlite3_step(statement);
        sqlite3_finalize(statement);
    }

    std::vector<std::string> basic_where(const std::string &query, const std::string &clause_value) {
        sqlite3_stmt *statement;
        int rc = sqlite3_prepare_v2(db_conn, query.c_str(), -1, &statement, 0);
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

    void delete_where_id(const std::string &query, size_t id) { //в большинстве случаев будем удалять по айдишнику
        sqlite3_stmt *statement;
        int rc = sqlite3_prepare_v2(db_conn, query.c_str(), -1, &statement, 0);
        if (rc != SQLITE_OK) {
            sqlite3_close(db_conn);
            throw std::runtime_error("Error while preparing statement. Error code = " + std::to_string(rc));
        }

        sqlite3_bind_int64(statement, 1, id, -1, SQLITE_STATIC);
        sqlite3_step(statement);
        sqlite3_finalize(statement);
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
        rc = sqlite3_prepare_v2(db_conn, db_queries::create_table_group.c_str(), -1, &statement, 0);
        if (rc != SQLITE_OK) {
            sqlite3_close(db_conn);
            throw std::runtime_error("Error while preparing statement. Error code = " + std::to_string(rc));
        }
        sqlite3_step(statement);

        //Table subject
        rc = sqlite3_prepare_v2(db_conn, db_queries::create_table_subject.c_str(), -1, &statement, 0);
        if (rc != SQLITE_OK) {
            sqlite3_close(db_conn);
            throw std::runtime_error("Error while preparing statement. Error code = " + std::to_string(rc));
        }
        sqlite3_step(statement);

        //Table element
        rc = sqlite3_prepare_v2(db_conn, db_queries::create_table_element.c_str(), -1, &statement, 0);
        if (rc != SQLITE_OK) {
            sqlite3_close(db_conn);
            throw std::runtime_error("Error while preparing statement. Error code = " + std::to_string(rc));
        }
        sqlite3_step(statement);

        //Table map
        rc = sqlite3_prepare_v2(db_conn, db_queries::create_table_map.c_str(), -1, &statement, 0);
        if (rc != SQLITE_OK) {
            sqlite3_close(db_conn);
            throw std::runtime_error("Error while preparing statement. Error code = " + std::to_string(rc));
        }
        sqlite3_step(statement);

        sqlite3_finalize(statement);
    }
}

#endif //FORMULAS_TMP_DB_UTILS_H

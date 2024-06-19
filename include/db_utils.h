#ifndef INCLUDE_DB_UTILS_H_
#define INCLUDE_DB_UTILS_H_

#include <sqlite3.h>

#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "constants.h"

namespace db {
sqlite3 *db_conn;

void init_conn() {
  // TODO(diduk001): придумать, как тут использовать std::unique_ptr
  int rc = sqlite3_open(consts::dbName, &db_conn);
  if (rc != SQLITE_OK) {
    sqlite3_close(db_conn);
    throw std::runtime_error("Error while connecting db");
  }
}

void close_conn() { sqlite3_close(db_conn); }
}  // namespace db

#endif  // INCLUDE_DB_UTILS_H_

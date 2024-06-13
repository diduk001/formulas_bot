#include <iostream>
#include <string>
#include "Control_element.h"
#include <format>

#include "../include/constants.h"
#include "../include/db_utils.h"
#inclue <sqlite3.h>

//Constructors, destructor
Control_element::Control_element() {
    this->id = 0;
    this->name = "";
    this->coef = 0;
    this->is_blocking = false;
    this->mark = -1;
    this->description = "";
}

Control_element::Control_element(const Control_element& other) {
    this->id = other.id;
    this->name = other.name;
    this->coef = other.coef;
    this->is_blocking = other.is_blocking;
    this->mark = other.mark;
    this->description = other.description;
}

Control_element::Control_element(std::string name, float coef, bool is_blocking, float mark, std::string description) {
    this->id = 0;
    this->name = name;
    this->coef = coef;
    this->is_blocking = is_blocking;
    this->mark = mark;
    this->description = description;
}

Control_element::Control_element(size_t id, std::string name, float coef, bool is_blocking, float mark, std::string description) {
    this->id = id;
    this->name = name;
    this->coef = coef;
    this->is_blocking = is_blocking;
    this->mark = mark;
    this->description = description;
}

Control_element::Control_element(size_t id) {
    this->id = 0;
    this->name = "";
    this->coef = 0;
    this->is_blocking = false;
    this->mark = -1;
    this->description = "";

    db::init_conn();
    const auto query_result = db::basic_where(db_queries::basic_where_from_element, std::to_string(id));
    if (res) {
        this->id = id;
        this->name = res->getString("name");
        this->coef = res->getDouble("value");
        this->is_blocking = res->getBoolean("block");
        this->mark = -1;
        this->description = res->getString("decription");
    }
    else
        std::cout << "Failed to get element from db" << std::endl;
    res->close();
    pstmt->close();
}

Control_element::~Control_element() = default;

//Getters, setters
inline size_t Control_element::get_id() const {
    return this->id;
}

inline std::string Control_element::get_name() const {
    return this->name;
}

inline float Control_element::get_coef() const {
    return this->coef;
}

inline bool Control_element::get_blocking() const {
    return this->is_blocking;
}

inline float Control_element::get_mark() const {
    return this->mark;
}

inline std::string Control_element::get_description() const {
    return this->description;
}

void Control_element::set_id(size_t id) {
    this->id = id;
}

void Control_element::set_name(std::string name) {
    this->name = name;
}

void Control_element::set_coef(float coef) {
    this->coef = coef;
}

void Control_element::set_blocking(bool is_blocking) {
    this->is_blocking = is_blocking;
}

void Control_element::set_mark(float mark) {
    this->mark = mark;
}

void Control_element::set_description(std::string description) {
    this->description = description;
}

//Operators
bool Control_element::operator==(const Control_element& other) const {
    if (this->name == other.name && this->coef == other.coef && this->is_blocking == other.is_blocking &&
        this->mark == other.mark && this->description == other.description)
        return true;
    else
        return false;
}

bool Control_element::operator!=(const Control_element& other) const {
    return !(*this == other);
}

Control_element& Control_element::operator=(const Control_element& other) {
    if (this != &other) {
        this->name = other.name;
        this->coef = other.coef;
        this->is_blocking = other.is_blocking;
        this->mark = other.mark;
        this->description = other.description;
    }
    return *this;
}

std::string Control_element::print() const {
    std::string output;
    output = std::format("��������: {}\n�����������: {}\n����������� �� �������: {}\n�������������� ����������: {}",
                          this->get_name(), this->get_coef(), this->get_blocking(), this->description);
    return output;
}

void Control_element::commit(sql::Connection* conn, size_t subject_id) {
    sql::PreparedStatement* pstmt = conn->prepareStatement("INSERT INTO Element (name, subject_id, value, block, description) VALUES (?, ?, ?, ?, ?)");
    if (this->get_id() == 0) {
        pstmt->setString(1, this->name);
        pstmt->setUInt64(2, subject_id);
        pstmt->setDouble(3, this->coef);
        pstmt->setBoolean(4, this->is_blocking);
        pstmt->setString(5, this->description);

        pstmt->execute();

        sql::Statement* stmt = conn->createStatement();
        stmt->execute("SELECT LAST_INSERT_ID()");
        sql::ResultSet* res = stmt->getResultSet();
        if (res->next())
            this->id= res->getUInt64(1);
        res->close();
        stmt->close();
    }
    else {
        sql::PreparedStatement* pstmt = conn->prepareStatement("UPDATE Element SET name = ?, value = ?, block = ?, description = ? WHERE id = ?;");
        pstmt->setString(1, this->name);
        pstmt->setDouble(2, this->coef);
        pstmt->setBoolean(3, this->is_blocking);
        pstmt->setString(4, this->description);
        pstmt->setUInt64(5, this->id);
    }
    pstmt->close();
}

void Control_element::erase(sql::Connection* conn) const {
    if (this->id != 0) {
        sql::Statement* stmt = conn->createStatement();
        stmt->execute("DELETE FROM Element WHERE id = " + std::to_string(this->id) + ";");
        stmt->close();
    }
}

void Control_element::from_db(sql::Connection* conn, size_t id) {
    sql::PreparedStatement* pstmt = conn->prepareStatement("SELECT * FROM Element WHERE element_id = ?");
    pstmt->setDouble(1, id);
    sql::ResultSet* res(pstmt->executeQuery());
    if (res) {
        this->id = id;
        this->name = res->getString("name");
        this->coef = res->getDouble("value");
        this->is_blocking = res->getBoolean("block");
        this->mark = -1;
        this->description = res->getString("decription");
    }
    else
        std::cout << "Failed to get element from db" << std::endl;
    res->close();
    pstmt->close();
}

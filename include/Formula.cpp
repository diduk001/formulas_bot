#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <cmath>
#include <format>
#include "Formula.h"

bool cmp_coefs(Control_element e1, Control_element e2)
{
    return e1.get_coef() > e2.get_coef();
}


//Constructors, destructor
Formula::Formula() = default;

Formula::Formula(std::vector<Control_element> elements)
{
    this->elements = elements;
}

Formula::Formula(const Formula& other)
{
    this->elements = other.elements;
}

Formula::Formula(sql::Connection* conn, size_t subject_id)
{
    sql::PreparedStatement* pstmt = conn->prepareStatement("SELECT * FROM Element WHERE subject_id = ?;");
    pstmt->setInt(1, subject_id);

    sql::ResultSet* res(pstmt->executeQuery());

    if (res)
    {
        this->elements.clear();
        while (res->next())
            this->add(Control_element(res->getUInt64("element_id"), res->getString("name"), res->getDouble("value"), res->getBoolean("block"), -1, res->getString("description")));
        res->close();
    }
    else
        std::cout << "Failed to get formula from db" << std::endl;
}

Formula::~Formula() = default;

//Getters, setters
inline std::vector<Control_element> Formula::get_elements() const
{
    return this->elements;
}

inline size_t Formula::get_size() const
{
    return this->elements.size();
}

void Formula::set_elements(std::vector<Control_element>* elements)
{
    this->elements = *elements;
}

Control_element& Formula::operator[](size_t s) const
{
    if (s > this->get_size())
    {
        std::cout << "List index out of range";
        exit(1);
    }
    else
        return this->get_elements()[s];
}

//Operations
void Formula::add(Control_element c)
{
    this->elements.push_back(c);
}

float Formula::evaluate() const
{
    float mark = 0;
    std::vector<Control_element> elems = this->elements;
    for (auto it = elems.begin(); it != elems.end(); it++)
        if (it->get_coef() != -1)
            mark += it->get_coef() * it->get_mark();
    return mark;
}

std::vector<Control_element> Formula::predict(unsigned short mark) const
{
    float cur = mark;
    float unk_coef_sum = 0;
    std::vector<Control_element> unk_elems, elems = this->elements;
    for (auto it = elems.begin(); it != elems.end(); it++)
        if ((*it).get_mark() == -1)
        {
            unk_coef_sum += (*it).get_coef();
            unk_elems.push_back(*it);
        }
        else
            cur -= (*it).get_mark() * (*it).get_coef();
    std::sort(unk_elems.begin(), unk_elems.end(), cmp_coefs);
    for (auto it = unk_elems.begin(); it != unk_elems.end(); it++)
    {
        float new_mark = std::ceil(cur / unk_coef_sum);
        (*it).set_mark(new_mark);
        cur -= new_mark * (*it).get_coef();
        unk_coef_sum -= (*it).get_coef();
    }
    return unk_elems;
}

std::string Formula::print()
{
    std::string output = "Formula:\n";
    std::vector<Control_element> elems = this->elements;
    for (auto it = elems.begin(); it != elems.end(); it++)
    {
        output += it->print() + "\n";
    }
    return output;
}

void Formula::from_db(sql::Connection* conn, size_t subject_id)
{
    sql::PreparedStatement* pstmt = conn->prepareStatement("SELECT * FROM Element WHERE subject_id = ?;");
    pstmt->setInt(1, subject_id);

    sql::ResultSet* res(pstmt->executeQuery());

    if (res)
    {
        this->elements.clear();
        while (res->next())
            this->add(Control_element(res->getUInt64("element_id"), res->getString("name"), res->getDouble("value"), res->getBoolean("block"), -1, res->getString("description")));
        res->close();
    }
    else
        std::cout << "Failed to get formula from db" << std::endl;
}

void remove_formula(sql::Connection* conn, size_t subject_id)
{
    if (subject_id != 0)
    {
        sql::Statement* stmt = conn->createStatement();
        stmt->execute("DELETE FROM Element WHERE subject_id = " + std::to_string(subject_id) + ";");
        stmt->close();
    }
}
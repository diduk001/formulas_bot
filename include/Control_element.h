#ifndef HSE_1COURSE_PROJECT_Control_element_H
#define HSE_1COURSE_PROJECT_Control_element_H

#include <string>
#include <iostream>
#incldue <sqlite3.h>

#include "../include/constants.h"
#include "../include/db_utils.h"

class Control_element
{
private:
    size_t id;
    std::string name;
    float coef;
    bool is_blocking;
    float mark;
    std::string description;
public:
    //Constructors, destructor
    Control_element();

    Control_element(const Control_element&);

    Control_element(std::string name, float coef, bool is_block, float mark, std::string description);

    Control_element(size_t id, std::string name, float coef, bool is_block, float mark, std::string description);

    Control_element(size_t id);

    ~Control_element();

    //Getters, setters
    inline size_t get_id() const;

    inline std::string get_name() const;

    inline float get_coef() const;

    inline bool get_blocking() const;

    inline float get_mark() const;

    inline std::string get_description() const;

    void set_id(size_t id);

    void set_name(std::string name);

    void set_coef(float coef);

    void set_blocking(bool is_blocking);

    void set_mark(float mark);

    void set_description(std::string description);

    //Operators
    bool operator==(const Control_element& other) const;

    bool operator!=(const Control_element& other) const;

    Control_element& operator=(const Control_element& other);

    std::string print() const;

    //Operations
    void commit(size_t subject_id);

    void from_db(size_t id);

    void erase() const;
};

#endif //HSE_1COURSE_PROJECT_Control_element_H

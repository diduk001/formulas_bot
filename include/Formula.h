#include "Control_element.h"
#include <string>
#include <vector>

#ifndef HSE_1COURSE_PROJECT_FORMULA_H
#define HSE_1COURSE_PROJECT_FORMULA_H


class Formula {
private:
    std::vector <Control_element> elements;
public:
    //Constructors, destructor
    Formula();

    explicit Formula(std::vector <Control_element>);

    Formula(const Formula&);

    Formula(sql::Connection* conn, size_t subject_id);

    ~Formula();

    //Getters, setters
    inline std::vector <Control_element> get_elements() const;

    inline size_t get_size() const;

    void set_elements(std::vector <Control_element>*);

    Control_element& operator[](size_t) const;

    //Operations
    void add(Control_element);

    float evaluate() const;

    std::vector<Control_element> predict(unsigned short mark) const;

    std::string print();

    void from_db(sql::Connection* conn, size_t subject_id);
};

void remove_formula(sql::Connection* conn, size_t subject_id);

#endif //HSE_1COURSE_PROJECT_FORMULA_H

//
// Created by 4s4r on 04.06.2024.
//
#include <iostream>
#include <string>
#ifndef INCLUDE_SUBJECT_H_
#define INCLUDE_SUBJECT_H_

class Subject {
  std::string professor_name;
  std::string professor_email;
  std::string description;
  size_t subject_id;
  std::string subject_name;

 public:
  Subject() : subject_id(0) {}

  ~Subject() = default;

  void set_professor_name(const std::string& name) {
    professor_name = name;
  }

  void set_professor_email(const std::string& email) {
    professor_email = email;
  }

  void set_description(const std::string& desc) {
    description = desc;
  }

  void set_subject_id(size_t id) {
    subject_id = id;
  }

  void set_subject_name(const std::string& name) {
    subject_name = name;
  }

  std::string get_professor_name() const {
    return professor_name;
  }

  std::string get_professor_email() const {
    return professor_email;
  }

  std::string get_description() const {
    return description;
  }

  size_t get_subject_id() const {
    return subject_id;
  }

  std::string get_subject_name() const {
    return subject_name;
  }

  std::string print_all() const {
    std::string all_info;
    all_info = "Название дисциплины: " + get_subject_name() + '\n';
    all_info += "ФИ(О) профессора: " + get_professor_name() + '\n';
    all_info += "Электронная почта профессора: " + get_professor_email();
    all_info += "\nОписание: " + get_description();
    return all_info;
  }
};

#endif  // INCLUDE_SUBJECT_H_

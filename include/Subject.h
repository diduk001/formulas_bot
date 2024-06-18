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
  Subject();

  ~Subject();

  void set_professor_name(std::string name);

  void set_professor_email(std::string email);

  void set_description(std::string desc);

  void set_subject_id(size_t id);

  void set_subject_name(std::string name);

  std::string get_professor_name() const;

  std::string get_professor_email() const;

  std::string get_description() const;

  size_t get_subject_id() const;

  std::string get_subject_name() const;

  std::string print_all() const;
};

#endif  // INCLUDE_SUBJECT_H_

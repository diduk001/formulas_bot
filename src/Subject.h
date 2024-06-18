//
// Created by 4s4r on 04.06.2024.
//
#include <iostream>
#ifndef TELEGRAMBOT_SUBJECT_H
#define TELEGRAMBOT_SUBJECT_H


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


  std::string get_professor_name();

  std::string get_professor_email();

  std::string get_description();

  size_t get_subject_id();

  std::string get_subject_name();

  std::string print_all();

};


#endif //TELEGRAMBOT_SUBJECT_H

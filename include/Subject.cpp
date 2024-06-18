//
// Created by 4s4r on 04.06.2024.
//

#include "Subject.h"

#include <string>
#include <utility>

Subject::Subject() : subject_id(0) {}

Subject::~Subject() = default;

void Subject::set_professor_name(std::string name) {
  this->professor_name = std::move(name);
}

void Subject::set_professor_email(std::string email) {
  this->professor_email = std::move(email);
}

void Subject::set_description(std::string desc) {
  this->description = std::move(desc);
}

void Subject::set_subject_id(size_t id) { this->subject_id = id; }

void Subject::set_subject_name(std::string name) {
  this->subject_name = std::move(name);
}

std::string Subject::get_professor_name() const { return this->professor_name; }

std::string Subject::get_professor_email() const { return this->professor_email; }

std::string Subject::get_description() const { return this->description; }

size_t Subject::get_subject_id() const { return this->subject_id; }

std::string Subject::get_subject_name() const { return this->subject_name; }

std::string Subject::print_all() const {
  std::string all_info;
  all_info = "Название дисциплины: " + this->get_subject_name() + '\n';
  all_info += "ФИ(О) профессора: " + this->get_professor_name() + '\n';
  all_info += "Электронная почта профессора: " + this->get_professor_email();
  all_info += "\nОписание: " + this->get_description();
  return all_info;
}

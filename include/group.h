
#include <iostream>
#include <string>
#ifndef INCLUDE_MODELS_GROUP_H_
#define INCLUDE_MODELS_GROUP_H_

class Group {
  std::string group_name;
  int64_t owner_id;

 public:
  Group() : owner_id(0) {}

  Group(const Group &other)
    : group_name(other.group_name), owner_id(other.owner_id) {}

  Group(std::string name, int64_t id) {
    this->group_name = name;
    this->owner_id = id;
  }

  ~Group() = default;

  void set_group_name(const std::string &name) { this->group_name = name; }

  void set_owner_id(int64_t id) { this->owner_id = id; }

  std::string get_group_name() const { return this->group_name; }

  int64_t get_owner_id() const { return this->owner_id; }
};

#endif  // INCLUDE_MODELS_GROUP_H_

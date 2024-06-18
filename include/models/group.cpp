#include "group.h"

#include <iostream>

Group::Group() : group_name(""), owner_id(0) {}

Group::Group(const Group &other)
    : group_name(other.group_name), owner_id(other.owner_id) {}

Group::Group(std::string name, int64_t id) {
  this->group_name = name;
  this->owner_id = id;
}

Group::~Group() = default;

void Group::set_group_name(const std::string &name) { this->group_name = name; }

void Group::set_owner_id(int64_t id) { this->owner_id = id; }

std::string Group::get_group_name() const { return this->group_name; }

int64_t Group::get_owner_id() const { return this->owner_id; }

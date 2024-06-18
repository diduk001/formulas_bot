#include "group.h"

Group::Group(const Group &other)
    : group_name(other.group_name), owner_id(other.owner_id) {}

Group::Group(std::string name, int64_t id) {
  this->group_name = name;
  this->owner_id = id;
}

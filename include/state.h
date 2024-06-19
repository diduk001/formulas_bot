#include <cstdint>
#include <iostream>
#include <unordered_map>

#ifndef INCLUDE_STATE_H_
#define INCLUDE_STATE_H_

enum class GroupState {
  NONE,
  WAITING_FOR_GROUP_NAME,
  WAITING_FOR_NEW_GROUP_NAME
};

std::unordered_map<int64_t, GroupState> userStates;
std::unordered_map<int64_t, Group*> userGroup;

void setGroupState(int64_t userId, GroupState state) {
  userStates[userId] = state;
}

GroupState getGroupState(int64_t userId) {
  if (userStates.find(userId) == userStates.end()) {
    return GroupState::NONE;
  }
  return userStates[userId];
}

Group* getGroup(int64_t userId) {
  if (userGroup.find(userId) == userGroup.end()) {
    userGroup[userId] = new Group();
  }
  return userGroup.at(userId);
}

#endif  // INCLUDE_STATE_H_

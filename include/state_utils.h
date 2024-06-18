#include <iostream>
#include <unordered_map>

#ifndef INCLUDE_STATE_UTILS_H_
#define INCLUDE_STATE_UTILS_H_

enum class Group_State {
  NONE,
  WAITING_FOR_GROUP_NAME,
  WAITING_FOR_NEW_GROUP_NAME
};

std::unordered_map<int64_t, Group_State> userStates;

void setState(int64_t userId, Group_State state) { userStates[userId] = state; }

Group_State getState(int64_t userId) {
  if (userStates.find(userId) == userStates.end()) {
    return Group_State::NONE;
  }
  return userStates[userId];
}

#endif  // INCLUDE_STATE_UTILS_H_

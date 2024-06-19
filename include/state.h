#ifndef INCLUDE_STATE_H_
#define INCLUDE_STATE_H_

#include "Subject.h"

#include <cstdint>
#include <iostream>
#include <unordered_map>

enum class State {
  NONE,
  WAITING_FOR_NAME,
  WAITING_FOR_PROFESSOR_NAME,
  WAITING_FOR_PROFESSOR_EMAIL,
  WAITING_FOR_DESCRIPTION
};

enum class GroupState {
  NONE,
  WAITING_FOR_GROUP_NAME,
  WAITING_FOR_NEW_GROUP_NAME
};

std::unordered_map<int64_t, State> userStates;
std::unordered_map<int64_t, Subject*> userSubject;

std::unordered_map<int64_t, GroupState> userGroupStates;
std::unordered_map<int64_t, Group*> userGroup;

void setState(int64_t userId, State state) { userStates[userId] = state; }

State getState(int64_t userId) {
  if (userStates.find(userId) == userStates.end()) {
    return State::NONE;
  }
  return userStates[userId];
}

Subject* getSubject(int64_t userId) {
  if (userSubject.find(userId) == userSubject.end()) {
    userSubject[userId] = new Subject();
  }
  return userSubject.at(userId);
}

void eraseStateAndSubject(int64_t userId) {
  if (userStates.find(userId) != userStates.end()) {
    userStates.erase(userId);
    userSubject.erase(userId);
  }
}

void setGroupState(int64_t userId, GroupState state) {
  userGroupStates[userId] = state;
}

GroupState getGroupState(int64_t userId) {
  if (userGroupStates.find(userId) == userGroupStates.end()) {
    return GroupState::NONE;
  }
  return userGroupStates[userId];
}

Group* getGroup(int64_t userId) {
  if (userGroup.find(userId) == userGroup.end()) {
    userGroup[userId] = new Group();
  }
  return userGroup.at(userId);
}

#endif  // INCLUDE_STATE_H_

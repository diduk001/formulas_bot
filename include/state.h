//
// Created by f4s4r on 6/18/24.
//

#ifndef INCLUDE_STATE_H_
#define INCLUDE_STATE_H_

#include <cstdint>
#include <iostream>
#include <unordered_map>

#include "Subject.h"

enum class State {
  NONE,
  WAITING_FOR_NAME,
  WAITING_FOR_PROFESSOR_NAME,
  WAITING_FOR_PROFESSOR_EMAIL,
  WAITING_FOR_DESCRIPTION
};

std::unordered_map<int64_t, State> userStates;
std::unordered_map<int64_t, Subject*> userSubject;

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

#endif  // INCLUDE_STATE_H_

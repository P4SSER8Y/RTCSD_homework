//
// Created by troy on 12/2/16.
//

#include "FSM.h"
#include <iostream>

State::State(std::string Name = "UNNAMED") {
    this->FnEntry = nullptr;
    this->Name = Name;
}

State* State::Trigger() {
    for (int i = 0; i < this->Condition.size(); i++)
        if (this->Condition[i]())
            return this->NextState[i];
    return nullptr;
}

void State::Add(bool (*fn)(void), State *NextState) {
    this->Condition.push_back(fn);
    this->NextState.push_back(NextState);
}

void State::SetEntry(void (*fn)(void)) {
    this->FnEntry = fn;
}

void State::Entry() {
    if (this->FnEntry != nullptr)
        FnEntry();
}


Machine::Machine(State *InitState = nullptr) {
    this->SetState(InitState);
}

void Machine::SetState(State *state) {
    this->Curr = state;
    std::cout << "Set State <" << state->Name << ">" << std::endl;
    state->Entry();
}

void Machine::Trigger() {
    State *tmp;
    tmp = this->Curr->Trigger();
    if (tmp != nullptr) {
        std::cout << "Switch From <" << this->Curr->Name << "> " <<
                  "to <" << tmp->Name << ">" << std::endl;
        this->Curr = tmp;
        tmp->Entry();
    }
}

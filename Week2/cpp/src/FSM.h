#pragma once

#include <string>
#include <vector>

class State {
public:
    std::string Name;
    State(std::string);
    State* Trigger(void);
    void Add(bool(*fn)(void), State* NextState);
    void SetEntry(void(*fn)(void));
    void Entry(void);

private:
    std::vector<bool(*)(void)> Condition;
    std::vector<State*> NextState;
    void (*FnEntry)(void);
};

class Machine {
public:
    Machine(State *InitState);
    void SetState(State *state);
    State *Curr;
    void Trigger(void);
};

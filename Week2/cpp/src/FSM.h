#pragma once

#include <string>
#include <vector>
#include <functional>

class State {
public:
    std::string Name;
    State(std::string);
    State* Trigger(void);
    void Add(std::function<bool(void)> fn, State* NextState);
    void SetEntry(void(*fn)(void));
    void Entry(void);

private:
    std::vector<std::function<bool(void)>> Condition;
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

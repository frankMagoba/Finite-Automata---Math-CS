#include <algorithm>
#include "determinization.h"

static State*
determinizationProcess(vector<State*> &presentStates, const vector<char> &alphabet, const vector<State*> &sameStates,
                       const vector<State*> &init,
                       const vector<State*> &fin, const bool sync) {
    bool isInit = init == sameStates;

    vector<State*> groupState = sameStates;
    if (!sync) {
        // Recovering every state accessible with empty transition
        State::groupEmpty(groupState);
    }

    // Naming the new state
    string newID = concatenateID(sameStates);
    // Checking if the state isn't already there
    auto search = State::searchById(presentStates, newID);
    if (search != nullptr) {
        return search;
    }

    // Allocation of the state, and giving it its properties
    State* actual = initStateDet(presentStates, groupState, isInit, newID);

    // Merging transitions with the same character
    for (auto c: alphabet) {
        vector<State*> sameFinalState;
        locatingSameTransition(sameFinalState, groupState, c);
        // Creating the transition, with the character and the address of the terminal state
        if (!sameFinalState.empty()) {
            Transition* tr = new Transition;
            tr->trans = c;
            tr->dest = determinizationProcess(presentStates, alphabet, sameFinalState, init, fin, sync);
            actual->exits.push_back(tr);
        }
    }
    return actual;
}

FA* FA::determinize() {
    if (_determinized) {
        return this;
    }

    vector<State*> initials, finals, states;

    // Recovering final and initial states
    State::recoverSpecials(_states, &initials, &finals);

    determinizationProcess(states, _alphabet, initials, initials, finals, _synchronous);

    // Creating the FA in itself
    FA* determinized = new FA(states, _alphabet);
    determinized->_name = _name + " Determinized";
    return determinized;
}

static State*
initStateDet(vector<State*> &presentStates, const vector<State*> &sameStates, const bool init,
             const string &newID) {
    // Creating the state
    State* actual = new State;
    actual->id = newID;
    actual->initial = init;
    actual->final = State::isAnyFinal(sameStates);
    presentStates.push_back(actual);
    return actual;
}

static void locatingSameTransition(vector<State*> &sameFinalState, const vector<State*> &sameStates, const char c) {
    for (State* st: sameStates) {
        for (Transition* tr: st->exits) {
            bool isNotPresent = find_if(sameFinalState.begin(), sameFinalState.end(), [tr](const State* s) -> bool {
                return s == tr->dest;
            }) == sameFinalState.end();
            if (tr->trans == c && isNotPresent) {
                // We add the element if it is not already on the list and if the transition character correspond
                sameFinalState.push_back(tr->dest);
            }
        }
    }
}
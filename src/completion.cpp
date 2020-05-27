#include <algorithm>
#include <vector>
#include "completion.h"

FA* FA::completion() {
    // Normally we only complete Deterministic FA, but since it is technically possible to comple a NDFA, we allow it
    if (!_completed) {
        FA* newFA = new FA(*this); // Creates a new FA that will be complete
        completionProcess(newFA->_states, newFA->_alphabet); // Makes the completion
        newFA->sort();
        newFA->_completed = true;
        newFA->_name = _name + " Complete";
        return newFA;
    } else {
        return this;
    }

}

static void completionProcess(vector<State*> &list, const vector<char> &alphabet) {
    State* P = new State; //Declaration of a new state "P"
    int i = 0;
    while (State::searchById(list, to_string(list.size() + i)) != nullptr) {
        i++;
    }
    P->id = to_string(list.size() + i);


    // Declaration of "isPUsed" that will check if the state "P" has been used in this process.
    bool isPUsed = false;
    for (State* st: list) {
        for (char c : alphabet) {
            //Checking all alphabet for each state, to see if there are empty transitions. If yes, adds P as a transition.
            Transition* T = new Transition;
            if (Transition::searchByCharacter(st->exits, c) == nullptr) {
                T->dest = P;
                T->trans = c;
                st->exits.push_back(T);
                isPUsed = true; //As P has been used in this process
            }
        }
    }

    if (!isPUsed) {
        delete P; //If P has not been used, we don't need it, so it is deleted
    } else {
        for (char c: alphabet) {
            Transition* tr = new Transition;
            tr->trans = c;
            tr->dest = P;
            P->exits.push_back(tr);
        }
        list.push_back(P); //Adds P to the list of states
    }
}


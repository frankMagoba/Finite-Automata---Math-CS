#include "reading.h"

#include <iostream>

using namespace std;

bool FA::recognizeWord(string word) {
    vector<State*> cur;

    //Starts from all initial states
    State::recoverSpecials(_states, &cur, nullptr);

    //Transitions by character until the word is over
    for (char c : word) {
        if (cur.empty()) {
            //If the transition leads to no states, stop transitioning
            break;
        }

        cur = ReadChar(c, cur);
    }
    State::groupEmpty(cur);

    //if there is a way to reach at least 1 final state at the end of the word, it is recognized
    return State::isAnyFinal(cur);
}

static vector<State*> ReadChar(char c, vector<State*> cur) {
    vector<State*> next;

    //starts by grouping initial states with their empty word accessible states
    State::groupEmpty(cur);

    //if given an empty word, no additional transitions
    if (c == EMPTY) {
        next = cur;
    } else {
        for (State* St : cur) {
            for (Transition* T : St->exits) {
                if (T->trans == c) {
                    if (!State::searchById(next, T->dest->id)) {
                        next.push_back(T->dest);
                    }
                }
            }
        }
    }

    return next;
}


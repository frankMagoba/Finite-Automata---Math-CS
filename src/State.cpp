#include <algorithm>
#include "State.h"

using namespace std;

State* State::searchById(vector<State*> list, string id) {
    vector<State*>::iterator it;
    it = find_if(list.begin(), list.end(), [&id](State* st) -> bool {
        return st->id == id;
    });
    if (it != list.end()) {
        return *it;
    }
    return nullptr;
}


bool State::isAnyInitial(const vector<State*> &list) {
    for (State* st: list) {
        if (st->initial) {
            return true;
        }
    }
    return false;
}

bool State::isAnyFinal(const vector<State*> &list) {
    for (State* st: list) {
        if (st->final) {
            return true;
        }
    }
    return false;
}

void State::recoverSpecials(const vector<State*> &list, vector<State*> * initials, vector<State*> * finals) {
    for (State* st: list) {
        if(initials){
            if (st->initial) {
                initials->push_back(st);
            }
        }
        if(finals) {
            if (st->final) {
                finals->push_back(st);
            }
        }
    }
}

void State::groupEmpty(std::vector<State*> &emptyGroup) {
    for (int i = 0; i < emptyGroup.size(); i++) {
        // Note that we are using a classic int for loop, because otherwise iw wouldn't take into account the update made to empty group + vectors realloc on push
        for (Transition* tr: emptyGroup[i]->exits) {
            if (tr->trans == EMPTY) {
                if (!(State::searchById(emptyGroup, tr->dest->id))) {
                    emptyGroup.push_back(tr->dest);
                }
            }
        }
    }
}

static string readingPartID(string &id) {
    size_t pos;
    string value = id, delimiter = ".";
    if ((pos = id.find(delimiter)) != string::npos) {
        value = id.substr(0, pos);
        id.erase(0, pos + delimiter.length());
    }
    return value;
}

static bool isIDSmaller(const State* st1, const State* st2) {
    bool equal = true;
    string tmp1, tmp2;
    string id1 = st1->id, id2 = st2->id;
    do {
        tmp1 = readingPartID(id1);
        tmp2 = readingPartID(id2);
        if (stoi(tmp1) != stoi(tmp2)) {
            equal = false;
        }
    } while (equal);
    return stoi(tmp1) < stoi(tmp2);
}

void State::sortStates(std::vector<State*> &list) {
    sort(list.begin(), list.end(), isIDSmaller);
}

static bool isTransitionSmaller(const Transition* t1, const Transition* t2) {
    if (int(t1->trans) < int(t2->trans)) {
        return true;
    } else if (t1->trans == t2->trans) {
        return isIDSmaller(t1->dest, t2->dest);
    }
    return false;
}

void Transition::sortTransitions(std::vector<Transition*> &list) {
    sort(list.begin(), list.end(), isTransitionSmaller);
}
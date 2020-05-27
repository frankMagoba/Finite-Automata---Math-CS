#include <algorithm>
#include <string>
#include "Transition.h"

using namespace std;

Transition* Transition::searchByCharacter(vector<Transition*> &list, char c) {
    vector<Transition*>::iterator it;
    it = find_if(list.begin(), list.end(), [&c](Transition* tr) -> bool {
        return tr->trans == c;
    });
    if (it != list.end()) {
        return *it;
    }
    return nullptr;
}

void Transition::searchOccurrence(const vector<Transition*> &list, char c, vector<Transition*> &recover) {
    for (Transition* tr: list) {
        if (tr->trans == c) {
            recover.push_back(tr);
        }
    }
}
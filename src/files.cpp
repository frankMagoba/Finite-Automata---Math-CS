#include <fstream>
#include <algorithm>
#include "files.h"

using namespace std;

FA::FA(const string &nameFile) {
    ifstream inputStream(nameFile);

    if (inputStream) {
        creatingFAFile(inputStream, nameFile);
        _name = nameFile;
        sort();
        runTest();
        inputStream.close();
    }
}

bool FA::creatingFAFile(ifstream &stream, const string &nameFile) {
    string line;
    int alphabetSize{0}, numberStates{0}, numberTransitions{0};
    vector<string>* initStates, * finalStates;
    vector<char> alphabetCheck;

    alphabetSize = readUniqueNumber(stream);
    numberStates = readUniqueNumber(stream);
    initStates = readSpecialStates(stream);
    finalStates = readSpecialStates(stream);
    numberTransitions = readUniqueNumber(stream);

    if (!initStates || !finalStates) {
        cout << "Error in reading initial or final states of " << nameFile << endl;
        goto error;
    }

    //Creation of alphabet
    if (!generateAlphabet(alphabetSize, _alphabet)) {
        cout << "Error in the creation of the alphabet of " << nameFile << endl;
        goto error;
    }
    // Creation of states
    if (!generateStates(numberStates, _states)) {
        cout << "Error in the creation of the states of " << nameFile << endl;
        goto error;
    }

    giveAttributesStates(_states, initStates, finalStates);

    // Creation of all transitions
    if (createTransitions(stream, _states, alphabetCheck) != numberTransitions) {
        cout << "Error in the creation of the transitions of " << nameFile << endl;
        goto error;
    }

    if (alphabetCheck.size() > _alphabet.size()) {
        cout << "Conflict between the announced size of the alphabet and the alphabet used" << endl;
        goto error;
    }

    return true;

    error:
    cleaningFA();
    return false;
}

static vector<string>* readSpecialStates(ifstream &stream) {
    vector<string>* states = new vector<string>;
    string line, newState, delimiter = " ";
    int size{-1};
    size_t pos = 0;
    getline(stream, line);

    // Splitting instruction with ' '
    while ((pos = line.find(delimiter)) != string::npos) {
        newState = line.substr(0, pos);
        if (states->empty() && size == -1) {
            // First number is for the size
            size = stoi(newState);
        } else if (newState != delimiter && newState != "") {
            states->push_back(newState);
        }
        line.erase(0, pos + delimiter.length());
    }

    if (states->size() != size) {
        return nullptr;
    }
    return states;
}

static int readUniqueNumber(ifstream &stream) {
    string line;
    getline(stream, line);
    return stoi(line);
}

static int createTransitions(ifstream &stream, vector<State*> &states, vector<char> &alpha) {
    string line;
    int nbTransitions = 0;
    while (getline(stream, line)) {
        char c;
        string stateFrom, stateTo;
        // Splitting the instruction into 3 parts
        separateTransition(line, c, stateFrom, stateTo);

        if (createSingleTransition(states, stateFrom, stateTo, c)) {
            nbTransitions++;
        }

        addCharacterToAlphabet(alpha, c);
    }
    return nbTransitions;
}

static void giveAttributesStates(vector<State*> &list, const vector<string>* init, const vector<string>* final) {
    for (State* st: list) {
        if (find(init->begin(), init->end(), st->id) != init->end()) {
            st->initial = true;
        }
        if (find(final->begin(), final->end(), st->id) != final->end()) {
            st->final = true;
        }
    }
}

static State* allocateState(string id) {
    State* st = new State();
    st->id = id;
    return st;
}

static void separateTransition(string &transitionString, char &c, string &stateFrom, string &stateTo) {
    string::iterator it = transitionString.begin();
    string stateF, stateT;

    // First state
    while (isdigit(*it)) {
        stateFrom += *it;
        it++;
    }
    // Character of transition
    while (isalpha(*it) || *it == EMPTY) {
        c = *it;
        it++;
    }
    // Second state
    while (isdigit(*it)) {
        stateTo += *it;
        it++;
    }
}

static bool createSingleTransition(vector<State*> &list, const string &stateFromID, const string &stateToID,
                                   char transition) {
    // Looking for address of the two states
    State* stateFrom = State::searchById(list, stateFromID);
    State* stateTo = State::searchById(list, stateToID);

    if (stateFrom && stateTo && !verifyExistence(stateFrom, stateTo, transition)) {
        Transition* t = new Transition;
        t->trans = transition;
        t->dest = stateTo;
        stateFrom->exits.push_back(t);
        return true;
    }
    return false;
}

static void addCharacterToAlphabet(vector<char> &alpha, char c) {
    // We add character to alphabet if not in or empty word
    if (find(alpha.begin(), alpha.end(), c) == alpha.end() && c != EMPTY) {
        alpha.push_back(c);
    }
}

static bool verifyExistence(const State* stateFrom, const State* stateTo, char c) {
    vector<Transition*> recover;
    Transition::searchOccurrence(stateFrom->exits, c, recover);

    for (Transition* tr: recover) {
        if (tr->dest == stateTo) {
            return true;
        }
    }
    return false;
}

static bool generateAlphabet(int n, vector<char> &alphabet) {
    if (n > 25) {
        // We only deal with character from 'a' to 'z'
        return false;
    }
    for (int i = 0; i < n; i++) {
        alphabet.push_back('a' + i);
    }
    return true;
}

static bool generateStates(int n, vector<State*> &list) {
    if (n <= 0) {
        return false;
    }
    for (int i = 0; i < n; i++) {
        list.push_back(allocateState(to_string(i)));
    }
    return true;
}
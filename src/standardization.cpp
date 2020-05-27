#include "FA.h"
#include <string>

FA* FA::standardize() {

    //First, check if the Automata isn't already standard, in order to not create new state.
    if (_standard) {
        cout << "Already standardization." << endl;
        return this;
    }
    else if(checkStandard()){
        _standard= true;
        cout << "Already standardization." << endl;
        return this;
    }

    //Initialization of our new FA
    FA* newFA = new FA(*this);
    newFA->_name = _name + " Standardized";
    State* newIni = new State;
    newIni->initial = true;
    int i = 0;
    while (State::searchById(_states, to_string(_states.size() + i)) != nullptr) {
        i++;
    }
    newIni->id = to_string(newFA->_states.size() + i);

    //We will go into all the initial states
    for(State* st: newFA->_states){
        if(st->initial){

            //To know if the initial state that we will have at the end is final, we check if one of the initial state is final
            if(!newIni->final){
                if(st->final)
                    newIni->final = true;
            }

            // Then we plug all the transitions of our old initial(s) state(s) in the new one
            for(int i = 0 ; i < st->exits.size() ; i++){
                newIni->exits.push_back(st->exits[i]);
            }

            // Finally, we make our old initial state not initial
            st->initial = false;
        }
    }

    // We add our new and unique initial state to our states.
    newFA->_states.push_back(newIni);
    newFA->_standard = true;
    return newFA;

}


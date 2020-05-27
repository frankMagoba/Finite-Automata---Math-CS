#ifndef FINITE_AUTOMATA_MATH_CS_DETERMINIZATION_H
#define FINITE_AUTOMATA_MATH_CS_DETERMINIZATION_H

#include "FA.h"

/// Determinization for a state in synchronous automate
/// \param presentStates List of states, where states of the new automate will be (return by parameter)
/// \param alphabet Alphabet
/// \param sameStates States sharing the same character of transition. At first, put the initial states
/// \param init List of initial states
/// \param fin List of final states
/// \return Address of the state determinized (only used for recursion)
static State*
determinizationProcess(vector<State*> &presentStates, const vector<char> &alphabet, const vector<State*> &sameStates,
                       const vector<State*> &init,
                       const vector<State*> &fin, const bool sync);

/// Initialise a state
/// \param presentStates List of actual states (return by parameter)
/// \param sameStates States that will be merged
/// \param init True if the state is initial
/// \param newID ID of the new state
/// \return Address of the new state
static State*
initStateDet(vector<State*> &presentStates, const vector<State*> &sameStates, const bool init,
             const string &newID);

/// Recover states having the same character of transition in a list given
/// \param sameFinalState List of state sharing the same character of transition (return by parameter)
/// \param sameStates List of states to look in
/// \param c Character of transition
static void locatingSameTransition(vector<State*> &sameFinalState, const vector<State*> &sameStates, char c);

#endif //FINITE_AUTOMATA_MATH_CS_DETERMINIZATION_H

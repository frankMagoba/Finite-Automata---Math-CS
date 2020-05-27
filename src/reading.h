#ifndef FINITE_AUTOMATA_MATH_CS_READING_H
#define FINITE_AUTOMATA_MATH_CS_READING_H

#include "FA.h"
#include "State.h"

/// Takes a List of states and returns the list of all accessible states with a given transition character
/// \param c transition character
/// \param cur list of starting states
/// \return list of destination states
static vector<State*> ReadChar(char c, vector<State*> cur);


#endif //FINITE_AUTOMATA_MATH_CS_READING_H

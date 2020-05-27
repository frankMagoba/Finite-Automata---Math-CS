#ifndef FINITE_AUTOMATA___MATH_CS_STATE_H
#define FINITE_AUTOMATA___MATH_CS_STATE_H


#include "Transition.h"
#include <iostream>

//Single automata State
typedef struct State {
public:
    std::string id="";       //Arbitrary state name
    bool initial = false;   // true if this is an initial state
    bool final = false;     // true if this is a final state
    std::vector<Transition*> exits;      //list of outgoing transitions

    /// Search a state by ID
    /// \param list List of states to look in
    /// \param id ID of the state looked for
    /// \return Address of the state if found, nullptr if not
    static State* searchById(std::vector<State*> list, std::string id);

    /// Search if any initial states in list
    /// \param list List of states
    /// \return true if any, false if none
    static bool isAnyInitial(const std::vector<State*> &list);

    /// Search if any final states in list
    /// \param list List of states
    /// \return true if any, false if none
    static bool isAnyFinal(const std::vector<State*> &list);

    /// Recover initial and final states from a list
    /// \param list List of states
    /// \param initials List where initial states will be, ptrnull if not interested in initials
    /// \param finals List where final states will be, ptrnull if not interested in finals
    static void
    recoverSpecials(const std::vector<State*> &list, std::vector<State*> *initials, std::vector<State*> *finals);

    /// Takes a list of states and adds to the list all the groups accessible from those states by empty transitions
    /// \param emptyGroup List of states that empty states are added to
    static void groupEmpty(std::vector<State*> &emptyGroup);

    /// Sort states by ascending order (ex: 1 < 1.3 < 2)
    /// \param list List of State to sort
    static void sortStates(std::vector<State*> &list);
} State;

/// Read a string up to a dot, or the end
/// \param id String to read
/// \return Value read
static std::string readingPartID(std::string &id);

/// Inner function to sort States. Compare two states
/// \param st1 First State to compare
/// \param st2 Second State to compare
/// \return Bool (st1 < st2)
static bool isIDSmaller(const State* st1, const State* st2);

/// Inner function to sort Transitions. Compare two transitions
/// \param t1 First Transition to compare
/// \param t2 Second Transition to compare
/// \return Bool (t1 < t2)
static bool isTransitionSmaller(const Transition* t1, const Transition* t2);


#endif //FINITE_AUTOMATA___MATH_CS_STATE_H

#ifndef FINITE_AUTOMATA_MATH_CS_MINIMIZATION_H
#define FINITE_AUTOMATA_MATH_CS_MINIMIZATION_H

#include "FA.h"

//A pattern group is what ultimately becomes a state at the end of minimization
typedef struct PatternGroup
{
    vector<State*> group; // The States that come from the same original pattern group that share the same pattern
    vector<int> pattern; // This is a list of indexes reffering to this pattern's group exit destinations in the previous partition
} PatternGroup;

typedef vector<PatternGroup>* Partition;

/// Keeps creating new Partitions according to the Minimization algortihm until there is no increase in partition number
/// \param P initial partition
/// \param alphabet Initial FA alphabet
/// \return Final Partition
static Partition partitioning(Partition P, vector<char> alphabet, int n);

/// Turns a partition into a list of states
/// \param P Partition
/// \param alphabet initial Fa alphabet
/// \param TTable Transition table of the new FA
/// \return List of States
static vector<State*>* Partition2States(Partition P, vector<char> &alphabet, stringstream &CTable);

/// Get the pattern of a State in a Partition
/// \param source The previous Partition
/// \param exits Exits of a State
/// \param alphabet FA alphabet
/// \return Pattern of
static vector<int>* getPattern(Partition source, vector<Transition*> &exits, vector<char> alphabet);


/// Checks if 2 patterns are the same
/// \param p1 Pattern 1
/// \param p2 Pattern 2
/// \return True if they are the same
static bool isSamePattern(vector<int> &p1, vector<int> &p2);

/// Displays A partitions and it's pattern groups
/// \param P Partition to display
/// \param n Partition number. -1 for final Partition
/// \param alphabet Alphabet of original FA
static void displayPartition(Partition P, int n, vector<char> alphabet);

/// Deletes a partition from memory
/// \param P Partition to delete
static void deletePartition(Partition P);


#endif //FINITE_AUTOMATA_MATH_CS_MINIMIZATION_H

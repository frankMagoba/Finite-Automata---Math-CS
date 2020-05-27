#ifndef FINITE_AUTOMATA_MATH_CS_STRUCTURE_H
#define FINITE_AUTOMATA_MATH_CS_STRUCTURE_H

#include <iostream>
#include <vector>
#include <sstream>

#include "State.h"

using namespace std;


class FA {
private:
    string _name = "Finite automata";           //Arbitrary name
    vector<State*> _states;  //List of all the automaton's states
    vector<char> _alphabet;

    stringstream _correspondence;

    // Shows if in its current state the automaton is minimized/determinized/complete
    bool _minimized = false;
    bool _determinized = false;
    bool _completed = false;
    bool _synchronous = false;
    bool _standard = false;

public:
    FA();

    /// Creating FA from a file
    /// \param nameFile Path and name of the file
    explicit FA(const std::string &nameFile);

    /// Creating FA from existing states and alphabet
    /// \param states Vector of states
    /// \param alphabet Vector of alphabet
    FA(vector<State*> &states, vector<char> &alphabet);

    ~FA();

    /// Copy constructor
    /// \param toCopy FA to copy from
    FA(FA &toCopy);

    ///Displays the automaton
    void display() const;

    /// Checks if an FA recognizes a given word
    /// \param word the string to test
    /// \return True if it is recognized
    bool recognizeWord(string word);

    /// Check if an automate is synchronous
    /// \param display Display result and explanation if true (false by default)
    /// \return bool
    bool isSynchronous(const bool display = false) const;

    /// Check if an automate is deterministic
    /// \param display Display result and explanation if true (false by default)
    /// \return bool
    bool isDeterministic(const bool display = false) const;

    /// Check if an automate is complete
    /// \param display Display result and explanation if true (false by default)
    /// \return bool
    bool isComplete(const bool display = false) const;

    /// Check if an automate is standard
    /// \param display Display result and explanation if true (false by default)
    /// \return bool
    bool isStandard(const bool display = false) const;

    FA* minimize(const bool displayT = true);

    ///Standardize an FA
    /// \return Adress of the standard FA.
    FA* standardize();

    /// Determinize an FA
    /// \return Address of the determinized FA
    FA* determinize();


    /// Enhances a Deterministic Automaton and makes it being complete
    /// \return Address of the completed FA
    FA* completion();

    /// Complementarize an FA
    /// \return Address of the determinized FA
    FA* complementarize();

    /// Run every checkX
    void runTest();

    std::string getName();

private:
    /// Clean the alphabet and the list of states
    void cleaningFA();

    /// Inner function of the constructor from file
    /// \param stream Valid input stream
    /// \param nameFile Name of the file
    /// \return Integrity of the operation (true: Performed)
    bool creatingFAFile(ifstream &stream, const std::string &nameFile);

    /// Inner function of the copy constructor
    /// \param toCopyStates States of the FA to copy from
    /// \param newID ID of the state to create
    /// \return Address of the state (used only for recursion)
    State* copyStatesProcess(std::vector<State*> &toCopyStates, const string &newID);

    /// Check if the automate is synchronous or not. Should be used after every change in the automate
    void checkSynchronous();

    /// Check if the automate is deterministic or not. Should be used after every change in the automate
    void checkDeterministic();

    ///Check if the automate is complete or not. Should be used after every change in the automate
    void checkComplete();

    /// Check if the automate is standard or not. Should be used after every change in the automate
    bool checkStandard();

    /// Check if the automate is minimal or not. Should be used after every change in the automate
    bool checkMinimal();

    /// Sort transitions and states. It leads to a better display
    void sort();

};

/// Generate an ID from a list of states
/// \param sameStates List of states
/// \return ID generated
extern string concatenateID(vector<State*> sameStates);

/// Sub function of FA::isDeterministic(), checking the number of entry
/// \param list List of states to check in
static void oneEntry(const vector<State*> &list);

/// Sub function of FA::isDeterministic(), checking if every transition is unique
/// \param list List of states
/// \param alphabet Alphabet of the FA
static void uniqueTransition(const vector<State*> &list, vector<char> alphabet);




#endif //FINITE_AUTOMATA_MATH_CS_STRUCTURE_H
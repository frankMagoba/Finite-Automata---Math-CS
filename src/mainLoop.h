#ifndef FINITE_AUTOMATA_MATH_CS_MAINLOOP_H
#define FINITE_AUTOMATA_MATH_CS_MAINLOOP_H

#include "FA.h"

/// Handle the main loop of the program
/// \return
int mainLoop();

/// Display the main Menu
/// \return
int displayMainMenu();

/// Process one of the action of the main Menu
/// \param myFA List of FA
/// \param action ID of the action to process
void processAction(vector<FA*>* myFA, int action);

/// Clear the list of FA, load the new FA and display its characteristic
/// \param myFA List of FA
void addAutomateFromFiles(vector<FA*>* myFA);

/// Menu to select an FA
/// \param myFA List of FA
/// \return Adress of the FA selected
FA* pickFA(vector<FA*>* myFA);

/// Ask the number of the FA to load from a file (from 1 to 44, 43 being the one for testing)
/// \return Number of the file chose
int askForFileNumber();

/// Display the list of FA
/// \param myFa List of FA
void showMyFA(vector<FA*> myFa);

/// Display the menu of Computation
/// \return ID of the action
int displayComputeMenu();

/// Execute a computation on an FA
/// \param a ID of the computation
/// \param currentFA FA on which the computation will be performed
/// \param myFA List of FA
void processComputationFA(int a, FA* currentFA, vector<FA*>* myFA);

/// Show to an user if an FA is complete, and complete it if possible (add result to list)
/// \param currentFA FA on which to perform the process
/// \param myFA List of FA
void completationAndAdd(FA* currentFA, vector<FA*>* myFA);

/// Show to an user if an FA is deterministic, and determinize it if possible (add result to list)
/// \param currentFA FA on which to perform the process
/// \param myFA List of FA
void determinizeAndAdd(FA* currentFA, vector<FA*>* myFA);

/// Show to an user if an FA is standard, and standardize it if possible (add result to list)
/// \param currentFA FA on which to perform the process
/// \param myFA List of FA
void standardizeAndAdd(FA* currentFA, vector<FA*>* myFA);

/// Show to an user if an FA is minimized, and minimize it if possible (add result to list)
/// \param currentFA FA on which to perform the process
/// \param myFA List of FA
void minimizeAndAdd(FA* currentFA, vector<FA*>* myFA);

/// Complementarize (opposite language) an FA if possible (add result to list)
/// \param currentFA FA on which to perform the process
/// \param myFA List of FA
void ComplementarizationAndAdd(FA* currentFA, vector<FA*>* myFA);

/// Test recognition of word on an FA
/// \param myFA List of FA
void wordReco(vector<FA*>* myFA);







#endif //FINITE_AUTOMATA_MATH_CS_MAINLOOP_H

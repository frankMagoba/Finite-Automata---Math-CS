#include "minimization.h"


FA* FA::minimize(const bool displayT)
{
    if (_completed && _determinized)
    {
        Partition P = new vector<PatternGroup>;
        PatternGroup Finals, NonFinals;

        //The initial Partition is the F and NF states
        for (State *St: _states)
        {
            if (St->final)
            {
                Finals.group.push_back(St); //Final
            } else
            {
                NonFinals.group.push_back(St); //NonFinal
            }
        }
        if (!NonFinals.group.empty())
        {
            P->push_back(NonFinals);
        }
        if (!Finals.group.empty())
        {
            P->push_back(Finals);
        }

        if (displayT) {
            display();
            displayPartition(P, 0, _alphabet);
        }

        P = partitioning(P, _alphabet, 1);

        //Creates a new FA from a list of states
        FA *newAuto = new FA;

        newAuto->_name = "Minimized " + _name;
        newAuto->_correspondence << endl << "Table of Correspondence of " << _name << " to " << newAuto->_name << ":"
                                 << endl << endl;
        newAuto->_states = *Partition2States(P, _alphabet, newAuto->_correspondence);
        if (newAuto->_states.size() == _states.size()) {
            if (displayT) cout << "FA " << _name << "is already minimal" << endl;
            _minimized = true;
        }

        deletePartition(P);
        newAuto->_alphabet = _alphabet;
        newAuto->_completed = true;
        newAuto->_determinized = true;
        newAuto->_minimized = true;
        newAuto->_synchronous = true;


        return newAuto;
    } else
    {
        if (displayT) cout << "FA must be Complete and Deterministic." << endl;
        return nullptr;
    }

}


static Partition partitioning(Partition P, vector<char> alphabet, int n)
{
    vector<Partition> AllParts;
    vector<int> *patt;
    Partition nextP;
    PatternGroup *newPattGroup;
    int sizeP = P->size();
    vector<PatternGroup>::iterator EndPattGroups;


    for (PatternGroup const &Pgroup  : *P)
    {
        nextP = new vector<PatternGroup>;

        for (State *St : Pgroup.group)
        {
            //If the pattern of the current state matches one in an existing group, it joins that group, otherwise it creates a new one
            patt = getPattern(P, St->exits, alphabet);
            for (EndPattGroups = nextP->begin(); EndPattGroups != nextP->end(); ++EndPattGroups)
            {
                if (isSamePattern(*patt, EndPattGroups->pattern))
                {
                    EndPattGroups->group.push_back(St);
                    break;
                }
            }
            if (EndPattGroups == nextP->end())
            {
                newPattGroup = new PatternGroup;
                newPattGroup->group.push_back(St);
                newPattGroup->pattern = (*patt);
                nextP->push_back(*newPattGroup);
            }
        }
        //It is important to have a vector of partitions since similar patterns shouldn't mix while partitioning if they come from different initial pattern groups
        AllParts.push_back(nextP);
    }

    //Concat AllParts
    nextP = new vector<PatternGroup>;
    for (Partition Part: AllParts)
    {
        nextP->insert(nextP->end(), Part->begin(), Part->end());
    }

    //clear it up
    //(I dont really know when to use 'delete' so im kinda just yeeting it all lmaoooo)
    deletePartition(P);
    for (Partition part:AllParts)
    {
        deletePartition(part);
    }
    delete &AllParts;



    //If it is the same size, it means no additional partitioning is possible so it should return the latest partition
    //(since that latest partition and the previous one are the same, the patterns point to the correct indexes in the latest partition)
    if (nextP->size() > sizeP)
    {
        displayPartition(nextP, n, alphabet);
        nextP = partitioning(nextP, alphabet, n + 1);
    }
    else
    {
        displayPartition(nextP, -1, alphabet);
    }

    return nextP;
}

static vector<State *> *Partition2States(Partition P, vector<char> &alphabet, stringstream &CTable)
{
    vector<State *> *FaStates = new vector<State *>;
    State *newSt;

    //Creates correct state names at the right index and print the table of Correspondence
    for (int l = 0; l < P->size(); l++)
    {
        newSt = new State;
        newSt->id = to_string(l);
        CTable << " " << l << ":  ";

        for (State *curSt : (*P)[l].group)
        {
            if (curSt != (*P)[l].group[0])
            {
                CTable << " + ";
            }
            CTable << curSt->id;
        }
        CTable << endl;
        //If there is a final/initial state in the pattern group, the new state is final/initial
        newSt->initial = State::isAnyInitial((*P)[l].group);
        newSt->final = State::isAnyFinal((*P)[l].group);
        FaStates->push_back(newSt);
    }

    Transition *newTrans;

    //Sets up proper Transitions
    for (int i = 0; i < FaStates->size(); i++)
    {
        for (int j = 0; j < alphabet.size(); j++)
        {
            // For each state, it creates the transitions. To do this, it goes through every character and for each one,
            // it looks at the group it was made from in the original partition, it looks at that groups pattern,
            // by looking at said character's transition in this pattern, it find the index of the pattern group it was connected to.
            // This index is equivalent to the index of its corresponding state in the new list of state and hence,
            // we can finally access that state to add it as a transition
            newTrans = new Transition;
            newTrans->trans = alphabet[j];
            newTrans->dest = (*FaStates)[(*P)[i].pattern[j]];
            (*FaStates)[i]->exits.push_back(newTrans);
        }
    }

    return FaStates;
}

static vector<int> *getPattern(Partition source, vector<Transition *> &exits, vector<char> alphabet)
{
    vector<int> *newpatt = new vector<int>;
    for (char c: alphabet)
    {
        for (Transition *T : exits)
        {
            //This 'if' makes sure that the pattern order is consistant
            if (T->trans == c)
            {
                for (int i = 0; i < source->size(); i++)
                {
                    //Looks at the source Partition's patternGroups to find one in which the destination state exists. it adds its index in transitions
                    if (State::searchById((*source)[i].group, T->dest->id))
                    {
                        newpatt->push_back(i);
                    }
                }
                break;
            }
        }
    }
    return newpatt;
}


static bool isSamePattern(vector<int> &p1, vector<int> &p2)
{
    auto i = p1.begin(), j = p2.begin();
    for (i, j; i != p1.end() && j != p2.end(); ++i, ++j)
    {
        if (*i != *j)
            return false;
    }

    return i == p1.end() && j == p2.end();

}

static void displayPartition(Partition P, int n, vector<char> alphabet)
{
    //Displays partition number or final if it is final
    if (n == -1)
        cout << endl << endl << "X X X X Final Partition X X X X X";
    else
        cout << endl << endl << "X X X X X X " << "Partition " << n << " X X X X X X";

    //Display each pattern group
    for (int i = 0; i < P->size(); i++)
    {
        cout << endl << endl << "   Pattern group " << i << endl << "      Pattern: ";
        if (n == 0)
        {
            //If it is the initial partition, it is only divided between final and non-final states
            if (!State::isAnyFinal((*P)[i].group))
                cout << "Non-";
            cout << "Final States";
        } else
        {
            //Display the pattern of a group
            if (n == -1)
                cout << "(transitions to groups from this partition)";
            else
                cout << "(transitions to groups from partition " << n - 1 << ")";
            for (int j = 0; j < alphabet.size(); j++)
            {
                cout << endl << "         " << alphabet[j] << " : Group " << (*P)[i].pattern[j];
            }
        }
        //display the states of that belong to a group
        cout << endl << "   States: ";
        for (int c = 0; c < (*P)[i].group.size(); c++)
        {
            if (c != 0)
                cout << " , ";
            cout << (*P)[i].group[c]->id;
        }
    }
}


static void deletePartition(Partition P)
{
    for (PatternGroup curg : *P)
    {
        delete &curg.group;
        delete &curg.pattern;
        delete &curg;
    }
    delete P;
}
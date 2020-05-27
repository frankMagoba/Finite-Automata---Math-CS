#include "mainLoop.h"

static void separation() {
    cout << endl << "\n*-*-*-*-*-*-*-*-*-*-*-*-*\n" << endl;
}

int mainLoop() {
    vector<FA*>* myFA = new vector<FA*>;
    int looper = 0;
    while (looper != 5) {
        looper = displayMainMenu();
        if (looper == 5)
            return 0;
        processAction(myFA, looper);
    }
}


int displayMainMenu() {
    separation();
    cout << "~~Hello user~~" << endl;
    cout << "Make a choice : " << endl;
    cout << "[1] Load FA from files" << endl;
    cout << "[2] Display FA" << endl;
    cout << "[3] Compute FA (Determinize, Minimize, Complete...)" << endl;
    cout << "[4] Word Recognize" << endl;
    cout << "[5] Exit" << endl;

    int i = 0;
    cin >> i;
    while (i < 1 || i > 5) {
        cout << "Wrong entry. Please make a choice between 1 and 5." << endl;
        cin >> i;
    }
    return i;
}

void processAction(vector<FA*>* myFA, int action) {
    switch (action) {
        case 1:
            addAutomateFromFiles(myFA);
            break;

        case 2:
            FA* temp;
            temp = pickFA(myFA);
            if (temp != nullptr)
                temp->display();
            break;

        case 3:
            FA* temp1;
            temp1 = pickFA(myFA);
            if (temp1 == nullptr)
                break;
            int i;
            i = displayComputeMenu();
            processComputationFA(i, temp1, myFA);
            break;
        case 4:
            wordReco(myFA);
            break;
    }
}

void addAutomateFromFiles(vector<FA*>* myFA) {
    for (FA* automata: *myFA) {
        delete (automata);
    }
    myFA->clear();

    std::string myFile;
    myFile = "automata/L2Int1-7-" + to_string(askForFileNumber()) + ".txt";
    FA* temp = new FA(myFile);
    myFA->push_back(temp);
    temp->display();
}

FA* pickFA(vector<FA*>* myFA) {
    cout << "Choose a FA in:" << endl;
    showMyFA(*myFA);
    int i = 0;
    while (i < 1 || i > myFA->size()) {
        cout << "Your choice (0 to exit): ";
        cin >> i;
        if (i > -1 && i < myFA->size() + 1) {
            if (i == 0)
                return nullptr;
            return (*myFA)[i - 1];
        }
    }
}

int askForFileNumber() {
    separation();
    int r = 0;
    while (r < 1 || r > 44) {
        cout << "Enter the FA you want to load :" << endl;
        cin >> r;
        if (r > 0 && r < 45)
            return r;
        cout << "Not possible ! ";
    }
}

void showMyFA(vector<FA*> myFa) {
    cout << "My FA : " << endl;
    for (int i = 0; i < myFa.size(); i++) {
        cout << "[" << i + 1 << "] : " << myFa[i]->getName() << endl;
    }
}


int displayComputeMenu() {
    separation();
    separation();
    cout << "Choose computation : " << endl;
    cout << "[1] Completation" << endl;
    cout << "[2] Determinization" << endl;
    cout << "[3] Standardize" << endl;
    cout << "[4] Minimize" << endl;
    cout << "[5] Complementarize (opposition language)" << endl;
    cout << "[6] Exit" << endl;

    int i = 0;
    cin >> i;
    while (i < 1 || i > 6) {
        cout << "Wrong entry. Please make a choice between 1 and 5." << endl;
        cin >> i;
    }
    return i;
}

void processComputationFA(int a, FA* currentFA, vector<FA*>* myFA) {
    switch (a) {
        case 1:
            completationAndAdd(currentFA, myFA);
            break;
        case 2:
            determinizeAndAdd(currentFA, myFA);
            break;
        case 3:
            standardizeAndAdd(currentFA, myFA);
            break;
        case 4:
            minimizeAndAdd(currentFA, myFA);
            break;
        case 5:
            ComplementarizationAndAdd(currentFA, myFA);
            break;
        default:
        case 6:
            break;
    }
}


void completationAndAdd(FA* currentFA, vector<FA*>* myFA) {
    if (!currentFA->isComplete(true)) {
        FA* temp;
        temp = currentFA->completion();
        if (temp == nullptr)
            cout << "Can't complete : the FA needs to be Deterministic." << endl;
        else {
            temp->display();
            myFA->push_back(temp);
            cout << "Successful Completion!" << endl;
        }
    } else {
        cout << "Already Complete!" << endl;
    }
}

void determinizeAndAdd(FA* currentFA, vector<FA*>* myFA) {
    if (currentFA->isDeterministic(true)) {
        cout << "Already Deterministic!" << endl;
    } else {
        FA* temp;
        temp = currentFA->determinize();
        temp->display();
        myFA->push_back(temp);
        cout << "Successful Determinisation!" << endl;
    }
}

void standardizeAndAdd(FA* currentFA, vector<FA*>* myFA) {
    if (currentFA->isStandard(true)) {
        cout << "Already standard!" << endl;
    } else {
        FA* temp;
        temp = currentFA->standardize();
        temp->display();
        myFA->push_back(temp);
        cout << "Successful Standardisation!" << endl;
    }
}

void minimizeAndAdd(FA* currentFA, vector<FA*>* myFA) {
    separation();
    FA* temp;
    temp = currentFA->minimize();
    if (temp != nullptr) {
        temp->display();
        myFA->push_back(temp);
        cout << "Successful Minimisation!" << endl;
    }
}

void ComplementarizationAndAdd(FA* currentFA, vector<FA*>* myFA) {
    separation();
    FA* temp;
    temp = currentFA->complementarize();
    if (temp != nullptr) {
        temp->display();
        myFA->push_back(temp);
        cout << "Successful Completion!" << endl;
    }
    else
        cout << "Operation not possible: the FA needs to be Complete." << endl;
}

void wordReco(vector<FA*>* myFA) {
    separation();
    FA* temp = pickFA(myFA);
    if (temp != nullptr) {
        temp->display();
        string myWord;
        do {
            cout << "Write a word ('exit' to exit): ";
            cin >> myWord;
            if (temp->recognizeWord(myWord))
                cout << "Word is recognized." << endl;
            else
                cout << "Word is NOT recognized." << endl;
        } while (myWord != "exit");
    }
}
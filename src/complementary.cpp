#include "FA.h"

FA* FA::complementarize() {
    if (_completed) {
        cout << "Complementary automate obtained from";
        if (_minimized) {
            cout << " minimized version." << endl;
        } else {
            cout << " just completed version." << endl;
        }

        FA* complementary = new FA(*this);
        for (State* st: complementary->_states) {
            st->final = !(st->final);
        }

        complementary->_name = _name + " Complementary";

        return complementary;
    }
    return nullptr;
}
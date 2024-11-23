#include "subject.h"
#include "observer.h"
#include "board.h"
#include <vector>

// constructor
Subject::Subject(Board* theBoard): theBoard{theBoard} {}

// attach( Observer* o ) add the input observer
void Subject::attach( Observer* o ) {
    observers.push_back(o);
}

// detach(Observer* o) remove the input observer
void Subject::detach(Observer* o) {
    for (auto it = observers.begin(); it != observers.end(); ) {
        if (*it == o) {
            it = observers.erase(it); 
        } else {
            ++it;
        }
    }
}

// notifyObservers() call notify for every observer
void Subject::notifyObservers() {
    for (auto observer : observers) {
        observer->notify();
    }
}

// cleanupObservers() clean all the observer
void Subject::cleanupObservers() {
    auto& observers = getObservers();
    for (auto observer : observers) { // delete every observer
        delete observer; 
    }
    observers.clear();
}

// getState(int row, int col) return the char at current position
char Subject::getState(int row, int col) const {
    return theBoard->unitAt(row, col);
}

// destructor
Subject::~Subject() { 
    cleanupObservers(); 
    delete theBoard;
}

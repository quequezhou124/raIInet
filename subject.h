#ifndef SUBJECT_H
#define SUBJECT_H
#include "board.h"
#include <vector>

class Observer; // forward declaration
class Board;

class Subject {
  Board* theBoard;
  std::vector<Observer*> observers;
 protected:
  std::vector<Observer*>& getObservers() { return observers; }

 public:

  Board* getBoard() {return theBoard;}
  explicit Subject(Board* theBoard);
  void attach( Observer* o );
  void detach( Observer* o );
  void notifyObservers();
  char getState( int row, int col ) const;
  void cleanupObservers(); 
  ~Subject();
  void setBoard(Board* newBoard) {
    if (theBoard) {
        delete theBoard;  // Delete the old board to avoid a memory leak
    }
    theBoard = newBoard;
  }

};

#endif

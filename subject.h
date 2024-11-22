#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>

class Observer; // forward declaration
class Board;

class Subject {
  Board *theBoard;
  std::vector<Observer*> observers;
 protected:
  std::vector<Observer*>& getObservers() { return observers; }

 public:
  void attach( Observer* o );
  void detach( Observer* o );
  void notifyObservers();
  char getState( int row, int col ) const;
  void cleanupObservers(); 
  ~Subject();
};

#endif

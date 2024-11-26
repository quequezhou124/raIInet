#ifndef UNIT_H
#define UNIT_H
#include <iostream>

class Unit {
  protected:
    int row;
    int col;
    int strength;
    char name;
    bool displayed;
    bool doublespeed;
    bool locked;
    bool downloaded;
  public:
    Unit(int row, int col, int strength, char name, bool displayed = false, bool doublespeed = false, bool locked = false, bool downloaded = false);
    char getName() const { return name; }
    int getRow() const { return row; }
    int getCol() const { return col; }
    bool getDisplayed() const{return displayed;}
    bool getDoublespeed() const{return doublespeed;}
    bool getLocked() const{return locked;}
    void opendoublespeed() {
      doublespeed=true;
      return;
    }
    virtual int getStrength() = 0;
    virtual std::string getType () = 0;
    virtual void setStrength(int strength, int row, int col) = 0;
    virtual bool setrow(int row) = 0;
    virtual bool setcol(int col) = 0;
    virtual ~Unit() = default;
    bool getDownloaded() const {return downloaded;}
    void setDownloaded(bool newd) {downloaded = newd;}
};

#endif

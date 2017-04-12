#include "clause.h"

#include <list>
#include <fstream>

class Formula
{
 private:
  std::list<Clause *> myList;

  bool anyEmpty;

 public:
  Formula();
  Formula(const Formula &f);
  Formula(std::ifstream &ifs);

  int size() const;
  std::list<Clause *>::const_iterator begin() const;
  std::list<Clause *>::const_iterator end() const;
  bool isAnyClauseEmpty() const;
  int chooseVariable() const;

  void readFromFile(std::ifstream &ifs);
  void add(Clause *c);
  void set(int var);
  bool unitPropagation();
  
};

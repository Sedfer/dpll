#include "clause.h"

#include <list>

class Formula
{
 private:
  std::list<Clause *> myList;

 public:
  Formula();
  Formula(const Formula &f);

  int size() const;
  void add(Clause *c);
  std::list<Clause *>::const_iterator begin() const;
  std::list<Clause *>::const_iterator end() const;
  bool isAnyClauseEmpty() const;
  int chooseVariable() const;

  void set(int var);
  bool unitPropagation();
  
};

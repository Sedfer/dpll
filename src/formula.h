#include "clause.h"

#include <list>
#include <vector>
#include <fstream>

class Formula
{
 private:
  std::list<Clause *> myList;
  std::vector<int> pVars;    // total number of positive vars
  std::vector<int> nVars;    // total number of negative vars
  bool anyEmpty;  

  void addVars(Clause *c);
  void removeVars(Clause *c);
  
 public:
  Formula();
  Formula(const Formula &f);
  Formula(std::ifstream &ifs);
  ~Formula();

  int size() const;
  std::list<Clause *>::const_iterator begin() const;
  std::list<Clause *>::const_iterator end() const;
  bool isAnyClauseEmpty() const;
  int chooseVariable() const;

  void readFromFile(std::ifstream &ifs);
  void add(Clause *c);
  void set(int var);
  bool unitPropagation();
  bool pureLiteralElimination();
  
};

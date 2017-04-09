#include "formula.h"

#include <iostream>
#include <fstream>
using namespace std;

bool dpll(Formula &f);
void print(Clause &c);
void print(Formula &f);

int main(int argc, char *argv[])
{
  // if(argc < 2){
  //   cout << "File is not specified!" << endl;
  //   return 0;
  // }
  
  // ifstream file(argv[1]);

  // file.close();

  Formula f;

  Clause * c1 = new Clause(3);
  Clause * c2 = new Clause(3);
  Clause * c3 = new Clause(3);
  Clause * c4 = new Clause(3);

  c1->set(1);
  c1->set(2);
  c1->set(3);
  c2->set(-1);
  c2->set(-2);
  c2->set(-3);
  c3->set(1);
  c3->set(-2);
  c4->set(-1);
  c4->set(-3);

  f.add(c1);
  f.add(c2);
  f.add(c3);
  f.add(c4);

  bool res = dpll(f);
  cout << "dpll result: " << res << endl;
}

void print(Clause &c)
{
  for(int i = 1; i <= c.size(); i++){
    cout << c.get(i) << " ";
  }

  cout << endl;

  for(int i = 1; i <= c.size(); ++i){
    cout << c.get(-i) << " ";
  }

  cout << "empty: " << c.isEmpty() << endl;
}

void print(Formula &f)
{
  cout << "Formula (" << f.size() << " clauses):" << endl;
  for(Clause *c : f){
    print(*c);
  }
}

bool dpll(Formula &f)
{
  while(1){
    if(f.size() == 0)
      return true;
    
    if(f.isAnyClauseEmpty())
      return false;

    bool flag = false;
    // return true, if successful; false - if not possible
    flag |= f.unitPropagation();
    //flag |= f.pureLiteralElimination();
    if(!flag) break;
  }

  int var = f.chooseVariable();
  
  Formula nF(f);
  nF.set(var);

  if(dpll(nF))
    return true;
  
  nF = Formula(f);
  nF.set(-var);

  return dpll(nF);
}


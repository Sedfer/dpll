#include "formula.h"

#include <iostream>
#include <fstream>
#include <signal.h>
using namespace std;

void sigintHandler(int param);
bool dpll(Formula &f);

void print(Clause &c);
void print(Formula &f);

int main(int argc, char *argv[])
{
  signal(SIGINT, sigintHandler);
  
  if(argc < 2){
    cout << "File is not specified!" << endl;
    return 0;
  }
  
  ifstream file(argv[1]);
  if(!file.is_open()){
    cout << "Can not open file!" << endl;
    return 0;
  }
  
  Formula f(file);

  bool res = dpll(f);
  if(res){
    cout << "SATISFIABLE" << endl;
  }
  else{
    cout << "UNSATISFIABLE" << endl;
  }
  
  file.close();
}

void sigintHandler(int param)
{
  cout << "UNKNOWN" << endl;
  exit(0);
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

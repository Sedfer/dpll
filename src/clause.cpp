#include "clause.h"

#include <cstdlib>
using namespace std;

Clause::Clause() : Clause(0)
{ }

Clause::Clause(int size) : myCount(0)
{
  p = vector<bool>(size, false);
  n = vector<bool>(size, false);
}

int Clause::size() const
{
  return p.size();
}

void Clause::set(int var, bool value)
{
  bool pos = var > 0;
  var = abs(var);
  
  if(var > p.size() || var == 0){
    throw nullptr;
  }

  if(pos){
    if(!p[var-1] && value){
      ++myCount;
    }
    if(p[var-1] && !value){
      --myCount;
    }
    p[var-1] = value;
  }
  else{
    if(!n[var-1] && value){
      ++myCount;
    }
    if(n[var-1] && !value){
      --myCount;
    }
    n[var-1] = value;
  }
}

bool Clause::get(int var) const
{
  bool pos = var > 0;
  var = abs(var);

  if(var > p.size() || var == 0){
    throw nullptr;
  }

  if(pos){
    return p[var-1];
  }
  else{
    return n[var-1];
  }
}

bool Clause::isEmpty() const
{
  return count() == 0;
}

int Clause::count() const
{
  return myCount;
}

int Clause::findSingle() const
{
  if(count() != 1){
    return 0;
  }
  
  int res = 0;

  for(int i = 0; i < p.size(); ++i){
    if(p[i])
      return i + 1;
  }

  for(int i = 0; i < n.size(); ++i){
    if(n[i])
      return -(i + 1);
  }

  throw nullptr;
}

int Clause::chooseVariable() const
{
  for(int i = 0; i < p.size(); ++i){
    if(p[i])
      return i + 1;
  }

  for(int i = 0; i < n.size(); ++i){
    if(n[i])
      return -(i + 1);
  }

  return 0;
}

#include "clause.h"

#include <cstdlib>
using namespace std;

Clause::Clause() : Clause(0)
{ }

Clause::Clause(int size)
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
    p[var-1] = value;
  }
  else{
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
  for(bool b : p){
    if(b) return false;
  }

  for(bool b : n){
    if(b) return false;
  }

  return true;
}

int Clause::count() const
{
  int res = 0;

  for(bool b : p){
    res += b;
  }

  for(bool b : n){
    res += b;
  }

  return res;
}

int Clause::findSingle() const
{
  int res = 0;

  for(int i = 0; i < p.size(); ++i){
    if(!p[i])
      continue;

    if(res != 0)
      return 0;

    res = i + 1;
  }

  for(int i = 0; i < n.size(); ++i){
    if(!n[i])
      continue;

    if(res != 0)
      return 0;

    res = -(i + 1);
  }

  return res;
}

int Clause::chooseVariable() const
{
  for(int i = 0; i < p.size(); ++i){
    if(p[i])
      return i + 1;
  }

  for(int i = 0; i < n.size(); ++i){
    if(n[i])
      return -(i - 1);
  }

  return 0;
}

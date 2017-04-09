#include "formula.h"

using namespace std;

Formula::Formula()
{
  myList = list<Clause *>(0);
}

Formula::Formula(const Formula &f)
{
  myList = list<Clause *>(0);
  
  // create new copies of Clauses
  for(Clause *c : f){
    myList.push_back(new Clause(*c));
  }
}

int Formula::size() const
{
  return myList.size();
}

void Formula::add(Clause *c)
{
  myList.push_back(c);
}

list<Clause *>::const_iterator Formula::begin() const
{
  return myList.cbegin();
}

list<Clause *>::const_iterator Formula::end() const
{
  return myList.cend();
}

void Formula::set(int var)
{
  for(auto it = myList.begin(); it != myList.end();){
    if((*it)->get(var)){
      auto oldIt = it;
      ++it;
      delete *oldIt;
      myList.erase(oldIt);
      continue;
    }
    
    if((*it)->get(-var)){
      (*it)->set(-var, false);
    }

    ++it;
  }
}

bool Formula::unitPropagation()
{
  for(Clause *c : myList){
    int var = c->findSingle();
    if(var != 0){
      this->set(var);
      return true;
    }
  }

  return false;
}

bool Formula::isAnyClauseEmpty() const
{
  for(Clause *c : myList){
    if(c->isEmpty())
      return true;
  }

  return false;
}

int Formula::chooseVariable() const
{
  int var = 0;

  for(Clause *c : myList){
    var = c->chooseVariable();
    if(var != 0)
      break;
  }

  return var;
}

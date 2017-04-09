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

Formula::Formula(ifstream &ifs) : Formula()
{
  this->readFromFile(ifs);
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

void Formula::readFromFile(ifstream &ifs)
{
  string str;

  while(1){
    ifs >> str;
    if(str == "c"){
      getline(ifs, str);
      continue;
    }

    if(str == "p"){
      break;
    }

    throw nullptr;
  }

  ifs >> str;
  if(str != "cnf")
    throw nullptr;

  int var = 0, clause = 0;
  ifs >> var >> clause;

  for(int i = 0; i < clause; ++i){
    Clause *c = new Clause(var);
    int num;
    while(true){
      ifs >> num;
      if(num == 0)
	break;

      c->set(num);
    }

    this->add(c);
  }
}

#include "formula.h"

using namespace std;

Formula::Formula() : myList(), pVars(), nVars(), anyEmpty(false)
{ }

Formula::Formula(const Formula &f) : Formula()
{
  pVars = f.pVars;
  nVars = f.nVars;
  
  // create new copies of Clauses
  for(Clause *c : f){
    myList.push_back(new Clause(*c));
    anyEmpty |= c->isEmpty();
  }
}

Formula::Formula(ifstream &ifs) : Formula()
{
  this->readFromFile(ifs);
}

Formula::~Formula()
{
  for(Clause *c : myList){
    delete c;
  }
}

void Formula::addVars(Clause *c)
{
  if(pVars.size() < c->size()){
    pVars.resize(c->size(), 0);
    nVars.resize(c->size(), 0);
  }

  for(int i = 0; i < c->size(); ++i){
    pVars[i] += c->get(i+1);
    nVars[i] += c->get(-(i+1));
  }
}

void Formula::removeVars(Clause *c)
{
  for(int i = 0; i < c->size(); ++i){
    pVars[i] -= c->get(i+1);
    nVars[i] -= c->get(-(i+1));
  }
}

int Formula::size() const
{
  return myList.size();
}

void Formula::add(Clause *c)
{
  myList.push_back(c);
  addVars(c);
  anyEmpty |= c->isEmpty();
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
      removeVars(*oldIt);
      delete *oldIt;
      myList.erase(oldIt);
      continue;
    }
    
    if((*it)->get(-var)){
      (*it)->set(-var, false);
      anyEmpty |= (*it)->isEmpty();

      if(var > 0){
	--nVars[var-1];
      }
      else{
	--pVars[-var-1];
      }
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

bool Formula::pureLiteralElimination()
{
  for(int i = 0; i < pVars.size(); ++i){
    if(nVars[i] == 0 && pVars[i] > 0){
      this->set(i+1);
      return true;
    }
    if(pVars[i] == 0 && nVars[i] > 0){
      this->set(-(i+1));
      return true;
    }
  }

  return false;
}

bool Formula::isAnyClauseEmpty() const
{
  return anyEmpty;
}

int Formula::chooseVariable() const
{
  int var = 0, max = 0;

  for(int i = 0; i < pVars.size(); ++i){
    if(pVars[i] > max){
      var = i + 1;
      max = pVars[i];
    }
  }

  for(int i = 0; i < nVars.size(); ++i){
    if(nVars[i] > max){
      var = -(i + 1);
      max = nVars[i];
    }
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
    anyEmpty |= c->isEmpty();
  }
}

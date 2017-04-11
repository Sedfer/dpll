#include <vector>

class Clause
{
 private:
  std::vector<bool> p;
  std::vector<bool> n;

  int myCount;

 public:
  Clause();
  Clause(int size);

  int size() const;
  void set(int var, bool value = true);
  bool get(int var) const;

  bool isEmpty() const;
  int count() const;
  int findSingle() const;
  int chooseVariable() const;
};

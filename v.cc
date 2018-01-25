#include <iostream>

using namespace std;

class Plant {
public:
  virtual void info();
};

void Plant::info() {
  cout << "I am a plant" << endl;
}

class Engineer {
public:
  virtual void greet() = 0;
};

int main(int argc, char const *argv[]) {
  Plant* p = new Plant();
  p->info();

  // Engineer* e = new Engineer();

  return 0;
}

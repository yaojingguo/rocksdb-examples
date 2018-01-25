#include <iostream>

using namespace std;

class Plant {
public:
  virtual void info();
};

void Plant::info() {
  cout << "I am a plant" << endl;
}

int main(int argc, char const *argv[]) {
  Plant* p = new Plant();
  p->info();
  return 0;
}

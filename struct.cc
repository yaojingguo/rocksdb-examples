#include <iostream>

using namespace std;

struct Thing {
  virtual void info() = 0;
};

struct People: public Thing {
  void info() {
    cout << "I am a person" << endl;
  }
};

class Dog {
public:
  void info() {}
};

int main(int argc, char const *argv[]) {
  People p;
  p.info();

  Dog d;
  d.info();

  return 0;
}

#include <stdio.h>
#include <assert.h>

class Person {
public:
  explicit Person(const char* name) {
    this->name = name;
  }
private:
  const char* name;
};

void foo(Person p) {

}

int main(int argc, char const *argv[]) {
  Person p("xiaoyu");
  foo(p);
  foo("Yang Xu");
  return 0;
}

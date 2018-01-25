#include <iostream>
#include <exception>

using namespace std;

class MyBase {
  public:
  virtual void test() {}
};

class MyChild : public MyBase {
  void test() {
    cout << "testing..." << endl;
  }
};

void foo() {
  MyBase  *base = new MyBase();
  MyChild *child = dynamic_cast<MyChild*>(base);

  if (child == 0) {
    cout << "Null pointer returned" << endl;
  }
}

void bar() {
  try {
    MyBase  *base = new MyBase();
    MyChild &child = dynamic_cast<MyChild&>(*base);
  } catch (bad_cast &e) {
    cout << e.what() << endl;
  }
}

void three() {
  MyBase  *base = new MyBase();
  MyChild &child = static_cast<MyChild&>(*base);
}

void print(int *p) {
    cout << *p << endl;
}

void four() {
  const int myConst = 5;
  int *nonConst = const_cast<int*>(&myConst);
  *nonConst = 10;
  print(&myConst);
  cout << "myConst:  " << myConst << endl;
  cout << "nonConst: " << *nonConst << endl;
}

int main()
{
  MyChild *child = new MyChild();
  MyBase  *base = dynamic_cast<MyBase*>(child); // ok
  base->test();
  four();
}

// whether foo is declared noexcept depends on if the expression
// T() will throw any exceptions
template <class T>
void foo() noexcept(noexcept(T())) {}

void bar() noexcept(true) {}
void baz() noexcept { throw 42; }  // noexcept is the same as noexcept(true)

#include <iostream>


int main()
{
    std::cout << noexcept(int()) << std::endl;
    foo<int>();  // noexcept(noexcept(int())) => noexcept(true), so this is fine

    bar();  // fine
    baz();  // compiles, but at runtime this calls std::terminate
}

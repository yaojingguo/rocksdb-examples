// CPP code to illustrate 
// string& string::assign (const char* chars, size_type chars_len)

#include <iostream>
#include <string>
using namespace std;

// Function to demonstrate assign
void assignDemo(string str)
{
  char ptr[] = "GeeksforGeeks";

	str.assign((const char*) ptr, 5);

	cout << "After assign() : ";
	cout << str;
  cout << endl;

  ptr[0] = 'X';
  cout << "ptr: " << ptr << endl;
  
	cout << "After assign() : ";
	cout << str;
  cout << endl;
}
		
// Driver code
int main()
{
	string str("Hello World!");

	cout << "Original String : " << str << endl;
	assignDemo(str);

	return 0;
}


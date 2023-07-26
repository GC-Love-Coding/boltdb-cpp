#include <cstddef>
#include <iostream>

using namespace std;

int main(int argc, char** argv) {
  byte a{1};
  byte b{2};

  cout << int(a & b) << endl;
  cout << int(a | b) << endl;
  cout << int(~a) << endl;
  cout << int(a ^ b) << endl;
  cout << int(a << 1) << endl;
  cout << int(a << 16) << endl;
  cout << int(a >> 1) << endl;

  return 0;
}
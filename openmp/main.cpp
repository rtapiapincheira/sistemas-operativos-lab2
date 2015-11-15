#include <iostream>

using namespace std;

int main() {

  #pragma omp parallel
  {
    cout << "Hola mundo" << endl;
  }

  return 0;
}

#include <iostream>

using namespace std;

int main() {

  #pragma omp parallel num_threads(5)
  {
    cout << "Hola mundo" << endl;
  }

  return 0;
}

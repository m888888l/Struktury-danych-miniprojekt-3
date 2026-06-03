#include <iostream>
#include "HTOpenAddressing.hpp"
#include "HTSeparateChaining.hpp"

using namespace std;

int main(){
HTOpenAddressing tabela(3);
HTSeparateChaining chain(1);

chain.insert(3, 3);
chain.insert(3, 3);
chain.insert(4, 4);
chain.insert(40, 40);

chain.remove(30);
chain.remove(3);

chain.print();

return 0;
}
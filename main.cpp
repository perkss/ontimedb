#include <iostream>

extern "C" {
#include "LibraryCode.h"
}


int main(int argc, char **argv) {
    std::cout << "Actual application code \n";
    std::cout << "2 + 3 = " << add(2, 3) << '\n';
    return 0;
}
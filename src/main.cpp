#include <iostream>
#include "tool.h"

int main(int argc, char **argv)
{
    Tool tool;

    tool.printN("Hello", 10);
    for(int i = 0; i < 100; i++)
    {
        std::cout << "Kertoma " << i << " : " << tool.kertoma(i) << std::endl;
    }
}

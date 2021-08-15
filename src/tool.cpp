#include "tool.h"


void Tool::printN(std::string word, int count)
{
    count = abs(count);
    for(int i = 0; i < count; i++)
        std::cout << word << std::endl;
}

unsigned long Tool::kertoma(int x)
{
    return x <= 1 ? 1 : kertoma(x-1)*x;
}

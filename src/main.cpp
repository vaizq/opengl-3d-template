#include "application.hpp"
#include <iostream>


int main(int argc, char **argv)
{

    Application app;
    if(app.create() == -1)
    {
        std::cout << "Failed to create application." << std::endl;
    };
    app.run();
    
    return 0;
}


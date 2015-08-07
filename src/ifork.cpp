#include <iostream>
#include <unistd.h>


void internal_fork()
{
    pid_t child = -1;
    child = fork();
    if (child > 0)
    {
        if (setpgid(child, child) != 0)
        {
            std::cout << "Fail to set pgid from parent" << std::endl;
        }
    }
    else if (child == 0)
    {
        if (setpgid(0, child) != 0)
        {
            std::cout << "Fail to set pgid from child" << std::endl;
        }

        pid_t pgid = getpgid(child);
        std::cout << "child with pid (" << getpid()
                  << ") " << "has pgid (" << pgid << ")" << std::endl;

        while(true)
        {
            std::cout << "child alive (pid: " << getpid() << ")" << std::endl;
            sleep(5);
        }
    }
    else
    {
        std::cout << "fork failed" << std::endl;
    }
} 


int main()
{
    std::string input;
    while (true)
    {
        std::cout << "want to fork (y/n): ";
        std::cin >> input;
        if (std::cin.good() && !input.empty())
        {
            if (input == "y")
            {
                internal_fork(); 
            }
            else if (input == "n")
            {
                std::cout << "bye";
                break;
            }
            else
            {
                std::cout << "invalid input" << std::endl;
            }
        }
    }

    return (0);
}

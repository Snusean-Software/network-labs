#include <iostream>
#include <string>
#include <fstream>

#include <sys/types.h>
#include <unistd.h>

//const std::string ip = "172.23.12.132";
const std::string ip = "127.0.0.1";
const std::string port = "31337";
enum class Encrypt
{
    NETCAT,
    CRYPTCAT
} encrypt = Encrypt::CRYPTCAT;

int main(int argc, char *argv[])
{
    try
    {
        if (argc != 2)
        {
            throw std::runtime_error("Incorrect argument!");
        }

        std::string arg = argv[1];
        if (arg == "-chat")
        {
            bool work = true;
            // open client
            while (work)
            {
                std::string command;
                if (encrypt == Encrypt::NETCAT)
                {
                    command = "nc " + ip + ' ' + port;
                }
                else
                {
                    command = "cryptcat -n " + ip + ' ' + port;
                }
                system(command.c_str());

                std::cout << "Server not found or connection was interrupted.\nPrint 'R' to try again or 'Q' to quit: ";
                char k;
                while (std::cin >> k)
                {
                    if (k == 'r' or k == 'R')
                    {
                        break;
                    }
                    else if (k == 'q' or k == 'Q')
                    {
                        work = false;
                        break;
                    }
                    else
                    {
                        std::cout << "\nWrite 'Q' or 'R'!";
                    }
                }
            }
        }
        else if (arg == "-file")
        {
            while (true)
            {
                std::cout << "Enter full file path or type 'Q' if you want to stop client: ";
                std::string filepath;
                std::cin >> filepath;
                if (filepath == "q" || filepath == "Q")
                {
                    break;
                }
                std::ifstream test(filepath.c_str());
                if (!test)
                {
                    std::cerr << "Incorrect filepath! Try again.\n";
                    continue;
                }
                test.close();

                std::string command;
                if (encrypt == Encrypt::NETCAT)
                {
                    command = "nc -v -w 30 -p " + port + " -l < " + filepath;
                }
                else
                {
                    command = "cryptcat -n " + ip + ' ' + port + " < " + filepath;
                }
                system(command.c_str());
            }
        }
        else
            throw std::runtime_error("Incorrect argument!");
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}
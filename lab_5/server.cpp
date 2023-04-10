#include <iostream>
#include <string>
#include <fstream>

#include <sys/types.h>
#include <unistd.h>

const std::string ip = "172.23.12.132";
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
        if (argc != 2 && argc != 3)
        {
            throw std::runtime_error("Incorrect argument!");
        }

        std::string arg = argv[1];
        if (arg == "-chat")
        {
            // open server
            std::string command;
            if (encrypt == Encrypt::NETCAT)
            {
                command = "nc -l -p " + port;
            }
            else
            {
                command = "cryptcat -l -n -p " + port;
            }
            system(command.c_str());
        }
        else if (arg == "-file")
        {
            // open server
            while (true)
            {
                std::cout << "Enter filename or type 'Q' if you want to stop server: ";
                std::string filename;
                std::cin >> filename;
                if (filename == "q" || filename == "Q")
                {
                    break;
                }
                std::string command;

                if (encrypt == Encrypt::NETCAT)
                {
                    command = "nc -v -w 2 " + ip + ' ' + port + " > " + filename;
                }
                else
                {
                    command = "cryptcat -l -w 30 -n -p " + port +  " > " + filename;
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
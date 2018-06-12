//
// main.cpp for indie_studio in /home/debruy_p/projects/tek2/cpp/cpp_indie_studio/src/Server
//
// Made by Pierre Debruyne
// Login   <debruy_p@epitech.eu>
//
// Started on  Mon Apr 25 22:31:17 2016 Pierre Debruyne
// Last update Fri Jun  3 18:43:42 2016 olivier
//

#include <iostream>
#include <csignal>
#include "Server.hh"

int main(int ac, char **av)
{
    signal(SIGPIPE, SIG_IGN);
    if (ac != 3 && ac != 4) {
        std::cout << "Usage: ./server name port [password]" << std::endl;
        return 1;
    }
    try {
        if (Server::getSingleton().init(av[1], std::stoi(av[2]), (av[3]) ? av[3] : "") == 0) {
            Server::getSingleton().work();
        }
    } catch (std::invalid_argument &e) {
      std::cerr << "Wrong port... " << e.what() << std::endl;
    }

    return 0;
}

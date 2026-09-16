#include <iostream>
#include "Server.hpp"

Server::Server()
{
    std::cout << "Serveur créé" << std::endl;
}

Server::Server(const Server &other)
{
    std::cout << "Constructeur de copie" << std::endl;
}

Server &Server::operator=(Server &other)
{
    std::cout << "Operateur =" << std::endl;
    if (this != &other)
    {
    }
    return *this;
}

Server::~Server()
{
    std::cout << "Destructeur" << std::endl;
}

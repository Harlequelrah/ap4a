#include <iostream>
#include "Server.hpp"

Server::Server()
{
}

Server::Server(const Server &other)
{
}

Server &Server::operator=(const Server &other)
{
    std::cout << "Operateur =" << std::endl;
    if (this != &other)
    {
    }
    return *this;
}

Server::~Server()
{
}

void Server::consoleWriter(const std::string &type, double value)
{
    std::cout << type << " : " << value << std::endl;
}

void Server::fileWrite(const std::string &type, double value)
{
    std::ofstream fichier("logs/" + type + ".txt");
    fichier << type << " : " << value << std::endl;
    fichier.close();
}

std::ostream &operator<<(std::ostream &os, const Server &server)
{
    os << "Serveur";
    return os;
}

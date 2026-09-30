#ifndef SERVER_HPP
#define SERVER_HPP
#include <string>
#include <fstream>
#include <iostream>
class Server
{
public:
    // création normal
    Server();

    // création par copie
    Server(const Server &other);

    // affectation
    Server &operator=(const Server &other);

    // destructeur
    ~Server();

    // méthodes
    void consoleWriter(const std::string &type, double value);
    void fileWrite(const std::string &type, double value);

    friend std::ostream &operator<<(std::ostream& os ,const Server& server);
};

#endif

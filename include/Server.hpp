#ifndef SERVER_HPP
#define SERVER_HPP

class Server
{
public:
    // création normal
    Server();

    // création par copie
    Server(const Server &other);

    // affectation
    Server &operator=(Server &other);

    // destructeur
    ~Server();
    void consoleWriter();
};

#endif

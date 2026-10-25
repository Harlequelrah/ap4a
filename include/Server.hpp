#ifndef SERVER_HPP
#define SERVER_HPP
#include <filesystem>
#include <string>
#include <fstream>
#include <iostream>
#include "Measurement.hpp"
class Server
{
public:
    // Crée le serveur et prépare le répertoire des journaux.
    Server();

    // Constructeur de copie de la forme canonique.
    Server(const Server &other);

    // Opérateur d'affectation de la forme canonique.
    Server &operator=(const Server &other);

    // Détruit le serveur ; les fichiers sont gérés par les flux locaux.
    ~Server();

    // Affiche une mesure horodatée dans la console.
    void consoleWrite(const std::string &type,
                      const Measurement &value);

    // Ajoute une mesure au fichier CSV associé à son type.
    void fileWrite(const std::string &type,
                   const Measurement &value);

    // Centralise l'affichage, la sauvegarde et l'analyse d'une mesure.
    void processMeasurement(const std::string &type,
                            const Measurement &value);

    // Applique les seuils d'alerte aux mesures reçues.
    void analyzeMeasurement(const std::string &type,
                            const Measurement &value);

    // Permet d'afficher une représentation textuelle du serveur.
    friend std::ostream &operator<<(std::ostream &os, const Server &server);

private:
    // Affiche et persiste une alerte dans logs/alerts.log.
    void logAlert(const std::string &message);
};

#endif

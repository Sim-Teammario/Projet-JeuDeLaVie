// Projet-JeuDeLaVie.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//
// Created by: SimTeammario
// Ce jeu est une version C++ / SFML du jeu de la vie de Rad Conway

#include <iostream>
#include <string>
#include "Game.hpp"
#include "UI.hpp"

int main() {
    std::string filePath = "C:\\Users\\simon\\source\\repos\\Projet-JeuDeLaVie\\Grid3.txt"; // Chemin du fichier de base
    Game game;
    UI ui;

    std::cout << "Chargement du fichier de grille..." << std::endl;
    game.run(filePath); 
    std::cout << "Fichier de grille chargé." << std::endl;

    std::cout << "Affichage de la grille dans la console :" << std::endl;
    ui.printGridToConsole(game.getGrid());

    std::cout << "Lancement de l'interface utilisateur..." << std::endl;
    ui.run(game, "output");
    std::cout << "Interface utilisateur lancée." << std::endl;

    return 0;
}


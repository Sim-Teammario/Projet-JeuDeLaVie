#pragma once

#include <iostream>
#include <fstream> // Pour la lecture et l'�criture de fichiers
#include <string>
#include <vector>

class File {
public:
    // Constructeur de la classe File
    File() {}

    // Destructeur de la classe File
    ~File() {}

    // M�thode pour lire le fichier et extraire les donn�es
    bool readFile(const std::string& filePath, int& rows, int& cols, std::vector<std::vector<bool>>& cells) {
        std::ifstream file(filePath); 
        if (!file.is_open()) {
            std::cerr << "Erreur lors de l'ouverture du fichier : " << filePath << std::endl;
            return false;
        }

        file >> rows >> cols; // Lecture des dimensions de la grille (lignes, colonnes) 
        cells.resize(rows, std::vector<bool>(cols)); // Redimensionnement de la grille

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) { // Lecture de l'�tat de chaque cellule
                int cellState;
                file >> cellState;
                cells[i][j] = (cellState == 1);
            }
        }

        file.close();
        std::cout << "Fichier de grille lu avec succ�s : " << rows << " lignes, " << cols << " colonnes." << std::endl;
        return true;
    }

    // M�thode pour �crire l'�tat actuel de la grille dans un fichier
    bool writeFile(const std::string& filePath, int rows, int cols, const std::vector<std::vector<bool>>& cells) const {
        std::ofstream file(filePath);
        if (!file.is_open()) {
            std::cerr << "Erreur lors de l'ouverture du fichier : " << filePath << std::endl;
            return false;
        }

        file << rows << " " << cols << std::endl;  // �criture des dimensions de la grille (lignes, colonnes)

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                file << (cells[i][j] ? 1 : 0) << " ";
            }
            file << std::endl;
        }

        file.close();
        std::cout << "�tat de la grille �crit avec succ�s dans le fichier : " << filePath << std::endl;
        return true;
    }
};

/*
Les fichiers de grilles seront dans le format suivant :
5 10
0 0 1 0 0 0 0 0 0 0
0 0 0 1 0 0 0 0 0 0
0 1 1 1 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0

ici 5 repr�sente le nombre de lignes et 10 le nombre de colonnes
Les 0 et 1 repr�sentent l'�tat des cellules (0 pour morte et 1 pour vivante)
*/

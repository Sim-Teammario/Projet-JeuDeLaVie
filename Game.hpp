#pragma once

#include <iostream>
#include <vector>
#include <thread> 
#include <chrono>
#include "Cell.hpp"
#include "File.hpp"
#include "Grid.hpp"

class Game {
public:
    // Constructeur
    Game();

    // Destructeur
    ~Game();

    // Méthode pour lancer le jeu
    void run(const std::string& filePath, int iterations = -1);

    // Méthode pour effectuer une itération du jeu
    void iterate();

    // Méthode pour récupérer la grille
    Grid getGrid() const;

    int getCurrentIteration() const;

private:
    Grid grid_; // Grille du jeu
    File file_;
    int currentIteration_; // Compteur d'itérations
    bool isToric_; // Booléen indiquant si la grille est torique
    bool isFinished_; // Booléen indiquant si le jeu est terminé
    int maxIterations_; // Nombre maximum d'itérations

    // Méthode pour mettre à jour l'état de la grille
    void updateGrid();
};

// Implémentation des méthodes de la classe Game

Game::Game() : currentIteration_(0), isToric_(false), isFinished_(false), maxIterations_(-1) {}

Game::~Game() {}

void Game::run(const std::string& filePath, int iterations) {
    int rows, cols;
    std::vector<std::vector<bool>> cells;

    std::cout << "Lecture du fichier de grille..." << std::endl;
    if (!file_.readFile(filePath, rows, cols, cells)) {
        std::cerr << "Erreur lors de la lecture du fichier." << std::endl;
        return;
    }
    std::cout << "Fichier de grille lu avec succes : " << rows << " lignes, " << cols << " colonnes." << std::endl;

    grid_ = Grid(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            grid_.setCellState(i, j, cells[i][j]);
        }
    }

    maxIterations_ = iterations;
    currentIteration_ = 0;
    isFinished_ = false;
}



void Game::iterate() {
    if (maxIterations_ != -1 && currentIteration_ >= maxIterations_) {
        isFinished_ = true;
        return;
    }

    std::cout << "Iteration " << currentIteration_ << std::endl;
    updateGrid();
    ++currentIteration_;
}


Grid Game::getGrid() const {
    return grid_;
}

void Game::updateGrid() {
    grid_.updateGrid();
}

int Game::getCurrentIteration() const {
    return currentIteration_;
}

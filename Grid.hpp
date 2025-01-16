#pragma once

#include <vector>
#include "Cell.hpp"

class Grid {
public:
    // Constructeur par défaut
    Grid();

    // Constructeur de la grille avec les dimensions (lignes, colonnes)
    Grid(int rows, int cols);

    // Destructeur de la classe Grid
    ~Grid();

    // Retourne le nombre de lignes de la grille
    int getRows() const;

    // Retourne le nombre de colonnes de la grille
    int getCols() const;

    // Retourne l'état d'une cellule à une position donnée
    bool getCellState(int row, int col) const;

    // Modifie l'état d'une cellule à une position donnée
    void setCellState(int row, int col, bool state);

    // Met à jour l'état de toutes les cellules de la grille selon les règles du jeu de la vie
    void updateGrid();

    // Méthode pour afficher la grille (pour le mode console)
    void printGrid() const;

private:
    int rows_; // Nombre de lignes
    int cols_; // Nombre de colonnes
    std::vector<std::vector<Cell>> cells_; // Grille de cellules

    // Méthode utilitaire pour compter les voisins vivants d'une cellule
    int countLivingNeighbors(int row, int col) const;
};


// Implémentation des méthodes de la classe Grid

// Constructeur par défaut
Grid::Grid() : rows_(0), cols_(0) {}

// Constructeur de la grille avec les dimensions (lignes, colonnes)
Grid::Grid(int rows, int cols)
	: rows_(rows), cols_(cols), cells_(rows, std::vector<Cell>(cols)) { // Initialisation de la grille avec des cellules mortes
}

Grid::~Grid() {}

int Grid::getRows() const {
    return rows_;
}

int Grid::getCols() const {
    return cols_;
}

bool Grid::getCellState(int row, int col) const {
    return cells_[row][col].isAlive();
}

void Grid::setCellState(int row, int col, bool state) { // Méthode pour modifier l'état d'une cellule à une position donnée
    cells_[row][col].setAlive(state);
}

void Grid::updateGrid() {
    std::vector<std::vector<Cell>> newCells = cells_;

    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            int livingNeighbors = countLivingNeighbors(i, j);
            if (cells_[i][j].isAlive()) {
                if (livingNeighbors < 2 || livingNeighbors > 3) {
                    newCells[i][j].setAlive(false);
                }
            }
            else {
                if (livingNeighbors == 3) {
                    newCells[i][j].setAlive(true);
                }
            }
        }
    }

    cells_ = newCells;
}

int Grid::countLivingNeighbors(int row, int col) const {
    int count = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) continue;
            int newRow = row + i;
            int newCol = col + j;
            if (newRow >= 0 && newRow < rows_ && newCol >= 0 && newCol < cols_) {
                if (cells_[newRow][newCol].isAlive()) {
                    ++count;
                }
            }
        }
    }
    return count;
}

void Grid::printGrid() const {
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
			std::cout << (cells_[i][j].isAlive() ? 'O' : '.'); // Affichage de 'O' pour une cellule vivante et '.' pour une cellule morte
        }
        std::cout << std::endl;
    }
}
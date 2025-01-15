#pragma once

class Cell {
public:
    // Constructeur par défaut
    Cell() : isAlive_(false) {}

    // Constructeur avec état initial
    Cell(bool isAlive) : isAlive_(isAlive) {}

    // Obtenir l'état de la cellule
    bool isAlive() const {
        return isAlive_;
    }

    // Définir l'état de la cellule
    void setAlive(bool isAlive) {
        isAlive_ = isAlive;
    }

private:
    bool isAlive_; // true si la cellule est vivante, false si morte
};


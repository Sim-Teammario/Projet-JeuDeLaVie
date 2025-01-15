#pragma once

class Cell {
public:
    // Constructeur par d�faut
    Cell() : isAlive_(false) {}

    // Constructeur avec �tat initial
    Cell(bool isAlive) : isAlive_(isAlive) {}

    // Obtenir l'�tat de la cellule
    bool isAlive() const {
        return isAlive_;
    }

    // D�finir l'�tat de la cellule
    void setAlive(bool isAlive) {
        isAlive_ = isAlive;
    }

private:
    bool isAlive_; // true si la cellule est vivante, false si morte
};


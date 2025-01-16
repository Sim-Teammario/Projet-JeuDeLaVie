#pragma once

#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include <string>
#include <chrono>
#include <thread>
#include <iostream>
#include <fstream>

#ifdef _WIN32
#include <direct.h>
#else
#include <sys/stat.h>
#endif

// Classe pour l'interface utilisateur
class UI {
public:
    // Constructeur
    UI();

    // Destructeur
    ~UI();

    // M�thode pour d�marrer l'interface graphique
    void run(Game& game, std::string output_folder);

    // M�thode pour dessiner la grille
    void drawGrid(const Grid& grid, sf::RenderWindow& window) const;

    // M�thode pour enregistrer l'�tat du jeu dans un fichier
    void saveState(const Grid& grid, int iteration, const std::string& output_folder);

    // M�thode pour afficher la grille dans la console
    void printGridToConsole(const Grid& grid) const;

    // M�thode pour faire une pause entre deux it�rations
    void pause(int duration);

    // M�thode pour g�rer les �v�nements de clavier
    void handleKeyboardEvent(const sf::Event& event, Game& game, const std::string& output_folder);

private:
    sf::RenderWindow window_;
    const int cellSize_ = 10;
    const int windowMargin_ = 50;
    int windowHeight_ = 0;
    int windowWidth_ = 0;
    bool consoleMode_;
    bool saveOnClose_;
};

// Impl�mentation des m�thodes de la classe UI

UI::UI() : window_(sf::VideoMode(800, 600), "Jeu de la Vie"), consoleMode_(false), saveOnClose_(false) {
    windowHeight_ = window_.getSize().y;
    windowWidth_ = window_.getSize().x;
}


UI::~UI() {}

void UI::run(Game& game, std::string output_folder) {
    int iteration = 0;
    auto lastTime = std::chrono::high_resolution_clock::now();

    while (window_.isOpen()) {
        sf::Event event;
        while (window_.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                saveState(game.getGrid(), game.getCurrentIteration(), output_folder);
                window_.close();
            }
            handleKeyboardEvent(event, game, output_folder);
        }

        auto currentTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = currentTime - lastTime;
        if (elapsed.count() >= 1.0) { // Limiter � une it�ration par seconde
            game.iterate();
            lastTime = currentTime;
            iteration++;

            std::cout << "Iteration " << iteration << std::endl;
            printGridToConsole(game.getGrid());
        }

        // Effacement de la fen�tre avec la couleur violette.
        window_.clear(sf::Color(128, 0, 128)); // Fond violet

        // Dessin de la grille.
        drawGrid(game.getGrid(), window_);

        // Affichage de la fen�tre.
        window_.display();

        // Pause explicite pour s'assurer que la boucle ne tourne pas trop rapidement
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Pause de 100 millisecondes
    }
}

void UI::drawGrid(const Grid& grid, sf::RenderWindow& window) const {
    int gridWidth = grid.getCols() * cellSize_;
    int gridHeight = grid.getRows() * cellSize_;
    int offsetX = (windowWidth_ - gridWidth) / 2;
    int offsetY = (windowHeight_ - gridHeight) / 2;

    for (int i = 0; i < grid.getRows(); ++i) {
        for (int j = 0; j < grid.getCols(); ++j) {
            sf::RectangleShape cell(sf::Vector2f(static_cast<float>(cellSize_), static_cast<float>(cellSize_)));
            cell.setPosition(static_cast<float>(j * cellSize_ + offsetX), static_cast<float>(i * cellSize_ + offsetY));
            cell.setFillColor(grid.getCellState(i, j) ? sf::Color::Black : sf::Color::White);
            window.draw(cell);
        }
    }
}

void UI::saveState(const Grid& grid, int iteration, const std::string& output_folder) {
    // Cr�er le dossier de sortie s'il n'existe pas
    std::string filename = output_folder + "/iteration_" + std::to_string(iteration) + ".txt"; //le fichier aura le nom "iteration_X"
    std::ofstream file(filename);
    if (file.is_open()) {
        file << grid.getRows() << " " << grid.getCols() << std::endl;
        for (int i = 0; i < grid.getRows(); ++i) {
            for (int j = 0; j < grid.getCols(); ++j) {
                file << (grid.getCellState(i, j) ? 1 : 0) << " ";
            }
            file << std::endl;
        }
        file.close();
        std::cout << "Etat de la grille ecrit avec succes dans le fichier : " << filename << std::endl;
    }
    else {
        std::cerr << "Erreur lors de l'ouverture du fichier : " << filename << std::endl;
    }
}


void UI::printGridToConsole(const Grid& grid) const {
    for (int i = 0; i < grid.getRows(); ++i) {
        for (int j = 0; j < grid.getCols(); ++j) {
            std::cout << (grid.getCellState(i, j) ? 'O' : '.');
        }
        std::cout << std::endl;
    }
}

void UI::pause(int duration) {
    std::this_thread::sleep_for(std::chrono::milliseconds(duration));
}

void UI::handleKeyboardEvent(const sf::Event& event, Game& game, const std::string& output_folder) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.control && event.key.code == sf::Keyboard::S) {
            std::cout << "Sauvegarde de l'etat du jeu a l'iteration " << game.getCurrentIteration() << std::endl;
            saveState(game.getGrid(), game.getCurrentIteration(), output_folder);
        }
    }
}

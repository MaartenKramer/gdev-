#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "player.h"
#include "enemy.h"

class Game {
private:
    sf::RenderWindow window;
    sf::Font font;
    sf::Text scoreText;
    sf::Text gameOverText;

    Player* player;
    std::vector<Enemy*> enemies;

    float spawnTimer;
    float spawnInterval;

    int score;
    bool gameOver;
    bool gameWon;

    const float screenWidth;
    const float screenHeight;
    const int winScore;

    void spawnEnemy();
    void handleCollisions();
    void update(float deltaTime);
    void render();
    void deleteOffscreenEnemies();

public:
    Game();
    ~Game();

    void run();
    void restart();
};
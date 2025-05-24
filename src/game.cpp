    #include "..\\include\\game.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

Game::Game()
    : spawnTimer(0),
    spawnInterval(1.0f),
    score(0),
    gameOver(false),
    gameWon(false),
    screenWidth(800.0f),
    screenHeight(600.0f),
    winScore(30)
{
    // Generate random seed
    srand(static_cast<unsigned int>(time(nullptr)));

    // Make window
    window.create(sf::VideoMode(screenWidth, screenHeight), "////PRO RACING////");
    window.setFramerateLimit(60);

    // Load font
    font.loadFromFile("fonts\\framd.ttf");

    // Score text
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10, 10);

    // Game over text
    gameOverText.setFont(font);
    gameOverText.setCharacterSize(48);
    gameOverText.setFillColor(sf::Color::Red);

    // Spawn player
    player = new Player(screenWidth / 2, screenHeight - 50, 40, sf::Color::Green);
}

// Resets characters
Game::~Game() {
    delete player;

    for (auto enemy : enemies) {
        delete enemy;
    }
    enemies.clear();
}

//Spawn enemy
void Game::spawnEnemy() {
    float size = 75.0f;
    float xMin = screenWidth * 0.25f;
    float xMax = screenWidth * 0.75f;
    float x = xMin + static_cast<float>(rand()) / RAND_MAX * (xMax - xMin);
    sf::Color color = sf::Color::Magenta;

    enemies.push_back(new Enemy(x, -size, size, color, screenWidth));
}

// Check for collisions
void Game::handleCollisions() {
    for (auto enemy : enemies) {
        if (player->getBounds().intersects(enemy->getBounds())) {
            gameOver = true;
            return;
        }
    }

    // Win condition check
    if (score >= winScore) {
        gameOver = true;
        gameWon = true;
    }
}

// Delete any offscreen enemies and add 1 to score
void Game::deleteOffscreenEnemies() {
    auto it = enemies.begin();
    while (it != enemies.end()) {
        Enemy* enemy = *it;

        if (enemy->isOffScreen(screenHeight)) {
            score += 1;
            delete enemy;
            it = enemies.erase(it);
        }
        else {
            ++it;
        }
    }
}

void Game::run() {
    sf::Clock clock;

    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Restart at game over if enter is pressed
            if (gameOver && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return) {
                restart();
            }
        }

        if (!gameOver) {
            player->handleInput(deltaTime);
            update(deltaTime);
        }

        render();
    }
}

void Game::update(float deltaTime) {
    // Spawn new enemies
    spawnTimer += deltaTime;
    if (spawnTimer >= spawnInterval) {
        spawnTimer = 0;
        spawnEnemy();

        // Slowly increase enemy spawns
        spawnInterval = std::max(0.5f, spawnInterval - 0.025f);
    }

    // Update player actions
    player->update(deltaTime);
    player->constrainToScreen(screenWidth);

    // Update enemies actions
    for (auto enemy : enemies) {
        enemy->update(deltaTime);
    }
    deleteOffscreenEnemies();

    handleCollisions();

    // Translate score to text
    scoreText.setString("Score: " + std::to_string(score) + " / " + std::to_string(winScore));
}

void Game::render() {

    //Background color
    window.clear(sf::Color(60, 60, 60));

    // Render player
    player->render(window);

    // Render enemies
    for (auto enemy : enemies) {
        enemy->render(window);
    }

    // Display score
    window.draw(scoreText);

    // Display game over varients
    if (gameOver) {
        if (gameWon) {
            gameOverText.setString("You Win!");
            gameOverText.setFillColor(sf::Color::Green);
        }
        else {
            gameOverText.setString("Game Over!");
            gameOverText.setFillColor(sf::Color::Red);
        }

        // Game text display
        sf::FloatRect gameOverBounds = gameOverText.getLocalBounds();
        gameOverText.setPosition(
            (screenWidth - gameOverBounds.width) / 2,
            (screenHeight - gameOverBounds.height) / 2 - 30
        );
        window.draw(gameOverText);

        // Restart text display
        sf::Text restartText;
        restartText.setFont(font);
        restartText.setCharacterSize(24);
        restartText.setFillColor(sf::Color::White);
        restartText.setString("Press Enter to restart");
        sf::FloatRect restartBounds = restartText.getLocalBounds();
        restartText.setPosition(
            (screenWidth - restartBounds.width) / 2,
            (screenHeight - restartBounds.height) / 2 + 50
        );
        window.draw(restartText);
    }

    window.display();
}

void Game::restart() {
    // Reset all values
    score = 0;
    gameOver = false;
    gameWon = false;
    spawnInterval = 1.0f;
    spawnTimer = 0;

    // Reset player position
    player->rigidbody.position = Vector2(screenWidth / 2, screenHeight - 50);
    player->rigidbody.velocity = Vector2(0, 0);

    // delete all enemies
    for (auto enemy : enemies) {
        delete enemy;
    }
    enemies.clear();
}
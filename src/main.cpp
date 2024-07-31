#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>

using namespace sf;
using namespace std;

class Projectile {
public:
    CircleShape shape;
    float speed;
    Vector2f direction;

    Projectile(float radius, float speed, float startX, float startY, float targetX, float targetY)
        : speed(speed) {
        shape.setRadius(radius);
        shape.setFillColor(Color::Red);
        shape.setPosition(startX, startY);

        float dx = targetX - startX;
        float dy = targetY - startY;
        float length = sqrt(dx * dx + dy * dy);
        direction = Vector2f(dx / length, dy / length);
    }

    void move() {
        shape.move(direction * speed);
    }

    void draw(RenderWindow& window) {
        window.draw(shape);
    }
};

class Character {
private:
    float w; // Largura
    float h; // Altura
    float spd; // Velocidade
    int life; // Vida
    RectangleShape shape;
    Vector2f direction;
    bool moving;

public:
    float posX; // Posição do personagem
    float posY; // Posição do personagem
    Vector2f targetPosition;

    Character(float width, float height, float speed, int vida, float X, float Y) // Construtor
        : w(width),
        h(height),
        spd(speed),
        life(vida),
        posX(X),
        posY(Y),
        shape(Vector2f(width, height)),
        moving(false) {
        shape.setFillColor(Color::Cyan);
        shape.setPosition(X, Y);
    }

    void moveTo(float x, float y) {
        targetPosition = Vector2f(x, y);
        float dx = x - posX;
        float dy = y - posY;
        float length = sqrt(dx * dx + dy * dy);
        direction = Vector2f(dx / length, dy / length);
        moving = true;
    }

    void updateMovement() {
        if (moving) {
            float dx = direction.x * spd;
            float dy = direction.y * spd;

            if (sqrt(pow(targetPosition.x - posX, 2) + pow(targetPosition.y - posY, 2)) <= spd) {
                posX = targetPosition.x;
                posY = targetPosition.y;
                moving = false;
            } else {
                posX += dx;
                posY += dy;
            }
            
            shape.setPosition(posX, posY);
        }
    }

    void draw(RenderWindow& window) { // Desenhar o corpo do personagem na janela
        window.draw(shape);
    }

    Vector2f getPosition() const { // Nova função para obter a posição do personagem
        return shape.getPosition();
    }
};

int main() {
    RenderWindow window(VideoMode(800, 600), "Game Window");
    Character personagem(50.f, 50.f, 0.1, 100, 100.f, 100.f); // Velocidade do personagem ajustada para 2
    vector<Projectile> projectiles;

    while (window.isOpen()) {
        Event event; // Inicialização da variável que captura eventos
        while (window.pollEvent(event)) {
            switch (event.type) {
                case Event::Closed:
                    window.close();
                    break;
                case Event::KeyPressed: // Case para a captura de evento de teclas pressionadas
                    if (event.key.code == Keyboard::Escape) {  // Fechar a aplicação em caso de apertar 'Esc'
                        window.close();
                    }
                    break;
                case Event::MouseButtonPressed:
                    if (event.mouseButton.button == Mouse::Right) {
                        personagem.moveTo(event.mouseButton.x, event.mouseButton.y);
                    }
                    if (event.mouseButton.button == Mouse::Left) {
                        Vector2f characterPos = personagem.getPosition();
                        projectiles.push_back(Projectile(5.f, 0.08, characterPos.x + 25.f - 2.5f, characterPos.y, event.mouseButton.x, event.mouseButton.y)); // Velocidade do projétil ajustada para 2
                    }
                    break;
            }
        }

        personagem.updateMovement();

        for (auto& projectile : projectiles) {
            projectile.move();
        }

        window.clear();
        personagem.draw(window);
        for (auto& projectile : projectiles) {
            projectile.draw(window);
        }
        window.display();
    }
    return 0;
}

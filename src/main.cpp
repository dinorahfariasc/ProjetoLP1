#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class Character {
    private:
    float w; // Largura
    float h; // Altura
    float spd; // Velocidade
    int life; // Vida
    RectangleShape shape;
    
    public:

    float posX; // Posição do personagem
    float posY; // Posição do personagem

    Character(float width, float height, float speed, int vida, float X, float Y) // Construtor
        : w(width),
        h(height),
        spd(speed),
        life(vida),
        posX(X),
        posY(Y),
        shape(Vector2f(width, height)) {
        shape.setFillColor(Color::Cyan);
        shape.setPosition(X, Y);
    }

    void setPosition(float x, float y) { // Atualização da posição do personagem
        posX = x;
        posY = y;
        shape.setPosition(posX, posY);
    }

    void updateMovement(float wWindow, float hWindow) {
        if (Keyboard::isKeyPressed(Keyboard::A) && posX > 0) {
            posX -= spd;
        }
        if (Keyboard::isKeyPressed(Keyboard::D) && posX + w < wWindow) {
            posX += spd;
        }
        if (Keyboard::isKeyPressed(Keyboard::W) && posY > 0) {
            posY -= spd;
        }
        if (Keyboard::isKeyPressed(Keyboard::S) && posY + h < hWindow) {
            posY += spd;
        }
        shape.setPosition(posX, posY);  
    }


    void draw(RenderWindow& window) { // Desenhar o corpo do personagem na janela
        window.draw(shape);
    }
};

int main() {
    RenderWindow window(VideoMode(800, 600), "Game Window");
    Character personagem(50.f, 50.f, 2, 100, 100.f, 100.f);

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
                    
                    personagem.updateMovement(800.f, 600.f);

                    break;
                case Event::KeyReleased: // Case para a captura de evento de teclas soltas
                    cout << "Key released: " << event.key.code << endl;
                    break;
            }
        }

        window.clear();
        personagem.draw(window);
        window.display();
    }
    return 0;
}
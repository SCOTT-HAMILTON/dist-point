#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include <string.h>

using namespace sf;

float getDistance(Vector2f a, Vector2f b);

int main()
{
    int nb_point = 0;
    int delay = (int)1000/60;

    Color pcolor(255, 255, 255);
    RectangleShape p1(Vector2f(2, 2));
    RectangleShape p2(Vector2f(2, 2));
    int marge = 2*p1.getGlobalBounds().height;
    p1.setFillColor(pcolor);
    p2.setFillColor(pcolor);

    p1.setPosition(-10, -10);
    p2.setPosition(-10, -10);
    RenderWindow fenetre(VideoMode(640, 480), "dist-point");

    Event event;
    Clock c;
    Time a, p;
    a = c.getElapsedTime();
    p = c.getElapsedTime();

    Color ccolor1(0, 255, 0);
    Color ccolor2(0, 0, 255);
    Color ccolor3(255, 0, 0);

    sf::VertexArray c1(sf::Lines, 2);
    sf::VertexArray c2(sf::Lines, 2);
    sf::VertexArray c3(sf::Lines, 2);
    c1[0].position = Vector2f(-10, -10);
    c1[1].position = Vector2f(-10, -10);
    c2[0].position = Vector2f(-10, -10);
    c2[1].position = Vector2f(-10, -10);
    c3[0].position = Vector2f(-10, -10);
    c3[1].position = Vector2f(-10, -10);

    c1[0].color = ccolor1;
    c1[1].color = ccolor1;
    c2[0].color = ccolor2;
    c2[1].color = ccolor2;
    c3[0].color = ccolor3;
    c3[1].color = ccolor3;


    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        std::cout << "can't charge the font : arial.ttf" << std::endl;
        return 1;
    }

    std::string text("0");
    char tmp[9] = "";

    sf::Text textDist("distance : 0", font, 30);
    textDist.setPosition(50, 50);
    textDist.setColor(Color::White);

    float distance = 0;

    while (fenetre.isOpen()){
        a = c.getElapsedTime();
        if (a.asMilliseconds()-p.asMilliseconds()>delay){
            p = c.getElapsedTime();
            while (fenetre.pollEvent(event)){
                if (event.type == Event::Closed)fenetre.close();

                if (event.type == Event::MouseButtonPressed){
                    nb_point++;
                    if (nb_point >= 3){
                        nb_point = 1;
                    }
                    if (nb_point == 1){
                        c1[0].position = Vector2f(-10, -10);
                        c1[1].position = Vector2f(-10, -10);
                        c2[0].position = Vector2f(-10, -10);
                        c2[1].position = Vector2f(-10, -10);
                        c3[0].position = Vector2f(-10, -10);
                        c3[1].position = Vector2f(-10, -10);

                        p2.setPosition(-10, -10);
                        p1.setPosition(event.mouseButton.x, event.mouseButton.y);
                    }
                    if (nb_point == 2){
                        p2.setPosition(event.mouseButton.x, event.mouseButton.y);
                        if (p1.getPosition().x < p2.getPosition().x){
                            c1[0].position = Vector2f(p1.getPosition().x+marge, p1.getPosition().y+marge/2);
                            c1[1].position = Vector2f(p2.getPosition().x-marge, c1[0].position.y);
                        }else{
                            c1[0].position = Vector2f(p1.getPosition().x-marge, p1.getPosition().y+marge/2);
                            c1[1].position = Vector2f(p2.getPosition().x+marge, c1[0].position.y);
                        }

                        if (p1.getPosition().x < p2.getPosition().x){
                            if (p1.getPosition().y > p2.getPosition().y){
                                c2[0].position = Vector2f(c1[1].position.x+marge, c1[1].position.y-marge);
                                c2[1].position = Vector2f(p2.getPosition().x, p2.getPosition().y+marge);
                            }else{
                                c2[0].position = Vector2f(c1[1].position.x+marge, c1[1].position.y+marge);
                                c2[1].position = Vector2f(p2.getPosition().x, p2.getPosition().y-marge);
                            }

                        }else{
                            if (p1.getPosition().y > p2.getPosition().y){
                                c2[0].position = Vector2f(c1[1].position.x-marge, c1[1].position.y-marge);
                                c2[1].position = Vector2f(p2.getPosition().x, p2.getPosition().y+marge);
                            }else{
                                c2[0].position = Vector2f(c1[1].position.x-marge, c1[1].position.y+marge);
                                c2[1].position = Vector2f(p2.getPosition().x, p2.getPosition().y-marge);
                            }
                        }

                        if (p1.getPosition().x < p2.getPosition().x){
                            if (p1.getPosition().y > p2.getPosition().y){
                                c3[0].position = Vector2f(p1.getPosition().x+marge, p1.getPosition().y-marge);
                                c3[1].position = Vector2f(p2.getPosition().x-marge, p2.getPosition().y+marge);
                            }else{
                                c3[0].position = Vector2f(p1.getPosition().x+marge, p1.getPosition().y+marge);
                                c3[1].position = Vector2f(p2.getPosition().x-marge, p2.getPosition().y-marge);
                            }

                        }else{
                            if (p1.getPosition().y > p2.getPosition().y){
                                c3[0].position = Vector2f(p1.getPosition().x-marge, p1.getPosition().y-marge);
                                c3[1].position = Vector2f(p2.getPosition().x+marge, p2.getPosition().y+marge);
                            }else{
                                c3[0].position = Vector2f(p1.getPosition().x-marge, p1.getPosition().y+marge);
                                c3[1].position = Vector2f(p2.getPosition().x+marge, p2.getPosition().y-marge);
                            }
                        }

                        distance = getDistance(p1.getPosition(), p2.getPosition());
                        std::cout << "oui 1" << std::endl;
                        sprintf(tmp, "%f", distance);
                        std::cout << "oui 2" << std::endl;
                        text = "";
                        text = "distance : ";
                        std::cout << "oui 3" << std::endl;
                        text += std::string(tmp);
                        std::cout << "oui 4" << std::endl;
                        textDist.setString(text);
                        std::cout << "oui 5" << std::endl;
                    }
                }
            }
        }

        fenetre.draw(textDist);
        fenetre.draw(c3);
        fenetre.draw(c2);
        fenetre.draw(c1);
        fenetre.draw(p1);
        fenetre.draw(p2);
        fenetre.display();
        fenetre.clear();
    }

    return 0;
}

float getDistance(Vector2f a, Vector2f b){
    int cot1, cot2;
    if (a.x < b.x){
        cot1 = b.x-a.x;
        if (a.y < b.y){
            cot2 = b.y-a.y;
        }else{
            cot2 = a.y-b.y;
        }
    }

    else {
        cot1 = a.x-b.x;
        if (a.y < b.y){
            cot2 = b.y-a.y;
        }else{
            cot2 = a.y-b.y;
        }
    }
    return (float)std::sqrt(pow((double)cot1, (double)2)+pow((double)cot2, (double)2));
}

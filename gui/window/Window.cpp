/*
** EPITECH PROJECT, 2024
** Epitech_Tek2_YEP_Zappy
** File description:
** Window.cpp
*/

#include "Window.hpp"

Window::Window()
{
    _window.create(sf::VideoMode(1920, 1080), "Zappy");
    sf::Image *icon = new sf::Image();
    if (icon->loadFromFile("./resources/empire_nexus.jpeg"))
        _window.setIcon(1024, 1024, icon->getPixelsPtr());
    _globalFont = std::make_shared<sf::Font>();
    if (!_globalFont->loadFromFile("./resources/font.ttf"))
        std::cerr << "Error loading font" << std::endl;
}

Window::~Window() = default;

void Window::run(Parameters &params)
{
    if (_window.isOpen()) {
        getEvent(params);
        _window.clear();
        for (auto &i : _map) {
            _window.draw(*i);
        }
        if (_modals.find("info") != _modals.end())
            _modals["info"]->display(_window);
        _window.display();
    }
}

void Window::getEvent(Parameters &params)
{
    sf::Event event{};

    while (_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            _window.close();
        if (event.type == sf::Event::MouseButtonReleased) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                int index = 0;
                bool found = false;
                for (auto &i : _map) {
                    if (i->getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                        auto it = params._map[index];
                        displayInformation(it, params);
                        found = true;
                        break;
                    }
                    index++;
                }
                if (!found)
                    _modals.clear();
            }
        }
    }
}

void Window::displayInformation(const std::shared_ptr<Case>& selectedCase, Parameters &params)
{
    std::shared_ptr<Modal> modal = std::make_shared<Modal>();
    this->addComponentsModal(selectedCase, modal);
    int index = 0;
    for (auto &p : params._players) {
        if (p->getPosition()._x == selectedCase->_x && p->getPosition()._y == selectedCase->_y) {
            std::shared_ptr<sf::Text> playerText = std::make_shared<sf::Text>();
            std::string player = "Player: " + std::to_string(p->getId()) + "\n";
            playerText->setString(player);
            playerText->setCharacterSize(20);
            playerText->setFont(*_globalFont);
            playerText->setPosition(_window.getSize().x * 0.75 + 10, 300 + (index * 25));
            modal->addText(playerText);
        }
    }
    _modals.erase("info");
    _modals.insert({"info", modal});
}

void Window::addComponentsModal(const std::shared_ptr<Case> &selectedCase, std::shared_ptr<Modal> &modal)
{
    std::shared_ptr<sf::Text> cooText = std::make_shared<sf::Text>();
    std::string coo = "Case: Y:" + std::to_string(selectedCase->_y) + " X:" + std::to_string(selectedCase->_x) + "\n";
    cooText->setString(coo);
    cooText->setCharacterSize(20);
    cooText->setFont(*_globalFont);
    cooText->setPosition(_window.getSize().x * 0.75 + 10, 75);
    modal->addText(cooText);

    std::shared_ptr<sf::Text> foodText = std::make_shared<sf::Text>();
    std::string food = "Food: " + std::to_string(selectedCase->_food) + "\n";
    foodText->setString(food);
    foodText->setCharacterSize(20);
    foodText->setFont(*_globalFont);
    foodText->setPosition(_window.getSize().x * 0.75 + 10, 100);
    modal->addText(foodText);

    std::shared_ptr<sf::Text> linemateText = std::make_shared<sf::Text>();
    std::string linemate = "Linemate: " + std::to_string(selectedCase->_linemate) + "\n";
    linemateText->setString(linemate);
    linemateText->setCharacterSize(20);
    linemateText->setFont(*_globalFont);
    linemateText->setPosition(_window.getSize().x * 0.75 + 10, 125);
    modal->addText(linemateText);

    std::shared_ptr<sf::Text> deraumereText = std::make_shared<sf::Text>();
    std::string deraumere = "Deraumere: " + std::to_string(selectedCase->_deraumere) + "\n";
    deraumereText->setString(deraumere);
    deraumereText->setCharacterSize(20);
    deraumereText->setFont(*_globalFont);
    deraumereText->setPosition(_window.getSize().x * 0.75 + 10, 150);
    modal->addText(deraumereText);

    std::shared_ptr<sf::Text> siburText = std::make_shared<sf::Text>();
    std::string sibur = "Sibur: " + std::to_string(selectedCase->_sibur) + "\n";
    siburText->setString(sibur);
    siburText->setCharacterSize(20);
    siburText->setFont(*_globalFont);
    siburText->setPosition(_window.getSize().x * 0.75 + 10, 175);
    modal->addText(siburText);

    std::shared_ptr<sf::Text> mendianeText = std::make_shared<sf::Text>();
    std::string mendiane = "Mendiane: " + std::to_string(selectedCase->_mendiane) + "\n";
    mendianeText->setString(mendiane);
    mendianeText->setCharacterSize(20);
    mendianeText->setFont(*_globalFont);
    mendianeText->setPosition(_window.getSize().x * 0.75 + 10, 200);
    modal->addText(mendianeText);

    std::shared_ptr<sf::Text> phirasText = std::make_shared<sf::Text>();
    std::string phiras = "Phiras: " + std::to_string(selectedCase->_phiras) + "\n";
    phirasText->setString(phiras);
    phirasText->setCharacterSize(20);
    phirasText->setFont(*_globalFont);
    phirasText->setPosition(_window.getSize().x * 0.75 + 10, 225);
    modal->addText(phirasText);

    std::shared_ptr<sf::Text> thystameText = std::make_shared<sf::Text>();
    std::string thystame = "Thystame: " + std::to_string(selectedCase->_thystame) + "\n";
    thystameText->setString(thystame);
    thystameText->setCharacterSize(20);
    thystameText->setFont(*_globalFont);
    thystameText->setPosition(_window.getSize().x * 0.75 + 10, 250);
    modal->addText(thystameText);

    modal->setPosition(_window.getSize().x * 0.75, 50);
    modal->setSize(_window.getSize().x * 0.20, _window.getSize().y - 100);
    modal->setColor(100, 20, 20, 255);
}

void Window::rendMap(Parameters &params)
{
    for (auto &i : params._map) {
        std::shared_ptr<sf::RectangleShape> new_rect = std::make_shared<sf::RectangleShape>();
        if (params.getPlayerOnCase(i).empty())
            new_rect->setFillColor(sf::Color(85,107,47, 255));
        else
            new_rect->setFillColor(sf::Color(255, 99, 71, 255));
        new_rect->setSize(sf::Vector2f(32, 32));
        new_rect->setPosition(i->_x * 32 + 32, i->_y * 32 + 32);
        new_rect->setOutlineColor(sf::Color(128, 128, 128, 255));
        new_rect->setOutlineThickness(1);
        _map.push_back(new_rect);
    }
    params._eggs.renderEggs();
}

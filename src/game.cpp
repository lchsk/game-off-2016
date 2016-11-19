#include <iostream>

#include "game.h"

namespace pmt
{
    const std::string ASSETS_DIR = "assets/";

    Game::Game()
    {
        _window = std::make_unique<sf::RenderWindow>
            (sf::VideoMode(800, 450), "pimp-my-tank");

        _filenames = {
            "gun.png",
            "tank.png",
            "shell.png",
            "ground.png",
            "ground_sand.png",
            "ground_rock.png"
        };

        _tiles_map = {
            {1, "ground.png"},
            {2, "ground_sand.png"},
            {3, "ground_rock.png"}
        };

        for (std::string& filename : _filenames) {
            std::unique_ptr<sf::Texture> texture(new sf::Texture());

            std::string path = ASSETS_DIR + filename;

            if (! texture->loadFromFile(path)) {
                throw std::runtime_error("Unable to load " + path);
            }

            _textures[filename] = std::move(texture);
        }

        _player = std::make_shared<pmt::Tank>(
			_textures["tank.png"],
			_textures["gun.png"],
            0,
            false,
			100,
			350);

        _map = std::make_unique<pmt::Map>(_tiles_map, _textures);

        _bullet_mgr = std::make_unique<pmt::BulletMgr>();
        _bullet_mgr->add_bullets(pmt::BulletType::Missile,
                                 2,
                                 _textures["shell.png"]);
        // _bullet = std::make_unique<sf::Sprite>(*_textures["shell.png"]);
        // _bullet->setPosition(10, 300);
    }

    Game::~Game()
    {
    }

    void Game::run()
    {
        sf::Time per_frame = sf::seconds(1.0f / 60.0f);
        sf::Clock clock;
        sf::Time last_update;

        while (_window->isOpen()) {
            sf::Time delta = clock.getElapsedTime() - last_update;

            if (delta > per_frame) {
                handle_events();
                update(delta);
                render();
                last_update = clock.getElapsedTime();
            }
        }
    }

    void Game::update(sf::Time delta)
    {
        _bullet_mgr->update(delta);
    }

    void Game::render()
    {
        // _bullet->setPosition(x, 450 - y);

        _window->clear();
        _map->render(*_window);
        _player->render(*_window);
        _bullet_mgr->render(*_window);
        _window->display();
    }

    void Game::handle_events()
    {
        sf::Event event;

        while(_window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                _window->close();
            else if (event.type == sf::Event::KeyPressed
                     and event.key.code == sf::Keyboard::Escape)
                _window->close();
        }
    }
}

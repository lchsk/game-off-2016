#ifndef MAP_H
#define MAP_H

#include <memory>
#include <vector>
#include <unordered_map>

#include <SFML/Graphics.hpp>

#include "bullet_mgr.h"

namespace pmt
{
    class Map
    {
    public:
        Map(std::unordered_map<int, std::string> tiles,
            std::unordered_map
                <std::string, std::unique_ptr<sf::Texture> >& textures
        );
        ~Map();

        void update(sf::Time delta);
        void render(sf::RenderWindow& window);

        std::string get_param(std::string key);

        bool check_collision(std::shared_ptr<pmt::Bullet>& bullet);

    private:
        std::unique_ptr<sf::Sprite> _bg[8];
        double _bg_speeds[4];

        void _load_data(
            std::string filename,
            std::unordered_map<int, std::string> tiles,
            std::unordered_map
                <std::string, std::unique_ptr<sf::Texture> >& textures
        );

        void _load_meta(
            std::string filename
        );

        std::vector<sf::Sprite> _tiles;
        std::unordered_map<std::string, std::string> _meta;

        const int BG_WIDTH = 1800;
    };
}

#endif

#ifndef HUD_H
#define HUD_H

#include <memory>
#include <unordered_map>

#include <SFML/Graphics.hpp>

#include "tank.h"
#include "util.h"
#include "animation.h"

namespace pmt
{

    class Hud
    {
    public:
        Hud(std::unordered_map<std::string, std::unique_ptr<sf::Texture> >&
            textures, std::shared_ptr<sf::Font>& font);
        ~Hud();

        void render(sf::RenderWindow& window);
        void update(sf::Time& delta, double wind);

        void show_turn(std::shared_ptr<pmt::Tank>& tank);
        void show_cash(std::shared_ptr<pmt::Tank>& tank);

        bool is_shop_open() const;
        void open_shop(std::shared_ptr<pmt::Tank>& tank);
        void close_shop();
        void shop_up();
        void shop_down();
        void buy();

    private:
        void _draw_shop(sf::RenderWindow& window);
        void _check_cash();

        bool _no_cash;
        bool _show_cash;
        bool _shop_open;
        unsigned _top_shop_item;
        unsigned _selected;

        std::shared_ptr<pmt::Tank> _shop_client;

        std::shared_ptr<sf::Font> _font;

        std::unique_ptr<sf::Text> _text_shop_header;
        std::unique_ptr<sf::Text> _text_shop_info;

        std::unique_ptr<sf::Text> _text_turn_name;
        std::unique_ptr<sf::Text> _text_cash;
        std::unique_ptr<sf::Text> _text_weapon_count;
        std::unique_ptr<sf::Text> _text_weapon;
        std::unique_ptr<sf::Text> _text_wind;

        std::unique_ptr<sf::RectangleShape> _shop_overlay;

        std::unordered_map<OfferType, std::unique_ptr<sf::Text> > _shop_names;
        std::unordered_map<OfferType, std::unique_ptr<sf::Text> > _shop_descs;
        std::unordered_map<OfferType, std::unique_ptr<sf::Text> > _shop_prices;

        std::unique_ptr<pmt::Animation> _flag;
        std::unique_ptr<sf::Sprite> _pole;
    };
}

#endif

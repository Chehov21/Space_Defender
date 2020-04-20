#include"Palyer.h"

Player::Player()
{
    m_model.setPointCount(4);
    m_model.setPoint(0, sf::Vector2f(510.f, 340.f));
    m_model.setPoint(1, sf::Vector2f(470.f, 430.f));
    m_model.setPoint(2, sf::Vector2f(510.f, 400.f));
    m_model.setPoint(3, sf::Vector2f(550.f, 430.f));
    m_model.setOrigin(510.f, 390.f);
}

bool Player::load(const std::string& tileset, unsigned int width, unsigned int height)
{
    // load the tileset texture
    if (!m_texture.loadFromFile(tileset))
        return false;
}

void Player::rotate(sf::Vector2i mouse, sf::Vector2f startPosition)
{
    m_angle = atan((mouse.y - startPosition.y) / (mouse.x - startPosition.x)) * 180.0 / PI;
    if ((mouse.x < startPosition.x && mouse.y <= startPosition.y) || (mouse.x < startPosition.x && mouse.y > startPosition.y))
    {
        m_angle += 180;
    }
    m_model.setRotation(m_angle + 90);
}

void Player::shoot(sf::Vector2f start, sf::Vector2i end, std::vector<Bullet>& vec)
{
    Bullet bullet(start, end);
    vec.push_back(bullet);
}

void Player::shoot(sf::Vector2f start, sf::Vector2i end, std::vector<Bullet>& vec, int oneToThree)
{
    Bullet bullet(start, end,oneToThree);
    vec.push_back(bullet);
}

sf::ConvexShape Player::getModel()
{
    return m_model;
}

int Player::getScore(int count)
{
    m_score += count;
    return m_score;
}

int Player::getHighscore(int score)
{
    if (m_highscore < score)
    {
        m_highscore = score;
    }
    return m_highscore;
}

float Player::getAngle()
{
    return m_angle;
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // apply the entity's transform -- combine it with the one that was passed by the caller
    states.transform *= getTransform(); // getTransform() is defined by sf::Transformable

    // apply the texture
    states.texture = &m_texture;

    // you may also override states.shader or states.blendMode if you want

    // draw the vertex array
    target.draw(m_model, states);
}

bool isCoolision(std::vector<Enemy>& vec, Player& ship, sf::RenderWindow& window)
{
    for (Enemy& e : vec)
    {
        // Столкновение с кораблем
        if (ship.getModel().getLocalBounds().intersects(e.getEnemy().getGlobalBounds()))
        {
            return true;
        }
    }
    return false;
}

void isCoolision(std::vector<Enemy>& vec_e, std::vector<Bullet>& vec_b, Player& ship, sf::RenderWindow& window)
{
    int count_b = 0;
    int count_e = 0;
    for (Enemy& e : vec_e)
    {
        for (Bullet& b : vec_b)
        {
            if (e.getEnemy().getGlobalBounds().intersects(b.getBullet().getGlobalBounds())) {
                ship.getScore(1);
                vec_e.erase(vec_e.begin() + count_e);
                vec_b.erase(vec_b.begin() + count_b);
            }
            count_b++;
        }
        count_b = 0;
        count_e++;
    }
}


bool isCoolision(std::vector<Gain>& vec_g, std::vector<Bullet>& vec_b, Player& ship, sf::RenderWindow& window)
{
    int count_b = 0;
    int count_g = 0;
    for (Gain& g : vec_g)
    {
        for (Bullet& b : vec_b)
        {
            if (g.getGain().getGlobalBounds().intersects(b.getBullet().getGlobalBounds())) {
                ship.getScore(1);
                vec_g.erase(vec_g.begin() + count_g);
                vec_b.erase(vec_b.begin() + count_b);
                return true;
            }
            count_b++;
        }
        count_b = 0;
        count_g++;
    }
    return false;
}


//bool isCoolision(std::vector<Bullet>& vec_b, std::vector<Enemy>& vec_e, Player& ship, sf::RenderWindow &window)
//{
//    int count_e = 0;
//    int count_b = 0;
//
//    for (Enemy& e : vec_e)
//    {
//        // Столкновение с кораблем
//        if (ship.getModel().getLocalBounds().intersects(e.getEnemy().getGlobalBounds()))
//        {
//            return true;
//        }
//        for (Bullet& b : vec_b)
//        {
//            if (e.getEnemy().getGlobalBounds().intersects(b.getBullet().getGlobalBounds())) {
//                ship.getScore(1);
//                vec_e.erase(vec_e.begin() + count_e);
//                vec_b.erase(vec_b.begin() + count_b);
//            }
//            count_b++;
//        }
//        count_b = 0;
//        count_e++;
//    }
//}


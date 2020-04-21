#include"Palyer.h"

Player::Player()
{
    m_model.setPointCount(4);
    m_model.setPoint(0, sf::Vector2f(510.f, 340.f));
    m_model.setPoint(1, sf::Vector2f(470.f, 430.f));
    m_model.setPoint(2, sf::Vector2f(510.f, 400.f));
    m_model.setPoint(3, sf::Vector2f(550.f, 430.f));
    m_model.setOrigin(510.f, 390.f);
    if (!m_texture.loadFromFile("texture_ship.png"))
    {
        std::cout<<"Load failed!"<<std::endl;
    }
    m_model.setTexture(&m_texture);
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

void Player::shoot(sf::Vector2f start, sf::Vector2i end, CArray<Bullet>& arr)
{
    Bullet bullet(start, end);
    arr.push_back(bullet);
}

void Player::shoot(sf::Vector2f start, sf::Vector2i end, CArray<Bullet>& arr, int oneToThree)
{
    Bullet bullet(start, end,oneToThree);
    arr.push_back(bullet);
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

void Player::setTexture(int count)
{
    std::ostringstream countTexture;
    countTexture << "texture_ship";
    countTexture << count;
    countTexture << ".png";
    if (!m_texture.loadFromFile(countTexture.str()))
    {
        std::cout << "Load failed!" << std::endl;
    }
    m_model.setTexture(&m_texture);
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

bool isCoolision(CArray <Enemy>& arr, Player& ship, sf::RenderWindow& window)
{
    for(int i=0;i<arr.size();i++)
    {
        // Столкновение с кораблем
        if (ship.getModel().getLocalBounds().intersects(arr[i].getEnemy().getGlobalBounds()))
        {
            return true;
        }
    }
    return false;
}

void isCoolision(CArray<Enemy>& arrE, CArray<Bullet>& arrB, Player& ship, sf::RenderWindow& window)
{
    int count_b = 0;
    int count_e = 0;
    int sizeB = arrB.size();
    int sizeE = arrE.size();
    /*int* deleteE = new int[arrE.size()];
    int countDeleteE = 0;
    int* deleteB = new int[arrB.size()];
    int countDeleteB = 0;*/
    for (int i = 0; i < sizeE; i++)
    {
        for (int j = 0; j <sizeB; j++)
        {
            if (arrE[i].getEnemy().getGlobalBounds().intersects(arrB[j].getBullet().getGlobalBounds())) {
                ship.getScore(1);
                arrE.erase(count_e);
                arrB.erase(count_b);
                count_e--;
                sizeE--;
                sizeB--;
                i--;
                break;
                /*deleteE[countDeleteE] = count_e;
                countDeleteE++;
                deleteB[countDeleteB] = count_b;
                countDeleteB++;*/
            }
            count_b++;
        }
        count_b = 0;
        count_e++;
    }
    /*for (int i = 0; i < countDeleteE; i++)
    {
        arrE.erase(deleteE[i]);
        arrB.erase(deleteB[i]);
    }
    delete[] deleteE;
    delete[] deleteB;*/
}


bool isCoolision(CArray<Gain>& arrG, CArray<Bullet>& arrB, sf::RenderWindow& window)
{
    int count_b = 0;
    int count_g = 0;
    for(int i=0;i< arrG.size();i++)
    {
        for (int j = 0; j < arrB.size(); j++)
        {
            if (arrG[i].getGain().getGlobalBounds().intersects(arrB[j].getBullet().getGlobalBounds())) {
                arrG.erase(count_g);
                arrB.erase(count_b);
                j--;
                count_b--;
                count_g--;
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


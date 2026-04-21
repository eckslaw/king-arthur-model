#pragma once
#include <SFML/Graphics.hpp>
#include <filesystem>

#include "mapObjects/ellipseShape.h"



template<class t1, class t_2, class t2>
bool checkHit(
              t1& gameObject1,
              t_2& gameObjects2Container
             )
{
    return std::any_of(
                       begin(gameObjects2Container), end(gameObjects2Container),
                       [&gameObject1] (t2& gameObject2)
                       {
                           return gameObject1.intersect(gameObject2);
                       }
                       );
}

template<class t_1, class t1, class t_2, class t2>
bool checkHit(
              t_1& gameObj1Cont,
              t_2& gameObj2Cont
             )
{
    return std::any_of(
                       begin(gameObj1Cont), end(gameObj1Cont),
                       [&gameObj2Cont] (t1& gameObj1)
                       {
                        return checkHit<t1, t_2, t2>(gameObj1, gameObj2Cont);
                       }
                       );
}

// necessary for checking intersection warriors (vector) - kingArthur
// inclusive ref-member-kingArthur-variable of class Warrior
template<class t_2, class t2>
bool checkHit(
              t_2& gameObjects2Container
             )
{
    return std::any_of(
                       begin(gameObjects2Container), end(gameObjects2Container),
                       [](t2& gameObject2)
                       {
                           return gameObject2.intersect();
                       }
                       );
}



struct Utils {
    static std::filesystem::path getExeDir();

    static std::filesystem::path assetPath(
                                           std::filesystem::path const& rel
                                          );

    static std::vector<std::shared_ptr<EllipseShape>>& setSucceededOnGameMap(
                                                            std::vector<std::shared_ptr<EllipseShape>>& gameMapButtonVector
                                                            );

    static std::vector<sf::Texture> const& makeTextureVector(
                                                             std::vector<sf::Texture> &texturesVec,
                                                             std::vector<std::string> const &filePaths
                                                             );

    static std::vector<sf::Sprite>& makeSpriteVector(
                                                     std::vector<sf::Sprite>& ref_spriteVec,
                                                     std::vector<sf::Texture> const& textureVec
                                                    );
};
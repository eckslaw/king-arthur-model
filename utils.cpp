#include "utils.h"
#include <windows.h>
#include <iostream>

std::filesystem::path Utils::getExeDir()
{
    char buf[MAX_PATH];
    GetModuleFileNameA(nullptr, buf, MAX_PATH);
    return std::filesystem::path(buf).parent_path();
}

std::filesystem::path Utils::assetPath(
                                       std::filesystem::path const& rel
                                       )
{
    return getExeDir() / rel; // rel z.B. "assets/fonts/tole.ttf"
}

std::vector<std::shared_ptr<EllipseShape>>& Utils::setSucceededOnGameMap(
                                                std::vector<std::shared_ptr<EllipseShape>>& ref_gameMapButtonVector
                                                )
{
    for (auto& ref_buttonPtr : ref_gameMapButtonVector)
    {
        if (ref_buttonPtr->isSetActiveColor())
        {
            ref_buttonPtr->setPassive();
            ref_buttonPtr->setSuccessful();
            if (ref_buttonPtr->nextButton) {
                ref_buttonPtr->nextButton->setActive();
            }
            return ref_gameMapButtonVector;
        }
    }
    return ref_gameMapButtonVector;
}

std::vector<sf::Texture> const& Utils::makeTextureVector (
                                                           std::vector<sf::Texture>& ref_textureVec,
                                                           std::vector<std::string> const& ref_paths
                                                          )
{
    for (unsigned i = 0; i < ref_paths.size(); i++) {
        ref_textureVec.emplace_back();
    }

    std::for_each(begin(ref_paths), end(ref_paths),
                [&, i=0]
                  (std::string const &ref_path) mutable
                  {
                     ref_textureVec[i++].loadFromFile(assetPath(ref_path))?
                                                      std::cout << "texturefilepath " << i << " loaded" << std::endl :
                                                      std::cout << "texturefilepath " << i << " not loaded" << std::endl;
                  }
                 );
    return ref_textureVec;
}

std::vector<sf::Sprite>& Utils::makeSpriteVector(
                                                 std::vector<sf::Sprite>& ref_spriteVec,
                                                 std::vector<sf::Texture> const& ref_texVec
                                                )
{
    std::for_each(begin(ref_texVec), end(ref_texVec),
                [&] (sf::Texture const& ref_tex)
                  {
                    ref_spriteVec.emplace_back(ref_tex);
                  }
                 );
    return ref_spriteVec;
}
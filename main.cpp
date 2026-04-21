#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <windows.h>

#include <thread>
#include <iostream>
#include <filesystem>
#include <cmath>
#include <optional>
#include <vector>
#include <memory>

#include "memoryGame.h"
#include "utils.h"
#include "baseData.h"
#include "mapData.h"
#include "memoryData.h"
#include "videoData.h"
#include "setup/baseSetup.h"
#include "setup/gameMapSetup.h"
#include "event/gameMapEvents.h"
#include "render/gameMapRender.h"

int main()
{
    srand(static_cast<unsigned>(time(nullptr)));

    std::cout << "Working Directory: "
              << std::filesystem::current_path()
              << std::endl;

    std::vector<sf::Texture> gameMapTexVector;
    gameMapTexVector = Utils::makeTextureVector(
                                                gameMapTexVector,
                                                MapData::gameMapTexFilePathsVector
                                               );

    std::vector<Sprite> gameMapSpriteVector;
    gameMapSpriteVector = Utils::makeSpriteVector(
                                                  gameMapSpriteVector,
                                                  gameMapTexVector
                                                 );

   auto crownTexPtr = std::make_shared<sf::Texture>();

   crownTexPtr->loadFromFile(Utils::assetPath(MapData::crownTexFilePath)) ?
                                                            std::cout << "crown loaded" << std::endl :
                                                            std::cout << "crown not loaded" << std::endl;

   auto crownSpritePtr = std::make_shared<sf::Sprite>(
                                                      *crownTexPtr
                                                     );


   std::vector<sf::Texture> memoryTexVector;
   memoryTexVector = Utils::makeTextureVector(
                                              memoryTexVector,
                                              MemoryData::memoryTexFilePathsVector
                                             );


   std::vector<sf::Texture> videoGamObjTexs;
   std::vector<sf::Texture> videoKiArthTexsPage;
   std::vector<sf::Texture> videoKiArthTexsSquire;
   std::vector<sf::Texture> videoKiArthTexsKnight;

   videoGamObjTexs = Utils::makeTextureVector(
                                              videoGamObjTexs,
                                              VideoData::videoGamObjTexFilePathsVector
                                             );
   videoKiArthTexsPage = Utils::makeTextureVector(
                                                  videoKiArthTexsPage,
                                                  VideoData::videoKiArthTexFilePathsVectorI
                                                 );
   videoKiArthTexsSquire = Utils::makeTextureVector(
                                                    videoKiArthTexsSquire,
                                                    VideoData::videoKiArthTexFilePathsVectorII
                                                   );
   videoKiArthTexsKnight = Utils::makeTextureVector(
                                                    videoKiArthTexsKnight,
                                                    VideoData::videoKiArthTexFilePathsVectorIII
                                                   );

   BaseSetup::initializeBasics();
   GameMapSetup::initializeGameMap();

   gameMapSpriteVector = shapeMapSprites(gameMapSpriteVector);
   crownSpritePtr = shapeCrownSprite(crownSpritePtr);

   auto windowVideo = sf::RenderWindow(
                                       sf::VideoMode({BaseData::windowWidthVideoU, BaseData::windowHeightVideoU}),
                                       "Video Game",
                                       Style::None
                                       );
   windowVideo.setFramerateLimit(60);
   windowVideo.setMouseCursorGrabbed(true);
   windowVideo.setVisible(false);

   auto windowMemory = RenderWindow(
                                    VideoMode({BaseData::windowWidthMemoryU, BaseData::windowHeightMemoryU}),
                                    "Memory Game",
                                    Style::None
                                    );
   windowMemory.setFramerateLimit(60);
   windowMemory.setMouseCursorGrabbed(true);
   windowMemory.setVisible(false);

   auto windowGameMap = RenderWindow(
                                     VideoMode({BaseData::windowWidthGameMapU, BaseData::windowHeightGameMapU}),
                                     "King Arthur - Conquest of the Crown",
                                     Style::Titlebar | Style::Close
                                     );
   windowGameMap.setFramerateLimit(60);
   windowGameMap.setVisible(true);

   auto videoGamePtr = std::make_unique<VideoGame>(
                                                   windowVideo,
                                                   windowGameMap,
                                                   *BaseData::tole,
                                                   videoGamObjTexs,
                                                   videoKiArthTexsPage,
                                                   videoKiArthTexsSquire,
                                                   videoKiArthTexsKnight
                                                   );

   auto memoryGamePtr = std::make_unique<MemoryGame>(
                                                     windowMemory,
                                                     windowGameMap,
                                                     *BaseData::tole
                                                     );

    while (windowGameMap.isOpen())
    {
        BaseData::state.released = true;

        if (windowMemory.hasFocus())
        {
            memoryGamePtr->pollEvent();
            memoryGamePtr->updateMemory(3.f);
            memoryGamePtr->renderMemory(windowMemory);
        }
        else if (windowVideo.hasFocus())
        {
            videoGamePtr->pollEvent();
            videoGamePtr->updateVideo(3.f);
            videoGamePtr->renderVideo(windowVideo);
        }
        else {
            while (const std::optional event = windowGameMap.pollEvent())
            {
                if (event->is<Event::Closed>()) {
                    windowGameMap.close();
                }
                handleGameMapEvents(
                                    windowVideo,
                                    windowMemory,
                                    windowGameMap,
                                    *MapData::buttonContainerPtr,
                                    *crownSpritePtr,
                                     memoryTexVector,
                                    MapData::gameMapTextVector,
                                    *memoryGamePtr,
                                    *videoGamePtr,
                                    event
                                    );

            }
            renderGameMap(
                         windowGameMap,
                         *MapData::buttonContainerPtr,
                          BaseData::state,
                         *crownSpritePtr,
                         gameMapSpriteVector,
                         MapData::gameMapTextVector
                         );
        }
    }
        return 0;
}
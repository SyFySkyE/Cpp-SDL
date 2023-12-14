#include "TextureCache.h"
#include "ImageLoader.h"

#include <iostream>

namespace GameEngine {
    TextureCache::TextureCache()
    {
    }

    TextureCache::~TextureCache()
    {
    }

    GLTexture TextureCache::getTexture(std::string texturePath)
    {
        auto mit = _textureMap.find(texturePath);

        if (mit == _textureMap.end()) {
            // Load tex
            GLTexture newTex = ImageLoader::LoadPNG(texturePath);

            _textureMap.insert(std::make_pair(texturePath, newTex));

            std::cout << "loaded new tex";

            return newTex;
        }

        std::cout << "got cached tex";
        return mit->second;
    }

}

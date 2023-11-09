/*
 *  SimpleRenderEngine (https://github.com/mortennobel/SimpleRenderEngine)
 *
 *  Created by Morten Nobel-Jørgensen ( http://www.nobel-joergensen.com/ )
 *  License: MIT
 */

#pragma once

#include <memory>
#include <array>
#include "glm/glm.hpp"
#include "sre/impl/CPPShim.hpp"

namespace sre{

class SpriteAtlas;
class Texture;

class Sprite {
public:
    Sprite();
    Sprite(const Sprite&);

    float getRotation() const;                  // rotation in degrees
    void setRotation(float rotation);

    const glm::vec2 &getPosition() const;       // position in x,y plane (to pivot point)
    void setPosition(const glm::vec2 &position);

    const glm::vec2 &getScale() const;          // scale (if (1,1) then the actual size equals getSpriteSize() ).
    void setScale(const glm::vec2 &scale);

    const glm::bvec2 &getFlip() const;          // flip (in x or y direction)
    void setFlip(const glm::bvec2 &flip);

    uint16_t getOrderInBatch() const;                // render order
    void setOrderInBatch(uint16_t orderInBatch);

    const glm::vec4 &getColor() const;          // sprite color (and transparency) multiplied with texture color
    void setColor(const glm::vec4 &color);

    const glm::ivec2 &getSpritePos() const;     // sprite position in texture

    const glm::ivec2 &getSpriteSize() const;    // sprite size in texture

    const glm::vec2 &getSpriteAnchor() const;   // anchor (relative to spriteSize)

    std::array<glm::vec2,4> getTrimmedCorners();       // return the position of the trimmed sprite

    std::array<glm::vec2,4> getUVs();

private:
    Sprite(glm::ivec2 spritePos, glm::ivec2 spriteSize,glm::ivec2 spriteSourcePos,
        glm::ivec2 spriteSourceSize, glm::vec2  spriteAnchor, Texture* texture);

    float rotation    = 0;
    glm::vec2 position= {0.0f,0.0f};
    glm::vec2 scale   = {1.0f,1.0f};
    glm::bvec2 flip   = {false, false};
    union {
        uint64_t globalOrder;
		PACK(struct {
            uint16_t drawOrder;    // lowest priority
            uint32_t texture;
            uint16_t orderInBatch; // highest priority
        } ) details;
    }  order;
    glm::vec4 color   = {1.0f,1.0f,1.0f,1.0f};

    glm::ivec2 spritePos;
    glm::ivec2 spriteSize;
    glm::ivec2 spriteSourcePos;
    glm::ivec2 spriteSourceSize;
    glm::vec2  spriteAnchor;
    Texture* texture;
    friend class SpriteAtlas;
    friend class SpriteBatch;
    friend class Inspector;
};

}
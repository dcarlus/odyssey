#include "AlButtonBitmap.h"
#include "../../../tools/managers/SpriteManager.h"
#include <iostream>

using namespace std ;


AlButtonBitmap::AlButtonBitmap(const Position& pos,
                               string& sprite,
                               AlAbstractAction* action) : AlButton(pos,
                                                                    action) {
    string spritePath = "gui/buttons/released/" + sprite ;
    m_allSprites[STATE_RELEASED] = SpriteManager::getInstance() -> addSprite(spritePath) ;
    spritePath = "gui/buttons/active/" + sprite ;
    m_allSprites[STATE_ACTIVE] = SpriteManager::getInstance() -> addSprite(spritePath) ;
    m_sprite = m_allSprites[STATE_RELEASED] ;

    updateBounds(Position(m_bounds.getX(), m_bounds.getY()),
                 Dimension(al_get_bitmap_width(m_sprite),
                           al_get_bitmap_height(m_sprite))) ;
}

AlButtonBitmap::~AlButtonBitmap() {}


void AlButtonBitmap::display() {
    al_draw_bitmap(m_sprite, m_bounds.getX(), m_bounds.getY(), 0) ;
}

void AlButtonBitmap::update() {}

void AlButtonBitmap::changeState() {
    if (m_sprite == m_allSprites[STATE_RELEASED])
        m_sprite = m_allSprites[STATE_ACTIVE] ;
    else
        m_sprite = m_allSprites[STATE_RELEASED] ;
}

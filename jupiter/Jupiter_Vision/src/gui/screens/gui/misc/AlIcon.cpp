#include "AlIcon.h"
#include "../../../tools/managers/SpriteManager.h"
#include <iostream>

using namespace std ;


AlIcon::AlIcon(const Position& pos,
               const string& sprite) : AlComponent(pos, false) {
    string spritePath = "gui/icons/" + sprite ;
    m_sprite = SpriteManager::getInstance() -> addSprite(spritePath) ;
    resize(100, 100) ;

    updateBounds(Position(m_bounds.getX(), m_bounds.getY()),
                 Dimension(al_get_bitmap_width(m_sprite),
                           al_get_bitmap_height(m_sprite))) ;
}

AlIcon::~AlIcon() {}


void AlIcon::display() {
    int fullWidth = al_get_bitmap_width(m_sprite) ;
    int fullHeight = al_get_bitmap_height(m_sprite) ;
    int scaledWidth = (fullWidth * m_scaleWidth) / 100 ;
    int scaledHeight = (fullHeight * m_scaleHeight) / 100 ;

    al_draw_scaled_bitmap(m_sprite,
                          0, 0,
                          fullWidth, fullHeight,
                          m_bounds.getX(), m_bounds.getY(),
                          scaledWidth, scaledHeight,
                          0) ;
}

void AlIcon::update() {}

void AlIcon::trigger() {}

void AlIcon::resize(char percentWidth, char percentHeight) {
    m_scaleWidth = percentWidth ;
    m_scaleHeight = percentHeight ;
}

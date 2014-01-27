#include "AlComponent.h"

using namespace std ;


AlComponent::AlComponent(const Position& pos, bool translucent) {
    updateBounds(pos, Dimension()) ;
    setTranslucent(translucent) ;
    m_state = STATE_DEFAULT ;
}

AlComponent::~AlComponent() {}


bool AlComponent::testCursor(const Position& cursorPos) {
    return m_bounds.contains(cursorPos) ;
}

bool AlComponent::testCursor(float x, float y) {
    Position cursorPos = Position(x, y) ;
    return testCursor(cursorPos) ;
}


void AlComponent::setTranslucent(bool translucent) {
    static ALLEGRO_COLOR foregroundColor = al_map_rgba(0, 0, 0, 0) ;
    setColor(LAYER_FOREGROUND, foregroundColor) ;
    setOverColor(LAYER_FOREGROUND, foregroundColor) ;
    setActiveColor(LAYER_FOREGROUND, foregroundColor) ;

    if (translucent) {
        static ALLEGRO_COLOR translucentColor = al_map_rgba(0, 0, 0, 0) ;
        setColor(LAYER_BACKGROUND, translucentColor) ;
        setOverColor(LAYER_BACKGROUND, translucentColor) ;
        setActiveColor(LAYER_BACKGROUND, translucentColor) ;
    }
    else {
        setColor(LAYER_BACKGROUND, al_map_rgba(0, 0, 0, 192)) ;
        setOverColor(LAYER_BACKGROUND, al_map_rgba(0, 0, 0, 255)) ;
        setActiveColor(LAYER_BACKGROUND, al_map_rgba(255, 0, 0, 255)) ;
    }
}


void AlComponent::setColor(COMPONENT_LAYER layer, ALLEGRO_COLOR color) {
    m_colors[layer|STATE_DEFAULT] = color ;
}

void AlComponent::setActiveColor(COMPONENT_LAYER layer, ALLEGRO_COLOR color) {
    m_colors[layer|STATE_ACTIVE] = color ;
}

void AlComponent::setOverColor(COMPONENT_LAYER layer, ALLEGRO_COLOR color) {
    m_colors[layer|STATE_OVER] = color ;
}


void AlComponent::setState(COMPONENT_STATES state) {
    bool changedState = (m_state != state) ;
    m_state = state ;

    if (changedState) {
        switch (m_state) {
            case STATE_DEFAULT:
                actionOnDefault() ;
                break ;

            case STATE_OVER:
                actionOnOver() ;
                break ;

            case STATE_ACTIVE:
                actionOnActive() ;
                break ;
        }
    }
}


ALLEGRO_COLOR& AlComponent::getColor(COMPONENT_LAYER layer) {
    return m_colors[layer | m_state] ;
}

void AlComponent::actionOnDefault() {}

void AlComponent::actionOnOver() {}

void AlComponent::actionOnActive() {}


void AlComponent::updateBounds(const Position& pos, const Dimension& size) {
    m_bounds = Rectangle2D(pos.x, pos.y, size.x, size.y) ;
}

#include "AlButtonSimple.h"

using namespace std ;


AlButtonSimple::AlButtonSimple(const Position& pos,
                               const string& text,
                               AlAbstractAction* action,
                               ALLEGRO_FONT* font) : AlButton(pos, action) {
    m_textPosition = pos ;
    m_text = text ;
    m_font = font ;

    static int paddingLeftTop = 5 ;
    static int paddingRightBottom = 15 ;
    int width = al_get_text_width(m_font, m_text.c_str()) ;
    int height = al_get_font_line_height(m_font) ;

    updateBounds(Position(m_textPosition.x - paddingLeftTop,
                          m_textPosition.y - paddingLeftTop),
                 Dimension(width + paddingRightBottom,
                           height + paddingRightBottom)) ;
}

AlButtonSimple::~AlButtonSimple() {}


void AlButtonSimple::display() {
    al_draw_filled_rounded_rectangle(m_bounds.getX(), m_bounds.getY(),
                                     m_bounds.getMaxX(), m_bounds.getMaxY(),
                                     2.5f, 2.5f,
                                     getColor(LAYER_BACKGROUND)) ;

    al_draw_text(m_font,
                 getColor(LAYER_FOREGROUND),
                 m_textPosition.x,
                 m_textPosition.y,
                 ALLEGRO_ALIGN_LEFT,
                 m_text.c_str()) ;
}


void AlButtonSimple::update() {}

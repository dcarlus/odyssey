#include "AlLabel.h"
#include "../../../constants.h"
#include "../../../tools/Allegro.h"
#include <cassert>
#include <sstream>
#include <iterator>
#include <iostream>

using namespace std ;


AlLabel::AlLabel(const Position& pos,
                 const std::string& text,
                 ALLEGRO_FONT* font) : AlComponent(pos) {
    assert(font != 0) ;

    m_text = text ;
    m_font = font ;

    m_maxWidth = WINDOW_WIDTH - 20 ;
    if (pos.x < m_maxWidth)
        m_maxWidth -= pos.x ;

    adjustText() ;
}

AlLabel::~AlLabel() {}


void AlLabel::adjustText() {
    m_splits.clear() ;

    istringstream explodeSpaces(m_text) ;
    istream_iterator<string> beg(explodeSpaces), end ;
    vector<string> tokens(beg, end) ;

    string previousBuffer = "" ;
    string buffer = "" ;
	unsigned int max = tokens.size() ;
    for (unsigned int i = 0 ; i < max ; i++) {
        string tmp = tokens[i] + " " ;
        buffer += tmp ;

        if (al_get_text_width(m_font, buffer.c_str()) > m_maxWidth) {
            m_splits.push_back(previousBuffer) ;
            buffer = tmp ;
        }

        previousBuffer = buffer ;
    }

    m_splits.push_back(previousBuffer) ;
}

void AlLabel::display() {
    unsigned int index = 0 ;
    int lineHeight = al_get_font_line_height(m_font) ;

	unsigned int max = m_splits.size() ;
    for (unsigned int i = 0 ; i < max ; i++) {
        al_draw_text(m_font, getColor(LAYER_FOREGROUND),
                     m_bounds.getX(), m_bounds.getY() + (1.5f * index * lineHeight),
                     0, m_splits[i].c_str()) ;
        index++ ;
    }
}

void AlLabel::update() {}

void AlLabel::trigger() {}


void AlLabel::setText(const string& text) {
    m_text = text ;
    adjustText() ;
}

string& AlLabel::getText() {
    return m_text ;
}

void AlLabel::setMaxWidth(unsigned short maxWidth) {
    m_maxWidth = maxWidth ;
    adjustText() ;
}

void AlLabel::actionOnActive() {}

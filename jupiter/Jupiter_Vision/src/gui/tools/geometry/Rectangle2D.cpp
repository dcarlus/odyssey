#include "Rectangle2D.h"

using namespace std ;

Rectangle2D::Rectangle2D() {
    m_halfSize = Dimension() ;
    update(0.f, 0.f, 0.f, 0.f) ;
}

Rectangle2D::Rectangle2D(float w, float h) {
    m_halfSize = Dimension(w/2, h/2) ;
    update(0.f, 0.f, w, h) ;
}


Rectangle2D::Rectangle2D(float x, float y, float w, float h) {
    m_halfSize = Dimension(w/2, h/2) ;
    update(x, y, w, h) ;
}

Rectangle2D::~Rectangle2D() {}


bool Rectangle2D::contains(const Rectangle2D& other) {
    if (isEmpty() || other.isEmpty())
        return false ;

    return ((other.m_bound >= m_pos) && (other.m_pos <= m_bound)) ;
}

bool Rectangle2D::intersects(const Rectangle2D& other) {
    if (isEmpty() || other.isEmpty())
        return false ;

    return ((other.m_bound > m_pos) && (other.m_pos < m_bound)) ;
}

bool Rectangle2D::contains(const Position& p) {
    return ((p >= m_pos) && (p <= m_bound)) ;
}


bool Rectangle2D::intersectsLine(Position& p1, Position& p2) {
    unsigned char out1, out2 ;

    out2 = outcode(p2) ;
    if (out2 == 0)
        return true ;

    while ((out1 = outcode(p1)) != 0) {
        if ((out1 & out2) != 0)
            return false ;

        if ((out1 & (OUT_LEFT | OUT_RIGHT)) != 0) {
            float x = getX() ;

            if ((out1 & OUT_RIGHT) != 0)
                x += getWidth() ;

            p1.y = p1.y + (x - p1.x) * (p2.y - p1.y) / (p2.x - p1.x) ;
            p1.x = x ;
        }
        else {
            float y = getY() ;

            if ((out1 & OUT_BOTTOM) != 0)
                y += getHeight() ;

            p1.x = p1.x + (y - p1.y) * (p2.x - p1.x) / (p2.y - p1.y) ;
            p1.y = y ;
        }
    }

    return true ;
}


unsigned char Rectangle2D::outcode(float x, float y) {
    unsigned char out = 0 ;

    // Test if point is on the right or on the left
    if (m_size.x <= 0)                  out |= OUT_LEFT | OUT_RIGHT ;
    else if (x < m_pos.x)               out |= OUT_LEFT ;
    else if (x > (m_bound.x))           out |= OUT_RIGHT ;

    // Test if point is above or below
    if (m_size.y <= 0)                  out |= OUT_TOP | OUT_BOTTOM ;
    else if (y < m_pos.y)               out |= OUT_TOP ;
    else if (y > (m_bound.y))           out |= OUT_BOTTOM ;

    return out ;
}

unsigned char Rectangle2D::outcode(const Position& p) {
    return outcode(p.x, p.y) ;
}


void Rectangle2D::moveOffset(float x, float y) {
    Position offset = Position(x, y) ;
    m_pos = m_pos + offset ;
    m_bound = m_pos + m_size ;
    m_center = m_pos + m_halfSize ;
}

void Rectangle2D::moveTo(float x, float y) {
    m_pos = Position(x, y) ;
    m_bound = m_pos + m_size ;
    m_center = m_pos + m_halfSize ;
}


void Rectangle2D::update(float x, float y, float w, float h) {
    m_pos = Position(x, y) ;
    m_size = Dimension(w, h) ;
    m_halfSize = Dimension(w/2, h/2) ;
    m_bound = m_pos + m_size ;
    m_center = m_pos + m_halfSize ;
}



bool Rectangle2D::isEmpty() const {
    return (m_size.x <= 0 || m_size.y <= 0) ;
}

float Rectangle2D::getX() const {
    return m_pos.x ;
}

float Rectangle2D::getY() const {
    return m_pos.y ;
}

float Rectangle2D::getCenterX() const {
    return m_center.x ;
}

float Rectangle2D::getCenterY() const {
    return m_center.y ;
}

float Rectangle2D::getMaxX() const {
    return m_bound.x ;
}

float Rectangle2D::getMaxY() const {
    return m_bound.y ;
}

float Rectangle2D::getHalfWidth() const {
    return m_halfSize.x ;
}

float Rectangle2D::getHalfHeight() const {
    return m_halfSize.y ;
}

float Rectangle2D::getWidth() const {
    return m_size.x ;
}

float Rectangle2D::getHeight() const {
    return m_size.y ;
}

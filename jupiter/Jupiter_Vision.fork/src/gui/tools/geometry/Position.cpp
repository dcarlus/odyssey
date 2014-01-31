#include "Position.h"


Position::Position() {
    x = 0.f ;
    y = 0.f ;
}

Position::Position(float x, float y) {
    this -> x = x ;
    this -> y = y ;
}

Position::Position(const Position& pos) {
	this -> x = pos.x ;
	this -> y = pos.y ;
}

Position::~Position() {}


bool Position::operator== (const Position& p2) const {
    return ((x == p2.x) && (y == p2.y)) ;
}

bool Position::operator!= (const Position& p2) const {
    return !(*this == p2) ;
}


Position operator+ (const Position& a, const Position& b) {
    Position result ;
    result.x = a.x + b.x ;
    result.y = a.y + b.y ;
    return result ;
}

Position operator- (const Position& a, const Position& b) {
    Position result ;
    result.x = a.x - b.x ;
    result.y = a.y - b.y ;
    return result ;
}


bool operator> (const Position& p1, const Position& p2) {
    return (((p1.x > p2.x) && (p1.y > p2.y))
                || ((p1.x > p2.x) && (p1.y == p2.y))
                || ((p1.x == p2.x) && (p1.y > p2.y))) ;
}


bool operator>= (const Position& p1, const Position& p2) {
    return ((p1 > p2) || (p1 == p2)) ;
}


bool operator< (const Position& p1, const Position& p2) {
    return (((p1.x < p2.x) && (p1.y < p2.y))
                || ((p1.x < p2.x) && (p1.y == p2.y))
                || ((p1.x == p2.x) && (p1.y < p2.y))) ;
}


bool operator<= (const Position& p1, const Position& p2) {
    return ((p1 < p2) || (p1 == p2)) ;
}

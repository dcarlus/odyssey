#include "AlButton.h"
#include <cassert>

using namespace std ;


AlButton::AlButton(const Position& pos,
                   AlAbstractAction* action) : AlComponent(pos) {
    assert(action != 0) ;
    m_action = action ;
}

AlButton::~AlButton() {
    delete m_action ;
}


void AlButton::trigger() {
    actionOnActive() ;
}


void AlButton::actionOnActive() {
    m_action -> run() ;
}

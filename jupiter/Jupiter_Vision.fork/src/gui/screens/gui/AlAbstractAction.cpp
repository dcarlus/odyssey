#include "AlAbstractAction.h"

using namespace std ;


AlAbstractAction::AlAbstractAction() {}

AlAbstractAction::AlAbstractAction(const string& text) {
    m_text = text ;
}

AlAbstractAction::~AlAbstractAction() {}

string& AlAbstractAction::getText() {
    return m_text ;
}

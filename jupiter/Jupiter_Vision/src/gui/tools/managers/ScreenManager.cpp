#include "ScreenManager.h"
#include "../../screens/menus/ManualControlScreen.h"
#include <string>
#include <iostream>

using namespace std ;

ScreenManager* ScreenManager::Singleton = 0 ;

ScreenManager::ScreenManager() {
    #ifdef DEBUG
    Logger::print("ScreenManager initialization") ;
    #endif
    pushScreen(new ManualControlScreen()) ;
}

ScreenManager::~ScreenManager() throw() {
    while (!m_screens.empty()) {
        delete m_screens.top() ;
        m_screens.pop() ;
    }
}

ScreenManager* ScreenManager::getInstance() {
    if (Singleton == 0)
        Singleton = new ScreenManager() ;

    return Singleton ;
}


void ScreenManager::pushScreen(Screen* screen) {
    assert(screen != 0) ;
    m_screens.push(screen) ;
    m_screens.top() -> cache() ;
}

void ScreenManager::previousScreen() {
    delete m_screens.top() ;
    m_screens.pop() ;
    assert(!m_screens.empty()) ;
}

void ScreenManager::replaceScreen(Screen* screen) {
    delete m_screens.top() ;
    m_screens.pop() ;
    pushScreen(screen) ;
}

void ScreenManager::display() {
    m_screens.top() -> display() ;
}

void ScreenManager::update() {
    m_screens.top() -> update() ;
}


Screen* ScreenManager::getCurrentScreen() {
    return m_screens.top() ;
}

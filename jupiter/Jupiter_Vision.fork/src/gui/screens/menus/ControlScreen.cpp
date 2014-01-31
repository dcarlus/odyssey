#include "ControlScreen.h"
#include "../gui/AlComponent.h"
#include "../gui/labels/AlLabel.h"
#include "../gui/misc/VideoFrame.h"
#include "../../tools/managers/FontManager.h"
#include <iostream>

using namespace std ;


ControlScreen::ControlScreen(const string& title,
                             const string& background) : Screen(background) {
    m_title = title ;
    setTitleColor(255, 255, 255, 255)  ;
    setTextColor(255, 255, 255, 255)  ;

    const string FONT = "liberation" ;
    setTitleFont(FONT, 16) ;
    setTextFont(FONT, 12) ;
    setButtonsFont(FONT, 12) ;

//    addComponent(new VideoFrame(Position(80, 0), Dimension(640, 480))) ;
}

ControlScreen::~ControlScreen() {
	for (FontIterator it = m_fonts.begin() ; it != m_fonts.end() ; it++) {
        al_destroy_font(it -> second) ;
    }

    map<string, AlComponent*>::iterator componentIT ;
    for (componentIT = m_guiComponents.begin() ; componentIT != m_guiComponents.end() ; componentIT++)
        delete componentIT -> second ;
    m_guiComponents.clear() ;
}


void ControlScreen::update() {}

void ControlScreen::preload() {}


void ControlScreen::additionnalDisplay() {
    

    al_draw_text(m_fonts["title"],
                 m_colors["title"],
                 20,
                 20,
                 ALLEGRO_ALIGN_LEFT,
                 m_title.c_str()) ;

    map<string, AlComponent*>::iterator componentIT ;
    for (componentIT = m_guiComponents.begin() ; componentIT != m_guiComponents.end() ; componentIT++)
        componentIT -> second -> display() ;
}


AlComponent* ControlScreen::getComponent(const std::string& id) {
    if (m_guiComponents.count(id) > 0)
        return m_guiComponents[id] ;
    return 0 ;
}


void ControlScreen::addText(const std::string& id, const string& text, const Position& pos) {
    AlLabel* label = new AlLabel(pos, text, m_fonts["text"]) ;
    label -> setColor(AlComponent::LAYER_FOREGROUND, m_colors["text"]) ;
    addComponent(id, label) ;
}


void ControlScreen::addComponent(const string& id, AlComponent* component) {
    assert(component != 0) ;
    assert(m_guiComponents.count(id) == 0) ;
    m_guiComponents[id] = component ;
}


void ControlScreen::setButtonsFont(const string& path, unsigned char size) {
    m_fonts["buttons"] = FontManager::getInstance() -> addFont(path, size) ;
}

void ControlScreen::setTitleFont(const string& path, unsigned char size) {
    m_fonts["title"] = FontManager::getInstance() -> addFont(path, size) ;
}

void ControlScreen::setTitleColor(unsigned char red,
                   unsigned char green,
                   unsigned char blue,
                   unsigned char alpha) {
    m_colors["title"] = al_map_rgba(red, green, blue, alpha) ;
}

void ControlScreen::setTextFont(const string& path, unsigned char size) {
    m_fonts["text"] = FontManager::getInstance() -> addFont(path, size) ;
}

void ControlScreen::setTextColor(unsigned char red,
                  unsigned char green,
                  unsigned char blue,
                  unsigned char alpha) {
    m_colors["text"] = al_map_rgba(red, green, blue, alpha) ;
}

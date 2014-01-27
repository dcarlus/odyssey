#include "FontManager.h"
#include "../../constants.h"
#include <string>
#include <iostream>

using namespace std ;

FontManager* FontManager::Singleton = 0 ;

FontManager::FontManager() {
    #ifdef DEBUG
    Logger::print("FontManager initialization") ;
    #endif

    al_init_font_addon() ;
    assert(al_init_ttf_addon()) ;
}

FontManager::~FontManager() throw() {
    map< string, map<unsigned char, ALLEGRO_FONT*> >::iterator itA ;
    for (itA = m_fonts.begin() ; itA != m_fonts.end() ; itA++) {
        map<unsigned char, ALLEGRO_FONT*> bySize = itA -> second ;
        map<unsigned char, ALLEGRO_FONT*>::iterator itB ;
        for (itB = bySize.begin() ; itB != bySize.end() ; itB++) {
            al_destroy_font(itB -> second) ;
        }
    }
}

FontManager* FontManager::getInstance() {
    if (Singleton == 0)
        Singleton = new FontManager() ;

    return Singleton ;
}


ALLEGRO_FONT* FontManager::addFont(const std::string& filename, unsigned char size) {
    bool exists = false ;
    if (m_fonts.count(filename) > 0) {
        if (m_fonts[filename].count(size) > 0)
            exists = true ;
    }

    if (exists)
        return getFont(filename, size) ;

    std::string fullpath = string(PATH_TO_MEDIA) + "media/fonts/" + filename + ".ttf" ;
    map<unsigned char, ALLEGRO_FONT*> fontSizes = m_fonts[filename] ;
    fontSizes[size] = al_load_ttf_font(fullpath.c_str(), size, 0) ;
    return fontSizes[size] ;
}


ALLEGRO_FONT* FontManager::getFont(const std::string& filename, unsigned char size) {
    map<unsigned char, ALLEGRO_FONT*> fontSizes = m_fonts[filename] ;
    return fontSizes[size] ;
}

#include "Screen.h"
#include "../constants.h"

using namespace std ;


Screen::Screen(const string& background) {
    string path = string(PATH_TO_MEDIA) + "media/img/" + background + ".jpg" ;
    m_background = al_load_bitmap(path.c_str()) ;
}


Screen::~Screen() {}


void Screen::display() {
    al_draw_bitmap(m_background, 0, 0, 0) ;

    // Generic stuff here...
    additionnalDisplay() ;
}


void Screen::cache() {
    // Generic stuff here...
    preload() ;
}

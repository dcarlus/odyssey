#include "BWTagger.h"
#include <algorithm>
#include <iostream>
#include <map>

using namespace std ;


BWTagger::BWTagger() : Tagger(CV_LOAD_IMAGE_GRAYSCALE) {}

BWTagger::~BWTagger() {}


inline void BWTagger::detectBackgroundColor() {
    m_bgColor = 0 ;
}

inline void BWTagger::detectConnectedComponents(int y, int x, int beforeY, int beforeX) {
    unsigned char val = m_picture.at<unsigned char>(y, x) ;

    if (val != m_bgColor) {
        m_pixelMap[x][y].setX(x) ;
        m_pixelMap[x][y].setY(y) ;
        m_pixelMap[x][y].setComponentID(0) ;

        bool found = false ;            // connected component(s) found?
        unsigned int compoY = 0, compoX = 0 ; // ID of the components detected at X-1 and at Y-1

                                       /** LOOK THE PREVIOUS PIXEL ON Y AXIS **/
        if (beforeY >= 0) {
            unsigned char pxBeforeY = m_picture.at<unsigned char>(beforeY, x) ;
            if (pxBeforeY == val) {
                found = true ;
                compoY = m_pixelMap[x][beforeY].getComponentID() ;
            }
        }

                                       /** LOOK THE PREVIOUS PIXEL ON X AXIS **/
        if (beforeX >= 0) {
            unsigned char pxBeforeX = m_picture.at<unsigned char>(y, beforeX) ;
            if (pxBeforeX == val) {
                found = true ;
                compoX = m_pixelMap[beforeX][y].getComponentID() ;
            }
        }


                                   /** AFFECT PIXELS TO CONNECTED COMPONENTS **/
        if (!found) {
            // No connected component found...
            Component nextComponent ;
            m_connectedComponents[nextComponent.getID()] = nextComponent ;
            nextComponent.addPixel(&m_pixelMap[x][y]) ;
        }
        else {
            // At least one connected component has been found...
            // Affect the pixel to its connected component
            unsigned int id = std::max(compoY, compoX) ;
            Component* compo = &m_connectedComponents[id] ;
            compo -> addPixel(&m_pixelMap[x][y]) ;

            if ((compoY != 0) && (compoX != 0) && (compoY != compoX)) {
                unsigned int id_target = std::min(compoY, compoX) ;
                Component* target = &m_connectedComponents[id_target] ;
                compo -> merge(target) ;
            }
        }
    }
}

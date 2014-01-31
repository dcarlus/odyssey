#include "Component.h"
#include <cstdlib>
#include <cfloat>

#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

using namespace std ;

unsigned int Component::ComponentsCounter = 0 ;


Component::Component() {
    Component::ComponentsCounter++ ;
    m_id = Component::ComponentsCounter ;
    setColor() ;

    m_minBound = {65535.f, 65535.f} ;
    m_maxBound = {0.f, 0.f} ;
}


Component::~Component() {
    m_pixels.clear() ;
}


Component* Component::merge(Component* other) {
    if (other != 0) {
        Component* biggest ;
        Component* smallest ;

        // Determine which component is to copy into the other one
        if (other -> getSize() > getSize()) {
            biggest = other ;
            smallest = this ;
        }
        else {
            biggest = this ;
            smallest = other ;
        }

        // Adjust the bounds
        if (smallest -> m_minBound < biggest -> m_minBound)
            biggest -> m_minBound = smallest -> m_minBound ;
        if (smallest -> m_maxBound > biggest -> m_maxBound)
            biggest -> m_maxBound = smallest -> m_maxBound ;

        // Update the component ID of the pixels
		unsigned int max = (smallest -> m_pixels).size() ;
        for (unsigned int i = 0 ; i < max ; i++) {
            smallest -> m_pixels[i] -> setComponentID(biggest -> m_id) ;
        }

        // Transfert the pixels to the current component
        (biggest -> m_pixels).reserve((biggest -> m_pixels).size() + ((smallest -> m_pixels).size())) ;
        (biggest -> m_pixels).insert((biggest -> m_pixels).end(), (smallest -> m_pixels).begin(), (smallest -> m_pixels).end()) ;

        return smallest ;
    }

    return 0 ;
}


inline void Component::addPixel(int x, int y) {
    addPixel(new Pixel(x, y)) ;
}

void Component::addPixel(Pixel* px) {
    px -> setComponentID(m_id) ;
    m_pixels.push_back(px) ;

    adjustBounds(px) ;
}


void Component::draw(Mat& picture) {
	unsigned int max = m_pixels.size() ;
    for (unsigned int i = 0 ; i < max ; i++) {
        line(picture,
             Point((m_pixels[i] -> m_x), (m_pixels[i] -> m_y)),
             Point((m_pixels[i] -> m_x), (m_pixels[i] -> m_y)),
             m_color);
    }
}

unsigned int Component::getID() {
    return m_id ;
}

Position Component::getCenter() {
    float xOffset = (m_maxBound.x - m_minBound.x) / 2.f ;
    float yOffset = (m_maxBound.y - m_minBound.y) / 2.f ;
    return {m_minBound.x + xOffset,
            m_minBound.y + yOffset} ;
}

int Component::getSize() {
    return m_pixels.size() ;
}

Scalar& Component::getColor() {
    return m_color ;
}

std::vector<Pixel*>& Component::getPixels() {
    return m_pixels ;
}


void Component::setColor() {
    const unsigned char MAX_COLOR = 3 ;
    double rgb[MAX_COLOR] ;

    for (unsigned char i = 0 ; i < MAX_COLOR ; i++)
        rgb[i] = ((double) ((rand() % 255) + 5) / 255.) ;

    m_color = Scalar(rgb[0], rgb[1], rgb[2]) ;
}


void Component::adjustBounds(Pixel* px) {
    // Adjust the min bound
    if ((px -> m_x) < m_minBound.x)
        m_minBound.x = (px -> m_x) ;
    if ((px -> m_y) < m_minBound.y)
        m_minBound.y = (px -> m_y) ;

    // Adjust the max bound
    if ((px -> m_x) > m_maxBound.x)
        m_maxBound.x = (px -> m_x) ;
    if ((px -> m_y) > m_maxBound.y)
        m_maxBound.y = (px -> m_y) ;
}

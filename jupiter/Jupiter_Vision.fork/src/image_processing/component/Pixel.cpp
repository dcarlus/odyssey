#include "Pixel.h"

/** @brief  Create a new pixel. */
Pixel::Pixel() :   m_x(0),
                   m_y(0),
                   m_componentID(0) {}

/** @brief  Create a pixel. */
Pixel::Pixel(int x, int y) :   m_x(x),
                               m_y(y),
                               m_componentID(0) {}

/** @brief  Create a pixel. */
Pixel::Pixel(int x, int y, unsigned int id) :  m_x(x),
                                               m_y(y),
                                               m_componentID(id) {}

/** @brief  Delete a pixel. */
Pixel::~Pixel() {}



                                                                        /** SETTERS **/
void Pixel::setX(int x) {
    m_x = x ;
}

void Pixel::setY(int y) {
    m_y = y ;
}


void Pixel::setComponentID(unsigned int id) {
    m_componentID = id ;
}

unsigned int Pixel::getComponentID() {
    return m_componentID ;
}

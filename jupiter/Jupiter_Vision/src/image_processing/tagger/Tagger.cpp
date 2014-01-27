#include "Tagger.h"
#include <iostream>

using namespace std ;


Tagger::Tagger(int type) {
    m_type = type ;
    m_showPicture = false ;
    m_ready = false ;
    m_pixelMap = 0 ;
}


Tagger::~Tagger() {
    if (m_showPicture)
        destroyWindow(PICTURE_WINDOW) ;

    if (m_pixelMap != 0) {
    	delete[] m_pixelMap[0] ;
	    delete[] m_pixelMap ;
    }
}


void Tagger::load(char* file) {
    m_picture = imread(file, m_type) ;

    if (m_picture.data) {
        detectBackgroundColor() ;
        m_ready = true ;

        setPixelMatrice() ;
    }
}

void Tagger::run() {
    if (!m_ready) {
        cerr << "The tagger is not ready!" << endl ;
        return ;
    }

    m_connectedComponents.clear() ;

    int beforeY, beforeX ;
    for (int y = 0 ; y < m_picture.rows ; y++) {
        beforeY = y - 1 ;
        for (int x = 0 ; x < m_picture.cols ; x++) {
            beforeX = x - 1 ;
            detectConnectedComponents(y, x, beforeY, beforeX) ;
        }
    }
}

Position Tagger::getFirstComponentCenter(int threshold) {
    for (ComponentIterator it = m_connectedComponents.begin() ; it != m_connectedComponents.end() ; it++) {
        if ((it -> second.getSize()) >= threshold)
            return it -> second.getCenter() ;
    }

    Position pos = {-1.f, -1.f} ;
    return pos ;
}

void Tagger::colorizeComponents(int threshold) {
    // Create a white picture
    Mat colored(m_picture.rows, m_picture.cols, CV_8UC1, 255) ;

	for (ComponentIterator it = m_connectedComponents.begin() ; it != m_connectedComponents.end() ; it++) {
        if ((it -> second.getSize()) >= threshold)
            it -> second.draw(colored) ;
    }
}


unsigned int Tagger::countConnectedComponents(int threshold) {
    unsigned int count = 0 ;
    if (threshold > 0)  {
		for (ComponentIterator it = m_connectedComponents.begin() ; it != m_connectedComponents.end() ; it++) {
            if ((it -> second.getSize()) >= threshold)
                count++ ;
        }
    }
    else {
        count = m_connectedComponents.size() ;
    }

    return count ;
}

void Tagger::changeColors() {
	for (ComponentIterator it = m_connectedComponents.begin() ; it != m_connectedComponents.end() ; it++) {
        it -> second.setColor() ;
    }
}


void Tagger::setFrame(Mat& picture) {
    if (picture.data) {
        bool recreate ;

        if (m_picture.data) {
            recreate = (m_picture.rows != picture.rows)
                            || (m_picture.cols != picture.cols) ;
        }
        else {
            recreate = true ;
        }

        m_picture = picture ;
        detectBackgroundColor() ;
        m_ready = true ;
        setPixelMatrice(recreate) ;
    }
}


void Tagger::setPixelMatrice(bool recreate) {
    if (m_pixelMap == 0 || recreate) {
        m_pixelMap = new Pixel*[m_picture.cols] ;
        // It uses a 1D array for better performances
        unsigned int totalSize = m_picture.cols * m_picture.rows ;
        Pixel* dim_2 = new Pixel[totalSize] ;

        for (unsigned int i = 0 ; i < totalSize ; i++)
            dim_2[i] = Pixel() ;

        // Generate the 2D matrix from the 1D array
        for (int i = 0 ; i < m_picture.cols ; i++)
	        m_pixelMap[i] = &dim_2[i * m_picture.rows] ;
    }
}

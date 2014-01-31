#ifndef __BWTAGGER_H__
#define __BWTAGGER_H__

#include "Tagger.h"

class BWTagger : public Tagger {
    protected:
        /** @brief  Background color. */
        unsigned char m_bgColor ;


    public:
        /** @brief  Create a tagger to open black/white pictures. */
        BWTagger() ;

        /** @brief  Destroy the BWTagger */
        virtual ~BWTagger() ;


    protected:
        /** @brief  Detect the background color. */
        inline void detectBackgroundColor() ;

        /** @brief  Detect a connected components. */
        inline virtual void detectConnectedComponents(int y, int x, int beforeY, int beforeX) ;
} ;

#endif

#ifndef __ALLEGRO_BUTTON_SIMPLE_H__
#define __ALLEGRO_BUTTON_SIMPLE_H__

#include "AlButton.h"

#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <string>

/**
 * @brief   A simple button with text and rectangle as background.
 * @author  Denis CARLUS
 */
class AlButtonSimple : public AlButton {
    protected:
        /** @brief  Text displayed on the button. */
        std::string m_text ;
        /** @brief  Font used by the button. */
        ALLEGRO_FONT* m_font ;
        /** @brief  Position of the text inside the button. */
        Position m_textPosition ;


    public:
        /** @brief  Create a new AlButtonSimple. */
        AlButtonSimple(const Position& pos,
                       const std::string& text,
                       AlAbstractAction* action,
                       ALLEGRO_FONT* font) ;

        /** @brief  Destruction of an AlButtonSimple. */
        virtual ~AlButtonSimple() ;



        /** @brief  Display the button. */
        virtual void display() ;

        /** @brief  Update the button. */
        virtual void update() ;


    protected:
        /** @brief  Set the content of the button. */
        void setContent() ;
} ;

#endif

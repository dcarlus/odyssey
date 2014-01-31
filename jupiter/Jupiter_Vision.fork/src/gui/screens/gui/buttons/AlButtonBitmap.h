#ifndef __ALLEGRO_BUTTON_BITMAP_H__
#define __ALLEGRO_BUTTON_BITMAP_H__

#include "AlButton.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <string>
#include <map>

/**
 * @brief   A button using a bitmap as representation.
 * @author  Denis CARLUS
 */
class AlButtonBitmap : public AlButton {
    protected:
        /** @brief  Sprite used to display the button. */
        ALLEGRO_BITMAP* m_sprite ;

        /** @brief  All the sprites used by the button. */
        std::map<BUTTON_STATE, ALLEGRO_BITMAP*> m_allSprites ;


    public:
        /** @brief  Create a new AlButtonBitmap. */
        AlButtonBitmap(const Position& pos,
                       std::string& sprite,
                       AlAbstractAction* action) ;

        /** @brief  Destruction of an AlButtonBitmap. */
        virtual ~AlButtonBitmap() ;


        /** @brief  Display the button. */
        virtual void display() ;

        /** @brief  Update the button. */
        virtual void update() ;


        /** @brief  Change the button state. */
        virtual void changeState() ;
} ;

#endif

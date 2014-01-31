#ifndef __ALLEGRO_ICON_BITMAP_H__
#define __ALLEGRO_ICON_BITMAP_H__

#include "../AlComponent.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <string>

/**
 * @brief   An icon just displays an image.
 * @author  Denis CARLUS
 */
class AlIcon : public AlComponent {
    protected:
        /** @brief  Sprite used to display the button. */
        ALLEGRO_BITMAP* m_sprite ;
        /** @brief  Icon scale. */
        char m_scaleWidth ;
        /** @brief  Icon scale. */
        char m_scaleHeight ;


    public:
        /** @brief  Create a new AlIcon. */
        AlIcon(const Position& pos, const std::string& sprite) ;

        /** @brief  Destruction of an AlIcon. */
        virtual ~AlIcon() ;


        /** @brief  Display the component. */
        virtual void display() ;

        /** @brief  Update the component. */
        virtual void update() ;

        /** @brief  Trigger the component. */
        virtual void trigger() ;


        /**
         * @brief   Resize the icon.
         * @param   percent Percentage to resize the icon.
         */
        virtual void resize(char percentWidth, char percentHeight) ;
} ;

#endif

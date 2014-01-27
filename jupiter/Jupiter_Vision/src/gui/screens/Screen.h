#ifndef __SCREEN_H__
#define __SCREEN_H__

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <string>


/**
 * @brief   A screen to display graphical informations.
 * @author  Denis CARLUS
 * @version 1.0 26/01/2014
 */
class Screen {
    private:
        /** Background image of the screen. */
        ALLEGRO_BITMAP* m_background ;

    public:
        /** @brief  Create a Screen. */
        Screen(const std::string& background) ;


        /** @brief  Destroy the Screen. */
        virtual ~Screen() ;


        /** @brief  Display the game screen. */
        void display() ;

        /** @brief  Update the game screen. */
        virtual void update() = 0 ;

        /** @brief  Make the screen do action on key press. */
        virtual void keyPressed(int keycode) = 0 ;

        /** @brief  Make the screen do action on key release. */
        virtual void keyReleased(int keycode) = 0 ;

        /** @brief  Cache media used by the screen. */        
        void cache() ;

    protected:
        /** @brief  Preload media used by the screen. */
        virtual void preload() = 0 ;

        /** @brief  Custom display function adapted to the screen. */
        virtual void additionnalDisplay() = 0 ;
} ;

#endif

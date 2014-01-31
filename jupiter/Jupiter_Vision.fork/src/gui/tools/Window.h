#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <stdio.h>
#include <allegro5/allegro.h>

/**
 * @brief   Abstraction of the displays used by Allegro library.
 * @author  Denis CARLUS
 */
class Window {
	protected:
	    /** @brief  Display used by Allegro. */
		ALLEGRO_DISPLAY* m_display ;
	    /** @brief  To know if the application is displayed on fullscreen. */
        bool m_fullscreen ;

	public:
        /** @brief  Create a new Window with given size. */
		Window(int sizeX, int sizeY) ;

        /** @brief  Destroy the Window. */
		virtual ~Window() ;


        /** @brief  Refresh the display. */
		void refresh() ;

        /** @brief  Switch between fullscreen and windowed mode. */
        void switchFullscreen() ;

        /** @brief  Get the underlying display used by Allegro.. */
		ALLEGRO_DISPLAY* getDisplay() ;

        /** @brief  Get the width of the displaying window. */
        int getWidth() ;

        /** @brief  Get the height of the displaying window. */
        int getHeight() ;
} ;
#endif

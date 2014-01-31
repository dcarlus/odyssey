#ifndef __ALLEGRO_SINGLETON_H__
#define __ALLEGRO_SINGLETON_H__

#include <easysocket/tools.h>
#include "Timer.h"
#include "Window.h"

#include <string>
#include <vector>
#include <iostream>


typedef void(*callback)() ;

/**
 * @brief   Singleton managing the thread of game logics, display, etc.
 *          It contains the main loop of the game.
 * @author  Denis CARLUS
 */
class Allegro : private NoCopy {
    private:
        /** @brief Singleton of the Allegro. */
        static Allegro* Singleton ;

		/** @brief	To know if the application continue to run. */
		bool m_isRunning ;

		/** @brief	Main window of the application. */
		Window* m_window ;
		/** @brief	Timer to run the game at 60 frame per second. */
		Timer* m_FPSTimer ;
		/** @brief 	Register all the events in this queue. */
		ALLEGRO_EVENT_QUEUE* m_event_queue ;

        /** Additionnal function to run before the main loop. */
        std::vector<callback> m_callBefore ;
        /** Additionnal function to run after the main loop. */
        std::vector<callback> m_callAfter ;




                                            /** CONSTRUCTION AND DESTRUCTION **/
        /**
         * @brief Construction of a Allegro handler.
         */
        Allegro() ;

        /** @brief Destruction of the Allegro handler. */
        ~Allegro() throw() ;


    public:
        /**
         * @brief Get the unique instance of Allegro.
         * @return  The unique instance of Allegro.
         */
        static Allegro* getInstance() ;


		/** @brief	Refresh the window content. */
		void refresh() ;

		/** @brief	Run the application main loop. */
		void run() ;

        /** Add a function to run before the main loop. */
        void addExtraRunBefore(void (*extra)(void)) ;

        /** Add a function to run after the main loop. */
        void addExtraRunAfter(void (*extra)(void)) ;


		/** @brief	Stop the application. */
		void stop() ;


        /** @brief  Get the width of the display. */
        int getDisplayWidth() ;

        /** @brief  Get the height of the display. */
        int getDisplayHeight() ;

	private:
	    /**
	     * @brief   Handle keyboard when a key is pressed.
	     * @param   The catched event.
	     */
		void keyboardKeyDownEvents(ALLEGRO_EVENT& ev) ;
} ;

#endif

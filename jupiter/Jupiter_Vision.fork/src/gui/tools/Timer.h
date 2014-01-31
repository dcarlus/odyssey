#ifndef __TIMER_H__
#define __TIMER_H__

#include <allegro5/allegro.h>

/**
 * @brief   Abstraction of the Allegro library timer.
 * @author  Denis CARLUS
 */
class Timer {
	protected:
	    /** @brief  Underlying Allegro time. */
		ALLEGRO_TIMER* m_timer ;

	public:
	    /**
	     * @brief   Create a time with a frequency.
	     * @param   frequency   Frequency of the timer.
	     */
		Timer(float frequency) ;

        /** @brief  Destroy the timer. */
		virtual ~Timer() ;


        /** @brief  Start the timer. */
		void start() ;

        /** @brief  Get the underlying Allegro time. */
		ALLEGRO_TIMER* getAllegroTimer() ;
} ;
#endif

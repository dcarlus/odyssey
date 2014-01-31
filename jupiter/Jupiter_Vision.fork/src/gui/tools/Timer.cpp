#include "Timer.h"

Timer::Timer(float frequency) : m_timer(0) {
	m_timer = al_create_timer(frequency) ;
	assert(m_timer != 0) ;
}

Timer::~Timer() {
	al_destroy_timer(m_timer) ;
}


void Timer::start() {
	al_start_timer(m_timer) ;
}


ALLEGRO_TIMER* Timer::getAllegroTimer() {
	return m_timer ;
}

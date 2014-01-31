#include "Allegro.h"
#include "../constants.h"
#include <easysocket/tools.h>
#include "managers/ScreenManager.h"

using namespace std ;

Allegro* Allegro::Singleton = 0 ;


Allegro::Allegro() : m_isRunning(true), m_event_queue(0) {
    #ifdef DEBUG
        Logger::print("Game initialization") ;
    #endif

	// Set up the application requirements
	m_window = new Window(WINDOW_WIDTH, WINDOW_HEIGHT) ;
	m_FPSTimer = new Timer(1.f/60.f) ;

    assert(al_install_keyboard()) ;                    // Allows to use keyboard
	m_event_queue = al_create_event_queue() ;          // Handle several events
	assert(m_event_queue != 0) ;
	al_register_event_source(m_event_queue, al_get_display_event_source(m_window -> getDisplay())) ;
	al_register_event_source(m_event_queue, al_get_timer_event_source(m_FPSTimer -> getAllegroTimer())) ;
	al_register_event_source(m_event_queue, al_get_keyboard_event_source()) ;
    al_install_mouse() ;
    al_register_event_source(m_event_queue, al_get_mouse_event_source()) ;
	m_FPSTimer -> start() ;

    ScreenManager::getInstance() ;

	// Set up the game data
	refresh() ;
}

Allegro::~Allegro() throw () {
	delete m_FPSTimer ;
	delete m_window ;
	al_destroy_event_queue(m_event_queue) ;
}


Allegro* Allegro::getInstance() {
    if (Singleton == 0)
        Singleton = new Allegro() ;
    return Singleton ;
}


void Allegro::refresh() {
    ScreenManager::getInstance() -> display() ;
	m_window -> refresh() ;
}


void Allegro::run() {
	while (m_isRunning) {
		ALLEGRO_EVENT ev ;
		al_wait_for_event(m_event_queue, &ev) ;

		if (ev.type == ALLEGRO_EVENT_TIMER) {
		    if (ev.timer.source == m_FPSTimer -> getAllegroTimer()) {
//                for (auto& f : m_callBefore)
//                    f() ;

		        // Wait for the clock tic
		        // Do the staff during one clock tic
		        refresh() ;
                ScreenManager::getInstance() -> update() ;

//                for (auto& f : m_callAfter)
//                    f() ;
            }
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			// A key on the keyboard has been pressed
			keyboardKeyDownEvents(ev) ;
		}
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			// The application is to be stopped on window closure
			stop() ;
		}
        #ifdef USE_MOUSE
		else if (ev.type == ALLEGRO_EVENT_MOUSE_AXES ||
                    ev.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY) {
            Position mousePos(ev.mouse.x, ev.mouse.y) ;
            CursorPositionBuffer::getInstance() -> addPosition(mousePos) ;
		}
		else {
		    CursorPositionBuffer::getInstance() -> lostCursor() ;
		}
		#endif
	}
}


void Allegro::addExtraRunBefore(void (*extra)(void)) {
    m_callBefore.push_back(extra) ;
}

void Allegro::addExtraRunAfter(void (*extra)(void)) {
    m_callAfter.push_back(extra) ;
}

void Allegro::stop() {
    m_isRunning = false ;
}


void Allegro::keyboardKeyDownEvents(ALLEGRO_EVENT& ev) {
	switch (ev.keyboard.keycode) {
	    /* Stop the application */
		case ALLEGRO_KEY_ESCAPE:
		    stop() ;
		    break ;

		default:
		    ScreenManager::getInstance() -> getCurrentScreen() -> keyPressed(ev.keyboard.keycode) ;
		    break ;
	}
}


int Allegro::getDisplayWidth() {
    return m_window -> getWidth() ;
}

int Allegro::getDisplayHeight() {
    return m_window -> getHeight() ;
}

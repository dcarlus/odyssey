#include "Window.h"
#include <easysocket/tools.h>
#include <allegro5/allegro_image.h>
//#include <GL/glew.h>
#include <GL/gl.h>
#include <string>

using namespace std ;

Window::Window(int sizeX, int sizeY) : m_display(0) {
	assert(al_init()) ;

    #ifdef DEBUG
    Logger::print("Set up display") ;
    #endif

    m_fullscreen = false ;
    al_set_new_display_flags(ALLEGRO_OPENGL) ;
	m_display = al_create_display(sizeX, sizeY) ;
	assert(m_display != 0) ;
	assert(al_init_image_addon()) ;

    // Setup OpenGL
//    glewInit() ;
    glEnable(GL_DEPTH_TEST) ;
//    glEnable(GL_LIGHTING) ;
    glEnable(GL_TEXTURE_2D) ;
    glFrontFace(GL_CCW) ;
    al_clear_to_color(al_map_rgb(0,0,0)) ;

    glMatrixMode(GL_PROJECTION) ;
    glLoadIdentity() ;
    glOrtho(0.0f, sizeX, sizeY, 0.0f, 0.0f, 1.0f) ;
    glMatrixMode(GL_MODELVIEW) ;
	refresh() ;
}


Window::~Window() {
    al_destroy_display(m_display) ;
}

void Window::refresh() {
	al_flip_display() ;
}

void Window::switchFullscreen() {
    m_fullscreen = !m_fullscreen ;
    al_toggle_display_flag(m_display, ALLEGRO_FULLSCREEN_WINDOW, m_fullscreen) ;
}

ALLEGRO_DISPLAY* Window::getDisplay() {
	return m_display ;
}

/** @brief  Get the width of the displaying window. */
int Window::getWidth() {
    return al_get_display_width(m_display) ;
}

/** @brief  Get the height of the displaying window. */
int Window::getHeight() {
    return al_get_display_height(m_display) ;
}

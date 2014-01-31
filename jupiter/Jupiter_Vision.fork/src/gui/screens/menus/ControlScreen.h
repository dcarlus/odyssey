#ifndef __POLYPHEMUS__CONTROL_SCREEN_H__
#define __POLYPHEMUS__CONTROL_SCREEN_H__

#include "../Screen.h"
#include "../gui/AlComponent.h"
#include "../gui/AlAbstractAction.h"
#include "../../constants.h"
#include "../../tools/Allegro.h"
#include "../../tools/geometry/Position.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <string>
#include <map>

/**
 * @brief   A control screen is used to control Mercury. It provides GUI
 *          elements to build a useful graphical interface.          
 * @author  Denis CARLUS
 */
class ControlScreen : public Screen {
	typedef std::map<std::string, ALLEGRO_FONT*>::iterator FontIterator ;
	typedef std::map<std::string, ALLEGRO_COLOR>::iterator ColorIterator ;

    private:
        /** @brief  Fonts used on the screen. */
        std::map<std::string, ALLEGRO_FONT*> m_fonts ;
        /** @brief  Colors used on the screen. */
        std::map<std::string, ALLEGRO_COLOR> m_colors ;
        /** @brief  GUI components on the screen. */
        std::map<std::string, AlComponent*> m_guiComponents ;

    protected:
        /** @brief  Title of the screen. */
        std::string m_title ;
        /** @brief  Actions on the screen. */
        std::map<std::string, AlAbstractAction*> m_actions ;
        /** @brief  Last used button. */
        AlComponent* m_lastPressedButton ;


    public:
        /** @brief  Create an ControlScreen. */
        ControlScreen(const std::string& title = "",
                      const std::string& background = "background") ;

        /** @brief  Destroy an IntroScreen. */
        virtual ~ControlScreen() ;


        /** @brief  Move the cursor and test the buttons. */
        virtual void update() ;


    protected:
        /** @brief  Preload media used by the screen. */
        virtual void preload()  ;

        /**
         * @brief  Display the screen.
         * @warning The fonts must have been defined for title and texts.
         */
        virtual void additionnalDisplay() ;

        /**
         * @brief   Get the component with given ID.
         * @param   id  ID of the component.
         * @return  The component if found, 0 else.
         */
        AlComponent* getComponent(const std::string& id) ;


        /**
         * @brief  Add a text to display.
         * @param   id      ID of the component to easily retreive it.
         * @param   text    The text to display.
         * @param   pos     Position of the text. If the screen already has a
         *                  text, the position is computed relatively to the
         *                  previously one.
         * @param   width   Width of the text. If null, take the right border
         *                  of the window.
         * @warning Font must be defined for text before calling this function.
         */
        void addText(const std::string& id,
                     const std::string& text,
                     const Position& pos) ;

        /**
         * @brief   Add a GUI component.
         * @param   id          ID of the component to easily retreive it.
         * @param   component   Component to add to the screen.
         */
        void addComponent(const std::string& id, AlComponent* component) ;


        /** @brief  Set the buttons font. */
        void setButtonsFont(const std::string& path, unsigned char size) ;

        /** @brief  Set the title font. */
        void setTitleFont(const std::string& path, unsigned char size) ;

        /** @brief  Set the title color. */
        void setTitleColor(unsigned char red,
                           unsigned char green,
                           unsigned char blue,
                           unsigned char alpha) ;

        /** @brief  Set the text font. */
        void setTextFont(const std::string& path, unsigned char size) ;

        /** @brief  Set the text color. */
        void setTextColor(unsigned char red,
                          unsigned char green,
                          unsigned char blue,
                          unsigned char alpha) ;
}  ;

#endif

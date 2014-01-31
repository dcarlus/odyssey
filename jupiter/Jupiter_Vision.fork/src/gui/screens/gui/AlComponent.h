#ifndef __ALLEGRO_COMPONENT_H__
#define __ALLEGRO_COMPONENT_H__

#include "../../tools/geometry/Position.h"
#include "../../tools/geometry/Rectangle2D.h"
#include <allegro5/allegro.h>
#include <string>
#include <map>

/**
 * @brief   GUI component from which all the components are created (buttons,
 *          etc).
 * @author  Denis CARLUS
 */
class AlComponent {
    public:
        /** @brief  States of the component. */
        enum COMPONENT_STATES {STATE_DEFAULT    = 1,
                               STATE_ACTIVE     = 2,
                               STATE_OVER       = 4} ;

        /** @brief  Layer of the component. */
        enum COMPONENT_LAYER {LAYER_FOREGROUND  = 8,
                              LAYER_BACKGROUND  = 16} ;

    protected:
        /** @brief  Bounds of the component. */
        Rectangle2D m_bounds ;   

    private:

        /** @brief  Colors used to display the component. */
        std::map<unsigned char, ALLEGRO_COLOR> m_colors ;
        /** @brief  State of the component. */
        COMPONENT_STATES m_state ;
        /** @brief  To display, or not, the component background. */
        bool m_translucent ;


    public:
        /**
         * @brief   Create a new AlComponent.
         * @param   pos         Position of the component.
         * @param   translucent Make the component translucent.
         */
        AlComponent(const Position& pos, bool translucent = false) ;

        /** @brief  Destruction of an AlComponent. */
        virtual ~AlComponent() ;


        /** @brief  Display the component. */
        virtual void display() = 0 ;

        /** @brief  Update the component. */
        virtual void update() = 0 ;

        /** @brief  Align the component on X when its bounds are set. */
        void alignX() ;

        /** @brief  Align the component on Y when its bounds are set. */
        void alignY() ;

        /**
         * @brief   Test the position of the cursor compared to the button.
         * @param   pos Position of the cursor.
         */
        bool testCursor(const Position& cursorPos) ;

        /**
         * @brief   Test the position of the cursor compared to the button.
         * @param   x Position of the cursor.
         * @param   y Position of the cursor.
         */
        bool testCursor(float x, float y) ;

        /** @brief  Trigger the component action. */
        virtual void trigger() = 0 ;

        /**
         * @brief   Set the default colors of the component.
         * @param   layer   Layer to which the color is applied.
         * @param   color   Color of the layer.
         */
        void setColor(COMPONENT_LAYER layer, ALLEGRO_COLOR color) ;

        /**
         * @brief   Set the active colors of the component.
         * @param   layer   Layer to which the color is applied.
         * @param   color   Color of the layer.
         */
        void setActiveColor(COMPONENT_LAYER layer, ALLEGRO_COLOR color) ;

        /**
         * @brief   Set the colors of the component when cursor is over.
         * @param   layer   Layer to which the color is applied.
         * @param   color   Color of the layer.
         */
        void setOverColor(COMPONENT_LAYER layer, ALLEGRO_COLOR color) ;

        /** @brief  Set the state of the component. */
        void setState(COMPONENT_STATES state) ;


    protected:
        /** @brief  Set the component translucent. No background displayed. */
        void setTranslucent(bool translucent) ;

        /**
         * @brief  Get the wanted color.
         * @param   state   State of the component.
         * @param   layer   Layer of the component.
         */
        ALLEGRO_COLOR& getColor(COMPONENT_LAYER layer) ;

        /** @brief  Action to perform when component is in default state. */
        virtual void actionOnDefault() ;

        /** @brief  Action to perform when component is in over state. */
        virtual void actionOnOver() ;

        /** @brief  Action to perform when component is in active state. */
        virtual void actionOnActive() ;


        /**
         * @brief   Update the bounds of the component.
         * @param   pos     Position of the component.
         * @param   size    Size of the component.
         */
        void updateBounds(const Position& pos, const Dimension& size) ;
} ;

#endif

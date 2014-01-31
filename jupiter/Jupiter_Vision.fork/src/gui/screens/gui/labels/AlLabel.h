#ifndef __ALLEGRO_LABEL_H__
#define __ALLEGRO_LABEL_H__

#include "../AlComponent.h"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include <string>
#include <vector>

/**
 * @brief   Label to display text in the frame.
 * @author  Denis CARLUS
 */
class AlLabel : public AlComponent {
    protected:
        /** @brief  Maximal width of the label. */
        unsigned short m_maxWidth ;
        /** @brief  Text of the label. */
        std::string m_text ;
        /** @brief  Text is splitted into several parts. */
        std::vector<std::string> m_splits ;
        /** @brief  Font of the label. */
        ALLEGRO_FONT* m_font ;


    public:
        /**
         * @brief   Create a new AlLabel.
         * @param   pos Position of the label
         */
        AlLabel(const Position& pos,
                const std::string& text,
                ALLEGRO_FONT* font) ;

        /** @brief  Destruction of an AlLabel. */
        virtual ~AlLabel() ;


        /** @brief  Display the button. */
        virtual void display() ;

        /** @brief  Update the button. */
        virtual void update() ;


        /** @brief  Trigger the component action. */
        virtual void trigger() ;

        /** @brief  Set the text of the label. */
        void setText(const std::string& text) ;

        /** @brief  Get the text of the label. */
        std::string& getText() ;

        /**
         * @brief   Set the max width of the label.
         * @param   maxWidth    Maximal width of the label.
         */
        void setMaxWidth(unsigned short maxWidth) ;


    protected:
        /**
         * @brief   Adjust the text of the label to the frame or given max
         *          width.
         */
        void adjustText() ;

        /** @brief  Action to perform when component is in active state. */
        virtual void actionOnActive() ;
} ;

#endif

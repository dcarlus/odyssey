#ifndef __ALLEGRO_ABSTRACT_ACTION_H__
#define __ALLEGRO_ABSTRACT_ACTION_H__

#include <string>

/**
 * @brief   Action used to make some specific tasks when used with a GUI
 *          component for example.
 * @author  Denis CARLUS
 */
class AlAbstractAction {
    protected:
        /** @brief  Text displayed by the action. */
        std::string m_text ;

    public:
        /** @brief  Create an AlAbstractAction. */
        AlAbstractAction() ;

        /**
         * @brief   Create an AlAbstractAction.
         * @param   text    Text displayed by the action.
         */
        AlAbstractAction(const std::string& text) ;

        /** @brief  Destroy an AlAbstractAction. */
        virtual ~AlAbstractAction() ;


        /** @brief  Run the action. */
        virtual void run() = 0 ;

        /** @brief  Get the text linked to the action. */
        std::string& getText() ;
} ;

#endif

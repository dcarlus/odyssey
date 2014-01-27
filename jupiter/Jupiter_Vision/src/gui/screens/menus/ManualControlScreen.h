#ifndef __POLYPHEMUS__MANUAL_CONTROL_SCREEN_H__
#define __POLYPHEMUS__MANUAL_CONTROL_SCREEN_H__

#include "../gui/AlAbstractAction.h"
#include "ControlScreen.h"
#include <string>

/**
 * @brief   Menu to manually control the robot.
 * @author  Denis CARLUS
 * @version 1.0 26/01/2014
 */
class ManualControlScreen : public ControlScreen {
    public:
        /** @brief  Create a ManualControlScreen. */
        ManualControlScreen() ;

        /** @brief  Destruction of a ManualControlScreen. */
        virtual ~ManualControlScreen() ;


        /** @brief  Make the screen do action on key press. */
        virtual void keyPressed(int keycode) ;

        /** @brief  Make the screen do action on key release. */
        virtual void keyReleased(int keycode) ;

    protected:
        /**
         * @brief   Create a thread to update the battery load.
         * @param   execution   The action to execute.
         */
        static void* updateBattery(void* execution) ;


        /**
         * @brief   Action to move Mercury ahead.
         * @author  Denis CARLUS
         * @version 1.0 26/01/2014
         */
        class MoveAhead : public AlAbstractAction {
            /** @brief  Run the action. */
            virtual void run() ;
        } ;

        /**
         * @brief   Action to move Mercury back.
         * @author  Denis CARLUS
         * @version 1.0 26/01/2014
         */
        class MoveBack : public AlAbstractAction {
            /** @brief  Run the action. */
            virtual void run() ;
        } ;

        /**
         * @brief   Action to turn Mercury on the right.
         * @author  Denis CARLUS
         * @version 1.0 26/01/2014
         */
        class TurnRight : public AlAbstractAction {
            /** @brief  Run the action. */
            virtual void run() ;
        } ;

        /**
         * @brief   Action to turn Mercury on the left.
         * @author  Denis CARLUS
         * @version 1.0 26/01/2014
         */
        class TurnLeft : public AlAbstractAction {
            /** @brief  Run the action. */
            virtual void run() ;
        } ;

        /**
         * @brief   Action to stop Mercury.
         * @author  Denis CARLUS
         * @version 1.0 26/01/2014
         */
        class Stop : public AlAbstractAction {
            /** @brief  Run the action. */
            virtual void run() ;
        } ;

        /**
         * @brief   Action to modify the LED state.
         * @author  Denis CARLUS
         * @version 1.0 26/01/2014
         */
        class LED : public AlAbstractAction {
            /** @brief  Run the action. */
            virtual void run() ;
        } ;

        /**
         * @brief   Action to get the battery load.
         * @author  Denis CARLUS
         * @version 1.0 26/01/2014
         */
        class BatteryLoad : public AlAbstractAction {
            /** @brief  Run the action. */
            virtual void run() ;
        } ;
} ;

#endif

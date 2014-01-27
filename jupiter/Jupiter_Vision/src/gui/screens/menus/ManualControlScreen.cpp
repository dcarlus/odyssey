#include "ManualControlScreen.h"
#include "../gui/buttons/AlButtonBitmap.h"
#include "../gui/labels/AlLabel.h"
#include "../../tools/managers/ScreenManager.h"
#include "../../../clients/CommandClient.h"
#include <iostream>
#include <easysocket/tools.h>
#include <allegro5/allegro.h>

extern "C" {
    #include <Robot.h>
}


using namespace std ;


ManualControlScreen::ManualControlScreen() : ControlScreen("Manual control") {
    string sprite ;
    AlButtonBitmap* button ;

    // Up button
    string id = "go_ahead" ;
    m_actions[id] = new MoveAhead() ;
    sprite = "control/up" ;
    button = new AlButtonBitmap(Position(480.f, 16.f), sprite, m_actions[id]) ;
    addComponent(id, button) ;

    // Right button
    id = "turn_right" ;
    m_actions[id] = new TurnRight() ;
    sprite = "control/right" ;
    button = new AlButtonBitmap(Position(560.f, 96.f), sprite, m_actions[id]) ;
    addComponent(id, button) ;

    // Down button
    id = "go_back" ;
    m_actions[id] = new MoveBack() ;
    sprite = "control/down" ;
    button = new AlButtonBitmap(Position(480.f, 176.f), sprite, m_actions[id]) ;
    addComponent(id, button) ;

    // Left button
    id = "turn_left" ;
    m_actions[id] = new TurnLeft() ;
    sprite = "control/left" ;
    button = new AlButtonBitmap(Position(400.f, 96.f), sprite, m_actions[id]) ;
    addComponent(id, button) ;

    // Stop button
    id = "stop" ;
    m_actions[id] = new Stop() ;
    sprite = "control/stop" ;
    button = new AlButtonBitmap(Position(480.f, 96.f), sprite, m_actions[id]) ;
    addComponent(id, button) ;

    // LED button
    id = "led" ;
    m_actions[id] = new LED() ;
    sprite = "control/led" ;
    button = new AlButtonBitmap(Position(32.f, 96.f), sprite, m_actions[id]) ;
    addComponent(id, button) ;

    // Emulate Stop key pressed
    m_lastPressedButton = 0 ;
    keyPressed(ALLEGRO_KEY_PAD_5) ;
}

ManualControlScreen::~ManualControlScreen() {
    // Emulate Stop key pressed
    keyPressed(ALLEGRO_KEY_PAD_5) ;
}


void ManualControlScreen::keyPressed(int keycode) {
    string id ;
    bool switchButton = false ;

    switch (keycode) {
        case ALLEGRO_KEY_PAD_8:
            id = "go_ahead" ;
            break ;

        case ALLEGRO_KEY_PAD_4:
            id = "turn_left" ;
            break ;

        case ALLEGRO_KEY_PAD_2:
            id = "go_back" ;
            break ;

        case ALLEGRO_KEY_PAD_6:
            id = "turn_right" ;
            break ;

        case ALLEGRO_KEY_PAD_5:
            id = "stop" ;
            break ;

        case ALLEGRO_KEY_PAD_0:
            id = "led" ;
            switchButton = true ;
            ((AlButtonBitmap*) getComponent(id)) -> changeState() ;
            break ;
    }

    m_actions[id] -> run() ;

    if (!switchButton) {
        if (m_lastPressedButton != 0)
            ((AlButtonBitmap*) m_lastPressedButton) -> changeState() ;
        m_lastPressedButton = ((AlButtonBitmap*) getComponent(id)) ;
        ((AlButtonBitmap*) m_lastPressedButton) -> changeState() ;
    }
}

void ManualControlScreen::keyReleased(int keycode) {}


void ManualControlScreen::MoveAhead::run() {
    CommandClient::getInstance() -> sendMoveCommand(ROBOT_COMMAND_FORWARD) ;
}

void ManualControlScreen::MoveBack::run() {
    CommandClient::getInstance() -> sendMoveCommand(ROBOT_COMMAND_BACKWARD) ;
}

void ManualControlScreen::TurnRight::run() {
    CommandClient::getInstance() -> sendMoveCommand(ROBOT_COMMAND_RIGHT) ;
}

void ManualControlScreen::TurnLeft::run() {
    CommandClient::getInstance() -> sendMoveCommand(ROBOT_COMMAND_LEFT) ;
}

void ManualControlScreen::Stop::run() {
    CommandClient::getInstance() -> sendMoveCommand(ROBOT_COMMAND_STOP) ;
}

void ManualControlScreen::LED::run() {
    CommandClient::getInstance() -> sendLEDCommand() ;
}

#ifndef __JUPITER__DISPLAYABLE_INTERFACE__
#define __JUPITER__DISPLAYABLE_INTERFACE__

/**
 * @brief   Interface to make an object displayable on screen.
 * @author  Denis CARLUS
 * @version 1.0 21/01/2014
 */
class Displayable {
    public:
        /** @brief  Display the element. */
        virtual void display() = 0 ;
} ;

#endif

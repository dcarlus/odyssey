#ifndef __PIXEL_H__
#define __PIXEL_H__

class Pixel {
    public:
        /** @brief  Location of the pixel. */
        int m_x ;
        int m_y ;
        /** @brief  ID of the component the pixel belongs. */
        unsigned int m_componentID ;


        /** @brief  Create a new pixel. */
        Pixel() ;
        /** @brief  Create a pixel. */
        Pixel(int x, int y) ;
        /** @brief  Create a pixel. */
        Pixel(int x, int y, unsigned int id) ;
        /** @brief  Delete a pixel. */
        virtual ~Pixel() ;



                                                                                /** SETTERS **/
        /** @brief  Set the X coordinate. */
        void setX(int x) ;

        /** @brief  Set the Y coordinate. */
        void setY(int y) ;


        /** @brief  Set the ID of the component the pixel belongs. */
        void setComponentID(unsigned int id) ;

        /** @brief  Get the component ID. */
        unsigned int getComponentID() ;
} ;

#endif

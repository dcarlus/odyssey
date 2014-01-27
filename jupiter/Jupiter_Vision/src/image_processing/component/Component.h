#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include "../../tools/geometry/Position.h"
#include "Pixel.h"
#include <opencv2/core/core.hpp>
#include <vector>

using namespace cv ;

class Component {
    protected:
        /** @brief  Counter of components. */
        static unsigned int ComponentsCounter ;

        /** @brief  ID of the component. */
        unsigned int m_id ;
        /** @brief  Color of the component. */
        Scalar m_color ;
        /** @brief  Pixels in the component. */
        std::vector<Pixel*> m_pixels ;

        /** @brief  Minimal bound of the component. */
        Position m_minBound ;
        /** @brief  Maximal bound of the component. */
        Position m_maxBound ;


    public:
        /** @brief  Create a new connected component. */
        Component() ;

        /** @brief  Destroy a connected component. */
        virtual ~Component() ;

        /**
         * @brief   Merge two connected components. It automatically copy data
         *          from the smallest one to the biggest to limit time
         *          consumption.
         * @param   other   The other component to merge with.
         * @return  The component that can be removed if not removed yet.
         */
        virtual Component* merge(Component* other) ;

        /** @brief  Add a new pixel to the component. */
        inline virtual void addPixel(int x, int y) ;

        /** @brief  Add a new pixel to the component. */
        void addPixel(Pixel* px) ;

        /** @brief  Draw the component on picture. */
        virtual void draw(Mat& picture) ;

        /** @brief  Get the ID of the component. */
        virtual unsigned int getID() ;

        /** @brief  Get the center point of the component. */
        Position getCenter() ;

        /** @brief  Get the amount of pixels in the component. */
        int getSize() ;

        /** @brief  Get the pixel color when the component is drawn. */
        virtual Scalar& getColor() ;

        /** @brief  Get the pixels of the Component. */
        std::vector<Pixel*>& getPixels() ;


        /** @brief  Set the color of the component making it visible. */
        void setColor() ;


    protected:
        /** @brief  Adjust the bounds of the component. */
        void adjustBounds(Pixel* px) ;
} ;

#endif

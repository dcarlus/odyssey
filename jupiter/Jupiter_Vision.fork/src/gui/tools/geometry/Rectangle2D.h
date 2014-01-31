#ifndef __GEOMETRY_RECTANGLE2D_H__
#define __GEOMETRY_RECTANGLE2D_H__

#include "Position.h"

/**
 * @brief   Some rectangle utilities, from Java Rectangle2D class code.
 * @author  See Java code!
 */
class Rectangle2D {
    public:
        /**
         * @brief  The bitmask that indicates that a point lies on left, above,
         *         on right or below this Rectangle2D.
         */
        enum OUT_SIDE {OUT_LEFT     = 1,
                       OUT_TOP      = 2,
                       OUT_RIGHT    = 4,
                       OUT_BOTTOM   = 8} ;


    protected:
        /** @brief  Position of the rectangle. */
        Position m_pos ;

        /** @brief  Dimention of the rectangle. */
        Dimension m_size ;

        /** @brief  Half size of the rectangle. */
        Dimension m_halfSize ;

        /** @brief  Position of the other bound point (position + size). */
        Position m_bound ;

        /** @brief  Position of the center point (position + size / 2). */
        Position m_center ;


    public:
        /** @brief  Create a new Rectangle2D. */
        Rectangle2D() ;

        /** @brief  Create a new Rectangle2D. */
        Rectangle2D(float w, float h) ;

        /** @brief  Create a new Rectangle2D. */
        Rectangle2D(float x, float y, float w, float h) ;

        /** @brief  Destruction of a Rectangle2D. */
        virtual ~Rectangle2D() ;



        /**
         * @brief   Test if this Rectangle2D contains another one.
         * @param   other   The other Rectangle2D to test.
         * @return  true if the two Rectangle2D are overlapping; false otherwise.
         */
        bool contains(const Rectangle2D& other) ;

        /**
         * @brief   Test if this Rectangle2D intersects another one.
         * @param   other   The other Rectangle2D to test.
         * @return  true if the two Rectangle2D intersect; false otherwise.
         */
        bool intersects(const Rectangle2D& other) ;

        /**
         * @brief   Tests if the specified point is inside this Rectangle2D.
         * @param   p   Point to test.
         * @return  true if the given point is in this Rectangle2D; false
         *          otherwise.
         */
        bool contains(const Position& p) ;


        /**
         * @brief   Tests if the specified line segment intersects the interior
         *          of this Rectangle2D. 
         * @param   p1  Start point of the line segment.
         * @param   p2  End point of the line segment.
         * @return  true if the specified line intersects the interior of this
         *          Rectangle2D; false otherwise.
         */
        bool intersectsLine(Position& p1, Position& p2) ;


        /**
         * @brief   Determines where the specified point lies with respect to
         *          this Rectangle2D. This method computes a binary OR of the
         *          appropriate mask values indicating, for each side of this
         *          Rectangle2D, whether or not the specified point is on the
         *          same side of the edge as the rest of this Rectangle2D.
         */
        unsigned char outcode(float x, float y) ;

        /**
         * @brief   Determines where the specified point lies with respect to
         *          this Rectangle2D. This method computes a binary OR of the
         *          appropriate mask values indicating, for each side of this
         *          Rectangle2D, whether or not the specified point is on the
         *          same side of the edge as the rest of this Rectangle2D.
         */
        unsigned char outcode(const Position& p) ;


        /** @brief  Move the rectangle with an offset, without modifying its size. */
        void moveOffset(float x, float y) ;

        /** @brief  Move the rectangle to the given position without modifying its size. */
        void moveTo(float x, float y) ;

        /** @brief  Update the rectangle position and size. */
        void update(float x, float y, float w, float h) ;

        /** @brief  Test if the Rectangle2D has an area. */
        bool isEmpty() const ;

        /** @brief  Get the position on X. */
        float getX() const ;
        /** @brief  Get the position on Y. */
        float getY() const ;
        /** @brief  Get the position on X. */
        float getCenterX() const ;
        /** @brief  Get the position on Y. */
        float getCenterY() const ;
        /** @brief  Get the bound at X + width. */
        float getMaxX() const ;
        /** @brief  Get the bound at Y + height. */
        float getMaxY() const ;
        /** @brief  Get the width. */
        float getHalfWidth() const ;
        /** @brief  Get the height. */
        float getHalfHeight() const ;
        /** @brief  Get the width. */
        float getWidth() const ;
        /** @brief  Get the height. */
        float getHeight() const ;
} ;

#endif

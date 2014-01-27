#ifndef __POSITION_2D_H__
#define __POSITION_2D_H__

/**
 * @brief   Position in the 2D space using two short values.
 * @author  Denis CARLUS
 */
struct Position {
    /** @brief   Position of the point on X axis. */
    float x ;

    /** @brief   Position of the point on X axis. */
    float y ;


    /** @brief  Create a position. */
    Position() ;

    /** @brief  Create a position. */
    Position(float x, float y) ;

    /** @brief  Copy a position. */
    Position(const Position& pos) ;

    /** @brief  Destruction of a position. */
    virtual ~Position() ;

    /**
     * @brief   Comparison of Point2D.
     * @param   p1  First point of comparison.
     * @param   p2  Second point of comparison.
     * @return  TRUE if points are at the same position, FALSE else.
     */
    bool operator== (const Position& p2) const ;

    /**
     * @brief   Comparison of Point2D.
     * @param   p1  First point of comparison.
     * @param   p2  Second point of comparison.
     * @return  TRUE if points are at the different position, FALSE else.
     */
    bool operator!= (const Position& p2) const ;


    /** @brief  Add two Positions. */
    friend Position operator+ (const Position& a, const Position& b) ;

    /** @brief  Substract two Positions. */
    friend Position operator- (const Position& a, const Position& b) ;

    /**
     * @brief   Comparison of Point2D.
     * @param   p1  First point of comparison.
     * @param   p2  Second point of comparison.
     * @return  TRUE if at least one coordinate of p1 is higher than p2, the
     *          other coordinate must be at least equal to the p2's one.
     */
    friend bool operator> (const Position& p1, const Position& p2) ;

    /**
     * @brief   Comparison of Point2D.
     * @param   p1  First point of comparison.
     * @param   p2  Second point of comparison.
     * @return  TRUE if p1 is higher than p2 or they are equal.
     */
    friend bool operator>= (const Position& p1, const Position& p2) ;

    /**
     * @brief   Comparison of Point2D.
     * @param   p1  First point of comparison.
     * @param   p2  Second point of comparison.
     * @return  TRUE if at least one coordinate of p2 is higher than p1, the
     *          other coordinate must be at least equal to the p1's one.
     */
    friend bool operator< (const Position& p1, const Position& p2) ;

    /**
     * @brief   Comparison of Point2D.
     * @param   p1  First point of comparison.
     * @param   p2  Second point of comparison.
     * @return  TRUE if p2 is higher than p1 or they are equal.
     */
    friend bool operator<= (const Position& p1, const Position& p2) ;
} ;


typedef Position Distance ;
typedef Position Dimension ;
typedef Position Speed ;

#endif

#include "Math.h"

Math Math::Singleton ;
const double Math::pi = 4. * atan(1.) ;
const double Math::rad_coeff = Math::pi / 180. ;
const double Math::deg_coeff = 180. / Math::pi ;


Math::Math() throw() {}

Math::~Math() throw() {}


double Math::toRadian(double degree) {
    return degree * Singleton.rad_coeff ;
}


double Math::toDegree(double radian) {
    return radian * Singleton.deg_coeff ;
}

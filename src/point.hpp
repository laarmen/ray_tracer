#pragma once


#include "screen_vector/vector.hpp"

class Point {
  private:
    double abs;

    double ord;

    double app;


  public:
    //Returns the abscissa of the point.
    double x() const;

    //Returns the ordinate of the point.
    double y() const;

    //Returns the applicate of the point.
    double z() const;

    //Returns the vector from `p` to `this`
    rt::vector operator -(const Point & p) const;

    void operator +=(const rt::vector & v);

};

#ifndef POINT_H_
#define POINT_H_

class Point
{
public:
 	/**
     * Constructs a point where all of the components are 0.
     */
    Point();
    
	/**
     * Constructs a point with the specified values (X, Y, Z).
     */
	Point(double x, double y, double z);

    /**
     * Returns the X component of the point.
     */
    double GetX() const;
    
    /**
     * Returns the Y component of the point.
     */
    double GetY() const;
    
    /**
     * Returns the Z component of the point.
     */
    double GetZ() const;
    
    /**
     * Returns the Euclidean distance from this point to the 
     * other point passed as a parameter.
     */
	double DistanceTo(const Point &otherPoint) const;

    /**
     * Returns the cross product of this point interpreted as a vector
     * with the other specified point interpreted as a vector.
     */
    Point CrossProduct(const Point &otherPoint) const;
    
    /**
     * Returns the vector length of the point, that is, the distance 
     * of the point from the origin.
     */
    double Length() const;
    
	/**
     * Normalize the point in-place to become a unit vector.
     */
    void Normalize();
    
    /**
     * Reverse the direction of the point with respect to the origin.
     * Changes are made in-place.
     */
    void Reverse();
    
    /**
     * Returns a new point whose components are the sum of the
     * components of the argument points.
     */
    Point operator+(const Point &otherPoint) const;

    /**
     * Returns a new point whose components are the difference of the
     * components of the argument points.
     */
    Point operator-(const Point &otherPoint) const;

    /**
     * Returns a new point whose components have been scaled by the
     * constant factor.
     */
    Point operator*(double scalingFactor) const;

    /**
     * Returns a new point whose components are the product of the
     * components of the argument points.
     */
    Point operator*(const Point &otherPoint) const;
    
    /**
     * Returns a new point whose components have been divided by the
     * constant factor.
     */
    Point operator/(double scalingFactor) const;

    /**
     * Adds the value of the other point to this point. Returns a
     * reference to this point for convenience.
     */
    Point &operator+=(const Point &otherPoint);
    
private:
	double x;
	double y;
    double z;
};

/**
* This allows us to multiply with the scaling factor on the left,
* ex: "2.5 * point". Otherwise we could only multiply with the
* scaling factor on the right.
*/
Point operator*(double scalingFactor, const Point &point);

#endif

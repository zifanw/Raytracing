//==========================================================
// STUDENT NAME: WANG Zifan
// NUS User ID.: t0915218
// COMMENTS TO GRADER:
// This project is originally writen with Xcode in Mac OS
//
// ============================================================
//
// FILE: Sphere.cpp



#include <cmath>
#include "Sphere.h"

using namespace std;



bool Sphere::hit( const Ray &r, double tmin, double tmax, SurfaceHitRecord &rec ) const 
{
    //***********************************************
    //*********** WRITE YOUR CODE HERE **************
    //***********************************************
    
    double a = 1.0;
    double b = 2.0 * dot(r.direction(),(r.origin() - center));
    double c = dot((r.origin() - center),(r.origin() - center)) - radius * radius;
    double d = b * b - 4 * a * c;
    
    if (d < 0)
	return false; // You can remove/change this if needed.
    
    else
    {
        double t1 = (-b - sqrt(d)) / (2 * a);
        double t2 = (-b + sqrt(d)) / (2 * a);
        double t;
        if(max(t1,t2) < tmin)
            return false;
        if(min(t1,t2) > tmax)
            return false;
        else if (t1 >= tmin && t2 <= tmin) t = t1;
        else if (t1 <= tmin && t2 >= tmin) t = t2;
        else t = min(t1, t2);
        
        rec.t = t;
        rec.p = r.pointAtParam(t);
        rec.mat_ptr = matp;
        Vector3d t0 = rec.p - center;
        rec.normal = t0 / t0.length();
        return true;
    }
    
}




bool Sphere::shadowHit( const Ray &r, double tmin, double tmax ) const 
{
    //***********************************************
    //*********** WRITE YOUR CODE HERE **************
    //***********************************************
    
    double a = 1.0;
    double b = 2.0 * dot(r.direction(),(r.origin() - center));
    double c = dot((r.origin() - center),(r.origin() - center)) - radius * radius;
    double d = b * b - 4 * a * c;
    
    if (d < 0)
        return false; // You can remove/change this if needed.
    
    else
    {
        double t1 = (-b + sqrt(d))/(2.0 * a);
        double t2 = (-b - sqrt(d))/(2.0 * a);
        
        if ((max(t1,t2) < tmin) || (min(t1,t2) > tmax) || ((t1 < tmin) && (t2 > tmax)))
            return false;
        else
            return true;

}
}


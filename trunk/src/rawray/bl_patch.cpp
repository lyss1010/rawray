/////////////////////////////////////////////////////////////////////////////
// bl_patch.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "bl_patch.h"
#include "material.h"
#include <math.h>

namespace rawray {

void BLPatch::RenderGL() {
    const Vector3& color = material_ ? material_->BaseColor() : Vector3(1);

    // Draw the lines around the perimeter 
    glBegin(GL_LINE_STRIP);
        glColor3f( color.x, color.y, color.z );

        glVertex3f(P00.x, P00.y, P00.z);
        glVertex3f(P01.x, P01.y, P01.z);
        glVertex3f(P11.x, P11.y, P11.z);
        glVertex3f(P10.x, P10.y, P10.z);
        glVertex3f(P00.x, P00.y, P00.z);
    glEnd();
}

void BLPatch::PreCalc() {
}


/*

// See: http://www.cs.utah.edu/~kpotter/pubs/bilinear.pdf
bool BLPatch::Intersect(HitInfo& hit, const Ray& ray, float minDistance, float maxDistance) {
    // NOTE: Do not use binary vector oprerators, it creates too many copies
    Vector3 x1 = P11; x1 -= P10; x1 -= P01; x1 += P00;
    Vector3 x2 = P10; x1 -= P00;
    Vector3 x3 = P01; x1 -= P00;
    Vector3 x4 = P00;

    // Manually solve: r + t*d = uv*x1 + u*x2 + v*x3 + x4
	// t.i = (1/d.i) * (uv*x1.i + u*x2.i + v*x3.i + x4.i - r.i)
    BLPatch::BLPatchData p;

	// setting tx*dx*dz = tz*dz*dx where tx=tz=t and substituting the above equation
	p.A1 = x1.x * ray.direction.z - x1.z * ray.direction.x;
	p.B1 = x2.x * ray.direction.z - x2.z * ray.direction.x;
	p.C1 = x3.x * ray.direction.z - x3.z * ray.direction.x;
	p.D1 = ray.direction.z * (x4.x - ray.origin.x) - ray.direction.x * (x4.z - ray.origin.z);

	// and then using ty*dy*dz = tz*dz*dy
	p.A2 = x1.y * ray.direction.z - x1.z * ray.direction.y;
	p.B2 = x2.y * ray.direction.z - x2.z * ray.direction.y;
	p.C2 = x3.y * ray.direction.z - x3.z * ray.direction.y;
	p.D2 = ray.direction.z * (x4.y - ray.origin.y) - ray.direction.y * (x4.z - ray.origin.z);

    // Set the following two equations equal to each other, you get back a quadratic
    // 0 = uvA1 + uB1 + vC1 + D1 = uvA2 + uB2 + vC2 + D2
    // 0 = v^2(A2C1 - A1C2) + v(A2D1 - A1D2 + B2C1 - B1C2) + (B2D1 - B1D2)
    float v1, v2;
    const int numRoots = math::SolveQuadratic( &v1, &v2,
                            ( p.A2*p.C1 - p.A1*p.C2 ),
                            ( p.A2*p.D1 - p.A1*p.D2 + p.B2*p.C1 - p.B1*p.C2 ),
                            ( p.B2*p.D1 - p.B1*p.D2 ) );

    if( numRoots < 1 ) return false;
    
    // Determine dominant axis, this is to ensure no div by 0 when we compute t
    uint8 axis; // 0=x, 1=y, 2=z
    if( ray.abs.x > ray.abs.y )
        axis = (ray.abs.x > ray.abs.z) ? 0 : 2;
    else
        axis = (ray.abs.y > ray.abs.z) ? 1 : 2;
    
    float t, u, v;
    if( numRoots == 1 ) {
		v = v1;
		u = ComputeU( v, p );
		hit.point = u*v*x1 + u*x2 + v*x3 + x4;
		t = (hit.point[axis] - ray.origin[axis]) / ray.direction[axis];

		if( !IsValid( t, u, v, minDistance, maxDistance, 0.5, 0.5 ) )
			return false;
    } else {
        const float u1 = ComputeU( v1, p );
        const float u2 = ComputeU( v2, p );
        
        Vector3 hit1 = u1*v1*x1 + u1*x2 + v1*x3 + x4;
        Vector3 hit2 = u2*v2*x1 + u2*x2 + v2*x3 + x4;

        const float inv_dir = 1.0f / ray.direction[axis];
        const float t1 = (hit1[axis] - ray.origin[axis]) * inv_dir;
        const float t2 = (hit2[axis] - ray.origin[axis]) * inv_dir;

		const bool hit_1_valid = IsValid( t1, u1, v1, minDistance, maxDistance, 0.5, 0.5 );
		const bool hit_2_valid = IsValid( t2, u2, v2, minDistance, maxDistance, 0.5, 0.5 );
		bool choose_hit_1 = true;

		if( hit_1_valid ) {
			if( hit_2_valid && t2 < t1)
				choose_hit_1 = false;
		} else {
			if( hit_2_valid )
				choose_hit_1 = false;
			else
				return false;
		}

		if( choose_hit_1 ) {
			t = t1;
			u = u1;
			v = v1;
			hit.point = hit1;
		} else {
			t = t2;
			u = u2;
			v = v2;
			hit.point = hit2;
		}
    }

	hit.distance = t;
    hit.texCoord.x = u;
    hit.texCoord.y = v;
    hit.material = material_;

    // Compute the normal by using the partial derivitive w/ respect to u and v individually
    hit.normal = math::Cross( ( (1-v)*(P10-P00) + v*(P11-P01) ), 
                              ( (1-u)*(P01-P00) + u*(P11-P10) ) );

    return true;
}

bool BLPatch::IsValid(float t, float u, float v, float min, float max, float mid1, float mid2) {
	if( t < min || t > max ) return false;
	if( u < 0.0f || u > 1.0f || v < 0.0f || v > 1.0f ) return false;

    return true;
//	if( (u <= mid1 || u >= mid2) || (v <= mid1 || v >= mid2) )
//		return true;

//	return false;
}

float BLPatch::ComputeU(float v, const BLPatch::BLPatchData& p) {
    const float divisor_a = v * (p.A2 + p.B2);
    const float divisor_b = v * (p.A2 - p.A1) + p.B2 - p.B1;

    // Choose the largest divisor for numerical stability
    if( fabs(divisor_b) > fabs(divisor_a) )
        return ( v*(p.C1 - p.C2) + p.D1 - p.D2 ) / divisor_b;

	return -(v*p.C2 + p.D2) / divisor_a;
}



*/



bool BLPatch::Intersect(HitInfo& hit, const Ray& ray, float minDistance, float maxDistance) {
    Vector3 out;
    if( RayPatchIntersection( ray.origin, ray.direction, out ) ) {
        float u = out.x;
        float v = out.y;
        hit.distance = out.z;
        hit.point = SrfEval( u, v );
        hit.normal = Normal( u, v );
        hit.material = material_;
        hit.texCoord.x = u;
        hit.texCoord.y = v;
        return true;
    }

    return false;
}




/**********************************************************************************/

int BLPatch::ComputeV(float* out1, float* out2,
             float a, float b, float c,
             float min, float max,
             float mid1, float mid2)
{
    int numRoots = math::SolveQuadratic(out1, out2, a, b, c);

    switch( numRoots ) {
    case 1:
        if( *out1 < min || *out1 > max || (*out1 > mid1 && *out1 < mid2) )
            numRoots--;
    case 2:
        if( *out1 < min || *out1 > max || (*out1 > mid1 && *out1 < mid2) )
        {
            // out1 is invald, use out2 as our only possible valid one
            numRoots--;
            *out1 = *out2;

            // check if out2 is invalid
            if( *out2 < min || *out2 > max || (*out2 > mid1 && *out2 < mid2) )
                numRoots--;
        } else {
            // out1 was valid, check if out2 is valid also
            if( *out2 < min || *out2 > max || (*out2 > mid1 && *out2 < mid2) )
                numRoots--;
        }
    }

    return numRoots;
}



// What is the x,y,z position of a point at params u and v?
Vector3 BLPatch::SrfEval( double u, double v)
{
  Vector3 respt;
  respt.x = ( ( (1.0 - u) * (1.0 - v) * P00.x +
	     (1.0 - u) *        v  * P01.x + 
	     u  * (1.0 - v) * P10.x +
	     u  *        v  * P11.x));
  respt.y = (  ( (1.0 - u) * (1.0 - v) * P00.y +
	      (1.0 - u) *        v  * P01.y + 
	      u  * (1.0 - v) * P10.y +
	      u  *        v  * P11.y));
  respt.z = (  ( (1.0 - u) * (1.0 - v) * P00.z +
	      (1.0 - u) *        v  * P01.z + 
	      u  * (1.0 - v) * P10.z +
	      u  *        v  * P11.z));
  return respt;
}

//+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+
// Find tangent (du)
//+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+
Vector3 BLPatch::TanU( double v)
{
  Vector3 tanu;
  tanu.x = ( ( 1.0 - v ) * (P10.x - P00.x) + v * (P11.x - P01.x));
  tanu.y = ( ( 1.0 - v ) * (P10.y - P00.y) + v * (P11.y - P01.y));
  tanu.z = ( ( 1.0 - v ) * (P10.z - P00.z) + v * (P11.z - P01.z));
  return tanu;
}

//+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+
// Find tanget (dv)
//+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+
Vector3 BLPatch::TanV( double u)
{
  Vector3 tanv;
  tanv.x = ( ( 1.0 - u ) * (P01.x - P00.x) + u * (P11.x - P10.x) );
  tanv.y = ( ( 1.0 - u ) * (P01.y - P00.y) + u * (P11.y - P10.y) );
  tanv.z = ( ( 1.0 - u ) * (P01.z - P00.z) + u * (P11.z - P10.z) );
  return tanv;
}


//+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+
// Find the normal of the patch
//+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+
Vector3 BLPatch::Normal( double u, double v)
{
  return math::Cross( TanU( v ), TanV( u ) );
}
  
//choose between the best denominator to avoid singularities
//and to get the most accurate root possible
inline double getu(double v, double M1, double M2, double J1,double J2,
	    double K1, double K2, double R1, double R2)
{

  double denom = (v*(M1-M2)+J1-J2);
  double d2 = (v*M1+J1);
  if(fabs(denom) > fabs(d2)) // which denominator is bigger
    {
      return (v*(K2-K1)+R2-R1)/denom;
    }
  return -(v*K1+R1)/d2;
}

// compute t with the best accuracy by using the component
// of the direction that is largest
double computet(Vector3 dir, Vector3 orig, Vector3 srfpos)
{
  // if x is bigger than y and z
  if(fabs(dir.x) >= fabs(dir.y) && fabs(dir.x) >= fabs(dir.z))
    return (srfpos.x - orig.x) / dir.x;
  // if y is bigger than x and z
  else if(fabs(dir.y) >= fabs(dir.z)) // && fabs(dir.y) >= fabs(dir.x))
    return (srfpos.y - orig.y) / dir.y;
  // otherwise x isn't bigger than both and y isn't bigger than both
  else  //if(fabs(dir.z) >= fabs(dir.x) && fabs(dir.z) >= fabs(dir.y))
    return (srfpos.z - orig.z) / dir.z;    
}
	    


//+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+
//             RayPatchIntersection
// intersect rays of the form p = r + t q where t is the parameter
// to solve for. With the patch pointed to by *this
// for valid intersections:
// place the u,v intersection point in uv[0] and uv[1] respectively.
// place the t value in uv[2]
// return true to this function
// for invalid intersections - simply return false uv values can be 
// anything
//+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+
bool BLPatch::RayPatchIntersection(const Vector3& r, const Vector3& q, Vector3& uv)
{
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Equation of the patch:
  // P(u, v) = (1-u)(1-v)P00 + (1-u)vP01 + u(1-v)P10 + uvP11
  // Equation of the ray:
  // R(t) = r + tq
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  Vector3 pos1, pos2; //Vector pos = ro + t*rd;
  int num_sol; // number of solutions to the quadratic
  double vsol[2]; // the two roots from quadraticroot
  double t2,u; // the t values of the two roots

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Variables for substitition
  // a = P11 - P10 - P01 + P00
  // b = P10 - P00
  // c = P01 - P00
  // d = P00  (d is shown below in the #ifdef raypatch area)
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~  

  // Find a w.r.t. x, y, z
  double ax = P11.x - P10.x - P01.x + P00.x;
  double ay = P11.y - P10.y - P01.y + P00.y;
  double az = P11.z - P10.z - P01.z + P00.z;


  // Find b w.r.t. x, y, z
  double bx = P10.x - P00.x;
  double by = P10.y - P00.y;
  double bz = P10.z - P00.z;

  // Find c w.r.t. x, y, z
  double cx = P01.x - P00.x;
  double cy = P01.y - P00.y;
  double cz = P01.z - P00.z;


  double rx = r.x;
  double ry = r.y;
  double rz = r.z;

  // Retrieve the xyz of the q part of ray
  double qx = q.x;
  double qy = q.y;
  double qz = q.z;

  // Find d w.r.t. x, y, z - subtracting r just after  
  double dx = P00.x - r.x;
  double dy = P00.y - r.y;
  double dz = P00.z - r.z;
  

  // Find A1 and A2
  double A1 = ax*qz - az*qx;
  double A2 = ay*qz - az*qy;

  // Find B1 and B2
  double B1 = bx*qz - bz*qx;
  double B2 = by*qz - bz*qy;

  // Find C1 and C2
  double C1 = cx*qz - cz*qx;
  double C2 = cy*qz - cz*qy;

  // Find D1 and D2
  double D1 = dx*qz - dz*qx;
  double D2 = dy*qz - dz*qy;
 
  Vector3 dir(qx,qy,qz), orig(rx,ry,rz);
  double A = A2*C1 - A1*C2;
  double B = A2*D1 -A1*D2 + B2*C1 -B1*C2;
  double C = B2*D1 - B1*D2;
  
  uv.x = (-2); 
  uv.y = (-2); 
  uv.z = (-2);

  double ray_epsilon = 0.00000001;

  float out1, out2;
  //num_sol = QuadraticRoot(A,B,C,-ray_epsilon,1+ray_epsilon,vsol);
    num_sol = ComputeV( &out1, &out2, A, B, C, -0.0f, 1.0f, 0.5f, 0.5f );
    vsol[0] = out1;
    vsol[1] = out2;

  switch(num_sol)
    {
    case 0:
      return false; // no solutions found
    case 1:
      uv.y = ( vsol[0]);
      uv.x = ( getu(uv.y,A2,A1,B2,B1,C2,C1,D2,D1));
      pos1 = SrfEval(uv.x,uv.y);
      uv.z = ( computet(dir,orig,pos1) );
      if(uv.x < 1+ray_epsilon && uv.x > -ray_epsilon && uv.z > 0)//vars okay?
	return true;
      else
	return false; // no other soln - so ret false
    case 2: // two solutions found
      uv.y = ( vsol[0]);
      uv.x = ( getu(uv.y,A2,A1,B2,B1,C2,C1,D2,D1));
      pos1 = SrfEval(uv.x,uv.y);
      uv.z = ( computet(dir,orig,pos1) ); 
      if(uv.x < 1+ray_epsilon && uv.x > -ray_epsilon && uv.z > 0)
	{
	  u = getu(vsol[1],A2,A1,B2,B1,C2,C1,D2,D1);
	  if(u < 1+ray_epsilon && u > ray_epsilon)
	    {
	      pos2 = SrfEval(u,vsol[1]);
	      t2 = computet(dir,orig,pos2);
	      if(t2 < 0 || uv.z < t2) // t2 is bad or t1 is better
		return true; 
	      // other wise both t2 > 0 and t2 < t1
	      uv.y = ( vsol[1]);
	      uv.x = (  u );
	      uv.z = ( t2 );
	      return true;
	    }
	  return true; // u2 is bad but u1 vars are still okay
	}
      else // doesn't fit in the root - try other one
	{
	  uv.y = ( vsol[1] );
	  uv.x = ( getu(vsol[1],A2,A1,B2,B1,C2,C1,D2,D1) );
	  pos1 = SrfEval(uv.x,uv.y);
	  uv.z = ( computet(dir,orig,pos1) ); 
	  if(uv.x < 1+ray_epsilon && uv.x > -ray_epsilon &&uv.z > 0)
	    return true;
	  else
	    return false;
	}
      break;
    }
 
  return false; 
}


} // namespace rawray

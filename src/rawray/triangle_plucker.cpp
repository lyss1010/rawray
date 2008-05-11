/////////////////////////////////////////////////////////////////////////////
// triangle_plucker.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "triangle_plucker.h"
#include "math/tuple3.h"
#include "material.h"
#include <new>

namespace rawray {

TrianglePlucker* TrianglePlucker::newTriangle(TriangleMesh* mesh, int index, Material* material) {
    uint8* memory = static_cast<uint8*>(
        _aligned_malloc( sizeof(TrianglePlucker), ALIGNMENT ));
    
	if( !memory ) return NULL;
	
	// Call constructor with placement new
	return new (memory) TrianglePlucker(mesh, index, material);
}

void TrianglePlucker::deleteObject() {
	this->~TrianglePlucker();
	_aligned_free( this );
}

void TrianglePlucker::PreCalc() {
    const Tuple3I vertexIndices = mesh_->GetVertexIndices()[ index_ ];
    const Vector3& v0 = mesh_->GetVertices()[ vertexIndices.x ];
    const Vector3& v1 = mesh_->GetVertices()[ vertexIndices.y ];
    const Vector3& v2 = mesh_->GetVertices()[ vertexIndices.z ];
    
    // Compute the plucker coords of the 3 lines representing edges
    pluckA_ = PluckerCoord( v2-v1, v1 );
    pluckB_ = PluckerCoord( v0-v2, v2 );
    pluckC_ = PluckerCoord( v1-v0, v0 );
}

// SSE Enhanced intersection of 4x rays simultaneously
#ifdef SSE
void TrianglePlucker::IntersectPack(HitPack& hitpack, float minDistance, float maxDistance) {
	stats::triangleIntersections += 4;

	const Tuple3I vertexIndices = mesh_->GetVertexIndices()[ index_ ];
    const __m128& v0 = mesh_->GetVertices()[ vertexIndices.x ].v;
    const __m128& v1 = mesh_->GetVertices()[ vertexIndices.y ].v;
    const __m128& v2 = mesh_->GetVertices()[ vertexIndices.z ].v;

	const __m128& ray_d_x = hitpack.ray_d_x;
    const __m128& ray_d_y = hitpack.ray_d_y;
    const __m128& ray_d_z = hitpack.ray_d_z;
    const __m128& ray_o_x = hitpack.ray_o_x;
    const __m128& ray_o_y = hitpack.ray_o_y;
    const __m128& ray_o_z = hitpack.ray_o_z;

	const __m128& pluckA_u = pluckA_.u_.v;
	const __m128& pluckB_u = pluckB_.u_.v;
	const __m128& pluckC_u = pluckC_.u_.v;

	const __m128& pluckA_v = pluckA_.v_.v;
	const __m128& pluckB_v = pluckB_.v_.v;
	const __m128& pluckC_v = pluckC_.v_.v;


	// Compute plucker coordinates of eye rays
	// We only need to compute v as the u coord is just the ray direction
	// The v coordinate is direction cross origin
    __asm {
        // Load the z and y portions of our data to work on for the 1st part of the cross product
		mov    edx,  ray_d_y;
        movaps xmm0, [edx];
		mov    edx,  ray_d_z;
        movaps xmm1, [edx];

		mov    edx,  ray_o_y;
        movaps xmm2, [edx];
		mov    edx,  ray_o_z;
        movaps xmm3, [edx];

        // 1st element of cross product
        mulps  xmm0, xmm3; // ay * bz
        mulps  xmm2, xmm1; // az * by
        subps  xmm0, xmm2; // ay * bz - az * by

        // Load the x portion of our data for the 2nd part of the cross product
        // the values xmm1 and xmm3 are still untouched (the z portions)
		mov    edx,  ray_d_x;
        movaps xmm2, [edx];
		mov    edx,  ray_o_x;
        movaps xmm4, [edx];

        // 2nd element of cross prodcut
        mulps xmm1, xmm4; // az * bz
        mulps xmm3, xmm2; // ax * bz
        subps xmm1, xmm3; // az * bz - ax * bz

        // Load the y portion of our data for the 3rd part of the cross product
        // the values xmm2 and xmm4 are still untouched (the x portions)
		mov    edx,  ray_d_y;
        movaps xmm3, [edx];
		mov    edx,  ray_o_y;
        movaps xmm5, [edx];

        // 3rd element of cross product
        mulps xmm2, xmm5; // ax * by
        mulps xmm4, xmm3; // ay * bx
        subps xmm2, xmm4; // ax * by - ay * bx
	}

	// Compute the orientations of the edge A vs. the ray
	__m128 dirA;
	__asm {
		// Load plucker coords of A.u
		mov    edx,  pluckA_u;
		movaps xmm3, [edx];
		movaps xmm4, xmm3;
		movaps xmm5, xmm3;

        shufps xmm3, xmm3, 0;   // 00:00:00:00
        shufps xmm2, xmm2, 85;  // 01:01:01:01
        shufps xmm3, xmm3, 170; // 10:10:10:10

		// xmm3 = pluckA_u . pluck_v
		mulps  xmm3, xmm0;
		mulps  xmm4, xmm1;
		mulps  xmm5, xmm2;

		addps  xmm3, xmm4;
		addps  xmm3, xmm5;

		// Load plucker coords of A.v
		mov    edx,  pluckA_v;
		movaps xmm4, [edx];
		movaps xmm5, xmm4;
		movaps xmm6, xmm5;

		shufps xmm4, xmm4, 0;   // 00:00:00:00
        shufps xmm5, xmm5, 85;  // 01:01:01:01
        shufps xmm6, xmm6, 170; // 10:10:10:10

		// xmm4 = pluckA_v . pluck_u
		mov   edx,  ray_o_x;
		mulps xmm4, [edx];
		mov   edx,  ray_o_y;
		mulps xmm5, [edx];
		mov   edx,  ray_o_z;
		mulps xmm6, [edx];

		addps xmm4, xmm5;
		addps xmm4, xmm6;

		// xmm3 = orientation = pluckA_u . pluck_v - pluckA_v . pluck_u
		subps  xmm3, xmm4;
		movaps dirA, xmm3;
	}

	// Compute the orientations of the edge B vs. the ray
	__m128 dirB;
	__asm {
		// Load plucker coords of B.u
		mov    edx,  pluckB_u;
		movaps xmm3, [edx];
		movaps xmm4, xmm3;
		movaps xmm5, xmm3;

        shufps xmm3, xmm3, 0;   // 00:00:00:00
        shufps xmm2, xmm2, 85;  // 01:01:01:01
        shufps xmm3, xmm3, 170; // 10:10:10:10

		// xmm3 = pluckB_u . pluck_v
		mulps  xmm3, xmm0;
		mulps  xmm4, xmm1;
		mulps  xmm5, xmm2;

		addps  xmm3, xmm4;
		addps  xmm3, xmm5;

		// Load plucker coords of B.v
		mov    edx,  pluckB_v;
		movaps xmm4, [edx];
		movaps xmm5, xmm4;
		movaps xmm6, xmm5;

		shufps xmm4, xmm4, 0;   // 00:00:00:00
        shufps xmm5, xmm5, 85;  // 01:01:01:01
        shufps xmm6, xmm6, 170; // 10:10:10:10

		// xmm4 = pluckB_v . pluck_u
		mov   edx,  ray_o_x;
		mulps xmm4, [edx];
		mov   edx,  ray_o_y;
		mulps xmm5, [edx];
		mov   edx,  ray_o_z;
		mulps xmm6, [edx];

		addps xmm4, xmm5;
		addps xmm4, xmm6;

		// xmm3 = orientation = pluckB_u . pluck_v - pluckB_v . pluck_u
		subps  xmm3, xmm4;
		movaps dirB, xmm3;
	}

	// Compute the orientations of the edge C vs. the ray
	__m128 dirC;
	__asm {
		// Load plucker coords of C.u
		mov    edx,  pluckC_u;
		movaps xmm3, [edx];
		movaps xmm4, xmm3;
		movaps xmm5, xmm3;

        shufps xmm3, xmm3, 0;   // 00:00:00:00
        shufps xmm2, xmm2, 85;  // 01:01:01:01
        shufps xmm3, xmm3, 170; // 10:10:10:10

		// xmm3 = pluckC_u . pluck_v
		mulps  xmm3, xmm0;
		mulps  xmm4, xmm1;
		mulps  xmm5, xmm2;

		addps  xmm3, xmm4;
		addps  xmm3, xmm5;

		// Load plucker coords of C.v
		mov    edx,  pluckC_v;
		movaps xmm4, [edx];
		movaps xmm5, xmm4;
		movaps xmm6, xmm5;

		shufps xmm4, xmm4, 0;   // 00:00:00:00
        shufps xmm5, xmm5, 85;  // 01:01:01:01
        shufps xmm6, xmm6, 170; // 10:10:10:10

		// xmm4 = pluckC_v . pluck_u
		mov   edx,  ray_o_x;
		mulps xmm4, [edx];
		mov   edx,  ray_o_y;
		mulps xmm5, [edx];
		mov   edx,  ray_o_z;
		mulps xmm6, [edx];

		addps xmm4, xmm5;
		addps xmm4, xmm6;

		// xmm3 = orientation = pluckC_u . pluck_v - pluckC_v . pluck_u
		subps  xmm3, xmm4;
		movaps dirC, xmm3;
	}


	// Test to see if all rays missed
	bool rayHit[4] = {false, false, false, false};
	int numHit = 0;
	for( int i=0; i<4; ++i ) {
		
		// See if we had a hit (all directions have same sign)
		// We will assume a dir == 0 is the same as dir > 0
		if( dirA.m128_f32[i] >= 0.0f ) { 
			// Orientations must be positive
			if( dirB.m128_f32[i] < 0.0f || dirC.m128_f32[i] < 0.0f )
				continue;

		} else {
			// Orientations must be negative
			if( dirB.m128_f32[i] >= 0.0f || dirC.m128_f32[i] >= 0.0f )
				continue;
		}

		++numHit;
		rayHit[i] = true;
	}
	
	// Exit immediately if none hit at all
	memset( hitpack.hit_result, 0, sizeof(hitpack.hit_result) );
	if( numHit == 0 )
		return;


	// Compute barycentric coordinates
	// alpha = dirA / (dirA + dirB + dirC)
	// beta  = dirB / (dirA + dirB + dirC)
	// gamma = dirC / (dirA + dirB + dirC)
	__m128 alpha, beta, gamma;
	__asm {
		movaps xmm0, dirA;
		movaps xmm1, dirB;
		movaps xmm2, dirC;
		
		// xmm7 = dirA + dirB + dirC
		movaps xmm7, xmm0;
		addps  xmm7, xmm1;
		addps  xmm7, xmm2;

		// xmm7 = 1.0 / (dirA + dirB + dirC)
		rcpps  xmm7, xmm7;

		mulps  xmm0, xmm7; // xmm0 = alpha
		movaps alpha, xmm0;

		mulps  xmm1, xmm7; // xmm1 = beta
		movaps beta, xmm0;

		mulps  xmm2, xmm7; // xmm2 = gamma
		movaps gamma, xmm0;
	}

	__m128 hit_x, hit_y, hit_z;
	__asm {
		// Load verticies
		mov    edx,  v0;
		movaps xmm5, [edx];
		mov    edx,  v1;
		movaps xmm6, [edx];
		mov    edx,  v2;
		movaps xmm7, [edx];

		// Calculate X portion of the hits
		movaps xmm3, xmm5;		// xmm3 = v0
		shufps xmm3, xmm3, 0;	// xmm3 = v0.x
		mulps  xmm3, xmm0;		// xmm3 = alpha * v0.x

		movaps xmm4, xmm6;		// xmm4 = v1
		shufps xmm4, xmm4, 0;	// xmm4 = v1.x
		mulps  xmm4, xmm1;		// xmm4 = beta * v1.x

		addps  xmm3, xmm4;		// xmm3 = alpha * v0.x + beta * v1.x

		movaps xmm4, xmm7;		// xmm4 = v2
		shufps xmm4, xmm4, 0;	// xmm4 = v2.x
		mulps  xmm4, xmm2;		// xmm4 = gamma * v2.x

		addps  xmm3, xmm4;		// xmm3 = alpha * v0.x + beta * v1.x + gamma * v2.x
		movaps hit_x, xmm3;

		
		// Calculate Y portion of the hits
		movaps xmm3, xmm5;		// xmm3 = v0
		shufps xmm3, xmm3, 85;	// xmm3 = v0.y
		mulps  xmm3, xmm0;		// xmm3 = alpha * v0.y

		movaps xmm4, xmm6;		// xmm4 = v1
		shufps xmm4, xmm4, 85;	// xmm4 = v1.y
		mulps  xmm4, xmm1;		// xmm4 = beta * v1.y

		addps  xmm3, xmm4;		// xmm3 = alpha * v0.y + beta * v1.y

		movaps xmm4, xmm7;		// xmm4 = v2
		shufps xmm4, xmm4, 85;	// xmm4 = v2.y
		mulps  xmm4, xmm2;		// xmm4 = gamma * v2.y

		addps  xmm3, xmm4;		// xmm3 = alpha * v0.y + beta * v1.y + gamma * v2.y
		movaps hit_y, xmm3;


		// Calculate Z portion of the hits
		movaps xmm3, xmm5;		// xmm3 = v0
		shufps xmm3, xmm3, 170;	// xmm3 = v0.z
		mulps  xmm3, xmm0;		// xmm3 = alpha * v0.z

		movaps xmm4, xmm6;		// xmm4 = v1
		shufps xmm4, xmm4, 170;	// xmm4 = v1.z
		mulps  xmm4, xmm1;		// xmm4 = beta * v1.z

		addps  xmm3, xmm4;		// xmm3 = alpha * v0.z + beta * v1.z

		movaps xmm4, xmm7;		// xmm4 = v2
		shufps xmm4, xmm4, 170;	// xmm4 = v2.z
		mulps  xmm4, xmm2;		// xmm4 = gamma * v2.z

		addps  xmm3, xmm4;		// xmm3 = alpha * v0.z + beta * v1.z + gamma * v2.z
		movaps hit_z, xmm3;
	}

	// Calculate distances
	__m128 distance;
	__asm {
		// Assuming ray.direction is normalized, dot prodcut will give us length of (hit.point - ray.origin)
		//     xmm3, hit_z; // Still in register from previous calculations
		movaps xmm4, hit_y;
		movaps xmm5, hit_x;

		// Calculate hit.point - ray.origin
		mov   edx,  ray_o_x;
		subps xmm5, [edx];
		mov   edx,  ray_o_y;
		subps xmm4, [edx];
		mov   edx,  ray_o_z;
		subps xmm3, [edx];

		// Calculate dot product of (hit.point-ray.origin) . ray.direction
		mov   edx,  ray_d_x;
		mulps xmm5, [edx];
		mov   edx,  ray_d_y;
		mulps xmm4, [edx];
		mov   edx,  ray_d_z;
		mulps xmm3, [edx];

		addps  xmm3, xmm4;
		addps  xmm3, xmm5;
		movaps distance, xmm3;
	}


	for( int i=0; i<4; ++i ) {
		if( !rayHit[i] || 
			distance.m128_f32[i] < minDistance || 
			distance.m128_f32[i] > maxDistance )
		{
			continue;
		}

		hitpack.hit_result[i] = 1.0f;
        hitpack.hits[i].distance = distance.m128_f32[i];
        hitpack.hits[i].material = material_;
        hitpack.hits[i].point.x = hit_x.m128_f32[i];
		hitpack.hits[i].point.y = hit_y.m128_f32[i];
		hitpack.hits[i].point.z = hit_z.m128_f32[i];

        Interpolate( hitpack.hits[i], alpha.m128_f32[i], beta.m128_f32[i], gamma.m128_f32[i] );
	}
}
#endif //SSE

// Plucker coordinate triangle intersection test
// See: http://tog.acm.org/resources/RTNews/html/rtnv10n3.html#art11
// See: http://tog.acm.org/resources/RTNews/html/rtnv11n1.html#art3
// See: http://www.flipcode.com/archives/Plcker_Coordinates_for_the_Rest_of_Us-Part_4_Applications.shtml
bool TrianglePlucker::Intersect(HitInfo& hit, float minDistance, float maxDistance) {
	stats::triangleIntersections++;
	
	const Ray& ray = hit.eyeRay;
    PluckerCoord pluckRay( ray.direction, ray.origin );
    
    const float dirA = pluckA_.GetOrientation( pluckRay );
    const float dirB = pluckB_.GetOrientation( pluckRay );
    float dirC;

    // Favor larger code for less redundant operations
    // Perform directionality tests as soon as possible and only if nesecary
    // We will assume a dir == 0 is the same as dir > 0
    if( dirA >= 0.0f ) { 
        // Orientations must be positive
        if( dirB < 0.0f ) return false;

        dirC = pluckC_.GetOrientation( pluckRay );
        if( dirC < 0.0f ) return false;

    } else {
        // Orientations must be negative
        if( dirB >= 0.0f ) return false;

        dirC = pluckC_.GetOrientation( pluckRay );
        if( dirC >= 0.0f ) return false;
    }
    
    // Our orientations are also unnormalized barycentric coordinates
    const float norm = 1.0f / (dirA + dirB + dirC);
    const float alpha = dirA * norm;
    const float beta =  dirB * norm;
    const float gamma = dirC * norm;

    // Compute the hit point by interpolation based by our barycentric coords
    const Tuple3I vertexIndices = mesh_->GetVertexIndices()[ index_ ];
    hit.point = alpha * mesh_->GetVertices()[ vertexIndices.x ] + 
                beta  * mesh_->GetVertices()[ vertexIndices.y ] + 
                gamma * mesh_->GetVertices()[ vertexIndices.z ];

    // Assuming ray.direction is normalized, dot prodcut will give us length of (hit.point - ray.origin)
    hit.distance = math::Dot( (hit.point - ray.origin), ray.direction );
    if( hit.distance < minDistance || hit.distance > maxDistance )
        return false;

    hit.material = material_;
    Interpolate(hit, alpha, beta, gamma);

    return true;
}

bool TrianglePlucker::Hit(const Ray& ray, float minDistance, float maxDistance) const {
	stats::triangleIntersections++;

    PluckerCoord pluckRay( ray.direction, ray.origin );
    
    const float dirA = pluckA_.GetOrientation( pluckRay );
    const float dirB = pluckB_.GetOrientation( pluckRay );
    float dirC;

    // Favor larger code for less redundant operations
    // Perform directionality tests as soon as possible and only if nesecary
    // We will assume a dir == 0 is the same as dir > 0
    if( dirA >= 0.0f ) { 
        // Orientations must be positive
        if( dirB < 0.0f ) return false;

        dirC = pluckC_.GetOrientation( pluckRay );
        if( dirC < 0.0f ) return false;

    } else {
        // Orientations must be negative
        if( dirB >= 0.0f ) return false;

        dirC = pluckC_.GetOrientation( pluckRay );
        if( dirC >= 0.0f ) return false;
    }

    
    // Our orientations are also unnormalized barycentric coordinates
    const float norm = 1.0f / (dirA + dirB + dirC);
    const float alpha = dirA * norm;
    const float beta =  dirB * norm;
    const float gamma = dirC * norm;

    // Compute the hit point by interpolation based by our barycentric coords
    const Tuple3I vertexIndices = mesh_->GetVertexIndices()[ index_ ];
    Vector3 hit = alpha * mesh_->GetVertices()[ vertexIndices.x ] + 
                  beta  * mesh_->GetVertices()[ vertexIndices.y ] + 
                  gamma * mesh_->GetVertices()[ vertexIndices.z ];

    // Assuming ray.direction is normalized, dot prodcut will give us length of (hit.point - ray.origin)
    const float distance = math::Dot( (hit - ray.origin), ray.direction );
    return ( distance > minDistance && distance < maxDistance );
}

} // namespace rayray

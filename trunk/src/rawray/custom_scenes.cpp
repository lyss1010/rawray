/////////////////////////////////////////////////////////////////////////////
// custom_scenes.cpp --> (extension of glut_window.cpp)
//
/////////////////////////////////////////////////////////////////////////////
#include "glut_window.h"
#include "light.h"
#include "lambert.h"
#include "sphere.h"
#include "triangle_mesh.h"
#include "triangle.h"
#include "float.h"

namespace rawray {

void GlutWindow::MakeSpiralScene() {
    cam_.SetEye( Vector3(2.33f, -1.03f, -4.24f) );
	cam_.SetViewDir( Vector3(-2.47f, 0.72f, 4.43f) );
    cam_.SetUp( Vector3(0, 1, 0) );
    cam_.SetFOV( 45 );

    scene_.AddLight( new Light( 
						Vector3(3, -15, -3),
						Vector3(1, 1, 1),
						700 ) );

	scene_.AddLight( new Light( 
						Vector3(-3, 15, 3),
						Vector3(1, 1, 1),
						700 ) );
    
	const float dt = 1.0f / options::spiral_num_sphere;
	const float a = options::spiral_radius;
    for (int i=0; i<options::spiral_radius; ++i ) {
        const float t = i * dt;
        const float theta = 4 * math::PI * t;
        const float r = a*theta;

        const float x = r*cos(theta);
        const float y = r*sin(theta);
        const float z = 2 * ( 2 * math::PI * a - r);

        const float red = 0.20f*(exp(r-x*x+abs(y)));
        const float green = 0.12f*( abs(tan(z)) + abs(tan(-z) ) ) ;
        const float blue = -2.25f;

		Material* mat = scene_.AddMaterial( new Lambert( Vector3(red,green,blue) ) );
        rawray::Sphere* sphere = new Sphere( Vector3(x,y,z), r/10, mat );
        scene_.AddObject(sphere);
    }

    scene_.PreCalc();
}

void GlutWindow::MakeLorenzScene() {
	//cam_.SetEye( Vector3(-63.8f, -30.3f, -1.6f) );
	//cam_.SetViewDir( Vector3(5.65f, 2.23f, 2.58f) );
	cam_.SetEye( Vector3(-33.78f, -37.13f, 47.70f) );
	cam_.SetViewDir( Vector3(6.52f, 7.42f, -3.58f) );

    cam_.SetUp( Vector3(0, 1, 0) );
    cam_.SetFOV( 45 );

    Light* light = new Light( Vector3(-3, 15, 3),
                              Vector3(1, 1, 1),
                              1000 );
    scene_.AddLight(light);

	float base_dt = options::lorenz_dt;
	float min_dist = options::lorenz_min_distance;
	float max_dist = options::lorenz_max_distance;

	const float r = options::lorenz_radius;
	const float sigma = options::lorenz_sigma;
	const float rho = options::lorenz_rho;
	const float beta = options::lorenz_beta;
	Vector3 delta, l( options::lorenz_start );

	if( base_dt > 0.0f ) {
		min_dist = FLT_MIN;
		max_dist = FLT_MAX;
	} else {
		base_dt = 0.0001f;
	}

	// MIN == -16.35  -25.50  00.00
	// MAX ==  18.90   31.80  58.20
    for (int i=0; i<options::lorenz_num_sphere; ++i ) {
		float dt = base_dt;

		do {
			delta.x = sigma * ( l.y - l.x );
			delta.y = l.x * (rho - l.z) - l.y;
			delta.z = (l.x * l.y) - (beta * l.z);
			delta *= dt;

			float length = delta.Length();
            if( length < min_dist )
				dt *= 1.5f;
			else if( length > max_dist )
				dt /= 1.5f;
			else
				break;
		} while( true );

		l += delta;

		const float red = 0.3f + (l.Dot( Vector3(0.5f,0,1) )) / 250;
        const float green = 0.3f + (l.Dot( Vector3(1,1,1) )) / 300;
		const float blue = 0.4f + (l.Dot( Vector3(1,1,0) )) / 100;

		Material* mat = scene_.AddMaterial( new Lambert( Vector3(red,green,blue) ) );
        rawray::Sphere* sphere = new Sphere( l, r, mat );
        scene_.AddObject(sphere);
    }

    scene_.PreCalc();
}

void GlutWindow::MakeBunnyScene() {
    // set up the camera
    options::bg_color = Vector3(0.0f, 0.0f, 0.2f);

    cam_.SetEye( Vector3(-2.0f, 3.0f, 5.0f) );
    cam_.SetLookAt( Vector3(-0.5f, 1.0f, 0.0f) );
    cam_.SetUp( Vector3(0, 1, 0) );
    cam_.SetFOV( 45 );

    Light* light = new Light( Vector3(-3, 15, 3),
							  Vector3(1, 1, 1),
							  500 );
    scene_.AddLight(light);

	Material* mat = scene_.AddMaterial( 
						new Lambert( Vector3(0.86f, 0.89f, 0.91f) ) );

    TriangleMesh* bunny = new TriangleMesh;
    bunny->LoadOBJ( "./../res/bunny.obj" );
	scene_.AddMesh( bunny );
    
    // create all the triangles in the bunny mesh and add to the scene
    for (uint32 i = 0; i < bunny->GetNumTriangles(); ++i)
    {
        Triangle* t = new Triangle( *bunny, i, mat );
        scene_.AddObject(t);
    }
    
    scene_.PreCalc();
}

} // namespace rawray

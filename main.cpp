//
//  main.cpp
//  assign4
//
//  Created by Sail Wang on 26/07/2017.
//  Copyright © 2017 Sail Wang. All rights reserved.
//
//==========================================================
// STUDENT NAME: WANG Zifan
// NUS User ID.: t0915218
// COMMENTS TO GRADER:
// This project is originally writen with Xcode in Mac OS
//
// ============================================================
// FILE: Main.cpp



#include <cstdlib>
#include <cstdio>
#include <cmath>
#include "Util.h"
#include "Vector3d.h"
#include "Color.h"
#include "Image.h"
#include "Ray.h"
#include "Camera.h"
#include "Material.h"
#include "Light.h"
#include "Surface.h"
#include "Sphere.h"
#include "Plane.h"
#include "Triangle.h"
#include "Scene.h"
#include "Raytrace.h"

using namespace std;


// Constants for Scene 1.
static const int imageWidth1 = 640;
static const int imageHeight1 = 480;
static const int reflectLevels1 = 2;  // 0 -- object does not reflect scene.
static const int hasShadow1 = true;

// Constants for Scene 2.
static const int imageWidth2 = 640;
static const int imageHeight2 = 480;
static const int reflectLevels2 = 2;  // 0 -- object does not reflect scene.
static const int hasShadow2 = true;




///////////////////////////////////////////////////////////////////////////
// Raytrace the whole image of the scene and write it to a file.
///////////////////////////////////////////////////////////////////////////

void RenderImage( const char *imageFilename, const Scene &scene, int reflectLevels, bool hasShadow )
{
    int imgWidth = scene.camera.getImageWidth();
    int imgHeight = scene.camera.getImageHeight();
    
    Image image( imgWidth, imgHeight );	// To store the result of ray tracing.
    
    double startTime = Util::GetCurrRealTime();
    double startCPUTime = Util::GetCurrCPUTime();
    
    // Generate image.
    for ( int y = 0; y < imgHeight; y++ )
    {
        double pixelPosY = y + 0.5;
        
        for ( int x = 0; x < imgWidth; x++ )
        {
            double pixelPosX = x + 0.5;
            Ray ray = scene.camera.getRay( pixelPosX, pixelPosY );
            Color pixelColor = Raytrace::TraceRay( ray, scene, reflectLevels, hasShadow );
            pixelColor.clamp();
            image.setPixel( x, y, pixelColor );
        }
        // printf( "%d ", y );
    }
    
    double stopCPUTime = Util::GetCurrCPUTime();
    double stopTime = Util::GetCurrRealTime();
    printf( "CPU time taken = %.1f sec\n", stopTime - startTime );
    printf( "Real time taken = %.1f sec\n", stopTime - startTime );
    
    // Write image to file.
    image.writeToFile( imageFilename );
}




// Forward declarations. These functions are defined later in the file.

void DefineScene1( Scene &scene, int imageWidth, int imageHeight );
void DefineScene2( Scene &scene, int imageWidth, int imageHeight );




void WaitForEnterKeyBeforeExit( void )
{
    fflush( stdin );
    getchar();
}




int main()
{
    atexit( WaitForEnterKeyBeforeExit );
    
    
    /*
    // Define Scene 1.
    
    Scene scene1;
    DefineScene1( scene1, imageWidth1, imageHeight1 );
    
    // Render Scene 1.
    
    printf( "Render Scene 1...\n" );
    RenderImage( "img_r2s.png", scene1, reflectLevels1, hasShadow1 );
    printf( "Image completed.\n" );
    
    */
    
    
     // Define Scene 2.
     
     Scene scene2;
     DefineScene2( scene2, imageWidth2, imageHeight2 );
     
     // Render Scene 2.
     
     printf( "Render Scene 2...\n" );
     RenderImage( " out2.png", scene2, reflectLevels2, hasShadow2 );
     printf( "Image completed.\n" );
    
    printf( "All done.\n" );
    return 0;
}





///////////////////////////////////////////////////////////////////////////
// Modeling of Scene 1.
///////////////////////////////////////////////////////////////////////////

void DefineScene1( Scene &scene, int imageWidth, int imageHeight )
{
    scene.backgroundColor = Color( 0.2f, 0.3f, 0.5f );
    
    scene.amLight.I_a = Color( 1.0f, 1.0f, 1.0f ) * 0.25f;
    
    // Define materials.
    
    scene.numMaterials = 5;
    scene.material = new Material[ scene.numMaterials ];
    
    // Light red.
    scene.material[0].k_d = Color( 0.8f, 0.4f, 0.4f );
    scene.material[0].k_a = scene.material[0].k_d;
    scene.material[0].k_r = Color( 0.8f, 0.8f, 0.8f ) / 1.5f;
    scene.material[0].k_rg = Color( 0.8f, 0.8f, 0.8f ) / 3.0f;
    scene.material[0].n = 64.0f;
    
    // Light green.
    scene.material[1].k_d = Color( 0.4f, 0.8f, 0.4f );
    scene.material[1].k_a = scene.material[0].k_d;
    scene.material[1].k_r = Color( 0.8f, 0.8f, 0.8f ) / 1.5f;
    scene.material[1].k_rg = Color( 0.8f, 0.8f, 0.8f ) / 3.0f;
    scene.material[1].n = 64.0f;
    
    // Light blue.
    scene.material[2].k_d = Color( 0.4f, 0.4f, 0.8f ) * 0.9f;
    scene.material[2].k_a = scene.material[0].k_d;
    scene.material[2].k_r = Color( 0.8f, 0.8f, 0.8f ) / 1.5f;
    scene.material[2].k_rg = Color( 0.8f, 0.8f, 0.8f ) / 2.5f;
    scene.material[2].n = 64.0f;
    
    // Yellow.
    scene.material[3].k_d = Color( 0.6f, 0.6f, 0.2f );
    scene.material[3].k_a = scene.material[0].k_d;
    scene.material[3].k_r = Color( 0.8f, 0.8f, 0.8f ) / 1.5f;
    scene.material[3].k_rg = Color( 0.8f, 0.8f, 0.8f ) / 3.0f;
    scene.material[3].n = 64.0f;
    
    // Gray.
    scene.material[4].k_d = Color( 0.6f, 0.6f, 0.6f );
    scene.material[4].k_a = scene.material[0].k_d;
    scene.material[4].k_r = Color( 0.6f, 0.6f, 0.6f );
    scene.material[4].k_rg = Color( 0.8f, 0.8f, 0.8f ) / 3.0f;
    scene.material[4].n = 128.0f;
    
    
    // Define point light sources.
    
    scene.numPtLights = 2;
    scene.ptLight = new PointLightSource[ scene.numPtLights ];
    
    scene.ptLight[0].I_source = Color( 1.0f, 1.0f, 1.0f ) * 0.6f;
    scene.ptLight[0].position = Vector3d( 100.0, 120.0, 10.0 );
    
    scene.ptLight[1].I_source = Color( 1.0f, 1.0f, 1.0f ) * 0.6f;
    scene.ptLight[1].position = Vector3d( 5.0, 80.0, 60.0 );
    
    
    // Define surface primitives.
    
    scene.numSurfaces = 15;
    scene.surfacep = new SurfacePtr[ scene.numSurfaces ];
    
    scene.surfacep[0] = new Plane( 0.0, 1.0, 0.0, 0.0, &(scene.material[2]) ); // Horizontal plane.
    scene.surfacep[1] = new Plane( 1.0, 0.0, 0.0, 0.0, &(scene.material[4]) ); // Left vertical plane.
    scene.surfacep[2] = new Plane( 0.0, 0.0, 1.0, 0.0, &(scene.material[4]) ); // Right vertical plane.
    scene.surfacep[3] = new Sphere( Vector3d( 40.0, 20.0, 42.0 ), 22.0, &(scene.material[0]) ); // Big sphere.
    scene.surfacep[4] = new Sphere( Vector3d( 75.0, 10.0, 40.0 ), 12.0, &(scene.material[1]) ); // Small sphere.
    
    // Cube +y face.
    scene.surfacep[5] = new Triangle( Vector3d( 50.0, 20.0, 90.0 ), Vector3d( 50.0, 20.0, 70.0 ),
                                     Vector3d( 30.0, 20.0, 70.0 ), &(scene.material[3]) );
    scene.surfacep[6] = new Triangle( Vector3d( 50.0, 20.0, 90.0 ), Vector3d( 30.0, 20.0, 70.0 ),
                                     Vector3d( 30.0, 20.0, 90.0 ), &(scene.material[3]) );
    
    // Cube +x face.
    scene.surfacep[7] = new Triangle( Vector3d( 50.0, 0.0, 70.0 ), Vector3d( 50.0, 20.0, 70.0 ),
                                     Vector3d( 50.0, 20.0, 90.0 ), &(scene.material[3]) );
    scene.surfacep[8] = new Triangle( Vector3d( 50.0, 0.0, 70.0 ), Vector3d( 50.0, 20.0, 90.0 ),
                                     Vector3d( 50.0, 0.0, 90.0 ), &(scene.material[3]) );
    
    // Cube -x face.
    scene.surfacep[9] = new Triangle( Vector3d( 30.0, 0.0, 90.0 ), Vector3d( 30.0, 20.0, 90.0 ),
                                     Vector3d( 30.0, 20.0, 70.0 ), &(scene.material[3]) );
    scene.surfacep[10] = new Triangle( Vector3d( 30.0, 0.0, 90.0 ), Vector3d( 30.0, 20.0, 70.0 ),
                                      Vector3d( 30.0, 0.0, 70.0 ), &(scene.material[3]) );
    
    // Cube +z face.
    scene.surfacep[11] = new Triangle( Vector3d( 50.0, 0.0, 90.0 ), Vector3d( 50.0, 20.0, 90.0 ),
                                      Vector3d( 30.0, 20.0, 90.0 ), &(scene.material[3]) );
    scene.surfacep[12] = new Triangle( Vector3d( 50.0, 0.0, 90.0 ), Vector3d( 30.0, 20.0, 90.0 ),
                                      Vector3d( 30.0, 0.0, 90.0 ), &(scene.material[3]) );
    
    // Cube -z face.
    scene.surfacep[13] = new Triangle( Vector3d( 30.0, 0.0, 70.0 ), Vector3d( 30.0, 20.0, 70.0 ),
                                      Vector3d( 50.0, 20.0, 70.0 ), &(scene.material[3]) );
    scene.surfacep[14] = new Triangle( Vector3d( 30.0, 0.0, 70.0 ), Vector3d( 50.0, 20.0, 70.0 ),
                                      Vector3d( 50.0, 0.0, 70.0 ), &(scene.material[3]) );
    
    
    // Define camera.
    
    scene.camera = Camera( Vector3d( 150.0, 120.0, 150.0 ), Vector3d( 45.0, 22.0, 55.0 ), Vector3d( 0.0, 1.0, 0.0 ),
                          (-1.0 * imageWidth) / imageHeight, (1.0 * imageWidth) / imageHeight, -1.0, 1.0, 3.0, 
                          imageWidth, imageHeight );
}





///////////////////////////////////////////////////////////////////////////
// Modeling of Scene 2.
///////////////////////////////////////////////////////////////////////////

void DefineScene2( Scene &scene, int imageWidth, int imageHeight )
{
    //***********************************************
    //*********** WRITE YOUR CODE HERE **************
    //***********************************************
    scene.backgroundColor = Color(0.5f, 0.23f, 0.5f);
    scene.amLight.I_a = Color( 1.0f, 1.0f, 1.0f ) * 0.25f;

    //define materials
    scene.numMaterials = 5;
    scene.material = new Material[ scene.numMaterials ];
    
    // Salmon
    scene.material[0].k_d = Color( 0.980f, 0.502f, 0.447f );
    scene.material[0].k_a = scene.material[0].k_d;
    scene.material[0].k_r = Color( 0.8f, 0.8f, 0.8f ) / 1.5f;
    scene.material[0].k_rg = Color( 0.8f, 0.8f, 0.8f ) / 3.0f;
    scene.material[0].n = 64.0f;
    
    // Lemon
    scene.material[1].k_d = Color( 1.0f, 0.98f, 0.804f );
    scene.material[1].k_a = scene.material[0].k_d;
    scene.material[1].k_r = Color( 0.8f, 0.8f, 0.8f ) / 1.5f;
    scene.material[1].k_rg = Color( 0.8f, 0.8f, 0.8f ) / 3.0f;
    scene.material[1].n = 64.0f;
    
    // MediumAquamarine
    scene.material[2].k_d = Color( 0.400f, 0.804, 0.667 );
    scene.material[2].k_a = scene.material[0].k_d;
    scene.material[2].k_r = Color( 0.8f, 0.8f, 0.8f ) / 1.5f;
    scene.material[2].k_rg = Color( 0.8f, 0.8f, 0.8f ) / 2.5f;
    scene.material[2].n = 64.0f;
    
    // Dark Orchid
    scene.material[3].k_d = Color( 0.600f, 0.196f, 0.800f);
    scene.material[3].k_a = scene.material[0].k_d;
    scene.material[3].k_r = Color( 0.8f, 0.8f, 0.8f ) / 1.5f;
    scene.material[3].k_rg = Color( 0.8f, 0.8f, 0.8f ) / 3.0f;
    scene.material[3].n = 64.0f;
    
    //DodgerBlue
    scene.material[4].k_d = Color( 0.118f, 0.565f, 1.000f );
    scene.material[4].k_a = scene.material[0].k_d;
    scene.material[4].k_r = Color( 0.8f, 0.8f, 0.8f ) / 1.5f;
    scene.material[4].k_rg = Color( 0.8f, 0.8f, 0.8f ) / 3.0f;
    scene.material[4].n = 64.0f;
    
    scene.numPtLights = 4;
    scene.ptLight = new PointLightSource[ scene.numPtLights ];
    
    scene.ptLight[0].I_source = Color( 1.0f, 1.0f, 1.0f ) * 0.2f;
    scene.ptLight[0].position = Vector3d( 50.0, 20.0, 110.0 );
    
    scene.ptLight[1].I_source = Color( 1.0f, 1.0f, 1.0f ) * 0.3f;
    scene.ptLight[1].position = Vector3d( 105.0, 80.0, 60.0 );

    scene.ptLight[2].I_source = Color( 1.0f, 1.0f, 1.0f) * 0.2f ;
    scene.ptLight[2].position = Vector3d( 55.0, 34.0, 100.0 );

    scene.ptLight[3].I_source = Color( 1.0f, 1.0f, 1.0f ) * 0.2f;
    scene.ptLight[3].position = Vector3d( 100.0, 100.0, 100.0 );

    scene.numSurfaces = 10;
    scene.surfacep = new SurfacePtr[ scene.numSurfaces ];
    
    scene.surfacep[0] = new Plane( 0.0, 1.0, 0.0, 0.0, &(scene.material[4]) ); // Horizontal plane.
    scene.surfacep[1] = new Plane( 1.0, 0.0, 0.0, 0.0, &(scene.material[2]) ); // Left vertical plane.
    scene.surfacep[2] = new Plane( 0.0, 0.0, 1.0, 0.0, &(scene.material[3]) ); // Right vertical plane.
    //sphere
    scene.surfacep[3] = new Sphere( Vector3d( 40.0, 90.0, 40.0 ), 11.0, &(scene.material[4]) );
    
     scene.surfacep[4] = new Sphere( Vector3d( 100.0, 20.0, 90.0 ), 22.0, &(scene.material[1]) );
    
      scene.surfacep[5] = new Sphere( Vector3d( 88.0, 44.0, 33.0 ), 14.0, &(scene.material[3]) );
    
   /*
    scene.surfacep[6] = new Triangle( Vector3d( 70.0, 90.0, 80.0 ), Vector3d( 40.0, 20.0, 30.0 ),
                                     Vector3d( 28.0, 34.0, 13.0 ), &(scene.material[0]) );
    scene.surfacep[7] = new Triangle( Vector3d( 70.0, 90.0, 80.0 ), Vector3d( 40.0, 20.0, 30.0 ),
                                     Vector3d( 70.0, 55, 65.0 ), &(scene.material[1]) );
    scene.surfacep[8] = new Triangle( Vector3d( 70.0, 90.0, 80.0 ), Vector3d( 28.0, 34.0, 13.0 ),
                                     Vector3d( 70.0, 55, 65.0 ), &(scene.material[2]) );
    scene.surfacep[9] = new Triangle( Vector3d( 40.0, 20.0, 30.0 ), Vector3d( 28.0, 34.0, 13.0 ),
                                     Vector3d( 70.0, 55, 65.0 ), &(scene.material[3]) );
    
    */
    
    scene.surfacep[6] = new Triangle( Vector3d( 40.0, 90.0, 40.0 ), Vector3d( 88.0, 44.0, 33.0 ),Vector3d( 100.0, 20.0, 90.0 ),
                                     &(scene.material[0]) );
    scene.surfacep[7] = new Triangle( Vector3d( 40.0, 90.0, 40.0 ), Vector3d( 100.0, 20.0, 90.0 ),
                                     Vector3d( 70.0, 55, 65.0 ), &(scene.material[1]) );
    scene.surfacep[8] = new Triangle( Vector3d( 40.0, 90.0, 40.0 ),Vector3d( 70.0, 55, 65.0 ), Vector3d( 88.0, 44.0, 33.0 ),
                                      &(scene.material[2]) );
    scene.surfacep[9] = new Triangle( Vector3d( 100.0, 20.0, 90.0 ), Vector3d( 88.0, 44.0, 33.0 ),
                                     Vector3d( 70.0, 55, 65.0 ), &(scene.material[3]) );
    
    
    
    
    // Define camera.
    
    scene.camera = Camera( Vector3d( 330, 100.0, 180.0 ), Vector3d( 0.0, 20.0, 0.0 ), Vector3d( 0.0, 1.0, 0.0 ),
                          (-1.0 * imageWidth) / imageHeight, (1.0 * imageWidth) / imageHeight, -1.0, 1.0, 3.0,
                          imageWidth, imageHeight );
    
}

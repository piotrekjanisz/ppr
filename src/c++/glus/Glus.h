/* 
 * File:   Glus.h
 * Author: piotrek
 *
 * Created on 22 listopad 2010, 22:17
 */

#ifndef GLUS_H
#define	GLUS_H

namespace Glus
{
#ifndef GLUSAPIENTRY
#define GLUSAPIENTRY
#endif
#ifndef GLUSAPIENTRYP
#define GLUSAPIENTRYP GLUSAPIENTRY *
#endif
#ifndef GLUSAPI
#define GLUSAPI extern
#endif

    typedef unsigned int GLUSenum;
    typedef unsigned char GLUSboolean;
    typedef unsigned int GLUSbitfield;
    typedef signed char GLUSbyte;
    typedef short GLUSshort;
    typedef int GLUSint;
    typedef int GLUSsizei;
    typedef unsigned char GLUSubyte;
    typedef unsigned short GLUSushort;
    typedef unsigned int GLUSuint;
    typedef float GLUSfloat;
    typedef float GLUSclampf;
    typedef double GLUSdouble;
    typedef double GLUSclampd;
    typedef char GLUSchar;

#ifdef __cplusplus
#define GLUSvoid void
#else
    typedef void GLUSvoid;
#endif

#define GLUS_ALPHA 0x1906
#define GLUS_RGB 0x1907
#define GLUS_RGBA 0x1908

#define PIf		3.1415926535897932384626433832795f

    typedef struct _GLUStgaimage
    {
        GLUSushort width;

        GLUSushort height;

        GLUSubyte* data;

        GLUSenum format;

    } GLUStgaimage;

    typedef struct _GLUSshape
    {
        GLUSfloat* vertices;

        GLUSfloat* normals;

        GLUSfloat* tangents;

        GLUSfloat* texCoords;

        GLUSuint* indices;

        GLUSuint numberVertices;

        GLUSuint numberIndices;

    } GLUSshape;

#define GLUS_TRUE	1
#define GLUS_FALSE	0

#define GLUS_BACKWARD_COMPATIBLE_BIT	0x0000
#define GLUS_FORWARD_COMPATIBLE_BIT		0x0002

    GLUSAPI GLUSboolean GLUSAPIENTRY glusLoadTgaImage(const GLUSchar* filename, GLUStgaimage* tgaimage);

    GLUSAPI GLUSvoid GLUSAPIENTRY glusDestroyTgaImage(GLUStgaimage* tgaimage);

    //

    GLUSAPI GLUSfloat GLUSAPIENTRY glusAmountf(const GLUSfloat vector[3]);

    GLUSAPI GLUSvoid GLUSAPIENTRY glusNormalizef(GLUSfloat vector[3]);

    GLUSAPI GLUSfloat GLUSAPIENTRY glusDotf(const GLUSfloat vector0[3], const GLUSfloat vector1[3]);

    GLUSAPI GLUSvoid GLUSAPIENTRY glusCrossf(GLUSfloat result[3], const GLUSfloat vector0[3], const GLUSfloat vector1[3]);

    //

    GLUSAPI GLUSvoid GLUSAPIENTRY glusOrthof(GLUSfloat result[16], GLUSfloat left, GLUSfloat right, GLUSfloat bottom, GLUSfloat top, GLUSfloat nearVal, GLUSfloat farVal);

    GLUSAPI GLUSvoid GLUSAPIENTRY glusFrustumf(GLUSfloat result[16], GLUSfloat left, GLUSfloat right, GLUSfloat bottom, GLUSfloat top, GLUSfloat nearVal, GLUSfloat farVal);

    GLUSAPI GLUSvoid GLUSAPIENTRY glusPerspectivef(GLUSfloat result[16], GLUSfloat fovy, GLUSfloat aspect, GLUSfloat zNear, GLUSfloat zFar);

    GLUSAPI GLUSvoid GLUSAPIENTRY glusLookAtf(GLUSfloat result[16], GLUSfloat eyeX, GLUSfloat eyeY, GLUSfloat eyeZ, GLUSfloat centerX, GLUSfloat centerY, GLUSfloat centerZ, GLUSfloat upX, GLUSfloat upY, GLUSfloat upZ);

    //

    GLUSAPI GLUSvoid GLUSAPIENTRY glusLoadIdentityf(GLUSfloat matrix[16]);

    GLUSAPI GLUSvoid GLUSAPIENTRY glusCopyMatrixf(GLUSfloat matrix[16], const GLUSfloat source[16]);

    GLUSAPI GLUSvoid GLUSAPIENTRY glusMultMatrixf(GLUSfloat matrix[16], const GLUSfloat matrix0[16], const GLUSfloat matrix1[16]);

    GLUSAPI GLUSboolean GLUSAPIENTRY glusInverseMatrixf(GLUSfloat matrix[16], const GLUSfloat source[16]);

    GLUSAPI GLUSvoid GLUSAPIENTRY glusTransposef(GLUSfloat matrix[16]);

    GLUSAPI GLUSvoid GLUSAPIENTRY glusTranslatef(GLUSfloat matrix[16], GLUSfloat x, GLUSfloat y, GLUSfloat z);

    GLUSAPI GLUSvoid GLUSAPIENTRY glusRotatef(GLUSfloat matrix[16], GLUSfloat angle, GLUSfloat x, GLUSfloat y, GLUSfloat z);

    GLUSAPI GLUSvoid GLUSAPIENTRY glusRotateRzRyRxf(GLUSfloat matrix[16], GLUSfloat anglex, GLUSfloat angley, GLUSfloat anglez);

    GLUSAPI GLUSvoid GLUSAPIENTRY glusScalef(GLUSfloat matrix[16], GLUSfloat x, GLUSfloat y, GLUSfloat z);

    GLUSAPI GLUSvoid GLUSAPIENTRY glusMultVectorf(GLUSfloat result[3], const GLUSfloat matrix[16], const GLUSfloat vector[3]);

    GLUSAPI GLUSvoid GLUSAPIENTRY glusMultPointf(GLUSfloat result[4], const GLUSfloat matrix[16], const GLUSfloat vector[4]);

    //

    GLUSAPI GLUSvoid GLUSAPIENTRY glusCreatePlanef(GLUSshape* shape, GLUSfloat halfExtend);

    GLUSAPI GLUSvoid GLUSAPIENTRY glusCreateCubef(GLUSshape* shape, GLUSfloat halfExtend);

    GLUSAPI GLUSvoid GLUSAPIENTRY glusCreateSpheref(GLUSshape* shape, GLUSfloat radius, GLUSuint numberSlices);

    GLUSAPI GLUSvoid GLUSAPIENTRY glusDestroyShapef(GLUSshape* shape);

};

#endif	/* GLUS_H */


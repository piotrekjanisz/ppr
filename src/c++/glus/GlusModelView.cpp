/**
 * GLUS - OpenGL 3 Utilities. Copyright (C) 2010 Norbert Nopper
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "Glus.h"

#include <math.h>

using namespace Glus;

GLUSvoid GLUSAPIENTRY Glus::glusOrthof(GLUSfloat result[16], GLUSfloat left, GLUSfloat right, GLUSfloat bottom, GLUSfloat top, GLUSfloat nearVal, GLUSfloat farVal)
{
    result[0] = 2.0f / (right - left);
    result[1] = 0.0f;
    result[2] = 0.0f;
    result[3] = 0.0f;
    result[4] = 0.0f;
    result[5] = 2.0f / (top - bottom);
    result[6] = 0.0f;
    result[7] = 0.0f;
    result[8] = 0.0f;
    result[9] = 0.0f;
    result[10] = -2.0f / (farVal + nearVal);
    result[11] = 0.0f;
    result[12] = -(right + left) / (right - left);
    result[13] = -(top + bottom) / (top - bottom);
    result[14] = -(farVal + nearVal) / (farVal - nearVal);
    result[15] = 1.0f;
}

GLUSvoid GLUSAPIENTRY Glus::glusFrustumf(GLUSfloat result[16], GLUSfloat left, GLUSfloat right, GLUSfloat bottom, GLUSfloat top, GLUSfloat nearVal, GLUSfloat farVal)
{
    result[0] = 2.0f * nearVal / (right - left);
    result[1] = 0.0f;
    result[2] = 0.0f;
    result[3] = 0.0f;
    result[4] = 0.0f;
    result[5] = 2.0f * nearVal / (top - bottom);
    result[6] = 0.0f;
    result[7] = 0.0f;
    result[8] = (right + left) / (right - left);
    result[9] = (top + bottom) / (top - bottom);
    result[10] = -(farVal + nearVal) / (farVal - nearVal);
    result[11] = -1.0f;
    result[12] = 0.0f;
    result[13] = 0.0f;
    result[14] = -(2.0f * farVal * nearVal) / (farVal - nearVal);
    result[15] = 0.0f;
}

GLUSvoid GLUSAPIENTRY Glus::glusPerspectivef(GLUSfloat result[16], GLUSfloat fovy, GLUSfloat aspect, GLUSfloat zNear, GLUSfloat zFar)
{
    GLUSfloat xmin, xmax, ymin, ymax;

    ymax = zNear * tanf(fovy * PIf / 360.0f);
    ymin = -ymax;
    xmin = ymin * aspect;
    xmax = ymax * aspect;

    glusFrustumf(result, xmin, xmax, ymin, ymax, zNear, zFar);
}

GLUSvoid GLUSAPIENTRY Glus::glusLookAtf(GLUSfloat result[16], GLUSfloat eyeX, GLUSfloat eyeY, GLUSfloat eyeZ, GLUSfloat centerX, GLUSfloat centerY, GLUSfloat centerZ, GLUSfloat upX, GLUSfloat upY, GLUSfloat upZ)
{
    GLUSfloat forward[3], side[3], up[3];
    GLUSfloat matrix[16];

    forward[0] = centerX - eyeX;
    forward[1] = centerY - eyeY;
    forward[2] = centerZ - eyeZ;
    glusNormalizef(forward);

    up[0] = upX;
    up[1] = upY;
    up[2] = upZ;

    glusCrossf(side, forward, up);
    glusNormalizef(side);

    glusCrossf(up, side, forward);

    matrix[0] = side[0];
    matrix[1] = up[0];
    matrix[2] = -forward[0];
    matrix[3] = 0.0f;
    matrix[4] = side[1];
    matrix[5] = up[1];
    matrix[6] = -forward[1];
    matrix[7] = 0.0f;
    matrix[8] = side[2];
    matrix[9] = up[2];
    matrix[10] = -forward[2];
    matrix[11] = 0.0f;
    matrix[12] = 0.0f;
    matrix[13] = 0.0f;
    matrix[14] = 0.0f;
    matrix[15] = 1.0f;

    glusLoadIdentityf(result);
    glusMultMatrixf(result, result, matrix);

    glusTranslatef(result, -eyeX, -eyeY, -eyeZ);
}


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

GLUSfloat GLUSAPIENTRY Glus::glusAmountf(const GLUSfloat vector[3])
{
    return sqrtf(vector[0] * vector[0] + vector[1] * vector[1] + vector[2] * vector[2]);
}

GLUSvoid GLUSAPIENTRY Glus::glusNormalizef(GLUSfloat vector[3])
{
    GLUSuint i;

    GLUSfloat a = glusAmountf(vector);

    if (a == 0.0f) {
        return;
    }

    for (i = 0; i < 3; i++) {
        vector[i] /= a;
    }
}

GLUSfloat GLUSAPIENTRY Glus::glusDotf(const GLUSfloat vector0[3], const GLUSfloat vector1[3])
{
    return vector0[0] * vector1[0] + vector0[1] * vector1[1] + vector0[2] * vector1[2];
}

GLUSvoid GLUSAPIENTRY Glus::glusCrossf(GLUSfloat result[3], const GLUSfloat vector0[3], const GLUSfloat vector1[3])
{
    GLUSuint i;

    GLUSfloat temp[3];

    temp[0] = vector0[1] * vector1[2] - vector0[2] * vector1[1];
    temp[1] = vector0[2] * vector1[0] - vector0[0] * vector1[2];
    temp[2] = vector0[0] * vector1[1] - vector0[1] * vector1[0];

    for (i = 0; i < 3; i++) {
        result[i] = temp[i];
    }
}


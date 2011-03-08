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

#include <stdlib.h>
#include <string.h>
#include <math.h>

using namespace Glus;

GLUSvoid GLUSAPIENTRY Glus::glusCreatePlanef(GLUSshape* shape, GLUSfloat halfExtend)
{
    GLUSuint i;

    GLUSuint numberVertices = 4;
    GLUSuint numberIndices = 6;

    GLUSfloat xy_vertices[] ={
        -1.0f, -1.0f, 0.0f, +1.0f,
        +1.0f, -1.0f, 0.0f, +1.0f,
        -1.0f, +1.0f, 0.0f, +1.0f,
        +1.0f, +1.0f, 0.0f, +1.0f
    };

    GLUSfloat xy_normals[] ={
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f
    };

    GLUSfloat xy_tangents[] ={
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f
    };

    GLUSfloat xy_texCoords[] ={
        0.0f, 0.0f,
        1.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f
    };

    GLUSuint xy_indices[] ={
        0, 1, 2,
        1, 3, 2
    };

    if (!shape) {
        return;
    }

    shape->vertices = 0;
    shape->normals = 0;
    shape->tangents = 0;
    shape->texCoords = 0;
    shape->indices = 0;
    shape->numberVertices = 0;
    shape->numberIndices = 0;

    shape->numberVertices = numberVertices;
    shape->numberIndices = numberIndices;

    shape->vertices = (GLUSfloat*) malloc(4 * numberVertices * sizeof (GLUSfloat));
    memcpy(shape->vertices, xy_vertices, sizeof ( xy_vertices));
    for (i = 0; i < numberVertices; i++) {
        shape->vertices[i * 4 + 0] *= halfExtend;
        shape->vertices[i * 4 + 1] *= halfExtend;
    }

    shape->normals = (GLUSfloat*) malloc(3 * numberVertices * sizeof (GLUSfloat));
    memcpy(shape->normals, xy_normals, sizeof ( xy_normals));

    shape->tangents = (GLUSfloat*) malloc(3 * numberVertices * sizeof (GLUSfloat));
    memcpy(shape->tangents, xy_tangents, sizeof ( xy_tangents));

    shape->texCoords = (GLUSfloat*) malloc(2 * numberVertices * sizeof (GLUSfloat));
    memcpy(shape->texCoords, xy_texCoords, sizeof ( xy_texCoords));

    shape->indices = (GLUSuint*) malloc(numberIndices * sizeof (GLUSuint));
    memcpy(shape->indices, xy_indices, sizeof ( xy_indices));
}

GLUSvoid GLUSAPIENTRY Glus::glusCreateCubef(GLUSshape* shape, GLUSfloat halfExtend)
{
    GLUSuint i;

    GLUSuint numberVertices = 24;
    GLUSuint numberIndices = 36;

    GLUSfloat cubeVertices[] ={
        -1.0f, -1.0f, -1.0f, +1.0f,
        -1.0f, -1.0f, +1.0f, +1.0f,
        +1.0f, -1.0f, +1.0f, +1.0f,
        +1.0f, -1.0f, -1.0f, +1.0f,
        -1.0f, +1.0f, -1.0f, +1.0f,
        -1.0f, +1.0f, +1.0f, +1.0f,
        +1.0f, +1.0f, +1.0f, +1.0f,
        +1.0f, +1.0f, -1.0f, +1.0f,
        -1.0f, -1.0f, -1.0f, +1.0f,
        -1.0f, +1.0f, -1.0f, +1.0f,
        +1.0f, +1.0f, -1.0f, +1.0f,
        +1.0f, -1.0f, -1.0f, +1.0f,
        -1.0f, -1.0f, +1.0f, +1.0f,
        -1.0f, +1.0f, +1.0f, +1.0f,
        +1.0f, +1.0f, +1.0f, +1.0f,
        +1.0f, -1.0f, +1.0f, +1.0f,
        -1.0f, -1.0f, -1.0f, +1.0f,
        -1.0f, -1.0f, +1.0f, +1.0f,
        -1.0f, +1.0f, +1.0f, +1.0f,
        -1.0f, +1.0f, -1.0f, +1.0f,
        +1.0f, -1.0f, -1.0f, +1.0f,
        +1.0f, -1.0f, +1.0f, +1.0f,
        +1.0f, +1.0f, +1.0f, +1.0f,
        +1.0f, +1.0f, -1.0f, +1.0f
    };

    GLUSfloat cubeNormals[] ={
        0.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        0.0f, +1.0f, 0.0f,
        0.0f, +1.0f, 0.0f,
        0.0f, +1.0f, 0.0f,
        0.0f, +1.0f, 0.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, +1.0f,
        0.0f, 0.0f, +1.0f,
        0.0f, 0.0f, +1.0f,
        0.0f, 0.0f, +1.0f,
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        +1.0f, 0.0f, 0.0f,
        +1.0f, 0.0f, 0.0f,
        +1.0f, 0.0f, 0.0f,
        +1.0f, 0.0f, 0.0f
    };

    GLUSfloat cubeTangents[] ={
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,

        +1.0f, 0.0f, 0.0f,
        +1.0f, 0.0f, 0.0f,
        +1.0f, 0.0f, 0.0f,
        +1.0f, 0.0f, 0.0f,

        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,

        +1.0f, 0.0f, 0.0f,
        +1.0f, 0.0f, 0.0f,
        +1.0f, 0.0f, 0.0f,
        +1.0f, 0.0f, 0.0f,

        0.0f, 0.0f, +1.0f,
        0.0f, 0.0f, +1.0f,
        0.0f, 0.0f, +1.0f,
        0.0f, 0.0f, +1.0f,

        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f
    };

    GLUSfloat cubeTexCoords[] ={
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
    };

    GLUSuint cubeIndices[] ={
        0, 2, 1,
        0, 3, 2,
        4, 5, 6,
        4, 6, 7,
        8, 9, 10,
        8, 10, 11,
        12, 15, 14,
        12, 14, 13,
        16, 17, 18,
        16, 18, 19,
        20, 23, 22,
        20, 22, 21
    };

    if (!shape) {
        return;
    }

    shape->vertices = 0;
    shape->normals = 0;
    shape->tangents = 0;
    shape->texCoords = 0;
    shape->indices = 0;
    shape->numberVertices = 0;
    shape->numberIndices = 0;

    shape->numberVertices = numberVertices;
    shape->numberIndices = numberIndices;

    shape->vertices = (GLUSfloat*) malloc(4 * numberVertices * sizeof (GLUSfloat));
    memcpy(shape->vertices, cubeVertices, sizeof ( cubeVertices));
    for (i = 0; i < numberVertices; i++) {
        shape->vertices[i * 4 + 0] *= halfExtend;
        shape->vertices[i * 4 + 1] *= halfExtend;
        shape->vertices[i * 4 + 2] *= halfExtend;
    }

    shape->normals = (GLUSfloat*) malloc(3 * numberVertices * sizeof (GLUSfloat));
    memcpy(shape->normals, cubeNormals, sizeof ( cubeNormals));

    shape->tangents = (GLUSfloat*) malloc(3 * numberVertices * sizeof (GLUSfloat));
    memcpy(shape->tangents, cubeTangents, sizeof ( cubeTangents));

    shape->texCoords = (GLUSfloat*) malloc(2 * numberVertices * sizeof (GLUSfloat));
    memcpy(shape->texCoords, cubeTexCoords, sizeof ( cubeTexCoords));

    shape->indices = (GLUSuint*) malloc(numberIndices * sizeof (GLUSuint));
    memcpy(shape->indices, cubeIndices, sizeof ( cubeIndices));
}

GLUSvoid GLUSAPIENTRY Glus::glusCreateSpheref(GLUSshape* shape, GLUSfloat radius, GLUSuint numberSlices)
{
    GLUSuint i, j;

    GLUSuint numberParallels = numberSlices;
    GLUSuint numberVertices = (numberParallels + 1) * (numberSlices + 1);
    GLUSuint numberIndices = numberParallels * numberSlices * 6;

    GLUSfloat angleStep = (2.0f * PIf) / ((GLUSfloat) numberSlices);

    GLUSuint* indexBuf;

    GLUSfloat helpVector[3] = {0.0f, 1.0f, 0.0f};

    if (!shape) {
        return;
    }

    shape->vertices = 0;
    shape->normals = 0;
    shape->tangents = 0;
    shape->texCoords = 0;
    shape->indices = 0;
    shape->numberVertices = 0;
    shape->numberIndices = 0;

    shape->numberVertices = numberVertices;
    shape->numberIndices = numberIndices;

    shape->vertices = (GLUSfloat*) malloc(4 * numberVertices * sizeof (GLUSfloat));

    shape->normals = (GLUSfloat*) malloc(3 * numberVertices * sizeof (GLUSfloat));

    shape->tangents = (GLUSfloat*) malloc(3 * numberVertices * sizeof (GLUSfloat));

    shape->texCoords = (GLUSfloat*) malloc(2 * numberVertices * sizeof (GLUSfloat));

    shape->indices = (GLUSuint*) malloc(numberIndices * sizeof (GLUSuint));

    for (i = 0; i < numberParallels + 1; i++) {
        for (j = 0; j < numberSlices + 1; j++) {
            GLUSuint vertexIndex = (i * (numberSlices + 1) + j) * 4;
            GLUSuint normalIndex = (i * (numberSlices + 1) + j) * 3;
            GLUSuint tangentIndex = (i * (numberSlices + 1) + j) * 3;
            GLUSuint texCoordsIndex = (i * (numberSlices + 1) + j) * 2;

            shape->vertices[vertexIndex + 0] = radius * sinf(angleStep * (GLUSfloat) i) * sinf(angleStep * (GLUSfloat) j);
            shape->vertices[vertexIndex + 1] = radius * cosf(angleStep * (GLUSfloat) i);
            shape->vertices[vertexIndex + 2] = radius * sinf(angleStep * (GLUSfloat) i) * cosf(angleStep * (GLUSfloat) j);
            shape->vertices[vertexIndex + 3] = 1.0f;

            shape->normals[normalIndex + 0] = shape->vertices[vertexIndex + 0] / radius;
            shape->normals[normalIndex + 1] = shape->vertices[vertexIndex + 1] / radius;
            shape->normals[normalIndex + 2] = shape->vertices[vertexIndex + 2] / radius;

            glusCrossf(&shape->tangents[tangentIndex], &shape->normals[normalIndex], helpVector);

            if (glusAmountf(&shape->tangents[tangentIndex]) == 0.0f) {
                shape->tangents[tangentIndex + 0] = 1.0f;
                shape->tangents[tangentIndex + 1] = 0.0f;
                shape->tangents[tangentIndex + 2] = 0.0f;
            }

            shape->texCoords[texCoordsIndex + 0] = (GLUSfloat) j / (GLUSfloat) numberSlices;
            shape->texCoords[texCoordsIndex + 1] = (1.0f - (GLUSfloat) i) / (GLUSfloat) (numberParallels - 1);
        }
    }

    indexBuf = shape->indices;
    for (i = 0; i < numberParallels; i++) {
        for (j = 0; j < numberSlices; j++) {
            *indexBuf++ = i * (numberSlices + 1) + j;
            *indexBuf++ = (i + 1) * (numberSlices + 1) + j;
            *indexBuf++ = (i + 1) * (numberSlices + 1) + (j + 1);

            *indexBuf++ = i * (numberSlices + 1) + j;
            *indexBuf++ = (i + 1) * (numberSlices + 1) + (j + 1);
            *indexBuf++ = i * (numberSlices + 1) + (j + 1);
        }
    }
}

GLUSvoid GLUSAPIENTRY Glus::glusDestroyShapef(GLUSshape* shape)
{
    if (!shape) {
        return;
    }

    if (shape->vertices) {
        free(shape->vertices);

        shape->vertices = 0;
    }

    if (shape->normals) {
        free(shape->normals);

        shape->normals = 0;
    }

    if (shape->tangents) {
        free(shape->tangents);

        shape->tangents = 0;
    }

    if (shape->texCoords) {
        free(shape->texCoords);

        shape->texCoords = 0;
    }

    if (shape->indices) {
        free(shape->indices);

        shape->indices = 0;
    }

    shape->numberVertices = 0;
    shape->numberIndices = 0;
}


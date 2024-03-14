#include "glview.h"
#include <QOpenGLFunctions>
#include <QOpenGLExtraFunctions>
#include <GL/gl.h>


QVector3D colorToVec(QString color) {
    color.remove(0, 1);
    return QVector3D((color.mid(0, 2).toInt(nullptr, 16) / 255.0f), (color.mid(2, 2).toInt(nullptr, 16) / 255.0f), (color.mid(4, 2).toInt(nullptr, 16) / 255.0f));
}

void glView::initializeGL() {

    initializeOpenGLFunctions();

    glEnable(GL_DEPTH_TEST);

    createVecInd(&object.indices);
    createVecVert(&object.vertices);

    scaleVal = 0;

    //start temp
    clearVecInd(&object.indices);
    clearVecVert(&object.vertices);
    float v[3] = {0.8f, 0.8f, -0.0f};
    addToVecVert(&object.vertices, v);
    v[0] = 0.8f;
    v[1] = -0.2f;
    addToVecVert(&object.vertices, v);
    v[0] = -0.2f;
    v[1] = -0.2f;
    addToVecVert(&object.vertices, v);
    v[0] = -0.2f;
    v[1] = 0.8f;
    addToVecVert(&object.vertices, v);

    int iv[2] = {0, 1};
    addToVecInd(&object.indices, iv);
    iv[0] = 1;
    iv[1] = 3;
    addToVecInd(&object.indices, iv);
    iv[0] = 0;
    iv[1] = 3;
    addToVecInd(&object.indices, iv);
    iv[0] = 2;
    iv[1] = 1;
    addToVecInd(&object.indices, iv);
    iv[0] = 2;
    iv[1] = 3;
    addToVecInd(&object.indices, iv);
    // //end temp
    loadObj(fname.toUtf8().data(), &object);
    initShaderPrograms();
    create4mat(matrices.perspectiveMatrix);
    create4mat(matrices.screenMatrix);
    matrices.screenMatrix[0][0] = 415.0f / 815.0f;
    rebuildPerspectiveMatrix();

    vao = new QOpenGLVertexArrayObject;
    vao->create();
    vbo = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    vbo->create();
    ebo = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    ebo->create();


    rebuildObject();
}

void glView::rebuildPerspectiveMatrix() {
    QMatrix4x4 projection;
    if (params.projectionType == "orthogonal") {
        projection.ortho(-1.0, 1.0, -1.0, 1.0, 0.0, 30.0);
    } else {
        projection.perspective(45.0f, 1.0, 0.5, 7.0);
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            matrices.perspectiveMatrix[i][j] = projection(i,j);
        }
    }

}

void glView::rebuildObject() {
    vao->bind();
    vbo->release();
    ebo->release();
    vbo->bind();
    vbo->allocate(object.vertices.data, sizeof(float) * object.vertices.size * 3);

    ebo->bind();
    ebo->allocate(object.indices.data, sizeof(int) * object.indices.size * 2);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    vao->release();





    create4mat(matrices.centMatrix);

    float offset[3];
    if (object.vertices.size > 0) {
        float scale;
        float minmaxxyz[3][2];
        for (int i = 0; i < 3; i++) {
            minmaxxyz[i][0] = object.vertices.data[i];
            minmaxxyz[i][1] = object.vertices.data[i];
        }
        for (int i = 1; i < object.vertices.size; i++) {
            for (int j = 0; j < 3; j++) {
                if (object.vertices.data[3*i + j] < minmaxxyz[j][0]) minmaxxyz[j][0] = object.vertices.data[3*i + j];
                if (object.vertices.data[3*i + j] > minmaxxyz[j][1]) minmaxxyz[j][1] = object.vertices.data[3*i + j];
            }

        }
        offset[0] = -(minmaxxyz[0][1] + minmaxxyz[0][0]) / 2;
        offset[1] = -(minmaxxyz[1][1] + minmaxxyz[1][0]) / 2;
        offset[2] = -(minmaxxyz[2][1] + minmaxxyz[2][0]) / 2;
        offset4mat(offset, matrices.centMatrix);
        float scales[3];
        for (int i = 0; i < 3; i++) {
            scales[i] = 1.2 / (minmaxxyz[i][1] - minmaxxyz[i][0]);
        }
        scale = scales[0];
        for (int i = 0; i < 2; i++) {
            if (scales[i] < scale) scale = scales[i];
        }
        if (scale != INFINITY) {
            scale4mat(scale, matrices.centMatrix);
        }

    }

    create4mat(matrices.offsetMatrix);
    float zoffset[3] = {0, 0, -3};
    offset4mat(zoffset, matrices.offsetMatrix);
}


void glView::initShaderPrograms() {
    programEdge.removeAllShaders();
    programVertex.removeAllShaders();
    programEdge.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/edgeVert");
    if (params.edgeType == "dashed") {
        programEdge.addShaderFromSourceFile(QOpenGLShader::Geometry, ":/shaders/edgeDashedGeo");
    }
    programEdge.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/edgeFrag");
    if (!programEdge.link()) {
        qDebug() << "Failed to link shader program";
    }

    programVertex.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/verVert");
    if (params.vertexType == "circle") {
        programVertex.addShaderFromSourceFile(QOpenGLShader::Geometry, ":/shaders/verRoundGeo");
    }
    else if (params.vertexType == "square") {
        programVertex.addShaderFromSourceFile(QOpenGLShader::Geometry, ":/shaders/verSquareGeo");
    }
    programVertex.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/verFrag");
    programVertex.link();

}

void glView::paintGL() {
    int attribLocation;
    QVector3D color;

    initShaderPrograms();



    QVector3D colorVec = colorToVec(this->params.backgroundColor);
    glClearColor(colorVec.x(), colorVec.y(), colorVec.z(), 1);
    glClear(GL_COLOR_BUFFER_BIT);

    float mMatrix[4][4];
    float vpMatrix[4][4];
    mult4matToRes(matrices.offsetMatrix, matrices.centMatrix, mMatrix);
    mult4matToRes(matrices.screenMatrix, matrices.perspectiveMatrix, vpMatrix);
    GLfloat mMatGLfloat[16];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            //transposing!!!!!!
            mMatGLfloat[4*j + i] = mMatrix[i][j];
        }
    }
    GLfloat vpMatGLfloat[16];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            //transposing!!!!!!
            vpMatGLfloat[4*j + i] = vpMatrix[i][j];
        }
    }

    vao->bind();

    GLint bufferSize;
    glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &bufferSize);




    programVertex.bind();
    attribLocation = programVertex.uniformLocation("MMatrix");
    glUniformMatrix4fv(attribLocation, 1, GL_FALSE, mMatGLfloat);
    attribLocation = programVertex.uniformLocation("VPMatrix");
    glUniformMatrix4fv(attribLocation, 1, GL_FALSE, vpMatGLfloat);

    attribLocation = programVertex.uniformLocation("geo");
    glUniform1i(attribLocation, params.vertexType != "no");

    color = colorToVec(params.vertexColor);
    attribLocation = programVertex.uniformLocation("dotcolor");
    glUniform4f(attribLocation, (GLfloat)color.x(), (GLfloat)color.y(), (GLfloat)color.z(), 1.0f);

    attribLocation = programVertex.uniformLocation("radius");
    if (attribLocation > 0) {
        float radius = 0;
        if (params.vertexThickness == '1') {
            radius = 0.002f;
        } else if (params.vertexThickness == '2') {
            radius = 0.03f;
        } else if (params.vertexThickness == '3') {
            radius = 0.06f;
        } else {
            radius = 0.18f;
        }
        glUniform1f(attribLocation, radius);
    }

    GLfloat screenMatGLfloat[16];
    float screen[4][4];
    mult4matToRes(matrices.screenMatrix, matrices.perspectiveMatrix, screen);
    create4mat(screen);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            screenMatGLfloat[4*i + j] = screen[i][j];
        }
    }
    attribLocation = programVertex.uniformLocation("screenMat");
    if (attribLocation > 0) {
        glUniformMatrix4fv(attribLocation, 1, GL_FALSE, screenMatGLfloat);
    }

    glDrawArrays(GL_POINTS, 0, object.vertices.size);
    programVertex.release();


    if (params.edgeType != "no") {
        programEdge.bind();
        attribLocation = programVertex.uniformLocation("MMatrix");
        glUniformMatrix4fv(attribLocation, 1, GL_FALSE, mMatGLfloat);
        attribLocation = programVertex.uniformLocation("VPMatrix");
        glUniformMatrix4fv(attribLocation, 1, GL_FALSE, vpMatGLfloat);

        attribLocation = programVertex.uniformLocation("geo");
        glUniform1i(attribLocation, params.edgeType != "solid");


        color = colorToVec(params.edgeColor);
        attribLocation = programEdge.uniformLocation("edgecolor");
        glUniform4f(attribLocation, (GLfloat)color.x(), (GLfloat)color.y(), (GLfloat)color.z(), 1.0f);

        if (params.edgeThickness == '1') {
            glLineWidth(1.0f);
        } else if (params.edgeThickness == '2') {
            glLineWidth(5.0f);
        } else if (params.edgeThickness == '3') {
            glLineWidth(20.0f);
        } else {
            glLineWidth(70.0f);
        }

        glDrawElements(GL_LINES, object.indices.size * 2, GL_UNSIGNED_INT, 0);
        programEdge.release();
    }

    vao->release();
    update();
}

void glView::mousePressEvent(QMouseEvent *event) {
    mousePos[0] = event->position().x();
    mousePos[1] = event->position().y();
}

void glView::mouseMoveEvent(QMouseEvent *event) {
    int movementSped = 300;
    if (event->buttons() & (Qt::LeftButton | Qt::RightButton)) {
        int newPos[2];
        newPos[0] = event->position().x();
        newPos[1] = event->position().y();
        float dPos[2];
        dPos[0] = newPos[0] - mousePos[0];
        dPos[1] = mousePos[1] - newPos[1];

        mousePos[0] = newPos[0];
        mousePos[1] = newPos[1];

        if (event->buttons() & Qt::LeftButton) {
            float offset[3] = {dPos[0] / movementSped, dPos[1] / movementSped, 0};
            offset4mat(offset, matrices.offsetMatrix);
        }

        if (event->buttons() & Qt::RightButton) {
            if (!(dPos[0] == dPos[1] && dPos[0] == 0)) {
                float quanterion[4];
                quanterionFromDmouse(dPos, quanterion);
                rotate4mat(quanterion, matrices.centMatrix);
            }
        }

    }

}

void glView::rescale(float newScale) {
    float delta;
    if (fabs(newScale - scaleVal) > 50) {
        if(newScale < scaleVal) newScale += 100;
        else scaleVal +=  100;
    }
    delta = newScale - scaleVal;
    scaleVal = newScale > 100 ? newScale - 100 : newScale;
    scale4mat(pow(1.01, delta), matrices.centMatrix);

}

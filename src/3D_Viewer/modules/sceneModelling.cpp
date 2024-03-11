#include "glview.h"
#include <QOpenGLFunctions>



QVector3D colorToVec(QString color) {
    color.remove(0, 1);
    return QVector3D((color.mid(0, 2).toInt(nullptr, 16) / 255.0f), (color.mid(2, 2).toInt(nullptr, 16) / 255.0f), (color.mid(4, 2).toInt(nullptr, 16) / 255.0f));
}

void glView::initializeGL() {
    initGLView();
    initializeOpenGLFunctions();
    //QVector3D colorVec = colorToVec(this->params.backgroundColor);
    //glClearColor(colorVec.x(), colorVec.y(), colorVec.z(), 1);
    glEnable(GL_DEPTH_TEST);

    createVecInd(object.indices);
    createVecVert(object.vertices);

    //start temp
    clearVecInd(object.indices);
    clearVecVert(object.vertices);
    float v[3] = {0.5f, 0.5f, 0.0f};
    addToVecVert(object.vertices, v);
    v[0] = 0.5f;
    v[1] = -0.5f;
    addToVecVert(object.vertices, v);
    v[0] = -0.5f;
    v[1] = -0.5f;
    addToVecVert(object.vertices, v);
    v[0] = -0.5f;
    v[1] = 0.5f;
    addToVecVert(object.vertices, v);

    int iv[2] = {0, 1};
    addToVecInd(object.indices, iv);
    iv[0] = 1;
    iv[1] = 3;
    addToVecInd(object.indices, iv);
    iv[0] = 0;
    iv[1] = 3;
    addToVecInd(object.indices, iv);
    //end temp

    initShaderPrograms();
    create4mat(object.centMatrix);
    create4mat(object.offsetMatrix);
    create4mat(object.rotationMatrix);
    vao.create();
    rebuildObject();
    paintGL();
}

void glView::rebuildObject() {
    GLuint VBO, IBO;
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &IBO);

    vao.bind();
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * object.vertices.size * 3, object.vertices.data, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * object.indices.size * 2, object.indices.data, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);


    vao.release();
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}


void glView::initShaderPrograms() {

    programEdge.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/edgeVert");
    if (params.edgeType == "dashed") {
        programEdge.addShaderFromSourceFile(QOpenGLShader::Geometry, ":/shaders/edgeDashedGeo");
    }
    programEdge.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/edgeFrag");
    programEdge.link();

    programVertex.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/verVert");
    if (params.edgeType == "circle") {
        programVertex.addShaderFromSourceFile(QOpenGLShader::Geometry, ":/shaders/verRoundGeo");
    }
    else if (params.edgeType == "square") {
        programVertex.addShaderFromSourceFile(QOpenGLShader::Geometry, ":/shaders/verSquareGeo");
    }
    programVertex.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/verFrag");
    programVertex.link();

}


void glView::paintGL() {


    QVector3D colorVec = colorToVec(this->params.backgroundColor);
    glClearColor(colorVec.x(), colorVec.y(), colorVec.z(), 1);
    glClear(GL_COLOR_BUFFER_BIT);

    // glBegin(GL_TRIANGLES);
    // glColor3f(1.0f, 0.0f,0.0f);
    // glVertex3f(-0.3f, -0.3f, 0.0f);
    // glVertex3f(0.3f, -0.3f, 0.0f);
    // glVertex3f(0.0f, 0.3f, 0.0f);
    // glEnd();
    float mvpMatrix[4][4];
    mult4matToRes(object.rotationMatrix, object.centMatrix, mvpMatrix);
    GLfloat mvpMatGLfloat[16];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            mvpMatGLfloat[4*i + j] = mvpMatrix[i][j];
        }
    }

    vao.bind();
    programEdge.bind();
    int mvpMatLocation = programEdge.uniformLocation("MVPMatrix");
    glUniformMatrix4fv(mvpMatLocation, 1, GL_FALSE, mvpMatGLfloat);

    QVector3D color = colorToVec(params.edgeColor);
    int colorLocation = programEdge.uniformLocation("edgecolor");

    glUniform4f(colorLocation, (GLfloat)color.x(), (GLfloat)color.y(), (GLfloat)color.z(), 1.0f);
    glLineWidth(52.0f);

    glDrawElements(GL_LINES, object.indices.size * 2, GL_UNSIGNED_INT, 0);
    programEdge.release();

    // programVertex.bind();
    // glDrawArrays(GL_POINTS, 0, object.vertices.size);
    // programVertex.release();
    vao.release();
    update();
}


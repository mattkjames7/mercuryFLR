#include "include/openglwidget.h"
#include "include/flatarrow.h"

OpenGLWidget::OpenGLWidget(QWidget *parent)
    : QOpenGLWidget(parent),
      mercury(nullptr),
      magnetopause(nullptr),
      streamline(nullptr),
      cutout(nullptr),
      flr(nullptr),
      ocb(nullptr),
      exampleTraces(nullptr)
{
}

OpenGLWidget::~OpenGLWidget()
{
    // Cleanup, if necessary
    delete this->mercury;
    delete this->magnetopause;
    delete this->streamline;
    delete this->cutout;
    delete this->flr;
    delete this->ocb;
    delete this->exampleTraces;
}

void OpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    float spec[4] = {0.5, 0.5, 0.5, 1.0};
    float shine[1] = {10.0};
    float amb[4] = {0.2, 0.2, 0.2, 1.0};
    float bright[4] = {1.0, 1.0, 1.0, 1.0};
    GLfloat light_position[] = {10.0, 0.0, 0.0, 1.0};

    initGL(light_position, spec, shine, amb, bright);

    // These constructors upload OpenGL buffers, so they must run while the
    // QOpenGLWidget context is current.
    mercury = new MercurySurface;
    magnetopause = new Magnetopause;
    streamline = new Streamline;
    cutout = new CutOut;
    flr = new FLR;
    ocb = new OCB;
    exampleTraces = new ExampleTraces;
}

void OpenGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Match the original SDL renderer's initial spherical camera exactly.
    const float eyeLatitude = 30.0f;
    const float eyeMlt = 15.0f;
    const float eyeDistance = 6.0f;
    const float latitude = eyeLatitude * M_PI / 180.0f;
    const float longitude = (eyeMlt + 12.0f) * 15.0f * M_PI / 180.0f;
    const float eyeX = eyeDistance * cosf(latitude) * cosf(longitude);
    const float eyeY = eyeDistance * cosf(latitude) * sinf(longitude);
    const float eyeZ = eyeDistance * sinf(latitude);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eyeX, eyeY, eyeZ,
              0.0, 0.0, 0.0,
              0.0, 0.0, 1.0);
    GLfloat lightPosition[] = {10.0f, 0.0f, 0.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    // Mercury.
    glEnable(GL_LIGHTING);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, mercury->buffers_[0]);
    glVertexPointer(3, GL_FLOAT, 0, nullptr);
    glBindBuffer(GL_ARRAY_BUFFER, mercury->buffers_[1]);
    glNormalPointer(GL_FLOAT, 0, nullptr);
    glBindBuffer(GL_ARRAY_BUFFER, mercury->buffers_[2]);
    glColorPointer(3, GL_FLOAT, 0, nullptr);
    glDrawArrays(GL_QUADS, 0, mercury->nVertices_ / 3);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // OCBs, matching the original blue segmented lines.
    glDisable(GL_LIGHTING);
    glLineWidth(5.0f);
    glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
    glBegin(GL_LINES);
    for (int i = 0; i < ocb->n_; ++i) {
        glVertex3f(ocb->xn_[i], ocb->yn_[i], ocb->zn_[i]);
        glVertex3f(ocb->xn_[i + 1], ocb->yn_[i + 1], ocb->zn_[i + 1]);
        glVertex3f(ocb->xs_[i], ocb->ys_[i], ocb->zs_[i]);
        glVertex3f(ocb->xs_[i + 1], ocb->ys_[i + 1], ocb->zs_[i + 1]);
    }
    glEnd();

    // KT17 example field traces: open traces are black and closed traces green.
    glLineWidth(3.0f);
    glBegin(GL_LINES);
    for (int i = 0; i < exampleTraces->nt; ++i) {
        for (int j = 0; j < exampleTraces->nstep[i] - 1; ++j) {
            const int p = i * exampleTraces->MaxTraceSteps + j;
            const float radius = sqrtf(exampleTraces->xt[p] * exampleTraces->xt[p]
                                     + exampleTraces->yt[p] * exampleTraces->yt[p]
                                     + (exampleTraces->zt[p] + 0.196f)
                                       * (exampleTraces->zt[p] + 0.196f));
            const float opacity = expf(1.0f - radius);
            if (exampleTraces->open[i])
                glColor4f(0.0f, 0.0f, 0.0f, opacity);
            else
                glColor4f(0.0f, 0.75f, 0.0f, opacity);
            glVertex3f(exampleTraces->xt[p], exampleTraces->yt[p], exampleTraces->zt[p]);
            glVertex3f(exampleTraces->xt[p + 1], exampleTraces->yt[p + 1],
                       exampleTraces->zt[p + 1]);
        }
    }
    glEnd();

    // Red outlines of the two cut planes and their centre line.
    glLineWidth(3.0f);
    glBegin(GL_LINES);
    for (int i = 0; i < 642; ++i) {
        const float dr = cutout->mpx_[i] - 1.42f;
        float opacity = 0.0f;
        if (dr >= -2.0f)
            opacity = 1.0f;
        else if (dr >= -5.0f)
            opacity = 1.0f + (dr + 2.0f) / 3.0f;
        glColor4f(1.0f, 0.0f, 0.0f, opacity);

        glVertex3f(cutout->mpx_[i], 0.0f, cutout->mpr_[i]);
        glVertex3f(cutout->mpx_[i + 1], 0.0f, cutout->mpr_[i + 1]);

        float dx = 0.0f, dy = 0.0f, dz = 0.0f;
        wiggleCart(1.42f, cutout->mpx_[i], cutout->mpr_[i], 0.0f,
                   0.2f, &dx, &dy, &dz);
        glVertex3f(cutout->mpx_[i] + dx, cutout->mpr_[i] + dy, 0.0f);
        dx = dy = dz = 0.0f;
        wiggleCart(1.42f, cutout->mpx_[i + 1], cutout->mpr_[i + 1], 0.0f,
                   0.2f, &dx, &dy, &dz);
        glVertex3f(cutout->mpx_[i + 1] + dx, cutout->mpr_[i + 1] + dy, 0.0f);

        glVertex3f(cutout->mpx_[i], 0.01f, 0.01f);
        glVertex3f(cutout->mpx_[i + 1], 0.01f, 0.01f);
    }
    glEnd();

    // Original and displaced FLR field lines.
    glColor3f(0.0f, 0.9f, 0.0f);
    glLineWidth(3.0f);
    glBegin(GL_LINES);
    for (int i = 0; i < flr->n_ - 1; ++i) {
        glVertex3f(flr->xd_[i], flr->yd_[i], flr->zd_[i]);
        glVertex3f(flr->xd_[i + 1], flr->yd_[i + 1], flr->zd_[i + 1]);
    }
    glEnd();
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    for (int i = 0; i < flr->n_ - 1; ++i) {
        // The undisplaced dawn-side trace is the reference trace and is
        // intentionally dashed; the perturbed trace above remains solid.
        if ((i / 4) % 2 != 0)
            continue;
        glVertex3f(flr->x_[i], flr->y_[i], flr->z_[i]);
        glVertex3f(flr->x_[i + 1], flr->y_[i + 1], flr->z_[i + 1]);
    }
    glEnd();

    // Magnetopause.
    glBindBuffer(GL_ARRAY_BUFFER, magnetopause->buffers_[0]);
    glVertexPointer(3, GL_FLOAT, 0, nullptr);
    glBindBuffer(GL_ARRAY_BUFFER, magnetopause->buffers_[2]);
    glColorPointer(4, GL_FLOAT, 0, nullptr);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glDrawArrays(GL_QUADS, 0, magnetopause->nVertex_ / 3);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);

    // Filled cut planes.
    glBindBuffer(GL_ARRAY_BUFFER, cutout->buffers_[0]);
    glVertexPointer(3, GL_FLOAT, 0, nullptr);
    glBindBuffer(GL_ARRAY_BUFFER, cutout->buffers_[2]);
    glColorPointer(4, GL_FLOAT, 0, nullptr);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glDrawArrays(GL_TRIANGLES, 0, cutout->nVertex_ / 3);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);

    // Mirrored solar-wind streamlines from the original renderer.
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(3.0f);
    glBegin(GL_LINES);
    for (int i = 0; i < streamline->n_ - 1; ++i) {
        glVertex3f(streamline->x_[i], streamline->y_[i], 0.0f);
        glVertex3f(streamline->x_[i + 1], streamline->y_[i + 1], 0.0f);
        glVertex3f(streamline->x_[i], -streamline->y_[i], 0.0f);
        glVertex3f(streamline->x_[i + 1], -streamline->y_[i + 1], 0.0f);
    }
    glEnd();

    // Arrowheads showing the anti-sunward flow direction on both streamlines.
    const float arrowRadius = 0.05f;
    glBegin(GL_TRIANGLES);
    for (int side = -1; side <= 1; side += 2) {
        for (int i = 0; i < 72; ++i) {
            const float a0 = M_PI * (i * 5.0f) / 180.0f;
            const float a1 = M_PI * ((i + 1) * 5.0f) / 180.0f;
            glVertex3f(2.5f, side * 0.5f + arrowRadius * cosf(a0),
                       arrowRadius * sinf(a0));
            glVertex3f(2.5f, side * 0.5f + arrowRadius * cosf(a1),
                       arrowRadius * sinf(a1));
            glVertex3f(2.4f, side * 0.5f, 0.0f);
        }
    }
    glEnd();

    // Magnetosonic wave fronts just inside the magnetopause.
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    const float waveRadii[] = {1.18f, 1.30f};
    for (float waveRadius : waveRadii) {
        for (int i = 0; i < 80; ++i) {
            const float mlt = i * 0.1f + 13.0f;
            const float theta0 = (mlt - 12.0f) * M_PI / 12.0f;
            const float theta1 = (mlt + 0.1f - 12.0f) * M_PI / 12.0f;
            const float opacity = 1.0f - fabsf((17.0f - mlt) / 4.0f);
            glColor4f(1.0f, 0.25f, 0.0f, opacity);

            const float r0 = waveRadius * sqrtf(2.0f / (1.0f + cosf(theta0)));
            const float r1 = waveRadius * sqrtf(2.0f / (1.0f + cosf(theta1)));
            float x0 = r0 * cosf(theta0), y0 = r0 * sinf(theta0), z0 = 0.01f;
            float x1 = r1 * cosf(theta1), y1 = r1 * sinf(theta1), z1 = 0.01f;
            float dx = 0.0f, dy = 0.0f, dz = 0.0f;
            wiggleCart(waveRadius, x0, y0, z0, 0.2f, &dx, &dy, &dz);
            x0 += dx; y0 += dy; z0 += dz;
            dx = dy = dz = 0.0f;
            wiggleCart(waveRadius, x1, y1, z1, 0.2f, &dx, &dy, &dz);
            glVertex3f(x0, y0, z0);
            glVertex3f(x1 + dx, y1 + dy, z1 + dz);
        }
    }
    glEnd();

    float waveArrowColour[] = {1.0f, 0.25f, 0.0f, 1.0f};
    flatArrow(0.949f, 0.949f, 213.0f, 0.3f, 0.15f, waveArrowColour);
    flatArrow(0.0f, 1.754f, 243.0f, 0.3f, 0.15f, waveArrowColour);
    glEnable(GL_LIGHTING);
}

void OpenGLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);

    const double aspect = h > 0 ? static_cast<double>(w) / h : 1.0;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-aspect, aspect, -1.0, 1.0, 1.5, 1000.0);
    glMatrixMode(GL_MODELVIEW);
}

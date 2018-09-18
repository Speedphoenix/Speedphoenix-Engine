#include "Camera.h"

#include "GameContainer.h"
#include "allegroImplem.h"

#include "debugNerrors.h"

Camera * Camera::m_currentCamera = nullptr;

Camera::Camera()
    :m_displayedDims(), m_takenView(), m_zoomFactor(1)
{
    if (!m_currentCamera)
        m_currentCamera = this;

    resizeView();
}

Camera::~Camera()
{
    //dtor
}

void Camera::update()
{
    if (m_follow)
    {
        setCameraCenterPos(*m_follow);
    }
}

//sets the width etc of takenView depending on the displayedView and the zoomFactor. Calls blockBorders() at the end
void Camera::calcTakenView()
{
    m_takenView.setWidth(m_displayedDims.width() * m_zoomFactor);
    m_takenView.setHeight(m_displayedDims.height() * m_zoomFactor);

    blockBorders();
}

//blocks if the screen gets too big for the map too
void Camera::blockBorders()
{
    GameContainer* instance = GameContainer::instance();
    bool tooBigx = false, tooBigy = false;

    //the first call to this function is in the initialization of the GameContainer
    if (!instance)
        return;


    //if the screen is too big for the map
    if (m_displayedDims.width() * m_zoomFactor > instance->maximumX())
        tooBigx = true;
    if (m_displayedDims.height() * m_zoomFactor > instance->maximumY())
        tooBigy = true;

    if (tooBigx || tooBigy)
    {
        double neededfactorx =  instance->maximumX() / m_displayedDims.width();
        double neededfactory = instance->maximumY() / m_displayedDims.height();

        //take the highest
        m_zoomFactor = ((neededfactorx > neededfactory)? neededfactorx : neededfactory);

        m_takenView.setWidth(m_displayedDims.width() * m_zoomFactor);
        m_takenView.setHeight(m_displayedDims.height() * m_zoomFactor);

        //forcibly change the size of the window?
        if (m_zoomFactor < maxCameraZoom)
            ES("The window is too big for this map")
    }

    if (m_takenView.absX() < 0)
        m_takenView.setAbsX(0);
    else if (m_takenView.endAbsX() > instance->maximumX())
        m_takenView.setEndAbsX(instance->maximumX());


    if (m_takenView.absY() < 0)
        m_takenView.setAbsY(0);
    else if (m_takenView.endAbsY() > instance->maximumY())
        m_takenView.setEndAbsY(instance->maximumY());
}

//blocks the zoom depending on max/minCameraZoom and calls calcTakenView()
void Camera::blockZoom()
{
    if (m_zoomFactor > maxCameraZoom)
        m_zoomFactor = maxCameraZoom;
    else if (m_zoomFactor < minCameraZoom)
        m_zoomFactor = minCameraZoom;

    calcTakenView();
}

//translate the camera (taken view) by dx and dy
void Camera::moveCamera(double dx, double dy)
{
    m_takenView.addXY(dx, dy);

    blockBorders();
}

void Camera::setCameraPos(double valx, double valy)
{
    m_takenView.setAbsPos(valx, valy);

    blockBorders();
}

void Camera::setCameraPos(const TransformBase& where)
{
    setCameraPos(where.absX(), where.absY());
}

void Camera::setCameraCenterPos(double valx, double valy)
{
    m_takenView.setCenterAbsPos(valx, valy);

    blockBorders();
}

void Camera::setCameraCenterPos(const TransformBase& where)
{
    setCameraCenterPos(where.centerAbsX(), where.centerAbsY());
}

//resizes the displayed view depending on the current display (from allegroImplem)
void Camera::resizeView()
{
    int askedWidth = al_get_display_width(currentDisplay);
    int askedHeight = al_get_display_height(currentDisplay);

    m_displayedDims.setDim(askedWidth, askedHeight);

    calcTakenView();
}

void Camera::resizeView(const ALLEGRO_EVENT& event)
{
    if (event.type != ALLEGRO_EVENT_DISPLAY_RESIZE)
        return;

    int askedWidth = event.display.width;
    int askedHeight = event.display.height;

    m_displayedDims.setDim(askedWidth, askedHeight);

    calcTakenView();
}

//may wanna make this a percentage increase instead of adding...
//directly add will make a faster zooming effect whe already zoomed...
void Camera::addZoom(double val)
{
    m_zoomFactor += val;

    blockZoom();
}

void Camera::setZoom(double val)
{
    m_zoomFactor = val;

    blockZoom();
}


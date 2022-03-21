#include "controller.h"

Controller::Controller(IView* pView) : m_pView(pView) {}

void Controller::handleEvent(std::unique_ptr<Event> pEvent) {
    switch(pEvent->getSource()) {
        case Source::CREATE_PRIMITIVE_BUTTON:
            //m_pModel->createPrimitive(m_pDocument, );
            break;
        default:
            break;
    }
}


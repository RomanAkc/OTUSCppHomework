#include "controller.h"
#include "primitives.h"

void Controller::handleEvent(std::unique_ptr<Event> pEvent) {
    if(!checkDocumentWithMessage()
        && pEvent->getSource() != Source::NEW_BUTTON
        && pEvent->getSource() != Source::IMPORT_BUTTON)
        return;

    switch(pEvent->getSource()) {
        case Source::CREATE_PRIMITIVE_BUTTON: {
            auto primitiveType = m_pView->showDlgSelectNewPrimitive();
            if(primitiveType == PrimitiveType::NOTHING)
                break;

            m_pModel->createPrimitive(m_pDocument, primitiveType);
            break;
        }
        case Source::DELETE_PRIMITIVE_BUTTON: {
            m_pModel->deletePrimitive(m_pDocument, m_pCurrentPrimitive);
            break;
        }
        case Source::SELECT_PRIMITIVE: {
            auto xy = m_pView->getCurrentCoordinates();
            m_pCurrentPrimitive = m_pModel->selectPrimitive(m_pDocument, xy.first, xy.second);
            break;
        }
        case Source::NEW_BUTTON: {
            m_pDocument = m_pModel->createDocument();
            break;
        }
        case Source::EXPORT_BUTTON: {
            auto fileName = m_pView->getFileName();
            m_pModel->exportDocument(m_pDocument, fileName);
            break;
        }
        case Source::IMPORT_BUTTON: {
            auto fileName = m_pView->getFileName();
            m_pDocument = m_pModel->importDocument(fileName);
            break;
        }
    }

    m_pView->updateInterface();
}

bool Controller::checkDocumentWithMessage() {
    if(!m_pDocument) {
        m_pView->showErrorMsgBox("No document!");
        return false;
    }

    return true;
}

void Controller::setView(IView *pView) {
    m_pView = pView;
}

void Controller::setModel(std::shared_ptr<IModel> pModel) {
    m_pModel = pModel;
}


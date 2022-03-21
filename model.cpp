#include "model.h"
#include "document.h"

void DocumentModel::createDocument() {
    m_pDocument = std::shared_ptr<IDocument>(new Document());
}

void DocumentModel::importDocument()  {
    m_pDocument = std::shared_ptr<IDocument>(new Document());
}
void DocumentModel::exportDocument() {}

void DocumentModel::createPrimitive(PrimitiveType type) {
    if(auto p = createPrimitiveImpl(type))
        m_pDocument->addPrimitive(p);
}

void DocumentModel::deletePrimitive(std::shared_ptr<IGraphicPrimitive> pPrimitive) {
    m_pDocument->delPrimitive(pPrimitive);
}

std::shared_ptr<IGraphicPrimitive> DocumentModel::selectPrimitive(int x, int y) {
    return m_pDocument->getPrimitiveByPoint(x, y);
}

std::shared_ptr<IGraphicPrimitive> DocumentModel::createPrimitiveImpl(PrimitiveType type) {
    switch(type) {
        case PrimitiveType::POINT:
            return std::shared_ptr<IGraphicPrimitive>(new Point());
        case PrimitiveType::LINE:
            return std::shared_ptr<IGraphicPrimitive>(new Line());
        case PrimitiveType::TRIANGLE:
            return std::shared_ptr<IGraphicPrimitive>(new Triangle());
    }
    return nullptr;
}


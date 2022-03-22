#include "model.h"
#include "document.h"

std::shared_ptr<IDocument> DocumentModel::createDocument() {
    return std::shared_ptr<IDocument>(new Document());
}

std::shared_ptr<IDocument> DocumentModel::importDocument(const std::string&)  {
    //import from file
    return std::shared_ptr<IDocument>(new Document());
}
void DocumentModel::exportDocument(std::shared_ptr<IDocument>, const std::string&) {
    //export to file
}

void DocumentModel::createPrimitive(std::shared_ptr<IDocument> pDoc, PrimitiveType type) {
    if(auto p = createPrimitiveImpl(type))
        pDoc->addPrimitive(p);
}

void DocumentModel::deletePrimitive(std::shared_ptr<IDocument> pDoc, std::shared_ptr<IGraphicPrimitive> pPrimitive) {
    pDoc->delPrimitive(pPrimitive);
}

std::shared_ptr<IGraphicPrimitive> DocumentModel::selectPrimitive(std::shared_ptr<IDocument> pDoc, int x, int y) {
    return pDoc->getPrimitiveByPoint(x, y);
}

std::shared_ptr<IGraphicPrimitive> DocumentModel::createPrimitiveImpl(PrimitiveType type) {
    switch(type) {
        case PrimitiveType::NOTHING:
            return nullptr;
        case PrimitiveType::POINT:
            return std::shared_ptr<IGraphicPrimitive>(new Point());
        case PrimitiveType::LINE:
            return std::shared_ptr<IGraphicPrimitive>(new Line());
        case PrimitiveType::TRIANGLE:
            return std::shared_ptr<IGraphicPrimitive>(new Triangle());
    }

    return nullptr;
}


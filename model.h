#pragma once
#include "primitives.h"
#include "document.h"
#include <memory>

class IModel {
public:
    IModel() = default;
    virtual ~IModel() = default;
    IModel(IModel&) = delete;
    IModel(IModel&&) = delete;
    IModel& operator=(const IModel&) = delete;
    IModel& operator=(IModel&&) = delete;

    virtual void createDocument() = 0;
    virtual void importDocument() = 0;
    virtual void exportDocument() = 0;
    virtual void createPrimitive(PrimitiveType type) = 0;
    virtual void deletePrimitive(std::shared_ptr<IGraphicPrimitive> pPrimitive) = 0;
    virtual std::shared_ptr<IGraphicPrimitive> selectPrimitive(int x, int y) = 0;
};


class DocumentModel : public IModel {
public:
    DocumentModel() = default;
    virtual ~DocumentModel() = default;
    DocumentModel(DocumentModel&) = delete;
    DocumentModel(DocumentModel&&) = delete;
    DocumentModel& operator=(const DocumentModel&) = delete;
    DocumentModel& operator=(DocumentModel&&) = delete;

    void createDocument() override;
    void importDocument() override;
    void exportDocument() override;
    void createPrimitive(PrimitiveType type) override;
    void deletePrimitive(std::shared_ptr<IGraphicPrimitive> pPrimitive) override;
    std::shared_ptr<IGraphicPrimitive> selectPrimitive(int x, int y) override;

private:
    std::shared_ptr<IDocument> m_pDocument;
    std::shared_ptr<IGraphicPrimitive> createPrimitiveImpl(PrimitiveType type) ;
};

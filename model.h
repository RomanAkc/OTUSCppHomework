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

    virtual std::shared_ptr<IDocument> createDocument() = 0;
    virtual std::shared_ptr<IDocument> importDocument(const std::string& fileName) = 0;
    virtual void exportDocument(std::shared_ptr<IDocument> pDoc, const std::string& fileName) = 0;
    virtual void createPrimitive(std::shared_ptr<IDocument> pDoc, PrimitiveType type) = 0;
    virtual void deletePrimitive(std::shared_ptr<IDocument> pDoc, std::shared_ptr<IGraphicPrimitive> pPrimitive) = 0;
    virtual std::shared_ptr<IGraphicPrimitive> selectPrimitive(std::shared_ptr<IDocument> pDoc, int x, int y) = 0;
};


class DocumentModel : public IModel {
public:
    DocumentModel() = default;
    virtual ~DocumentModel() = default;
    DocumentModel(DocumentModel&) = delete;
    DocumentModel(DocumentModel&&) = delete;
    DocumentModel& operator=(const DocumentModel&) = delete;
    DocumentModel& operator=(DocumentModel&&) = delete;

    std::shared_ptr<IDocument> createDocument() override;
    std::shared_ptr<IDocument> importDocument(const std::string& fileName) override;
    void exportDocument(std::shared_ptr<IDocument> pDoc, const std::string& fileName) override;
    void createPrimitive(std::shared_ptr<IDocument> pDoc, PrimitiveType type) override;
    void deletePrimitive(std::shared_ptr<IDocument> pDoc, std::shared_ptr<IGraphicPrimitive> pPrimitive) override;
    std::shared_ptr<IGraphicPrimitive> selectPrimitive(std::shared_ptr<IDocument> pDoc, int x, int y) override;

private:
    std::shared_ptr<IGraphicPrimitive> createPrimitiveImpl(PrimitiveType type);
};

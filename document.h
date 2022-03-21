#pragma once
#include <memory>
#include <vector>

#include "primitives.h"

class IDocument {
public:
    IDocument() = default;
    IDocument(IDocument&) = delete;
    IDocument(IDocument&&) = delete;
    IDocument& operator=(const IDocument&) = delete;
    IDocument& operator=(IDocument&&) = delete;
    virtual ~IDocument() = default;
    virtual void addPrimitive(std::shared_ptr<IGraphicPrimitive> pPrimitive) = 0;
    virtual void delPrimitive(std::shared_ptr<IGraphicPrimitive> pPrimitive) = 0;
    virtual std::shared_ptr<IGraphicPrimitive> getPrimitiveByPoint(int x, int y) = 0;
};

class Document : public IDocument {
public:
    Document() = default;
    Document(Document&) = delete;
    Document(Document&&) = delete;
    Document& operator=(const Document&) = delete;
    Document& operator=(Document&&) = delete;
    virtual ~Document() = default;
    virtual void addPrimitive(std::shared_ptr<IGraphicPrimitive> pPrimitive) override;
    virtual void delPrimitive(std::shared_ptr<IGraphicPrimitive> pPrimitive) override;
    virtual std::shared_ptr<IGraphicPrimitive> getPrimitiveByPoint(int x, int y) override;

private:
    std::vector<std::shared_ptr<IGraphicPrimitive>> m_vecPrimitives;
};

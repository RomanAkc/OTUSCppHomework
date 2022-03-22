#pragma once
#include <memory>

#include "event.h"
#include "model.h"
#include "view.h"

class IController {
public:
    IController() = default;
    IController(const IController&) = delete;
    IController(IController&&) = delete;
    IController& operator=(const IController&) = delete;
    IController& operator=(IController&&) = delete;
    virtual ~IController() = default;
    virtual void handleEvent(std::unique_ptr<Event>) = 0;
    virtual void setView(IView*) = 0;
    virtual void setModel(std::shared_ptr<IModel>) = 0;
};

class Controller : public IController {
public:
    Controller() = default;
    Controller(const Controller&) = delete;
    Controller(Controller&&) = delete;
    Controller& operator=(const Controller&) = delete;
    Controller& operator=(Controller&&) = delete;
    virtual ~Controller() = default;
    void handleEvent(std::unique_ptr<Event> pEvent) override;
    virtual void setView(IView*) override;
    virtual void setModel(std::shared_ptr<IModel>) override;

private:
    std::shared_ptr<IDocument> m_pDocument;
    std::shared_ptr<IGraphicPrimitive> m_pCurrentPrimitive;
    std::shared_ptr<IModel> m_pModel;
    IView* m_pView {nullptr};

    bool checkDocumentWithMessage();
};

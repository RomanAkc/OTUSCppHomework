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
};

class Controller : public IController {
public:
    Controller(IView* pView);
    Controller(const Controller&) = delete;
    Controller(Controller&&) = delete;
    Controller& operator=(const Controller&) = delete;
    Controller& operator=(Controller&&) = delete;
    virtual ~Controller() = default;
    void handleEvent(std::unique_ptr<Event> pEvent) override;

private:
    std::shared_ptr<IModel> m_pModel;
    IView* m_pView {nullptr};
};

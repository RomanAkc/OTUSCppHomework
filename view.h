#pragma once

class IView {
public:
    IView() = default;
    IView(const IView&) = delete;
    IView(IView&&) = delete;
    IView& operator=(const IView&) = delete;
    IView& operator=(IView&&) = delete;
    virtual ~IView() = default;

    virtual void showMainDlg() = 0;
    virtual void UpdateInterface() = 0;
};

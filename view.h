#pragma once
#include <string>
#include "primitives.h"

class IView {
public:
    IView() = default;
    IView(const IView&) = delete;
    IView(IView&&) = delete;
    IView& operator=(const IView&) = delete;
    IView& operator=(IView&&) = delete;
    virtual ~IView() = default;

    //paint interface
    virtual void showMainDlg() = 0;
    virtual void updateInterface() = 0;

    //dialog with user
    virtual void showErrorMsgBox(const std::string& sMessage) = 0;
    virtual std::string getFileName() = 0;
    virtual PrimitiveType showDlgSelectNewPrimitive() = 0;
    virtual std::pair<int, int> getCurrentCoordinates() = 0;

    //button clicks
    virtual void createNewDocButton() = 0;
    virtual void importDocButton() = 0;
    virtual void exportDocButton() = 0;
    virtual void addPrimitiveButton() = 0;
    virtual void removePrimitiveButton() = 0;
    virtual void selectMouseButton() = 0;
};

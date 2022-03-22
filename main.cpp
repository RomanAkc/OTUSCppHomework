#include <vector>

#include "primitives.h"
#include "document.h"
#include "event.h"
#include "view.h"
#include "controller.h"

class GraphicInterface : public IView {
public:
    GraphicInterface() {}
    GraphicInterface(const GraphicInterface&) = delete;
    GraphicInterface(GraphicInterface&&) = delete;
    GraphicInterface& operator=(const GraphicInterface&) = delete;
    GraphicInterface& operator=(GraphicInterface&&) = delete;
    virtual ~GraphicInterface() = default;

    void showMainDlg() override {
		//first show main dlg
	}

    void updateInterface() override {
        //update main dlg after model update
    }

    void showErrorMsgBox(const std::string&) override {
        //show message box with error
    }

    virtual std::string getFileName() override {
        //get file name from standard system choose file dlg
        return "1.txt";
    }

    PrimitiveType showDlgSelectNewPrimitive() override {
        // show dlg and select primitive
        return PrimitiveType::TRIANGLE;
    }

    std::pair<int, int> getCurrentCoordinates() override {
        // get coordinates of cursor
        return {0, 0};
    }

    //Button clicks:
    void createNewDocButton() override {
        m_pDocumentController->handleEvent(std::make_unique<Event>(Type::ButtonClick, Source::NEW_BUTTON));
    }

    void importDocButton() override {
        m_pDocumentController->handleEvent(std::make_unique<Event>(Type::ButtonClick, Source::IMPORT_BUTTON));
    }

    void exportDocButton() override {
        m_pDocumentController->handleEvent(std::make_unique<Event>(Type::ButtonClick, Source::EXPORT_BUTTON));
    }

    void addPrimitiveButton() override {
        m_pDocumentController->handleEvent(std::make_unique<Event>(Type::ButtonClick, Source::CREATE_PRIMITIVE_BUTTON));
    }

    void removePrimitiveButton() override {
        m_pDocumentController->handleEvent(std::make_unique<Event>(Type::ButtonClick, Source::DELETE_PRIMITIVE_BUTTON));
    }

    void selectMouseButton() override {
        m_pDocumentController->handleEvent(std::make_unique<Event>(Type::MouseButtonClick, Source::SELECT_PRIMITIVE));
    }

    void setController(std::shared_ptr<IController> pController) {
        m_pDocumentController = pController;
    }

private:
    std::shared_ptr<IController> m_pDocumentController;
};

int main(int, char **) {
    //Model
    std::shared_ptr<IModel> pModel(new DocumentModel());

    //View
    GraphicInterface interface;

    //Controller
    std::shared_ptr<IController> pController{new Controller()};

    //Links
    pController->setView(&interface);
    pController->setModel(pModel);
    interface.setController(pController);

    //show main dlg
    interface.showMainDlg();

    //Emulation user's actions
    interface.importDocButton();
    interface.addPrimitiveButton();
    interface.addPrimitiveButton();
    interface.removePrimitiveButton();
    interface.exportDocButton();

    return 0;
}

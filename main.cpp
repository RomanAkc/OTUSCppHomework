#include <iostream>
#include <vector>

#include "primitives.h"
#include "document.h"
#include "model.h"
#include "event.h"
#include "view.h"
#include "controller.h"


class GraphicInterface : public IView {
public:
	GraphicInterface() {
		m_pDocumentController = std::make_unique<Controller>(this);
	}
	GraphicInterface(const GraphicInterface&) = delete;
	GraphicInterface(GraphicInterface&&) = delete;
	GraphicInterface& operator=(const GraphicInterface&) = delete;
	GraphicInterface& operator=(GraphicInterface&&) = delete;
	virtual ~GraphicInterface() = default;

	virtual void showMainDlg() override {
		//show main dlg
	}

	void UpdateInterface() override {
		//update main dlg after model update
	}

	//Button clicks:
	void createNewButton() {
		m_pDocumentController->handleEvent(std::make_unique<Event>(Type::ButtonClick, Source::NEW_BUTTON));
	}

	void importDocButton() {
		m_pDocumentController->handleEvent(std::make_unique<Event>(Type::ButtonClick, Source::IMPORT_BUTTON));
	}

	void exportDocButton() {
		m_pDocumentController->handleEvent(std::make_unique<Event>(Type::ButtonClick, Source::EXPORT_BUTTON));
	}

	void addPrimitiveButton() {
		m_pDocumentController->handleEvent(std::make_unique<Event>(Type::ButtonClick, Source::DELETE_PRIMITIVE_BUTTON));
	}

	void removePrimitiveButton() {
		m_pDocumentController->handleEvent(std::make_unique<Event>(Type::ButtonClick, Source::CREATE_PRIMITIVE_BUTTON));
	}

	void selectMouseButton() {
		m_pDocumentController->handleEvent(std::make_unique<Event>(Type::MouseButtonClick, Source::SELECT_PRIMITIVE));
	}

private:
	std::unique_ptr<IController> m_pDocumentController;
};

int main(int, char **) {
	std::cout << "Hello, world!" << std::endl;
	return 0;
}

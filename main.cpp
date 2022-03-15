#include <iostream>
#include <vector>

enum class PrimitiveType {
	POINT,
	LINE,
	TRIANGLE
};

class IGraphicPrimitive {
	//All methods (ctor, copy/move, dctor etc.) - create by default 
};

class Point : public IGraphicPrimitive {

};

class Line : public IGraphicPrimitive {

};

class Triangle : public IGraphicPrimitive {

};

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
	virtual void addPrimitive(std::shared_ptr<IGraphicPrimitive> pPrimitive) override {
		m_vecPrimitives.push_back(pPrimitive);
	}
	virtual void delPrimitive(std::shared_ptr<IGraphicPrimitive> pPrimitive) override {
		m_vecPrimitives.erase(std::remove(m_vecPrimitives.begin(), m_vecPrimitives.end(), pPrimitive), m_vecPrimitives.end());
	}

	virtual std::shared_ptr<IGraphicPrimitive> getPrimitiveByPoint(int x, int y) override {
		if(m_vecPrimitives.empty())
			return nullptr;

		//get primitive by coordinates

		return m_vecPrimitives[0];
	}

private:
	std::vector<std::shared_ptr<IGraphicPrimitive>> m_vecPrimitives;
};


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

	void createDocument() override {
		m_pDocument = std::shared_ptr<IDocument>(new Document());
	}
	void importDocument() override {
		m_pDocument = std::shared_ptr<IDocument>(new Document());
	}
	void exportDocument() override {}
	void createPrimitive(PrimitiveType type) override {
		//Здесь создаем графический примитив
		if(auto p = createPrimitiveImpl(type))
			m_pDocument->addPrimitive(p);
	}

	void deletePrimitive(std::shared_ptr<IGraphicPrimitive> pPrimitive) override {
		m_pDocument->delPrimitive(pPrimitive);
	}

	std::shared_ptr<IGraphicPrimitive> selectPrimitive(int x, int y) override {
		return m_pDocument->getPrimitiveByPoint(x, y);
	}

private: 
	std::shared_ptr<IDocument> m_pDocument;

	std::shared_ptr<IGraphicPrimitive> createPrimitiveImpl(PrimitiveType type) {
		switch(type) {
		case PrimitiveType::POINT:
			return std::shared_ptr<IGraphicPrimitive>(new Point());
		case PrimitiveType::LINE:
			return std::shared_ptr<IGraphicPrimitive>(new Line());
		case PrimitiveType::TRIANGLE:
			return std::shared_ptr<IGraphicPrimitive>(new Triangle());
		}
		return nullptr;
	}
};



enum class Type {
	ButtonClick,
	MouseButtonClick,
};

enum class Source {
	NEW_BUTTON,
	IMPORT_BUTTON,
	EXPORT_BUTTON,
	CREATE_PRIMITIVE_BUTTON,
	DELETE_PRIMITIVE_BUTTON,
	SELECT_PRIMITIVE,
};

class Event final {
private:
	Type m_Type;
	Source m_Source;

public:
	Event() = delete;
	Event(Event&) = default;
	Event(Event&&) = default;
	Event& operator=(const Event&) = default;
	Event& operator=(Event&&) = default;
	Event(Type t, Source s) : m_Type(t), m_Source(s) {}

	Type getType() const {
		return m_Type;
	}

	Source getSource() const {
		return m_Source;
	}
};

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

class IView;

class Controller : public IController {
public:
	Controller(IView* pView) : m_pView(pView) {}
	Controller(const Controller&) = delete;
	Controller(Controller&&) = delete;
	Controller& operator=(const Controller&) = delete;
	Controller& operator=(Controller&&) = delete;
	virtual ~Controller() = default;

	virtual void handleEvent(std::unique_ptr<Event> pEvent) override {
		switch(pEvent->getSource()) {
		case Source::CREATE_PRIMITIVE_BUTTON:
			//m_pModel->createPrimitive(m_pDocument, );
			break;
		default:
			break;
		}
	}

private:
	std::shared_ptr<IModel> m_pModel;
	IView* m_pView {nullptr};
};

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

	void UpdateInterface() {
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

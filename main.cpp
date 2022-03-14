#include <iostream>
#include <vector>

enum class PrimitiveType {
	POINT,
	LINE,
	TRIANGLE
};

class IGraphicPrimitive {
	//Все методы (ctor, copy/move, dctor и т. п.) - создаются по дефолту, не будем их прописывать 
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

		//Получаем графический примитив по координате

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

	virtual std::shared_ptr<IDocument> createDocument() = 0;
	virtual std::shared_ptr<IDocument> importDocument() = 0;
	virtual void exportDocument(const std::shared_ptr<IDocument>& pDoc) = 0;
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

	std::shared_ptr<IDocument> createDocument() override {
		//Здесь создаем новый документ
		return std::shared_ptr<IDocument>(new Document());
	}
	std::shared_ptr<IDocument> importDocument() override {
		//Здесь испортирует документ из файла
		return std::shared_ptr<IDocument>(new Document());
	}
	virtual void exportDocument(const std::shared_ptr<IDocument>& pDoc) override {
		//Экспортируем документ в файл
	}
	virtual void createPrimitive(std::shared_ptr<IDocument> pDoc, PrimitiveType type) override {
		//Здесь создаем графический примитив
		if(auto p = createPrimitive(type))
			pDoc->addPrimitive(p);
	}

	virtual void deletePrimitive(std::shared_ptr<IDocument> pDoc, std::shared_ptr<IGraphicPrimitive> pPrimitive) {
		//Удаляем графический примитив
		pDoc->delPrimitive(pPrimitive);
	}

	virtual std::shared_ptr<IGraphicPrimitive> selectPrimitive(std::shared_ptr<IDocument> pDoc, int x, int y) {
		//Получаем текущий выбранный графический примитив
		return pDoc->getPrimitiveByPoint(x, y);
	}

private: 
	std::shared_ptr<IGraphicPrimitive> createPrimitive(PrimitiveType type) {
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

class Controller : public IController {
public:
	virtual void handleEvent(std::unique_ptr<Event> pEvent) override {
		if(!isCanHandle(pEvent)) {
			showMessageError("Need document");
			return;
		}

		handleEventImpl(pEvent);
	}

private:
	void handleEventImpl(const std::unique_ptr<Event>& pEvent) {
		;
	}

	bool isCanHandle(const std::unique_ptr<Event>& pEvent) const {
		return m_pDocument || !isNeedDocument(pEvent);
	}

	bool isNeedDocument(const std::unique_ptr<Event>& pEvent) const {
		return pEvent->getSource() != Source::NEW_BUTTON
			&& pEvent->getSource() != Source::IMPORT_BUTTON;
	}
	void showMessageError(const std::string& sMessage) {
		//Здесь показываем MessageBox с ошибкой
	}

private:
	std::shared_ptr<IDocument> m_pDocument;
	std::shared_ptr<IModel> m_pModel;
};

class GraphicInterface {
public:
	GraphicInterface() {
		m_pDocumentController = std::make_unique<Controller>();
	}
	GraphicInterface(const GraphicInterface&) = delete;
	GraphicInterface(GraphicInterface&&) = delete;
	GraphicInterface& operator=(const GraphicInterface&) = delete;
	GraphicInterface& operator=(GraphicInterface&&) = delete;
	virtual ~GraphicInterface() = default;

	void showMainDlg() {
		//Здесь отображаем главный диалог
	}

	void UpdateInterface() {
		//Обновляем окно после изменения модели
	}

	//Обработчики кнопок
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









	/*std::shared_ptr<IDocument> m_pDocument;



	std::shared_ptr<IDocument> createNewDocument() {
		//Здесь добавляем новый документ
	}

	std::shared_ptr<IDocument> importDocumentFromFile() {
		//Здесь добавляем новый документ
	}

	void epxportDocumentToFile(const std::shared_ptr<IDocument>& document) {
		//Здесь добавляем новый документ
	}

	std::unique_ptr<IGraphicPrimitive> createGraphicPrimitive() {
		//Здесь создаем графический примитив
	}

	void removeGraphicPrimitive(const std::shared_ptr<IDocument>& document) {
		;
	}*/


};

int main(int, char **) {
	std::cout << "Hello, world!" << std::endl;
	return 0;
}

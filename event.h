#pragma once

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
    Event(Type t, Source s);
    Type getType() const;
    Source getSource() const ;
};
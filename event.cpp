#include "event.h"

Event::Event(Type t, Source s) : m_Type(t), m_Source(s) {}

Type Event::getType() const {
    return m_Type;
}

Source Event::getSource() const {
    return m_Source;
}


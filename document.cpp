#include "document.h"
#include <algorithm>


void Document::addPrimitive(std::shared_ptr<IGraphicPrimitive> pPrimitive) {
    m_vecPrimitives.push_back(pPrimitive);
}
void Document::delPrimitive(std::shared_ptr<IGraphicPrimitive> pPrimitive) {
    m_vecPrimitives.erase(std::remove(m_vecPrimitives.begin(), m_vecPrimitives.end(), pPrimitive), m_vecPrimitives.end());
}

std::shared_ptr<IGraphicPrimitive> Document::getPrimitiveByPoint(int, int) {
    if(m_vecPrimitives.empty())
        return nullptr;

    //get primitive by coordinates

    return m_vecPrimitives[0];
}

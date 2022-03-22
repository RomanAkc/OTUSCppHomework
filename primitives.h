#pragma once

enum class PrimitiveType {
    NOTHING,
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

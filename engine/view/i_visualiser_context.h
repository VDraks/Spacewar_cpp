#pragma once

#include <string>

#include "math/vec_2.h"

namespace view {

class IVisualiserContext {
public:
    virtual ~IVisualiserContext() = default;

    virtual void drawText(const std::string& text, const math::Vec2& pos) = 0;
};

} // namespace view
#pragma once

#include "view/i_visualiser_context.h"

namespace view {

class IVisualiser {
public:
    virtual ~IVisualiser() = default;

    virtual void render(IVisualiserContext* context) = 0;
};

} // namespace view
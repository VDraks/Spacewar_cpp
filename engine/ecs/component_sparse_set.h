#pragma once

#include "component_id.h"
#include "sparse_set.h"

namespace ecs {
template<typename T>
using ComponentSparseSet = SparseSet<ComponentId, T>;
} // namespace ecs
//
// Created by ¡ı”ËÀ≥ on 2019-01-17.
//

#include "Objects.hpp"

namespace GL {
	namespace D {
		thread_local Context* context = nullptr;
	}

	Context::Context() {

	}

	VkDevice Context::GetDevice() {
		return nullptr;
	}

	void Context::SetError(int error) {

	}

	VkPhysicalDeviceMemoryProperties& Context::GetPhysicalMemoryProperties() { return _PhysicalMemoryProperties; }

	VkCommandBuffer Context::GetCommandBuffer() {
		return nullptr;
	}

	VkPipelineCache Context::GetPipelineCache() { return nullptr;  }
}

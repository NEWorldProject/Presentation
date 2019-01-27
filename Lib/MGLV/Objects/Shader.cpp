#include "Objects.hpp"

namespace GL {
    namespace D {
        extern thread_local Context* context;
    }

	namespace {
		VkShaderStageFlagBits TranslateStage(GLenum type) noexcept {
			switch (type) {
			case GL_FRAGMENT_SHADER: return VK_SHADER_STAGE_FRAGMENT_BIT;
			case GL_VERTEX_SHADER: return VK_SHADER_STAGE_VERTEX_BIT;
			default: return VK_SHADER_STAGE_ALL;
			}
		}

		int GetShaderSlot(VkShaderStageFlagBits type) noexcept {
			switch (type) {
			case VK_SHADER_STAGE_VERTEX_BIT: return 0;
			case VK_SHADER_STAGE_FRAGMENT_BIT: return 1;
			default: return -1;
			}
		}
	}

    Shader::Shader(GLenum type, const void* binary, GLsizei length, const char* entry) noexcept {
		VkShaderModuleCreateInfo createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		createInfo.codeSize = length;
		createInfo.pCode = reinterpret_cast<const uint32_t*>(binary);
		vkCreateShaderModule(D::context->GetDevice(), &createInfo, nullptr, &_Module);
		_StageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		_StageInfo.stage = TranslateStage(type);
		_StageInfo.module = _Module;
		_StageInfo.pName = entry;
    }

	Shader::~Shader() noexcept {
		vkDestroyShaderModule(D::context->GetDevice(), _Module, nullptr);
    }

	Program::Program() noexcept = default;

	Program::~Program() noexcept = default;

    void Program::AttachShader(const Shader& shader) noexcept {
		_Slot[GetShaderSlot(shader.GetStage().stage)] = std::addressof(shader);
    }

    void Program::DetachShader(const Shader& shader) noexcept {
		if (auto& slot = _Slot[GetShaderSlot(shader.GetStage().stage)]; slot == std::addressof(shader))
			slot = nullptr;
    }

    std::vector<VkPipelineShaderStageCreateInfo> Program::DumpStages() const noexcept {
		std::vector<VkPipelineShaderStageCreateInfo> shaderStages;
		for (auto x : _Slot)
			if (x)
				shaderStages.push_back(x->GetStage());
		return shaderStages;
    }
}

GLuint glvCreateShader(GLenum type, const void* binary, GLsizei length, const char* entry) noexcept {
	return reinterpret_cast<GLuint>(new GL::Shader(type, binary, length, entry));
}

void glvDeleteShader(GLuint shader) noexcept {
	delete reinterpret_cast<GL::Shader*>(shader);
}

GLuint glvCreateProgram() noexcept {
	return reinterpret_cast<GLuint>(new GL::Program());
}

void glvDeleteProgram(GLuint program) noexcept {
	delete reinterpret_cast<GL::Program*>(program);
}

void glvAttachShader(GLuint program, GLuint shader) noexcept {
	reinterpret_cast<GL::Program*>(program)->AttachShader(*reinterpret_cast<const GL::Shader*>(shader));
}

void glvDetachShader(GLuint program, GLuint shader) noexcept {
	reinterpret_cast<GL::Program*>(program)->DetachShader(*reinterpret_cast<const GL::Shader*>(shader));
}

#include <limits>
#include <MGLV/Functions.h>

namespace GL {
    namespace D {
        extern thread_local Context* _Context;
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

    void Shader::CreateMGLV(GLenum type, const void* binary, GLsizei length, const char* entry) noexcept {
		VkShaderModuleCreateInfo createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		createInfo.codeSize = length;
		createInfo.pCode = reinterpret_cast<const uint32_t*>(binary);
		vkCreateShaderModule(D::_Context->GetDevice(), &createInfo, nullptr, &_Module);
		_StageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		_StageInfo.stage = TranslateStage(type);
		_StageInfo.module = _Module;
		_StageInfo.pName = entry;
    }

	void Shader::Delete() noexcept {
		vkDestroyShaderModule(D::_Context->GetDevice(), _Module, nullptr);
		_Module = nullptr;
    }

    GLuint Program::Create() noexcept {
		for (auto& slot : _Slots) slot = nullptr;
    }

    void Program::Delete() noexcept {}

    void Program::AttachShader(const Shader& shader) noexcept {
		_Slots[GetShaderSlot(shader._StageInfo.stage)] = std::addressof(shader);
    }

    void Program::DetachShader(const Shader& shader) noexcept {
		if (auto& slot = _Slots[GetShaderSlot(shader._StageInfo.stage)]; slot == std::addressof(shader))
			slot = nullptr;
    }
}

GLuint glCreateShaderMGLV(GLenum type, const void* binary, GLsizei length, const char* entry) noexcept {
	auto shader = new GL::Shader();
	shader->CreateMGLV(type, binary, length, entry);
	return reinterpret_cast<GLuint>(shader);
}

void glDeleteShader(GLuint shader) noexcept {
	auto obj = reinterpret_cast<GL::Shader*>(shader);
	obj->Delete();
	delete obj;
}

GLuint glCreateProgram() noexcept {
	auto shader = new GL::Program();
	shader->Create();
	return reinterpret_cast<GLuint>(shader);
}

void glDeleteProgram(GLuint program) noexcept {
	auto obj = reinterpret_cast<GL::Program*>(program);
	obj->Delete();
	delete obj;
}

void glAttachShader(GLuint program, GLuint shader) noexcept {
	reinterpret_cast<GL::Program*>(program)->AttachShader(*reinterpret_cast<const GL::Shader*>(shader));
}

void glDetachShader(GLuint program, GLuint shader) noexcept {
	reinterpret_cast<GL::Program*>(program)->DetachShader(*reinterpret_cast<const GL::Shader*>(shader));
}

#pragma once
#include <MGLV/Functions.h>
#include <vulkan/vulkan.h>
#include <array>
#include <limits>
#include <vector>

namespace GL {
	class Context {
	public:
		Context();
		VkDevice GetDevice();
		void SetError(int error);
		VkPhysicalDeviceMemoryProperties& GetPhysicalMemoryProperties();
		VkCommandBuffer GetCommandBuffer();
		VkPipelineCache GetPipelineCache();
	private:
		VkPhysicalDeviceMemoryProperties _PhysicalMemoryProperties;
	};

	class Texture {
	public:
		void CreateTextures(GLenum target) noexcept;
		void Buffer(GLenum internalFormat, GLuint buffer) noexcept;
		void BufferRange(GLenum internalFormat, GLuint buffer, GLintptr offset, GLsizeiptr size) noexcept;
		void Storage1D(GLsizei levels, GLenum internalFormat, GLsizei width) noexcept;
		void Storage2D(GLsizei levels, GLenum internalFormat, GLsizei width, GLsizei height) noexcept;
		void Storage3D(GLsizei levels, GLenum internalFormat, GLsizei width, GLsizei height, GLsizei depth) noexcept;
		void Storage2DMultisample(GLsizei samples, GLenum internalFormat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations) noexcept;
		void Storage3DMultisample(GLsizei samples, GLenum internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations) noexcept;
		void SubImage1D(GLint level, GLint xOffset, GLsizei width, GLenum format, GLenum type, const void *pixels) noexcept;
		void SubImage2D(GLint level, GLint xOffset, GLint yOffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void *pixels) noexcept;
		void SubImage3D(GLint level, GLint xOffset, GLint yOffset, GLint zOffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void *pixels) noexcept;
		void CompressedSubImage1D(GLint level, GLint xOffset, GLsizei width, GLenum format, GLsizei imageSize, const void *data) noexcept;
		void CompressedSubImage2D(GLint level, GLint xOffset, GLint yOffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void *data) noexcept;
		void CompressedSubImage3D(GLint level, GLint xOffset, GLint yOffset, GLint zOffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void *data) noexcept;
		void CopySubImage1D(GLint level, GLint xOffset, GLint x, GLint y, GLsizei width) noexcept;
		void CopySubImage2D(GLint level, GLint xOffset, GLint yOffset, GLint x, GLint y, GLsizei width, GLsizei height) noexcept;
		void CopySubImage3D(GLint level, GLint xOffset, GLint yOffset, GLint zOffset, GLint x, GLint y, GLsizei width, GLsizei height) noexcept;
		void Parameterf(GLenum pName, GLfloat param) noexcept;
		void Parameterfv(GLenum pName, const GLfloat *param) noexcept;
		void Parameteri(GLenum pName, GLint param) noexcept;
		void ParameterIiv(GLenum pName, const GLint *params) noexcept;
		void ParameterIuiv(GLenum pName, const GLuint *params) noexcept;
		void Parameteriv(GLenum pName, const GLint *param) noexcept;
		void GenerateMipmap() noexcept;
		void BindUnit(GLuint unit, GLuint texture) noexcept;
		void GetImage(GLint level, GLenum format, GLenum type, GLsizei bufSize, void *pixels) noexcept;
		void GetCompressedImage(GLint level, GLsizei bufSize, void *pixels) noexcept;
		void GetLevelParameterfv(GLint level, GLenum pName, GLfloat *params) noexcept;
		void GetLevelParameteriv(GLint level, GLenum pName, GLint *params) noexcept;
		void GetParameterfv(GLenum pName, GLfloat *params) noexcept;
		void GetParameterIiv(GLenum pName, GLint *params) noexcept;
		void GetParameterIuiv(GLenum pName, GLuint *params) noexcept;
		void GetParameteriv(GLenum pName, GLint *params) noexcept;
	};

	class Buffer {
	public:
		constexpr Buffer() noexcept = default;
		void Create() noexcept;
		void Delete() noexcept;
		void Storage(GLsizeiptr size, const void *data, GLbitfield flags) noexcept;
		void SubData(GLintptr offset, GLsizeiptr size, const void *data) noexcept;
		void ClearData(GLuint unitSize, const void* data) noexcept;
		void ClearSubData(GLuint unitSize, GLintptr offset, GLsizeiptr size, const void* data) noexcept;
		void ZeroData() noexcept;
		void ZeroSubData(GLintptr offset, GLsizeiptr size) noexcept;
		void * Map(GLenum access) noexcept;
		void * MapRange(GLintptr offset, GLsizeiptr length, GLbitfield access) noexcept;
		GLboolean Unmap() noexcept;
		void FlushMappedRange(GLintptr offset, GLsizeiptr length) noexcept;
		static void CopySubData(Buffer& read, Buffer& write, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size) noexcept;
	private:
		VkBuffer _Buffer = nullptr;
		VkDeviceMemory _Memory = nullptr;
	};

	class Shader final {
	public:
		Shader(GLenum type, const void* binary, GLsizei length, const char* entry) noexcept;
		~Shader() noexcept;
		const VkPipelineShaderStageCreateInfo& GetStage() const noexcept { return _StageInfo; }
	private:
		VkShaderModule _Module{ nullptr };
		VkPipelineShaderStageCreateInfo _StageInfo{};
	};

	class Program final {
	public:
		Program() noexcept;
		~Program() noexcept;
		void AttachShader(const Shader& shader) noexcept;
		void DetachShader(const Shader& shader) noexcept;
		std::vector<VkPipelineShaderStageCreateInfo> DumpStages() const noexcept;
	private:
		std::array<const Shader*, 8> _Slot{ 
			nullptr, nullptr, nullptr, nullptr, 
			nullptr, nullptr, nullptr, nullptr
		}; // Just in case more is added in the future
	};

	class PipelineLayout final {
	public:
		PipelineLayout() noexcept;
		~PipelineLayout() noexcept;
		void Compile() noexcept;
		void AddBinding(GLuint binding, GLenum type) noexcept;
		VkPipelineLayout GetLayout() const noexcept { return reinterpret_cast<VkPipelineLayout>(_Layout); }
	private:
		uintptr_t _Layout = 0;
		VkDescriptorSetLayout _Sets = nullptr;
	};

	class Pipeline final {
	public:
		Pipeline() noexcept;
		~Pipeline() noexcept;
		void ElementBuffer(GLuint buffer) noexcept;
		// Setup Group
		void Compile() noexcept;
		void AttachProgram(const Program& program) noexcept;
		void AttachLayout(const PipelineLayout& layout) noexcept;
		void AddVertexBinding(GLuint index, GLsizei stride, GLboolean instanceFeed) noexcept;
		void AddAttribFormat(GLuint index, GLuint binding, GLint size, GLenum type, GLboolean normalized, GLuint offset) noexcept;
		void AddAttribIFormat(GLuint index, GLuint binding, GLint size, GLenum type, GLuint offset) noexcept;
		void AddAttribLFormat(GLuint index, GLuint binding, GLint size, GLenum type, GLuint offset) noexcept;
		// Dynamic Group
		void VertexBuffer(GLuint bindingIndex, Buffer& buffer) noexcept;
		void VertexBuffers(GLuint first, GLsizei count, const Buffer* buffers) noexcept;
		void BindingDivisor(GLuint bindingIndex, GLuint divisor) noexcept;
	private:
		uintptr_t _Pipeline = 0;
		std::vector<VkBuffer*> _Binds;
	};
}
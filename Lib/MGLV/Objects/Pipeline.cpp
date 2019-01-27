#include <limits>
#include "Objects.hpp"

namespace GL {
	namespace D {
		extern thread_local Context* context;
	}

	namespace {
		VkFormat GetFormat(const GLint size, const GLenum type, const bool normalized) noexcept {
			if (normalized) {
				switch (size) {
				case 1: switch (type) {
				case GL_UNSIGNED_BYTE: return VK_FORMAT_R8_UNORM;
				case GL_BYTE: return VK_FORMAT_R8_SNORM;
				case GL_UNSIGNED_SHORT: return VK_FORMAT_R16_UNORM;
				case GL_SHORT: return VK_FORMAT_R16_SNORM;
				default: return VK_FORMAT_UNDEFINED;
				}
				case 2: switch (type) {
				case GL_UNSIGNED_BYTE: return VK_FORMAT_R8G8_UNORM;
				case GL_BYTE: return VK_FORMAT_R8G8_SNORM;
				case GL_UNSIGNED_SHORT: return VK_FORMAT_R16G16_UNORM;
				case GL_SHORT: return VK_FORMAT_R16G16_SNORM;
				default: return VK_FORMAT_UNDEFINED;
				}
				case 3: switch (type) {
				case GL_UNSIGNED_BYTE: return VK_FORMAT_R8G8B8_UNORM;
				case GL_BYTE: return VK_FORMAT_R8G8B8_SNORM;
				case GL_UNSIGNED_SHORT: return VK_FORMAT_R16G16B16_UNORM;
				case GL_SHORT: return VK_FORMAT_R16G16B16_SNORM;
				default: return VK_FORMAT_UNDEFINED;
				}
				case 4: switch (type) {
				case GL_UNSIGNED_BYTE: return VK_FORMAT_R8G8B8A8_UNORM;
				case GL_BYTE: return VK_FORMAT_R8G8B8A8_SNORM;
				case GL_UNSIGNED_SHORT: return VK_FORMAT_R16G16B16A16_UNORM;
				case GL_SHORT: return VK_FORMAT_R16G16B16A16_SNORM;
				default: return VK_FORMAT_UNDEFINED;
				}
				default: return VK_FORMAT_UNDEFINED;
				}
			}
			switch (size) {
			case 1: switch (type) {
			case GL_UNSIGNED_BYTE: return VK_FORMAT_R8_USCALED;
			case GL_BYTE: return VK_FORMAT_R8_SSCALED;
			case GL_UNSIGNED_SHORT: return VK_FORMAT_R16_USCALED;
			case GL_SHORT: return VK_FORMAT_R16_SSCALED;
			default: return VK_FORMAT_UNDEFINED;
			}
			case 2: switch (type) {
			case GL_UNSIGNED_BYTE: return VK_FORMAT_R8G8_USCALED;
			case GL_BYTE: return VK_FORMAT_R8G8_SSCALED;
			case GL_UNSIGNED_SHORT: return VK_FORMAT_R16G16_USCALED;
			case GL_SHORT: return VK_FORMAT_R16G16_SSCALED;
			default: return VK_FORMAT_UNDEFINED;
			}
			case 3: switch (type) {
			case GL_UNSIGNED_BYTE: return VK_FORMAT_R8G8B8_USCALED;
			case GL_BYTE: return VK_FORMAT_R8G8B8_SSCALED;
			case GL_UNSIGNED_SHORT: return VK_FORMAT_R16G16B16_USCALED;
			case GL_SHORT: return VK_FORMAT_R16G16B16_SSCALED;
			default: return VK_FORMAT_UNDEFINED;
			}
			case 4: switch (type) {
			case GL_UNSIGNED_BYTE: return VK_FORMAT_R8G8B8A8_USCALED;
			case GL_BYTE: return VK_FORMAT_R8G8B8A8_SSCALED;
			case GL_UNSIGNED_SHORT: return VK_FORMAT_R16G16B16A16_USCALED;
			case GL_SHORT: return VK_FORMAT_R16G16B16A16_SSCALED;
			default: return VK_FORMAT_UNDEFINED;
			}
			default: return VK_FORMAT_UNDEFINED;
			}
		}

		VkFormat GetFormatI(const GLint size, const GLenum type) noexcept {
			switch (size) {
			case 1: switch (type) {
			case GL_UNSIGNED_BYTE: return VK_FORMAT_R8_UINT;
			case GL_BYTE: return VK_FORMAT_R8_SINT;
			case GL_UNSIGNED_SHORT: return VK_FORMAT_R16_UINT;
			case GL_SHORT: return VK_FORMAT_R16_SINT;
			case GL_UNSIGNED_INT: return VK_FORMAT_R32_UINT;
			case GL_INT: return VK_FORMAT_R32_SINT;
			default: return VK_FORMAT_UNDEFINED;
			}
			case 2:switch (type) {
			case GL_UNSIGNED_BYTE: return VK_FORMAT_R8G8_UINT;
			case GL_BYTE: return VK_FORMAT_R8G8_SINT;
			case GL_UNSIGNED_SHORT: return VK_FORMAT_R16G16_UINT;
			case GL_SHORT: return VK_FORMAT_R16G16_SINT;
			case GL_UNSIGNED_INT: return VK_FORMAT_R32G32_UINT;
			case GL_INT: return VK_FORMAT_R32G32_SINT;
			default: return VK_FORMAT_UNDEFINED;
			}
			case 3:switch (type) {
			case GL_UNSIGNED_BYTE: return VK_FORMAT_R8G8B8_UINT;
			case GL_BYTE: return VK_FORMAT_R8G8B8_SINT;
			case GL_UNSIGNED_SHORT: return VK_FORMAT_R16G16B16_UINT;
			case GL_SHORT: return VK_FORMAT_R16G16B16_SINT;
			case GL_UNSIGNED_INT: return VK_FORMAT_R32G32B32_UINT;
			case GL_INT: return VK_FORMAT_R32G32B32_SINT;
			default: return VK_FORMAT_UNDEFINED;
			}
			case 4:switch (type) {
			case GL_UNSIGNED_BYTE: return VK_FORMAT_R8G8B8A8_UINT;
			case GL_BYTE: return VK_FORMAT_R8G8B8A8_SINT;
			case GL_UNSIGNED_SHORT: return VK_FORMAT_R16G16B16A16_UINT;
			case GL_SHORT: return VK_FORMAT_R16G16B16A16_SINT;
			case GL_UNSIGNED_INT: return VK_FORMAT_R32G32B32A32_UINT;
			case GL_INT: return VK_FORMAT_R32G32B32A32_SINT;
			default: return VK_FORMAT_UNDEFINED;
			}
			default: return VK_FORMAT_UNDEFINED;
			}
		}

		VkFormat GetFormatF(const GLint size, const GLenum type) noexcept {
			switch (size) {
			case 1: switch (type) {
			case GL_HALF_FLOAT: return VK_FORMAT_R16_SFLOAT;
			case GL_FLOAT: return VK_FORMAT_R32_SFLOAT;
			case GL_DOUBLE: return VK_FORMAT_R64_SFLOAT;
			default: return VK_FORMAT_UNDEFINED;
			}
			case 2:switch (type) {
			case GL_HALF_FLOAT: return VK_FORMAT_R16G16_SFLOAT;
			case GL_FLOAT: return VK_FORMAT_R32G32_SFLOAT;
			case GL_DOUBLE: return VK_FORMAT_R64G64_SFLOAT;
			default: return VK_FORMAT_UNDEFINED;
			}
			case 3:switch (type) {
			case GL_HALF_FLOAT: return VK_FORMAT_R16G16B16_SFLOAT;
			case GL_FLOAT: return VK_FORMAT_R32G32B32_SFLOAT;
			case GL_DOUBLE: return VK_FORMAT_R64G64B64_SFLOAT;
			default: return VK_FORMAT_UNDEFINED;
			}
			case 4:switch (type) {
			case GL_HALF_FLOAT: return VK_FORMAT_R16G16B16A16_SFLOAT;
			case GL_FLOAT: return VK_FORMAT_R32G32B32A32_SFLOAT;
			case GL_DOUBLE: return VK_FORMAT_R64G64B64A64_SFLOAT;
			default: return VK_FORMAT_UNDEFINED;
			}
			default: return VK_FORMAT_UNDEFINED;
			}
		}

		struct LayoutCreate final {
			std::vector<VkDescriptorSetLayoutBinding> Bindings;
		};

		struct PipelineCreate final {
			std::vector<VkVertexInputAttributeDescription> Attribs;
			std::vector<VkVertexInputBindingDescription> Bindings;
			const Program* Program = nullptr;
			const PipelineLayout* Layout = nullptr;

			VkVertexInputAttributeDescription& PushAttrib(GLuint index) noexcept {
				Attribs.emplace_back().location = static_cast<uint32_t>(index);
				return Attribs.back();
			}

			VkVertexInputBindingDescription& PushBinding(GLuint index) noexcept {
				Bindings.emplace_back().binding = static_cast<uint32_t>(index);
				return Bindings.back();
			}
		};
	}

	PipelineLayout::PipelineLayout() noexcept {
		_Layout = reinterpret_cast<uintptr_t>(new LayoutCreate) + 1;
	}

	PipelineLayout::~PipelineLayout() noexcept {
		if (_Layout & 1) {
			delete reinterpret_cast<LayoutCreate*>(_Layout - 1);
		}
		else {
			vkDestroyPipelineLayout(D::context->GetDevice(), reinterpret_cast<VkPipelineLayout>(_Layout), nullptr);
			vkDestroyDescriptorSetLayout(D::context->GetDevice(), _Sets, nullptr);
		}
	}

	void PipelineLayout::Compile() noexcept {
		if (_Layout & 1) {
			auto obj = reinterpret_cast<LayoutCreate*>(_Layout - 1);
			VkDescriptorSetLayoutCreateInfo descriptorLayout = {};
			descriptorLayout.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
			descriptorLayout.pNext = nullptr;
			descriptorLayout.bindingCount = obj->Bindings.size();
			descriptorLayout.pBindings = obj->Bindings.data();
			vkCreateDescriptorSetLayout(D::context->GetDevice(), &descriptorLayout, nullptr, &_Sets);
			delete reinterpret_cast<LayoutCreate*>(_Layout - 1);
			VkPipelineLayoutCreateInfo layoutCreateInfo = {};
			layoutCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
			layoutCreateInfo.pNext = nullptr;
			layoutCreateInfo.pushConstantRangeCount = 0;
			layoutCreateInfo.pPushConstantRanges = nullptr;
			layoutCreateInfo.setLayoutCount = 1;
			layoutCreateInfo.pSetLayouts = &_Sets;
			vkCreatePipelineLayout(D::context->GetDevice(), &layoutCreateInfo, nullptr,
				reinterpret_cast<VkPipelineLayout*>(&_Layout));
		}
	}

	void PipelineLayout::AddBinding(GLuint binding, GLenum type) noexcept {
		static constexpr auto Convert = [](const GLenum type) noexcept->VkDescriptorType {
			switch (type) {
			case GL_UNIFORM_BUFFER: return VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
			default: return VK_DESCRIPTOR_TYPE_END_RANGE;
			}
		};
		if (_Layout & 1) {
			auto obj = reinterpret_cast<LayoutCreate*>(_Layout - 1);
			VkDescriptorSetLayoutBinding bind;
			bind.binding = binding;
			bind.descriptorType = Convert(type);
			bind.descriptorCount = 1;
			bind.stageFlags = VK_SHADER_STAGE_ALL;
			bind.pImmutableSamplers = nullptr;
			obj->Bindings.push_back(bind);
		}
	}

	Pipeline::Pipeline() noexcept {
		_Pipeline = reinterpret_cast<uintptr_t>(new PipelineCreate) + 1;
	}

	Pipeline::~Pipeline() noexcept {
		if (_Pipeline & 1)
			delete reinterpret_cast<PipelineCreate*>(_Pipeline - 1);
		else
			vkDestroyPipeline(D::context->GetDevice(), reinterpret_cast<VkPipeline>(_Pipeline), nullptr);
	}

	void Pipeline::ElementBuffer(GLuint buffer) noexcept {}

	void Pipeline::Compile() noexcept {
		if (_Pipeline & 1) {
			auto obj = reinterpret_cast<PipelineCreate*>(_Pipeline - 1);
			auto shaderStages = obj->Program->DumpStages();

			// vertex assembly
			VkPipelineVertexInputStateCreateInfo vertexInputInfo = {};
			vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
			vertexInputInfo.vertexBindingDescriptionCount = obj->Bindings.size();
			vertexInputInfo.vertexAttributeDescriptionCount = obj->Attribs.size();
			vertexInputInfo.pVertexBindingDescriptions = obj->Bindings.data();
			vertexInputInfo.pVertexAttributeDescriptions = obj->Attribs.data();

			VkPipelineInputAssemblyStateCreateInfo inputAssembly = {};
			inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
			inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
			inputAssembly.primitiveRestartEnable = VK_FALSE;

			// render state
			VkDynamicState dynamicStateEnables[VK_DYNAMIC_STATE_RANGE_SIZE];
			VkPipelineDynamicStateCreateInfo dynamicState = {};
			memset(dynamicStateEnables, 0, sizeof dynamicStateEnables);
			dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
			dynamicState.pNext = nullptr;
			dynamicState.pDynamicStates = dynamicStateEnables;
			dynamicState.dynamicStateCount = 0;

			VkPipelineViewportStateCreateInfo viewportState = {};
			viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
			viewportState.pNext = nullptr;
			viewportState.flags = 0;
			viewportState.viewportCount = 1;
			dynamicStateEnables[dynamicState.dynamicStateCount++] = VK_DYNAMIC_STATE_VIEWPORT;
			viewportState.scissorCount = 1;
			dynamicStateEnables[dynamicState.dynamicStateCount++] = VK_DYNAMIC_STATE_SCISSOR;
			viewportState.pScissors = nullptr;
			viewportState.pViewports = nullptr;

			// TODO: Specify Blending Methods in Creation Info
			// TODO: Figure which dynamic stencil states are needed
			VkPipelineColorBlendAttachmentState colorBlendAttachment = {};
			colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
			colorBlendAttachment.blendEnable = VK_FALSE;

			VkPipelineColorBlendStateCreateInfo colorBlending = {};
			colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
			colorBlending.logicOpEnable = VK_FALSE;
			colorBlending.logicOp = VK_LOGIC_OP_COPY;
			colorBlending.attachmentCount = 1;
			colorBlending.pAttachments = &colorBlendAttachment;
			colorBlending.blendConstants[0] = 0.0f;
			colorBlending.blendConstants[1] = 0.0f;
			colorBlending.blendConstants[2] = 0.0f;
			colorBlending.blendConstants[3] = 0.0f;

			VkPipelineRasterizationStateCreateInfo rasterizer = {};
			rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
			rasterizer.depthClampEnable = VK_FALSE;
			rasterizer.rasterizerDiscardEnable = VK_FALSE;
			rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
			rasterizer.lineWidth = 1.0f;
			rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
			rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;
			rasterizer.depthBiasEnable = VK_FALSE;

			VkPipelineMultisampleStateCreateInfo multisampling = {};
			multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
			multisampling.sampleShadingEnable = VK_FALSE;
			multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

			VkGraphicsPipelineCreateInfo pipelineInfo = {};
			pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
			pipelineInfo.stageCount = shaderStages.size();
			pipelineInfo.pStages = shaderStages.data();
			pipelineInfo.pVertexInputState = &vertexInputInfo;
			pipelineInfo.pInputAssemblyState = &inputAssembly;
			pipelineInfo.pViewportState = &viewportState;
			pipelineInfo.pRasterizationState = &rasterizer;
			pipelineInfo.pMultisampleState = &multisampling;
			pipelineInfo.pColorBlendState = &colorBlending;
			pipelineInfo.layout = obj->Layout->GetLayout();
			pipelineInfo.renderPass = nullptr; // TODO: supply this with a render pass object
			pipelineInfo.subpass = 0;
			pipelineInfo.basePipelineHandle = nullptr;

			vkCreateGraphicsPipelines(D::context->GetDevice(), D::context->GetPipelineCache(), 1, 
				&pipelineInfo, nullptr, reinterpret_cast<VkPipeline*>(&_Pipeline));
			delete obj;
		}
	}

	void Pipeline::AttachProgram(const Program& program) noexcept {
		if (_Pipeline & 1) {
			reinterpret_cast<PipelineCreate*>(_Pipeline - 1)->Program = std::addressof(program);
		}
	}

	void Pipeline::AttachLayout(const PipelineLayout& layout) noexcept {
		if (_Pipeline & 1) {
			reinterpret_cast<PipelineCreate*>(_Pipeline - 1)->Layout = std::addressof(layout);
		}
	}

	void Pipeline::VertexBuffer(GLuint bindingIndex, Buffer& buffer) noexcept {
	}

	void Pipeline::VertexBuffers(GLuint first, GLsizei count, const Buffer* buffers) noexcept {
	}

	void Pipeline::AddVertexBinding(GLuint index, GLsizei stride, GLboolean instanceFeed) noexcept {
		if (_Pipeline & 1) {
			auto& binding = reinterpret_cast<PipelineCreate*>(_Pipeline - 1)->PushBinding(index);
			binding.stride = static_cast<uint32_t>(stride);
			binding.inputRate = instanceFeed ? VK_VERTEX_INPUT_RATE_INSTANCE : VK_VERTEX_INPUT_RATE_VERTEX;
		}
	}

    void Pipeline::AddAttribFormat(GLuint index, GLuint binding, GLint size, GLenum type, GLboolean normalized,
            GLuint offset) noexcept {
		if (_Pipeline & 1) {
			auto& attr = reinterpret_cast<PipelineCreate*>(_Pipeline - 1)->PushAttrib(index);
			attr.format = GetFormat(size, type, normalized);
			attr.offset = static_cast<uint32_t>(offset);
			attr.binding = static_cast<uint32_t>(binding);
		}
    }

    void Pipeline::AddAttribIFormat(GLuint index, GLuint binding, GLint size, GLenum type, GLuint offset) noexcept {
		if (_Pipeline & 1) {
			auto& attr = reinterpret_cast<PipelineCreate*>(_Pipeline - 1)->PushAttrib(index);;
			attr.format = GetFormatI(size, type);
			attr.offset = static_cast<uint32_t>(offset);
			attr.binding = static_cast<uint32_t>(binding);
		}
    }

    void Pipeline::AddAttribLFormat(GLuint index, GLuint binding, GLint size, GLenum type, GLuint offset) noexcept {
		if (_Pipeline & 1) {
			auto& attr = reinterpret_cast<PipelineCreate*>(_Pipeline - 1)->PushAttrib(index);;
			attr.format = GetFormatF(size, type);
			attr.offset = static_cast<uint32_t>(offset);
			attr.binding = static_cast<uint32_t>(binding);
		}
    }

    void Pipeline::BindingDivisor(GLuint bindingIndex, GLuint divisor) noexcept {

    }

}

GLuint glvCreatePipelineLayout() noexcept {
	return reinterpret_cast<GLuint>(new GL::PipelineLayout);
}

void glvDeletePipelineLayout(GLuint layout) noexcept {
	delete reinterpret_cast<GL::PipelineLayout*>(layout);
}

void glvCompilePipelineLayout(GLuint layout) noexcept {
	reinterpret_cast<GL::PipelineLayout*>(layout)->Compile();
}

void glvPipelineLayoutAddBinding(GLuint layout, GLuint binding, GLenum type) noexcept {
	reinterpret_cast<GL::PipelineLayout*>(layout)->AddBinding(binding, type);
}

GLuint glvCreatePipelines() noexcept {
    return reinterpret_cast<GLuint>(new GL::Pipeline);
}

void glvDeletePipelines(GLuint pipeline) noexcept {
	delete reinterpret_cast<GL::Pipeline*>(pipeline);
}

void glvCompilePipeline(GLuint pipeline) noexcept {
    reinterpret_cast<GL::Pipeline*>(pipeline)->Compile();
}

void glvPipelineElementBuffer(GLuint pipeline, GLuint buffer) noexcept {
    reinterpret_cast<GL::Pipeline*>(pipeline)->ElementBuffer(buffer);
}

void glvPipelineVertexBuffer(GLuint pipeline, GLuint bindingIndex, GLuint buffer) noexcept {
    reinterpret_cast<GL::Pipeline*>(pipeline)->VertexBuffer(bindingIndex, *reinterpret_cast<GL::Buffer*>(buffer));
}

void glvPipelineVertexBuffers(GLuint pipeline, GLuint first, GLsizei count, const GLuint* buffers) noexcept {
    reinterpret_cast<GL::Pipeline*>(pipeline)->VertexBuffers(first, count, reinterpret_cast<const GL::Buffer*>(buffers));
}

void glvPipelineAddVertexBinding(GLuint pipeline, GLuint index, GLsizei stride, GLboolean instanceFeed) noexcept {
    reinterpret_cast<GL::Pipeline*>(pipeline)->AddVertexBinding(index, stride, instanceFeed);
}

void glvPipelineAddAttribFormat(GLuint pipeline, GLuint index, GLuint binding, GLint size, GLenum type, GLboolean normalized, GLuint offset) noexcept {
    reinterpret_cast<GL::Pipeline*>(pipeline)->AddAttribFormat(index, binding, size, type, normalized, offset);
}

void glvPipelineAddAttribIFormat(GLuint pipeline, GLuint index, GLuint binding, GLint size, GLenum type, GLuint offset) noexcept {
    reinterpret_cast<GL::Pipeline*>(pipeline)->AddAttribIFormat(index, binding, size, type, offset);
}

void glvPipelineAddAttribLFormat(GLuint pipeline, GLuint index, GLuint binding, GLint size, GLenum type, GLuint offset) noexcept {
    reinterpret_cast<GL::Pipeline*>(pipeline)->AddAttribLFormat(index, binding, size, type, offset);
}

void glvPipelineBindingDivisor(GLuint pipeline, GLuint bindingIndex, GLuint divisor) noexcept {
    reinterpret_cast<GL::Pipeline*>(pipeline)->BindingDivisor(bindingIndex, divisor);
}

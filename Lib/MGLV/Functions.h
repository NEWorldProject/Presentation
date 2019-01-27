#pragma once
#include <cstddef>
#include <cstdint>
#include "Enums.h"

#ifdef GL_VERSION_1_0
typedef unsigned int GLenum;
typedef float GLfloat;
typedef intptr_t GLint;
typedef int GLsizei;
typedef unsigned int GLbitfield;
typedef double GLdouble;
typedef uintptr_t GLuint;
typedef unsigned char GLboolean;
typedef uint8_t GLubyte;
void glCullFace(GLenum mode) noexcept;
void glFrontFace(GLenum mode) noexcept;
void glHint(GLenum target, GLenum mode) noexcept;
void glLineWidth(GLfloat width) noexcept;
void glPointSize(GLfloat size) noexcept;
void glPolygonMode(GLenum face, GLenum mode) noexcept;
void glScissor(GLint x, GLint y, GLsizei width, GLsizei height) noexcept;
void glDrawBuffer(GLenum buf) noexcept;
void glClear(GLbitfield mask) noexcept;
void glClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) noexcept;
void glClearStencil(GLint s) noexcept;
void glClearDepth(GLdouble depth) noexcept;
void glStencilMask(GLuint mask) noexcept;
void glColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha) noexcept;
void glDepthMask(GLboolean flag) noexcept;
void glDisable(GLenum cap) noexcept;
void glEnable(GLenum cap) noexcept;
void glFinish() noexcept;
void glFlush() noexcept;
void glBlendFunc(GLenum sfactor, GLenum dfactor) noexcept;
void glLogicOp(GLenum opcode) noexcept;
void glStencilFunc(GLenum func, GLint ref, GLuint mask) noexcept;
void glStencilOp(GLenum fail, GLenum zfail, GLenum zpass) noexcept;
void glDepthFunc(GLenum func) noexcept;
void glPixelStoref(GLenum pName, GLfloat param) noexcept;
void glPixelStorei(GLenum pName, GLint param) noexcept;
void glReadBuffer(GLenum src) noexcept;
void glReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void *pixels) noexcept;
void glGetBooleanv(GLenum pName, GLboolean *data) noexcept;
void glGetDoublev(GLenum pName, GLdouble *data) noexcept;
GLenum glGetError() noexcept;
void glGetFloatv(GLenum pName, GLfloat *data) noexcept;
void glGetIntegerv(GLenum pName, GLint *data) noexcept;
const GLubyte * glGetString(GLenum name) noexcept;
GLboolean glIsEnabled(GLenum cap) noexcept;
void glDepthRange(GLdouble n, GLdouble f) noexcept;
void glViewport(GLint x, GLint y, GLsizei width, GLsizei height) noexcept;
#endif /* GL_VERSION_1_0 */

#ifdef GL_VERSION_1_1
typedef float GLclampf;
typedef double GLclampd;
void glDrawArrays(GLenum mode, GLint first, GLsizei count) noexcept;
void glDrawElements(GLenum mode, GLsizei count, GLenum type, const void *indices) noexcept;
void glGetPointerv(GLenum pName, void **params) noexcept;
void glPolygonOffset(GLfloat factor, GLfloat units) noexcept;
void glBindTexture(GLenum target, GLuint texture) noexcept;
void glDeleteTextures(GLsizei n, const GLuint *textures) noexcept;
GLboolean glIsTexture(GLuint texture) noexcept;
#endif /* GL_VERSION_1_1 */

#ifdef GL_VERSION_1_2
void glDrawRangeElements(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void *indices) noexcept;
#endif /* GL_VERSION_1_2 */

#ifdef GL_VERSION_1_3
void glActiveTexture(GLenum texture) noexcept;
void glSampleCoverage(GLfloat value, GLboolean invert) noexcept;
#endif /* GL_VERSION_1_3 */

#ifdef GL_VERSION_1_4
void glBlendFuncSeparate(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha) noexcept;
void glMultiDrawArrays(GLenum mode, const GLint *first, const GLsizei *count, GLsizei drawcount) noexcept;
void glMultiDrawElements(GLenum mode, const GLsizei *count, GLenum type, const void *const*indices, GLsizei drawcount) noexcept;
void glPointParameterf(GLenum pName, GLfloat param) noexcept;
void glPointParameterfv(GLenum pName, const GLfloat *params) noexcept;
void glPointParameteri(GLenum pName, GLint param) noexcept;
void glPointParameteriv(GLenum pName, const GLint *params) noexcept;
void glBlendColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) noexcept;
void glBlendEquation(GLenum mode) noexcept;
#endif /* GL_VERSION_1_4 */

#ifdef GL_VERSION_1_5
typedef size_t GLsizeiptr;
typedef intptr_t GLintptr;
void glGenQueries(GLsizei n, GLuint *ids) noexcept;
void glDeleteQueries(GLsizei n, const GLuint *ids) noexcept;
GLboolean glIsQuery(GLuint id) noexcept;
void glBeginQuery(GLenum target, GLuint id) noexcept;
void glEndQuery(GLenum target) noexcept;
void glGetQueryiv(GLenum target, GLenum pName, GLint *params) noexcept;
void glGetQueryObjectiv(GLuint id, GLenum pName, GLint *params) noexcept;
void glGetQueryObjectuiv(GLuint id, GLenum pName, GLuint *params) noexcept;
void glBindBuffer(GLenum target, GLuint buffer) noexcept;
#endif /* GL_VERSION_1_5 */

#ifdef GL_VERSION_2_0
typedef char GLchar;
typedef int16_t GLshort;
typedef int8_t GLbyte;
typedef uint16_t GLushort;
void glBlendEquationSeparate(GLenum modeRGB, GLenum modeAlpha) noexcept;
void glDrawBuffers(GLsizei n, const GLenum *bufs) noexcept;
void glStencilOpSeparate(GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass) noexcept;
void glStencilFuncSeparate(GLenum face, GLenum func, GLint ref, GLuint mask) noexcept;
void glStencilMaskSeparate(GLenum face, GLuint mask) noexcept;
#endif /* GL_VERSION_2_0 */

#ifdef GL_VERSION_3_0
typedef uint16_t GLhalf;
void glColorMaski(GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a) noexcept;
void glGetBooleani_v(GLenum target, GLuint index, GLboolean *data) noexcept;
void glGetIntegeri_v(GLenum target, GLuint index, GLint *data) noexcept;
void glEnablei(GLenum target, GLuint index) noexcept;
void glDisablei(GLenum target, GLuint index) noexcept;
GLboolean glIsEnabledi(GLenum target, GLuint index) noexcept;
void glBeginTransformFeedback(GLenum primitiveMode) noexcept;
void glEndTransformFeedback() noexcept;
void glBindBufferRange(GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size) noexcept;
void glBindBufferBase(GLenum target, GLuint index, GLuint buffer) noexcept;
void glTransformFeedbackVaryings(GLuint program, GLsizei count, const GLchar *const*varyings, GLenum bufferMode) noexcept;
void glGetTransformFeedbackVarying(GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLsizei *size, GLenum *type, GLchar *name) noexcept;
void glClampColor(GLenum target, GLenum clamp) noexcept;
void glBeginConditionalRender(GLuint id, GLenum mode) noexcept;
void glEndConditionalRender() noexcept;
void glBindFragDataLocation(GLuint program, GLuint color, const GLchar *name) noexcept;
GLint glGetFragDataLocation(GLuint program, const GLchar *name) noexcept;
void glClearBufferiv(GLenum buffer, GLint drawbuffer, const GLint *value) noexcept;
void glClearBufferuiv(GLenum buffer, GLint drawbuffer, const GLuint *value) noexcept;
void glClearBufferfv(GLenum buffer, GLint drawbuffer, const GLfloat *value) noexcept;
void glClearBufferfi(GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil) noexcept;
const GLubyte * glGetStringi(GLenum name, GLuint index) noexcept;
GLboolean glIsRenderbuffer(GLuint renderbuffer) noexcept;
void glBindRenderbuffer(GLenum target, GLuint renderbuffer) noexcept;
void glDeleteRenderbuffers(GLsizei n, const GLuint *renderbuffers) noexcept;
void glGenRenderbuffers(GLsizei n, GLuint *renderbuffers) noexcept;
void glRenderbufferStorage(GLenum target, GLenum internalFormat, GLsizei width, GLsizei height) noexcept;
void glGetRenderbufferParameteriv(GLenum target, GLenum pName, GLint *params) noexcept;
GLboolean glIsFramebuffer(GLuint framebuffer) noexcept;
void glBindFramebuffer(GLenum target, GLuint framebuffer) noexcept;
void glDeleteFramebuffers(GLsizei n, const GLuint *framebuffers) noexcept;
void glGenFramebuffers(GLsizei n, GLuint *framebuffers) noexcept;
GLenum glCheckFramebufferStatus(GLenum target) noexcept;
void glFramebufferTexture1D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level) noexcept;
void glFramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level) noexcept;
void glFramebufferTexture3D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zOffset) noexcept;
void glFramebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer) noexcept;
void glGetFramebufferAttachmentParameteriv(GLenum target, GLenum attachment, GLenum pName, GLint *params) noexcept;
void glGenerateMipmap(GLenum target) noexcept;
void glBlitFramebuffer(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter) noexcept;
void glRenderbufferStorageMultisample(GLenum target, GLsizei samples, GLenum internalFormat, GLsizei width, GLsizei height) noexcept;
void glFramebufferTextureLayer(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer) noexcept;
void glBindVertexArray(GLuint array) noexcept;
#endif /* GL_VERSION_3_0 */

#ifdef GL_VERSION_3_1
void glDrawArraysInstanced(GLenum mode, GLint first, GLsizei count, GLsizei instancecount) noexcept;
void glDrawElementsInstanced(GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount) noexcept;
void glPrimitiveRestartIndex(GLuint index) noexcept;
void glGetUniformIndices(GLuint program, GLsizei uniformCount, const GLchar *const*uniformNames, GLuint *uniformIndices) noexcept;
void glGetActiveUniformsiv(GLuint program, GLsizei uniformCount, const GLuint *uniformIndices, GLenum pName, GLint *params) noexcept;
void glGetActiveUniformName(GLuint program, GLuint uniformIndex, GLsizei bufSize, GLsizei *length, GLchar *uniformName) noexcept;
GLuint glGetUniformBlockIndex(GLuint program, const GLchar *uniformBlockName) noexcept;
void glGetActiveUniformBlockiv(GLuint program, GLuint uniformBlockIndex, GLenum pName, GLint *params) noexcept;
void glGetActiveUniformBlockName(GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei *length, GLchar *uniformBlockName) noexcept;
void glUniformBlockBinding(GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding) noexcept;
#endif /* GL_VERSION_3_1 */

#ifdef GL_VERSION_3_2
typedef struct __GLsync *GLsync;
typedef uint64_t GLuint64;
typedef int64_t GLint64;
void glDrawElementsBaseVertex(GLenum mode, GLsizei count, GLenum type, const void *indices, GLint basevertex) noexcept;
void glDrawRangeElementsBaseVertex(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void *indices, GLint basevertex) noexcept;
void glDrawElementsInstancedBaseVertex(GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount, GLint basevertex) noexcept;
void glMultiDrawElementsBaseVertex(GLenum mode, const GLsizei *count, GLenum type, const void *const*indices, GLsizei drawcount, const GLint *basevertex) noexcept;
void glProvokingVertex(GLenum mode) noexcept;
GLsync glFenceSync(GLenum condition, GLbitfield flags) noexcept;
GLboolean glIsSync(GLsync sync) noexcept;
void glDeleteSync(GLsync sync) noexcept;
GLenum glClientWaitSync(GLsync sync, GLbitfield flags, GLuint64 timeout) noexcept;
void glWaitSync(GLsync sync, GLbitfield flags, GLuint64 timeout) noexcept;
void glGetInteger64v(GLenum pName, GLint64 *data) noexcept;
void glGetSynciv(GLsync sync, GLenum pName, GLsizei bufSize, GLsizei *length, GLint *values) noexcept;
void glGetInteger64i_v(GLenum target, GLuint index, GLint64 *data) noexcept;
void glFramebufferTexture(GLenum target, GLenum attachment, GLuint texture, GLint level) noexcept;
void glGetMultisamplefv(GLenum pName, GLuint index, GLfloat *val) noexcept;
void glSampleMaski(GLuint maskNumber, GLbitfield mask) noexcept;
#endif /* GL_VERSION_3_2 */

#ifdef GL_VERSION_3_3
void glBindFragDataLocationIndexed(GLuint program, GLuint colorNumber, GLuint index, const GLchar *name) noexcept;
GLint glGetFragDataIndex(GLuint program, const GLchar *name) noexcept;
void glGenSamplers(GLsizei count, GLuint *samplers) noexcept;
void glDeleteSamplers(GLsizei count, const GLuint *samplers) noexcept;
GLboolean glIsSampler(GLuint sampler) noexcept;
void glBindSampler(GLuint unit, GLuint sampler) noexcept;
void glSamplerParameteri(GLuint sampler, GLenum pName, GLint param) noexcept;
void glSamplerParameteriv(GLuint sampler, GLenum pName, const GLint *param) noexcept;
void glSamplerParameterf(GLuint sampler, GLenum pName, GLfloat param) noexcept;
void glSamplerParameterfv(GLuint sampler, GLenum pName, const GLfloat *param) noexcept;
void glSamplerParameterIiv(GLuint sampler, GLenum pName, const GLint *param) noexcept;
void glSamplerParameterIuiv(GLuint sampler, GLenum pName, const GLuint *param) noexcept;
void glGetSamplerParameteriv(GLuint sampler, GLenum pName, GLint *params) noexcept;
void glGetSamplerParameterIiv(GLuint sampler, GLenum pName, GLint *params) noexcept;
void glGetSamplerParameterfv(GLuint sampler, GLenum pName, GLfloat *params) noexcept;
void glGetSamplerParameterIuiv(GLuint sampler, GLenum pName, GLuint *params) noexcept;
void glQueryCounter(GLuint id, GLenum target) noexcept;
void glGetQueryObjecti64v(GLuint id, GLenum pName, GLint64 *params) noexcept;
void glGetQueryObjectui64v(GLuint id, GLenum pName, GLuint64 *params) noexcept;
void glVertexAttribDivisor(GLuint index, GLuint divisor) noexcept;
#endif /* GL_VERSION_3_3 */

#ifdef GL_VERSION_4_0
void glMinSampleShading(GLfloat value) noexcept;
void glBlendEquationi(GLuint buf, GLenum mode) noexcept;
void glBlendEquationSeparatei(GLuint buf, GLenum modeRGB, GLenum modeAlpha) noexcept;
void glBlendFunci(GLuint buf, GLenum src, GLenum dst) noexcept;
void glBlendFuncSeparatei(GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha) noexcept;
void glDrawArraysIndirect(GLenum mode, const void *indirect) noexcept;
void glDrawElementsIndirect(GLenum mode, GLenum type, const void *indirect) noexcept;
void glGetUniformdv(GLuint program, GLint location, GLdouble *params) noexcept;
GLint glGetSubroutineUniformLocation(GLuint program, GLenum shadertype, const GLchar *name) noexcept;
GLuint glGetSubroutineIndex(GLuint program, GLenum shadertype, const GLchar *name) noexcept;
void glGetActiveSubroutineUniformiv(GLuint program, GLenum shadertype, GLuint index, GLenum pName, GLint *values) noexcept;
void glGetActiveSubroutineUniformName(GLuint program, GLenum shadertype, GLuint index, GLsizei bufsize, GLsizei *length, GLchar *name) noexcept;
void glGetActiveSubroutineName(GLuint program, GLenum shadertype, GLuint index, GLsizei bufsize, GLsizei *length, GLchar *name) noexcept;
void glUniformSubroutinesuiv(GLenum shadertype, GLsizei count, const GLuint *indices) noexcept;
void glGetUniformSubroutineuiv(GLenum shadertype, GLint location, GLuint *params) noexcept;
void glPatchParameteri(GLenum pName, GLint value) noexcept;
void glPatchParameterfv(GLenum pName, const GLfloat *values) noexcept;
void glBindTransformFeedback(GLenum target, GLuint id) noexcept;
void glDeleteTransformFeedbacks(GLsizei n, const GLuint *ids) noexcept;
void glGenTransformFeedbacks(GLsizei n, GLuint *ids) noexcept;
GLboolean glIsTransformFeedback(GLuint id) noexcept;
void glPauseTransformFeedback() noexcept;
void glResumeTransformFeedback() noexcept;
void glDrawTransformFeedback(GLenum mode, GLuint id) noexcept;
void glDrawTransformFeedbackStream(GLenum mode, GLuint id, GLuint stream) noexcept;
void glBeginQueryIndexed(GLenum target, GLuint index, GLuint id) noexcept;
void glEndQueryIndexed(GLenum target, GLuint index) noexcept;
void glGetQueryIndexediv(GLenum target, GLuint index, GLenum pName, GLint *params) noexcept;
#endif /* GL_VERSION_4_0 */

#ifdef GL_VERSION_4_1
void glDepthRangef(GLfloat n, GLfloat f) noexcept;
void glClearDepthf(GLfloat d) noexcept;
void glViewportArrayv(GLuint first, GLsizei count, const GLfloat *v) noexcept;
void glViewportIndexedf(GLuint index, GLfloat x, GLfloat y, GLfloat w, GLfloat h) noexcept;
void glViewportIndexedfv(GLuint index, const GLfloat *v) noexcept;
void glScissorArrayv(GLuint first, GLsizei count, const GLint *v) noexcept;
void glScissorIndexed(GLuint index, GLint left, GLint bottom, GLsizei width, GLsizei height) noexcept;
void glScissorIndexedv(GLuint index, const GLint *v) noexcept;
void glDepthRangeArrayv(GLuint first, GLsizei count, const GLdouble *v) noexcept;
void glDepthRangeIndexed(GLuint index, GLdouble n, GLdouble f) noexcept;
void glGetFloati_v(GLenum target, GLuint index, GLfloat *data) noexcept;
void glGetDoublei_v(GLenum target, GLuint index, GLdouble *data) noexcept;
#endif /* GL_VERSION_4_1 */

#ifdef GL_VERSION_4_2
void glDrawArraysInstancedBaseInstance(GLenum mode, GLint first, GLsizei count, GLsizei instancecount, GLuint baseinstance) noexcept;
void glDrawElementsInstancedBaseInstance(GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount, GLuint baseinstance) noexcept;
void glDrawElementsInstancedBaseVertexBaseInstance(GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount, GLint basevertex, GLuint baseinstance) noexcept;
void glGetInternalformativ(GLenum target, GLenum internalFormat, GLenum pName, GLsizei bufSize, GLint *params) noexcept;
void glGetActiveAtomicCounterBufferiv(GLuint program, GLuint bufferIndex, GLenum pName, GLint *params) noexcept;
void glBindImageTexture(GLuint unit, GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum access, GLenum format) noexcept;
void glMemoryBarrier(GLbitfield barriers) noexcept;
void glDrawTransformFeedbackInstanced(GLenum mode, GLuint id, GLsizei instancecount) noexcept;
void glDrawTransformFeedbackStreamInstanced(GLenum mode, GLuint id, GLuint stream, GLsizei instancecount) noexcept;
#endif /* GL_VERSION_4_2 */

#ifdef GL_VERSION_4_3
typedef void(  *GLDEBUGPROC)(GLenum source,GLenum type,GLuint id,GLenum severity,GLsizei length,const GLchar *message,const void *userParam) noexcept;
void glDispatchCompute(GLuint num_groups_x, GLuint num_groups_y, GLuint num_groups_z) noexcept;
void glDispatchComputeIndirect(GLintptr indirect) noexcept;
void glCopyImageSubData(GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei srcWidth, GLsizei srcHeight, GLsizei srcDepth) noexcept;
void glFramebufferParameteri(GLenum target, GLenum pName, GLint param) noexcept;
void glGetFramebufferParameteriv(GLenum target, GLenum pName, GLint *params) noexcept;
void glGetInternalformati64v(GLenum target, GLenum internalFormat, GLenum pName, GLsizei bufSize, GLint64 *params) noexcept;
void glInvalidateTexSubImage(GLuint texture, GLint level, GLint xOffset, GLint yOffset, GLint zOffset, GLsizei width, GLsizei height, GLsizei depth) noexcept;
void glInvalidateTexImage(GLuint texture, GLint level) noexcept;
void glInvalidateFramebuffer(GLenum target, GLsizei numAttachments, const GLenum *attachments) noexcept;
void glInvalidateSubFramebuffer(GLenum target, GLsizei numAttachments, const GLenum *attachments, GLint x, GLint y, GLsizei width, GLsizei height) noexcept;
void glMultiDrawArraysIndirect(GLenum mode, const void *indirect, GLsizei drawcount, GLsizei stride) noexcept;
void glMultiDrawElementsIndirect(GLenum mode, GLenum type, const void *indirect, GLsizei drawcount, GLsizei stride) noexcept;
void glGetProgramInterfaceiv(GLuint program, GLenum programInterface, GLenum pName, GLint *params) noexcept;
GLuint glGetProgramResourceIndex(GLuint program, GLenum programInterface, const GLchar *name) noexcept;
void glGetProgramResourceName(GLuint program, GLenum programInterface, GLuint index, GLsizei bufSize, GLsizei *length, GLchar *name) noexcept;
void glGetProgramResourceiv(GLuint program, GLenum programInterface, GLuint index, GLsizei propCount, const GLenum *props, GLsizei bufSize, GLsizei *length, GLint *params) noexcept;
GLint glGetProgramResourceLocation(GLuint program, GLenum programInterface, const GLchar *name) noexcept;
GLint glGetProgramResourceLocationIndex(GLuint program, GLenum programInterface, const GLchar *name) noexcept;
void glShaderStorageBlockBinding(GLuint program, GLuint storageBlockIndex, GLuint storageBlockBinding) noexcept;
void glTextureView(GLuint texture, GLenum target, GLuint origtexture, GLenum internalFormat, GLuint minlevel, GLuint numlevels, GLuint minlayer, GLuint numlayers) noexcept;
void glDebugMessageControl(GLenum source, GLenum type, GLenum severity, GLsizei count, const GLuint *ids, GLboolean enabled) noexcept;
void glDebugMessageInsert(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *buf) noexcept;
void glDebugMessageCallback(GLDEBUGPROC callback, const void *userParam) noexcept;
GLuint glGetDebugMessageLog(GLuint count, GLsizei bufSize, GLenum *sources, GLenum *types, GLuint *ids, GLenum *severities, GLsizei *lengths, GLchar *messageLog) noexcept;
void glPushDebugGroup(GLenum source, GLuint id, GLsizei length, const GLchar *message) noexcept;
void glPopDebugGroup() noexcept;
void glObjectLabel(GLenum identifier, GLuint name, GLsizei length, const GLchar *label) noexcept;
void glGetObjectLabel(GLenum identifier, GLuint name, GLsizei bufSize, GLsizei *length, GLchar *label) noexcept;
void glObjectPtrLabel(const void *ptr, GLsizei length, const GLchar *label) noexcept;
void glGetObjectPtrLabel(const void *ptr, GLsizei bufSize, GLsizei *length, GLchar *label) noexcept;
#endif /* GL_VERSION_4_3 */

#ifdef GL_VERSION_4_4
void glClearTexImage(GLuint texture, GLint level, GLenum format, GLenum type, const void *data) noexcept;
void glClearTexSubImage(GLuint texture, GLint level, GLint xOffset, GLint yOffset, GLint zOffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void *data) noexcept;
void glBindBuffersBase(GLenum target, GLuint first, GLsizei count, const GLuint *buffers) noexcept;
void glBindBuffersRange(GLenum target, GLuint first, GLsizei count, const GLuint *buffers, const GLintptr *offsets, const GLsizeiptr *sizes) noexcept;
void glBindTextures(GLuint first, GLsizei count, const GLuint *textures) noexcept;
void glBindSamplers(GLuint first, GLsizei count, const GLuint *samplers) noexcept;
void glBindImageTextures(GLuint first, GLsizei count, const GLuint *textures) noexcept;
#endif /* GL_VERSION_4_4 */

#ifdef GL_VERSION_4_5
void glClipControl(GLenum origin, GLenum depth) noexcept;
void glCreateTransformFeedbacks(GLsizei n, GLuint *ids) noexcept;
void glTransformFeedbackBufferBase(GLuint xfb, GLuint index, GLuint buffer) noexcept;
void glTransformFeedbackBufferRange(GLuint xfb, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size) noexcept;
void glGetTransformFeedbackiv(GLuint xfb, GLenum pName, GLint *param) noexcept;
void glGetTransformFeedbacki_v(GLuint xfb, GLenum pName, GLuint index, GLint *param) noexcept;
void glGetTransformFeedbacki64_v(GLuint xfb, GLenum pName, GLuint index, GLint64 *param) noexcept;
void glCreateFramebuffers(GLsizei n, GLuint *framebuffers) noexcept;
void glNamedFramebufferRenderbuffer(GLuint framebuffer, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer) noexcept;
void glNamedFramebufferParameteri(GLuint framebuffer, GLenum pName, GLint param) noexcept;
void glNamedFramebufferTexture(GLuint framebuffer, GLenum attachment, GLuint texture, GLint level) noexcept;
void glNamedFramebufferTextureLayer(GLuint framebuffer, GLenum attachment, GLuint texture, GLint level, GLint layer) noexcept;
void glNamedFramebufferDrawBuffer(GLuint framebuffer, GLenum buf) noexcept;
void glNamedFramebufferDrawBuffers(GLuint framebuffer, GLsizei n, const GLenum *bufs) noexcept;
void glNamedFramebufferReadBuffer(GLuint framebuffer, GLenum src) noexcept;
void glInvalidateNamedFramebufferData(GLuint framebuffer, GLsizei numAttachments, const GLenum *attachments) noexcept;
void glInvalidateNamedFramebufferSubData(GLuint framebuffer, GLsizei numAttachments, const GLenum *attachments, GLint x, GLint y, GLsizei width, GLsizei height) noexcept;
void glClearNamedFramebufferiv(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLint *value) noexcept;
void glClearNamedFramebufferuiv(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLuint *value) noexcept;
void glClearNamedFramebufferfv(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLfloat *value) noexcept;
void glClearNamedFramebufferfi(GLuint framebuffer, GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil) noexcept;
void glBlitNamedFramebuffer(GLuint readFramebuffer, GLuint drawFramebuffer, GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter) noexcept;
GLenum glCheckNamedFramebufferStatus(GLuint framebuffer, GLenum target) noexcept;
void glGetNamedFramebufferParameteriv(GLuint framebuffer, GLenum pName, GLint *param) noexcept;
void glGetNamedFramebufferAttachmentParameteriv(GLuint framebuffer, GLenum attachment, GLenum pName, GLint *params) noexcept;
void glCreateRenderbuffers(GLsizei n, GLuint *renderbuffers) noexcept;
void glNamedRenderbufferStorage(GLuint renderbuffer, GLenum internalFormat, GLsizei width, GLsizei height) noexcept;
void glNamedRenderbufferStorageMultisample(GLuint renderbuffer, GLsizei samples, GLenum internalFormat, GLsizei width, GLsizei height) noexcept;
void glGetNamedRenderbufferParameteriv(GLuint renderbuffer, GLenum pName, GLint *params) noexcept;
void glCreateSamplers(GLsizei n, GLuint *samplers) noexcept;
void glCreateQueries(GLenum target, GLsizei n, GLuint *ids) noexcept;
void glGetQueryBufferObjecti64v(GLuint id, GLuint buffer, GLenum pName, GLintptr offset) noexcept;
void glGetQueryBufferObjectiv(GLuint id, GLuint buffer, GLenum pName, GLintptr offset) noexcept;
void glGetQueryBufferObjectui64v(GLuint id, GLuint buffer, GLenum pName, GLintptr offset) noexcept;
void glGetQueryBufferObjectuiv(GLuint id, GLuint buffer, GLenum pName, GLintptr offset) noexcept;
void glMemoryBarrierByRegion(GLbitfield barriers) noexcept;
void glGetTextureSubImage(GLuint texture, GLint level, GLint xOffset, GLint yOffset, GLint zOffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, GLsizei bufSize, void *pixels) noexcept;
void glGetCompressedTextureSubImage(GLuint texture, GLint level, GLint xOffset, GLint yOffset, GLint zOffset, GLsizei width, GLsizei height, GLsizei depth, GLsizei bufSize, void *pixels) noexcept;
GLenum glGetGraphicsResetStatus() noexcept;
void glGetnCompressedTexImage(GLenum target, GLint lod, GLsizei bufSize, void *pixels) noexcept;
void glGetnTexImage(GLenum target, GLint level, GLenum format, GLenum type, GLsizei bufSize, void *pixels) noexcept;
void glReadnPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLsizei bufSize, void *data) noexcept;
void glTextureBarrier() noexcept;
#endif /* GL_VERSION_4_5 */

#ifdef GL_VERSION_4_6
void glSpecializeShader(GLuint shader, const GLchar *pEntryPoint, GLuint numSpecializationConstants, const GLuint *pConstantIndex, const GLuint *pConstantValue) noexcept;
void glMultiDrawArraysIndirectCount(GLenum mode, const void *indirect, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride) noexcept;
void glMultiDrawElementsIndirectCount(GLenum mode, GLenum type, const void *indirect, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride) noexcept;
void glPolygonOffsetClamp(GLfloat factor, GLfloat units, GLfloat clamp) noexcept;
#endif /* GL_VERSION_4_6 */

// Begin Buffer
GLuint glvCreateBuffer() noexcept;
void glvDeleteBuffers(GLuint buffer) noexcept;
void glvBufferStorage(GLuint buffer, GLsizeiptr size, const void *data, GLbitfield flags) noexcept;
void glvBufferSubData(GLuint buffer, GLintptr offset, GLsizeiptr size, const void *data) noexcept;
void glvCopyBufferSubData(GLuint readBuffer, GLuint writeBuffer, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size) noexcept;
void glvClearBufferData(GLuint buffer, GLuint unitSize, const void* data) noexcept;
void glvClearBufferSubData(GLuint buffer, GLuint unitSize, GLintptr offset, GLsizeiptr size, const void* data) noexcept;
void glvZeroBufferData(GLuint buffer) noexcept;
void glvZeroBufferSubData(GLuint buffer, GLintptr offset, GLsizeiptr size) noexcept;
void * glvMapBuffer(GLuint buffer, GLenum access) noexcept;
void * glvMapBufferRange(GLuint buffer, GLintptr offset, GLsizeiptr length, GLbitfield access) noexcept;
GLboolean glvUnmapBuffer(GLuint buffer) noexcept;
void glvFlushMappedBufferRange(GLuint buffer, GLintptr offset, GLsizeiptr length) noexcept;
// End Buffer

// Begin Shader
GLuint glvCreateShader(GLenum type, const void *binary, GLsizei length, const char* entry) noexcept;
void glvDeleteShader(GLuint shader) noexcept;
GLuint glvCreateProgram() noexcept;
void glvDeleteProgram(GLuint program) noexcept;
void glvAttachShader(GLuint program, GLuint shader) noexcept;
void glvDetachShader(GLuint program, GLuint shader) noexcept;
// End Shader

// Begin Pipeline
GLuint glvCreatePipelineLayout() noexcept;
void glvDeletePipelineLayout(GLuint layout) noexcept;
void glvCompilePipelineLayout(GLuint layout) noexcept;
void glvPipelineLayoutAddBinding(GLuint layout, GLuint binding, GLenum type) noexcept;
GLuint glvCreatePipelines() noexcept;
void glvDeletePipelines(GLuint pipeline) noexcept;
void glvCompilePipeline(GLuint pipeline) noexcept;
void glvPipelineElementBuffer(GLuint pipeline, GLuint buffer) noexcept;
void glvPipelineVertexBuffer(GLuint pipeline, GLuint bindingIndex, GLuint buffer) noexcept;
void glvPipelineVertexBuffers(GLuint pipeline, GLuint first, GLsizei count, const GLuint* buffers) noexcept;
void glvPipelineAddVertexBinding(GLuint pipeline, GLuint index, GLsizei stride, GLboolean instanceFeed) noexcept;
void glvPipelineAddAttribFormat(GLuint pipeline, GLuint index, GLuint binding, GLint size, GLenum type, GLboolean normalized, GLuint offset) noexcept;
void glvPipelineAddAttribIFormat(GLuint pipeline, GLuint index, GLuint binding, GLint size, GLenum type, GLuint offset) noexcept;
void glvPipelineAddAttribLFormat(GLuint pipeline, GLuint index, GLuint binding, GLint size, GLenum type, GLuint offset) noexcept;
void glvPipelineBindingDivisor(GLuint pipeline, GLuint bindingIndex, GLuint divisor) noexcept;
// End Pipeline

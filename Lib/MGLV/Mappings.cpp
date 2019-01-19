#include "Functions.h"

void glCreateBuffers(GLsizei n, GLuint *buffers) noexcept {
    for (GLsizei i = 0; i < n; ++i) {
        auto obj = new GL::Buffer();
        obj->Create();
        buffers[i] = reinterpret_cast<GLuint>(obj);
    }
}

void glDeleteBuffers(GLsizei n, const GLuint *buffers) noexcept{
    for (GLsizei i = 0; i < n; ++i) {
        auto obj = reinterpret_cast<GL::Buffer*>(buffers[i]);
        obj->Delete();
        delete obj;
    }
}

void glNamedBufferStorage(GLuint buffer, GLsizeiptr size, const void *data, GLbitfield flags) noexcept {
    reinterpret_cast<GL::Buffer*>(buffer)->Storage(size, data, flags);
}

void glNamedBufferSubData(GLuint buffer, GLintptr offset, GLsizeiptr size, const void *data) noexcept {
    reinterpret_cast<GL::Buffer*>(buffer)->SubData(offset, size, data);
}

void glCopyNamedBufferSubData(GLuint readBuffer, GLuint writeBuffer, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size) noexcept {
    GL::Buffer::CopySubData(*reinterpret_cast<GL::Buffer*>(readBuffer), *reinterpret_cast<GL::Buffer*>(writeBuffer),
            readBuffer, writeBuffer, size);
}

void glClearNamedBufferData(GLuint buffer, GLenum internalFormat, GLenum format, GLenum type, const void *data) noexcept {
    reinterpret_cast<GL::Buffer*>(buffer)->ClearData(internalFormat, format, type, data);
}

void glClearNamedBufferSubData(GLuint buffer, GLenum internalFormat, GLintptr offset, GLsizeiptr size, GLenum format, GLenum type, const void *data) noexcept {
    reinterpret_cast<GL::Buffer*>(buffer)->ClearSubData(internalFormat, offset, size, format, type, data);
}

void glZeroNamedBufferDataMGLV(GLuint buffer) noexcept {
    reinterpret_cast<GL::Buffer*>(buffer)->ZeroDataMGLV();
}

void glZeroNamedBufferSubDataMGLV(GLuint buffer, GLintptr offset, GLsizeiptr size) noexcept{
    reinterpret_cast<GL::Buffer*>(buffer)->ZeroSubDataMGLV(offset, size);
}

void * glMapNamedBuffer(GLuint buffer, GLenum access) noexcept {
    return reinterpret_cast<GL::Buffer*>(buffer)->Map(access);
}

void * glMapNamedBufferRange(GLuint buffer, GLintptr offset, GLsizeiptr length, GLbitfield access) noexcept {
    return reinterpret_cast<GL::Buffer*>(buffer)->MapRange(offset, length, access);
}

GLboolean glUnmapNamedBuffer(GLuint buffer) noexcept {
    return reinterpret_cast<GL::Buffer*>(buffer)->Unmap();
}

void glFlushMappedNamedBufferRange(GLuint buffer, GLintptr offset, GLsizeiptr length) noexcept {
    reinterpret_cast<GL::Buffer*>(buffer)->FlushMappedRange(offset, length);
}

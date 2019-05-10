#pragma once
#include <vector>
#include <GL/glew.h>
#include "Renderer.h"
#include "ErrorHandling.h"

struct VertexBufferElement {
	unsigned int type;
	unsigned int count;
	char normalized;

	static unsigned int getSizeOfType(unsigned int type) {
		switch (type) {
		case GL_FLOAT:return 4;
		case GL_UNSIGNED_INT:return 4;
		}

		return 0;
		ASSERT(false);
	}
};


class VertexBufferLayout {
private:
	std::vector<VertexBufferElement> elements;
	unsigned int stride;

public:
	VertexBufferLayout() :
		stride(0) {
	}

	template<typename T>
	void push(unsigned int count) {
		static_assert(false);
	}

	template<>
	void push<float>(unsigned int count) {
		elements.push_back({ GL_FLOAT, count, GL_FALSE });
		stride += sizeof(GL_FLOAT) * count;
	}

	template<>
	void push<unsigned int>(unsigned int count) {
		elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		stride += sizeof(GLuint) * count;
	}

	inline const std::vector<VertexBufferElement> getElements() const { return elements; }
	inline unsigned int getStride() const { return stride; }

};

#pragma once
#include "Renderer.h"
#include "UiElement.h"

class UiRenderer {

private:
	Renderer renderer;
	VertexArray quadMesh;
	VertexBuffer vb;
	VertexBufferLayout lay;
	Shader Ui;

public:
	UiRenderer(Renderer& renderer);
	void RenderElement(UiElement& element);
	
};
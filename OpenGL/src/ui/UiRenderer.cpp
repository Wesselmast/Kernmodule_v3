#include "UiRenderer.h"


float quad[] = {
	 0,	0,	0, 0,
	 0,	1,	1, 0,
	 1,	1,	1, 1,
	 1,	1,	1, 1,
	 1,	0,	0, 1,
	 0,	0,	0, 0
};



UiRenderer::UiRenderer(Renderer & renderer) : renderer(renderer), vb(quad, 6 * 4 * sizeof(float)), Ui("res/shaders/Ui.shader"){

	lay.Push<float>(2);
	lay.Push<float>(2);
	quadMesh.AddBuffer(vb, lay);
}

void UiRenderer::RenderElement(UiElement& element)
{
	renderer.DrawUi(quadMesh, Ui ,element.position, element.size, element.texture);
}

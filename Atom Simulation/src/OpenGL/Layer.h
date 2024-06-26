#pragma once

#include <string>

#include "Debug.h"

#include "Renderer.h"
#include "Shader.h"
#include "Camera.h"
#include "Texture2D.h"
#include "TextureCubeMap.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"

class Layer {
public:
	Layer(const std::string& name = "Layer");
	virtual ~Layer() = default;

	virtual void OnDraw() {}
	virtual void OnUpdate() {}
	virtual void OnResize(int width, int height) {}

	const std::string& GetName() const { return m_DebugName; }
protected:
	std::string m_DebugName;
};


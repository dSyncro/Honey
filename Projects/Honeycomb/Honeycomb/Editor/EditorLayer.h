#pragma once

#include <Honey.h>
#include <Honeycomb/Frames/InspectorFrame.h>
#include <Honeycomb/Frames/SceneHierarchyFrame.h>

namespace Honey {

	class EditorLayer : public Honey::Layer {

	public:

		EditorLayer() : Layer("Editor Layer") {}
		~EditorLayer() = default;

		virtual void onAttach() override;
		virtual void onDetach() override;
		virtual void onUpdate() override;
		virtual void onEvent(Event& e) override;
		virtual void onImGuiRender() override;

	private:

		Entity _entity, _camera, _spriteA, _spriteB;

		Reference<Scene> _activeScene;

		Reference<VertexArray> _vertexArray;
		Reference<Texture2D> _texture;
		Reference<FrameBuffer> _frameBuffer;

		ShaderLibrary _shaderLib;

		Math::Vector2 _viewportSize;

		Reference<Font> _font;
		Reference<FontAtlas> _atlas;

		SceneHierarchyFrame _hierarchy;
		InspectorFrame _inspector;
	};
}

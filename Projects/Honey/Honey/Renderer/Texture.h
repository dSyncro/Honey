#pragma once

#include <string>

#include <Honey/Core/MemoryManagement.h>
#include <Honey/Math/Vector/Vector2Int.h>

namespace Honey {

	class Texture {

	public:

		enum class Channel {
			Red = 0,
			Green,
			Blue,
			Alpha
		};

		enum class PixelFormat {
			R,
			RG,
			RGB,
			BGR,
			RGBA,
			BGRA
		};

		virtual ~Texture() = default;

		virtual std::size_t GetWidth() const = 0;
		virtual std::size_t GetHeight() const = 0;

		virtual void* GetRawData() = 0;
		virtual void SetData(void* data, std::size_t size, const Math::Vector2Int& offset = Math::Vector2Int::zero()) = 0;

		virtual void BindToSlot(uint32_t slot = 0) const = 0;
	};

	class Texture2D : public Texture {

	public:

		static Reference<Texture2D> Create(std::size_t width, std::size_t height, PixelFormat format = PixelFormat::RGBA);
		static Reference<Texture2D> Create(const std::string& path);

		virtual bool operator ==(const Texture2D& other) const = 0;
		virtual bool operator !=(const Texture2D& other) const = 0;

	};

}

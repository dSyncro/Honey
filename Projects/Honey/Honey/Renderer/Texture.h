#pragma once

#include <string>

#include <Honey/Core/MemoryManagement.h>
#include <Honey/Math/Math.h>

namespace Honey {

	/**
	 * @brief Texture abstraction.
	*/
	class Texture {

	public:

		/**
		 * @brief Possible texture channels.
		*/
		enum class Channel {
			Red = 0, /** @brief Red channel. */
			Green, /** @brief Green channel. */
			Blue, /** @brief Blue channel. */
			Alpha /** @brief Alpha channel. */
		};

		/**
		 * @brief Supported texture pixel formats.
		*/
		enum class PixelFormat {
			R, /** @brief Single red channel. */
			RGB, /** @brief Common red-green-blue format. */
			RGBA, /** @brief Common red-green-blue-alpha format. */
		};

		virtual ~Texture() = default;

		/**
		 * @brief Get texture width.
		 * @return Texture width.
		*/
		virtual UInt getWidth() const = 0;

		/**
		 * @brief Get texture height.
		 * @return Texture height.
		*/
		virtual UInt getHeight() const = 0;

		/**
		 * @brief Get texture size.
		 * @return Texture size.
		*/
		virtual Math::Size getSize() const = 0;

		/**
		 * @brief Get pointer to texture.
		 * @return Texture raw data.
		*/
		virtual void* getRawData() = 0;

		/**
		 * @brief Set data to texture.
		 * @param data New data.
		 * @param size Data size in bytes.
		 * @param offset Data can be set starting from an arbitrary point in memory.
		 * Offset represent that point.
		*/
		virtual void setData(void* data, UInt size, const Math::Vector2Int& offset = Math::Vector2Int::zero()) = 0;

		/**
		 * @brief Bind texture to a certain texture slot.
		 * @param slot The slot to bind the texture to.
		*/
		virtual void bindToSlot(UInt slot = 0) const = 0;
	};

	/**
	 * @brief 2D Texture abstraction.
	*/
	class Texture2D : public Texture {

	public:

		/**
		 * @brief Create a new Texture2D from its components.
		 * @param width Texture width.
		 * @param height Texture height.
		 * @param format Texture pixel format.
		 * @return A new memory managed Texture2D.
		*/
		static Reference<Texture2D> create(UInt width, UInt height, PixelFormat format = PixelFormat::RGBA);

		/**
		 * @brief Create a new Texture2D loading it from disk.
		 * @param path Image file path.
		 * @return A new memory managed Texture2D.
		*/
		static Reference<Texture2D> create(const std::string& path);

		/**
		 * @brief Check if two Texture2D are equal to each other.
		 * @param other The other Texture2D.
		*/
		virtual bool operator ==(const Texture2D& other) const = 0;

		/**
		 * @brief Check if two Texture2D differ from each other.
		 * @param other The other Texture2D.
		*/
		virtual bool operator !=(const Texture2D& other) const = 0;

	};

}

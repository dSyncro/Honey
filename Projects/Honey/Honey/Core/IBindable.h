/**
 * @file IBindable.h
*/

#pragma once

namespace Honey {

	/**
	 * @brief Interface for Bindable objects.
	*/
	class IBindable {

	public:

		virtual ~IBindable() = default;

		/**
		 * @brief Bind object.
		*/
		virtual void bind() const = 0;

		/**
		 * @brief Unbind object.
		*/
		virtual void unbind() const = 0;

		/**
		 * @brief Check if object is bound.
		 * @return A boolean expressing if the object is bound or not.
		*/
		virtual bool isBound() const = 0;

	};

}

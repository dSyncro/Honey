#pragma once

namespace Honey {

	class IBindable {

	public:

		virtual ~IBindable() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual bool IsBound() const = 0;

	};

}

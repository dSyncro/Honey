#pragma once

#include "Font.h"

#include <Honey/Core/Assertion.h>

namespace Honey {

	class FontLibrary {

	public:

		FontLibrary();
		~FontLibrary();

		void AddFont(const Reference<Font>& font);
		void RemoveFont(const Reference<Font>& font);

	private:

	};

}

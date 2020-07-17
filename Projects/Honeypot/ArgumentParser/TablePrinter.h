#pragma once

#include "../Libraries/Console.h"

#include <variant>
#include <vector>

class TablePrinter {

public:

	struct Column {

		struct Item {

			enum class CollapseMethod {
				Truncate = 0,
				Ellide,
				Multiline
			};

			Item(const std::string& value, AnsiStyle::Forecolors forecolor, AnsiStyle::Backcolors backcolor, 
				CollapseMethod collapse = CollapseMethod::Truncate);

			std::string Value;
			AnsiStyle::Forecolors ForegroundColor;
			AnsiStyle::Backcolors BackgroundColor;
			CollapseMethod Collapse;
		};

		Column(
			std::string header,
			float weight = 1,
			std::size_t minWidth = 0,
			AnsiStyle::Forecolors forecolor = Forecolors::Black,
			AnsiStyle::Backcolors backcolor = Backcolors::White,
			bool isVisible = true
		);

		Column(
			std::string header,
			std::size_t width,
			std::size_t minWidth = 0,
			AnsiStyle::Forecolors forecolor = Forecolors::Black,
			AnsiStyle::Backcolors backcolor = Backcolors::White,
			bool isVisible = true
		);

		std::string Header;
		std::variant<std::size_t, float> Measure;
		std::size_t MinimumWidth;
		AnsiStyle::Forecolors ForegroundColor;
		AnsiStyle::Backcolors BackgroundColor;
		bool IsVisible;

		std::size_t GetItemsCount() const { return _items.size(); }

		Item& GetItem(std::size_t index) { return _items[index]; }
		const Item& GetItem(std::size_t index) const { return _items[index]; }

		void AddItem(const Item& item) { _items.push_back(item); }

		void RemoveItem(const Item& item);
		void RemoveItemAt(std::size_t index);

		std::size_t IndexOf(const Item& item);

		static bool HaveSameName(const Column& a, const Column& b) { return a.Header == b.Header; }

	private:

		std::vector<Item> _items;
	};

	TablePrinter(std::size_t maxWidth = 64) : MaximumWidth(maxWidth) {}
	~TablePrinter() = default;

	std::size_t GetColumnsCount() const { return _columns.size(); }

	void AddColumn(const Column& column) { _columns.push_back(column); }
	void Clear() { _columns.clear(); }

	Column& GetColumn(std::size_t index) { return _columns[index]; }
	const Column& GetColumn(std::size_t index) const { return _columns[index]; }

	void Remove(const Column& column);
	void RemoveAt(std::size_t index);

	std::size_t GetMinimumWidth() const;
	std::size_t IndexOf(const Column& column) const;

	void Print();

	std::size_t MaximumWidth;

private:

	std::vector<Column> _columns;
};
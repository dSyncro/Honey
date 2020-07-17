#include "TablePrinter.h"

using namespace AnsiStyle;

TablePrinter::Column::Item::Item(const std::string& value, Forecolors forecolor, Backcolors backcolor, CollapseMethod collapse)
	: Value(value), ForegroundColor(forecolor), BackgroundColor(backcolor), Collapse(collapse)
{
}

TablePrinter::Column::Column(
	std::string header,
	float weight,
	std::size_t minWidth,
	Forecolors headerForeColor,
	Backcolors headerBackColor,
	bool isVisible
)
	: Header(header),
	Measure(weight),
	MinimumWidth(minWidth),
	BackgroundColor(headerBackColor),
	ForegroundColor(headerForeColor),
	IsVisible(isVisible)
{
}

TablePrinter::Column::Column(
	std::string header,
	std::size_t width,
	std::size_t minWidth,
	Forecolors headerForeColor,
	Backcolors headerBackColor,
	bool isVisible
)
	: Header(header),
	Measure(width),
	MinimumWidth(minWidth),
	BackgroundColor(headerBackColor),
	ForegroundColor(headerForeColor),
	IsVisible(isVisible)
{
}

void TablePrinter::Column::RemoveItem(const Item& item)
{
	std::size_t index = IndexOf(item);
	RemoveItemAt(index);
}

void TablePrinter::Column::RemoveItemAt(std::size_t index)
{
	if (index >= _items.size()) return;
	_items.erase(_items.begin() + index);
}

std::size_t TablePrinter::Column::IndexOf(const Item& item)
{
	std::size_t i;
	for (i = 0; i < _items.size(); i++)
		if (item.Value == _items[i].Value) break;
	return i;
}

std::size_t TablePrinter::GetMinimumWidth() const
{
	std::size_t min = 0;
	for (const Column& col : _columns)
		min += col.MinimumWidth;
	return min;
}

std::size_t TablePrinter::IndexOf(const Column& column) const
{
	std::size_t i;
	for (i = 0; i < _columns.size(); i++)
		if (Column::HaveSameName(_columns[i], column)) break;
	return i;
}

void TablePrinter::Remove(const Column& column)
{
	std::size_t index = IndexOf(column);
	RemoveAt(index);
}

void TablePrinter::RemoveAt(std::size_t index)
{
	if (index >= _columns.size()) return;
	_columns.erase(_columns.begin() + index);
}

void TablePrinter::Print()
{
	std::size_t fixedWidth = 0;
	float globalWeight = 0.0f;

	for (const Column& col : _columns)
	{
		if (col.Measure.index() == 0) fixedWidth += std::get<0>(col.Measure);
		else globalWeight += std::get<1>(col.Measure);
	}

	std::size_t distributable = MaximumWidth - fixedWidth;

	std::size_t maxRows = 0;
	std::size_t columnCount = _columns.size();

	std::size_t* rows = new std::size_t[columnCount];
	std::size_t* widths = new std::size_t[columnCount];

	for (std::size_t i = 0; i < _columns.size(); i++)
	{
		std::size_t width;
		const Column& col = _columns[i];
		switch (col.Measure.index())
		{
			case 0:
				width = std::get<0>(col.Measure);
				break;
			case 1:
				width = distributable * std::get<1>(col.Measure) / globalWeight;
				break;
			default:
				width = 0;
				break;
		}

		widths[i] = width;

		if (!col.IsVisible) continue;

		Console::SetForegroundColor(col.ForegroundColor);
		Console::SetBackgroundColor(col.BackgroundColor);
		Console::Align(Console::AlignmentInfo(width), col.Header);

		std::size_t count = col.GetItemsCount();
		rows[i] = count;
		if (count > maxRows) maxRows = count;
	}

	for (std::size_t rowIndex = 0; rowIndex < maxRows; rowIndex++)
	{
		for (std::size_t columnIndex = 0; columnIndex < columnCount; columnIndex++)
		{
			if (rows[columnIndex] < rowIndex) continue;

			const Column& col = _columns[columnIndex];
			if (!col.IsVisible) continue;

			const Column::Item& item = col.GetItem(rowIndex);
			if (item.Value.length() > widths[columnIndex])
			{
				switch (item.Collapse)
				{
					case Column::Item::CollapseMethod::Truncate:
						break;
					case Column::Item::CollapseMethod::Ellide:
						break;
					case Column::Item::CollapseMethod::Multiline:
						break;
				}
			}
			else Console::Align(Console::AlignmentInfo());
		}
	}

	delete[] rows;
	delete[] widths;
}
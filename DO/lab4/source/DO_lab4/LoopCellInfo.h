#pragma once

#include "Cell.h";

struct LoopCellInfo {
	LoopCellInfo& operator=(const LoopCellInfo& a) {
		Cell = a.Cell;
		Plus = a. Plus;
		RowIndex = a.RowIndex;
		ColIndex = a.ColIndex;
		return *this;
	}

	Cell& Cell;
	bool Plus;
	int RowIndex;
	int ColIndex;
};
#include "Board.h"
#include <map>

Board::Board(int n_rows, int n_columns, int n_types, std::vector<int> count):
	n_rows(n_rows), n_columns(n_columns),
	_pokemons(std::vector<std::vector<int>>(n_rows, std::vector<int>(n_columns, -1)))
{
	std::map<int, int> countType; // countType[x] counts number of type x
	for (int i = 0; i < n_rows; ++i) {
		for (int j = 0; j < n_columns; ++j) {
			int type;
			do {
				type = rand() % n_types;
			} while (countType[type] >= count[type]);
			countType[type] += 1;
			addPokemon(i, j, type + 1);
		}
	}
}

int Board::getNRows()
{
	return n_rows;
}

int Board::getNColumns()
{
	return n_columns;
}

void Board::addPokemon(int x, int y, int type)
{
	_pokemons[x][y] = type;
}

int Board::getPokemon(int x, int y)
{
	return _pokemons[x][y];
}

void Board::removePokemon(int x, int y)
{
	_pokemons[x][y] = -1;
}
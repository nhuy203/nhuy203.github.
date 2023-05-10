#pragma once
#include <vector>

class Board
{
    int n_rows, n_columns;

    std::vector<std::vector<int>> _pokemons;	// pokemons

public:
	
	Board(int n_rows, int n_columns, int n_types, std::vector<int> count);

	int getNRows();

	int getNColumns();

	void addPokemon(int x, int y, int type);

	int getPokemon(int x, int y);

	void removePokemon(int x, int y);

};

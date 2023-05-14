# Pikachu Game

Pikachu Game made with C++, SDL2.

I. Introduction.

The Matching Game (commonly known as Pikachu Puzzle Game) includes a board of multiple cells, each of which presents a figure. The player finds and matches a pair of cells that contain the same figure and connect each other in some particular pattern. A legal match will make the two cells disappear. The game ends when all matching pairs are found.

II.Detailed Description.

1. Standard Mode.

   1.1 Game starting: Initialize a board with the given size while satisfying the following conditions
  
        +) The total number of cells must be even.

        +) The number of distinct characters is specified in advance.

        +) For each character, determine an even number to define the number of occurrences for that character.
        
    1.2 Any matching pair must satisfy the following conditions.
    
        +) Characters on the two cells must be identical.
        
        
        +) When the cells disappear, their positions are replaced with blank spaces.
        
    1.3 Game finishing: check the following conditions.
    
        +) Are there any cells left?
        
        +) Are there any valid pairs left?
 
  2. Advaned Features.

    Players will experience the game better if one (or more) of the following extras can be added to the game.
    
        +) Color and sound effects.
        
        +) Leaderboard: The top N players that finished their games with the shortest time will register their information to the Leaderboard.
        
        +) Move suggestion: Show player a valid match when they press the "Help" key.

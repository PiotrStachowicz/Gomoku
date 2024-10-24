# Gomoku Game in C

Simple Gomoku game written in C, featuring an computer opponent using the Minimax algorithm with Alpha-Beta pruning. 
###### Maybe I'll add Monte Carlo Tree Search in the future... who knows :)

## Minimax Algorithm

The Minimax algorithm is a decision-making algorithm used in games to determine the optimal move for a given player.

#### Pseudo code:
```C++
function Minimax(node, depth, isMaximizingPlayer):
    if depth == 0 or node is a terminal node:
        return evaluate(node)  // Return the static evaluation of the node

    if isMaximizingPlayer:
        bestValue = -∞
        for each child of node:
            value = Minimax(child, depth - 1, false)  // Recursively call Minimax
            bestValue = max(bestValue, value)  // Maximize player's best option
        return bestValue
    else:
        bestValue = +∞
        for each child of node:
            value = Minimax(child, depth - 1, true)  // Recursively call Minimax
            bestValue = min(bestValue, value)  // Minimize opponent's best option
        return bestValue
```

## Alpha-Beta Pruning

Alpha-Beta pruning is an optimization technique for the Minimax algorithm. It reduces the number of nodes evaluated by the algorithm by "pruning" branches that cannot influence the final decision.

#### Pseudo code:
```C++
function AlphaBeta(node, depth, alpha, beta, isMaximizingPlayer):
    if depth == 0 or node is a terminal node:
        return evaluate(node)  // Return the static evaluation of the node

    if isMaximizingPlayer:
        bestValue = -∞
        for each child of node:
            value = AlphaBeta(child, depth - 1, alpha, beta, false)
            bestValue = max(bestValue, value)
            alpha = max(alpha, bestValue)  // Update alpha
            if beta <= alpha:  // Beta cut-off
                break  // No need to explore further
        return bestValue
    else:
        bestValue = +∞
        for each child of node:
            value = AlphaBeta(child, depth - 1, alpha, beta, true)
            bestValue = min(bestValue, value)
            beta = min(beta, bestValue) 
```

## How to Run

1. **Clone the Repository**:
  Clone this repository to your local machine using:
  ```bash
  git clone <repository-url>
  ```
  
  Navigate to the Project Directory: Go to the project directory where the Makefile is located:

  ```bash
  cd src
  ```

2. **Build the Project**: Use the Makefile to compile the program:
  ```bash
  make
  ```

3. **Run the Game**: After building, run the executable to start the game:
  ```bash
  ./gomoku
  ```


## Feel Free to Contribute

Feel free to make any modifications or improvements to the project.

## License

This project is licensed under the MIT License. 
# Mastermind
Mastermind is a game in which the player tries to guess a secret combination of colors. The combination is a sequence of four pegs; each peg can be one of six different colors. (It is possible that some of the pegs could be the same color). The player must guess the correct colors in the correct order in order to win.

Every time the player guesses, they are told two numbers: the number of pegs that are correct where they are, and the number of pegs that could be correct if they were moved to a different position. For instance, the picture below there is one peg in the right place and two in the wrong place. The remaining peg does not belong in the combination

<img width="300" alt="Screen Shot 2022-06-10 at 12 56 07 AM" src="https://user-images.githubusercontent.com/83131937/173008298-c57dd766-f257-4bc2-82e3-703a13cb27fe.png">

Notice each peg can only be paired with one other. Thus, in the picture below only one blue peg could be moved into a correct position, not both. Similarly the red peg could only be moved into one correct position, not both. This guess should be marked as having two pegs in the wrong place.

<img width="300" alt="Screen Shot 2022-06-10 at 12 57 44 AM" src="https://user-images.githubusercontent.com/83131937/173008538-03cdd615-cbc3-42a7-9254-40a5567dfe85.png">

The user continues to guess until he gets the correct combination. The goal is to get the correct combination in as few guesses as possible.

## Mastermind Program
This C++ program allows the user to play Mastermind using numbers to represent colors. For instance, given 7 colors, then the numbers will 1 - 7.

### Workflow

- How many pegs must be between 2 and 8.
- How many colors must be between 6 and 20.
- If the user enters something out of bounds, the program will simply replace with the minimum value if too small or the maximum value if too large.

## Demo
![mastermind-demo](https://user-images.githubusercontent.com/83131937/173007567-7ebd66a1-18d5-41d0-95c2-01824d1a006d.gif)

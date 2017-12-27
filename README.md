# Scrabble Game with GUI

This side project uses the SFML library to create a visually appealing Scrabble game. The
gameboard image is a direct scan of an authentic American scrabble board; however, all
other images are custom made using Adobe Illustrator.

Currently, this project is unfinished. I am slowly working both the backend and frontend.
The draggable tiles are responsive and satisfying to control. In addition, I have created
and tested a trie like data structure for implementing an AI that was inspired by [this article](http://ericsink.com/downloads/faster-scrabble-gordon.pdf).

I will be updating this project when I have a change.

Recent updates:
* Button object that has a clicked sprite and unclicked sprite that functions like a normal button (since the SFML library does not provide such a feature).

TODO:
* Implement verification system and method after placing a word on the board.
* Create system for keeping track of the remaining tiles and randomly chosing and placing the proper amount of tiles into the rack.
* Update backend handling of tiles that have been placed and verified on previous turns.
* Create gameloop.
* Implement AI system for determining all possible moves and create system for documentic heuristics in order to improve speed and intelligence. 

This project is compeltely for fun. Here is a gif showcasing the current GUI functionality:

![gif example](pics/LargeGIF.gif)

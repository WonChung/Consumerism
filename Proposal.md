# Final Project Proposal
Henry Chen and Won Chung

Overview
We'll be making an implementation of the online multiplayer game agar.io with a few
simplifications.  This implementation will take place in a windowed mode where the
user selects which mode they would like to play in. The UI will be similar to that
of Lab 3, where the users chooses which game mode to play (in addition to the exit button)  
The options are 1) Singleplayer with no movement (only the user's ball can move),
 2) Singleplayer with random AI movement, and 3) completely random AI with no
 player involvement (as to simulate an AI FFA).  
In the game, the user controls a ball that runs into and absorbs other nearby
smaller balls to increase in size (with size being inversely related to speed),
with a scoreboard in the corner listing top ball sizes (based on area). The user
loses when his/her ball runs into the ball that is bigger in size. 

# Course Concepts Used
Windowed interactions via mouse and keyboard based off of QTCreator.
Parallelization of position and velocity calculations via CUDA.
Texture mapping of the background via OpenGL.  

# Other software Tools
OpenGL,  QTCreator, and CUDA.

# Goals
Create a windowed mode game that we can implement with CUDA, OpenGL, QTCreator.
There are options on the side of the window for the user to choose the gamemode,
or to exit.

Our stretch goals to implement "upgrades" that the user's ball can pickup to
increase its speed or size.

# References
MetaBalls for 2D collisions.  
Agar.io for inspiration.  
Labs - 2 -> QTWindow. 3 -> QTMovement, 4 ->Texturemapping, 7->CUDA Cores.

# Assessment

 What would make your project a success?

 A game that imitates agar.io while improving upon the monotonous gameplay that
 the web based game provides. We successfully have a game that does not break or
 have a bunch of memory leaks with the MetaBalls. As long as we get a decent
 understanding of MetaBalls, we are quite content.

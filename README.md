# 2DTransformations
This C++ project is a graphical application that implements a simple animation of the Mario Bros. mushroom using the Qt framework. The program creates a widget with various timers and event handlers to control the movement and rendering of the figure.

The main features of the project include:
- Timer Initialization: Several timers are set up to control different animations within the application.
- Figure Initialization: The coordinates of the mushroom figure from the Mario Bros. game are assigned using homogeneous coordinates.
- Keyboard Event Handling: The program responds to key presses to allow the user to translate the figure using the arrow keys (A, D, W, S).
- Paint Event: The paintEvent function is overridden to handle the rendering of the figure on the widget using QPainter.
- Drawing Functions: The dibujarFiguraMapeada function is responsible for drawing the mapped figure on the canvas.

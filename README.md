# function-grapher-fall23

This C++ program creates rendered images of graphs of mathematical expressions. The program takes in inputted functions, parses their expressions, evaluates them, and then renders them into an image based on specified bounds and colors. Explanations of the various methods are explained below. 

##READER:
The reader class reads input from a stream and proceeds to process various directives for plotting. These include plot, function, color, and fill(above, below, between). At the end, it constructs the elements to form a plot based on a specified input.

##PLOT: 
The plot class stores and organizes the information for the plot's bounds, functions, and fill directives. 

##IMAGE:
The image class deals with creating images, in particular initializing the width, height, and pixel data of the image.
##FILL:

The fill class fills the color in an image based on specified constraints. The function can fill for other above a function, below a function, or between two functions. 

##FUNC: 
The function class handles drawing a function on an image. It evaluates the x-coordinate based on specific bounds, and then assigns the corresponding pixel in the image with a specified function color as well.

##EXPR_PARSER:
The expression parser class parses mathematical expressions, handling tokens such as numbers, variables, and math operations. It further constructs an expression tree for the parsed expression to be evaluated

##EXPR
The expression class has various classes and methods to evaluate parsed expressions. It includes binary and unary operations, evaluating the expression for eventual use in plotting and rendering it. 

##RENDERER
The renderer class generates a rendered image using the information stored in function and fill of the Plot object. The renderer will initialize an image and process directives to draw functions and apply colors as well.

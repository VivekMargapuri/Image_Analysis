# Image_Analysis


There are 3 classes in the project namely Ffill, Displays and Perimeter.
Ffill is the class that has function called 'ffutil' which flood fills through the pixel values and we use a separate 'Mat' to fill these pixels with Red. As a result, we get the pixel representation of the flood fill algorithm.
The out put from ffutil function is utilized to draw a boundary around the pixels. It is important to note that the perimeter drawn is both inward and outward.
The class 'Displays' has two functions. Namely, display_imgs and display_pix.
display_imgs is utlized to load and show a simple RGB image  where as display_pix is used to render and show pixel representations of ffutil and perimeter functions.
Note: for the time being, display_imgs is itself being used for the rendering pixel representations. display_pix is not being used, however it is fully functional.
Note 2: Presently all the functions are being passed in a single command as different arguments. This means that currently with a single command we can see input image and results of ffutil and perimeter functions. The serial command line API has yet not been programmed. However, it will be done during the second session.

##### Make sure all the headers that contain classes are in the same folder as that of the view.cpp
### Instructions to run the code: 
1.cmake . <br />
2.make <br />
3. /view <target_image> <x_value> <y_value> <region_output_path> <perimeter_output_path> <br />
4. Press 1 to execute floodfill and press enter <br />
5. Close the image window (note: if the window doesn't close even after clicking 'x' mark, next instruction will appear on the command line) <br />
6. Press 2 to execute perimeter and press enter (repeat step 5) <br />
7. Press 3 to execute smooth_perimeter and press enter <br />


### Design of the approach:
While being a part of a big team, it is really important that code has to be modular and easily readable. As a result, I've created classes for each of different set of functions. The Ffill class currently has only function. However, we can call the same function with more or less number of arguments (function overloading). This helps to add multiple more minute parameters such a upper_threshold, lower_threshold, distance_threshold and many more. In my function, I primarily used BGR values of pixel and similiarity of the pixel to its neighbour depends on how much more or less overall intensities of two neighboring pixels differ. Hence, I individually set a low and high threshold of each of BGR value by trial and error. This method can further me improved by passing more parameters as argument to the function. All similar pixels have been colored red in this function and others are made black.  Additonally, to draw a fine boundary, each black pixel that has red neighbor is colored green. Presently the thickness of boundary is 1 pixel. This can be intensified by coloring an additional layer of black pixels surrounding the red ones.

#### Smoothening the perimeter:
My initial idea was to straight away implementing gaussian smoothening on the image. However, since I wasn't able to complete the entire function in the given time, I had to change my approach and perform box smoothening. It is not as concrete as gaussian smoothening but the change is easily noticable. As my 'ffutil' function strictly produces output in red and black pixels, each red pixel that doesn't have many neighboring red pixels is colored into black pixel. In this way, several countours and irregularities are eliminated. Finally, the a green border is drawn to the smoothened result.

#### Future Work:
It would be more productive to add additional parameters to flood fill and smooth_perimeter functions such that we can control the lower and upper pixel thresholds or thickness of the border to be drawn by  passing these values as paramters. As far a smooth_perimeter function is considered, I would like to try gaussian smootheing or curve fitting and compare the results of both to see how they perform with respect to different images.

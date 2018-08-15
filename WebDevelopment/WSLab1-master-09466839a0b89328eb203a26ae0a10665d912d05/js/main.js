/*
 * S18 CSCI470 Web Science
 * Single Page Web App Example - Behaviors
 * 
 * Phillip J. Curtiss, Assistant Professor
 * Department of Computer Science, Montana Tech
 * pcurtiss@mtech.edu, 406-498-5679
 * (c) 2018 All Rights Reserved
 */

// Unless necessary, leave the global scope as we found it by using an
// immediately invoked function expression (IIFE) - A type of function closure
(function() {
    // Obtain references to document elements we need
    var canvasElement = document.getElementById('scribbleArea');
    var clearButton = document.getElementById('clearButton');
	var colorButton = document.getElementById('colorButton');
	var eraseButton = document.getElementById('eraseButton');
	var sizeButton = document.getElementById('sizeButton');
	var w = window.innerWidth * .8;
	var h = window.innerHeight * .6;
	canvasElement.width = w;
	canvasElement.height = h;
	
	
    // Create a 2D drawing context from the Canvas element
    var context = canvasElement.getContext("2d");
	
    // These arrays store all of our stokes - this could be optimized using
    // an array of a single javascript object - more to follow
    var clickX = new Array(); // holds X-coordinate of mouse relative to canvasElement
    var clickY = new Array(); // holds Y-coordinate of mouse relative to canvasElement
    var clickDrag = new Array(); // holds whether point continues existing path
	var color = new Array(); // Holds the color of the line
	var width = new Array(); // Holds the width of the line
	
    // Determine if we are in a painting mode or not - for mouse movement
    var paint = false;
	var erase = false;
	
	//Track the current color, with the default being a blue
	var curColor = "#3333ff";
	var curColBool = false;
	var lineWidth = 5;
	var curWidth = 0;
    
	// Add the mouse coordinates and when we are starting a new stroke or not
    function addClick(x, y, dragging) {
        clickX.push(x);
        clickY.push(y);
        clickDrag.push(dragging);
		color.push(curColor);
		width.push(lineWidth);
    }

    // Redraw the canvas element contents - redrawing all of the paths
    function redraw() {
        // Clear the canvas
        context.clearRect(0, 0, context.canvas.width, context.canvas.height);

        // Setup the styles associated with drawing on the canvas
        context.lineJoin = "round"; // End-cap style
        

        // Iterate over the points in the array...
        for (var ndx = 0; ndx < clickX.length; ndx++) {
            // Start a path to stroke (draw)
            context.beginPath();

            // If true, move between the points comprising the path, 
            // otherwise, move to the start of the new path
            if (clickDrag[ndx] && ndx) {
                context.moveTo(clickX[ndx - 1], clickY[ndx - 1]);
            } else {
                context.moveTo(clickX[ndx] - 1, clickY[ndx]);
            }
			//Changes the color and width of the stroke to the stored values
			context.strokeStyle = color[ndx]; // Color of strokes
			context.lineWidth = width[ndx]; // width of the stroke
		
            // Draw from where the point currently is,
            // to the point given to the lineTo method
			context.lineTo(clickX[ndx], clickY[ndx]);
            context.closePath();
            context.stroke();
        }
    }

    // Event: MouseDown - Behavior from the User
    // Add an event listener to the canvasElement, passing
    // the anonymous function as the event handler
    canvasElement.addEventListener("mousedown", function(e) {
        // Get the current coordinates of the mouse
        // relative to the "page" offset from the canvasElement
        var mouseX = e.pageX - this.offsetLeft;
        var mouseY = e.pageY - this.offsetTop;

        // Begin paint mode... add the point as the start of a new
        // path to the array(s)
        if(!erase){
			paint = true;
			addClick(mouseX, mouseY, false);
		}else{
			erase = false;
			eraser(mouseX, mouseY);
		}
		
        // Redraw the canvas with the new path segment
        redraw();
    });
	
	//Removes points from the arrays if it's within a distance of the 
	function eraser(x, y){
		for(var i = 0; i < clickX.length; i++){
				if(Math.abs(clickX[i] - x)  < 10 && Math.abs(clickY[i] - y) < 10){
					clickX.splice(i, 1);
					clickY.splice(i, 1);
					color.splice(i, 1);
					width.splice(i, 1);
					clickDrag.splice(i, 1);
				}
			}
	}

    // Event: MouseMove - Behavior from the User
    // Add an event listener to the canvasElement, passing
    // the anonymous function as the event handler
    canvasElement.addEventListener("mousemove", function(e) {
        var mouseX = e.pageX - this.offsetLeft;
        var mouseY = e.pageY - this.offsetTop;
		
		// If we are in paint mode, then continue to add points
        // to the path we are constructing (dragging = true)
        if (paint) {

            // Set dragging to true to indicate we move point to point
            addClick(mouseX, mouseY, true);

            // Update canvas with the new points of the segment
            redraw();
			
        } else if (erase){
			eraser(mouseX, mouseY);
			redraw();
		}
    });

    // Event: MouseUp - Behavior from the User
    // Add an event listener to the canvasElement, passing
    // the anonymous function as the event handler
    canvasElement.addEventListener("mouseup", function(e) {
        // Turn off painting mode
        paint = false;
    });

    // Event: MouseLeave - Behavior from the User
    // Add an event listener to the canvasElement, passing
    // the anonymous function as the event handler
    canvasElement.addEventListener("mouseleave", function(e) {
        // Turn off painting mode
        paint = false;
    });

    // Event: Click - Behavior from the User
    // Add an event listener to the clearButton, passing
    // the anonymous function as the event handler
    clearButton.addEventListener("click", function(e) {
        // Reset the arrays that hold the path data
        clickX.length = 0;
        clickY.length = 0;
        clickDrag.length = 0;

        // Redraw the canvas
        redraw();
    });
	
	// Event: Click - Behavior from the User
	// Add an event listener to the colorButton, passsing 
	// the anonymous function as the event handler
	colorButton.addEventListener("click", function(e) {
		if(curColBool){
			curColor = "#3333ff";
		}else {
			curColor = "#ffff33";
		}
		curColBool = !curColBool;
	});

	// Event: Click - Behavior from the User
	// Add an event listener to the eraseButton, passing
	// the anonymous function as the event handler
	eraseButton.addEventListener("click", function(e) {
		if(erase){
			erase = false;
		} else{
			erase = true;
			paint = false;
		}
		
	});
	
	// Event: Click - Behavior from the User
	// Add an event listener to the sizeButton, passing 
	// the anonymous function as the event handler
	sizeButton.addEventListener("click", function(e) {
		if(curWidth == 0){
			lineWidth = 7;
			curWidth = curWidth + 1;
		}else if (curWidth == 1){
			lineWidth = 9;
			curWidth = curWidth + 1;
		}else if (curWidth == 2){
			lineWidth = 5;
			curWidth = 0;
		}
		
	});
	
	
})(); // End of Main IIFE
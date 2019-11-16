//Used Basem's files as the base code
"use strict";

var gl;
var pointList = [];
var colorList = []

window.onload = function init()		// If we want a function to be executed first, we have to wait for this function call (called the onload event)
// It occurs when all the script files have been read in the HTML
{
    var canvas = document.getElementById( "gl-canvas" );	// Acts like a pointer; gets the position of the element gl-canvas 
	// The return value of the function above is a WebGL context. It is a JS object that contains all the WebGL functions and parameters
    
	gl = WebGLUtils.setupWebGL( canvas );
	// Functions such as gl.bindbuffer, gl.FLOAT, gl.TRIANGLES are all members of this object 
    
	if ( !gl ) { alert( "WebGL isn't available" ); }

   	
		// We can adjust the h/w of the viewport to match the aspect ratio of the clipping rectangle
		// to ensure we don't distort objects 
		gl.viewport( 0, 0, canvas.width, canvas.height );	
		gl.clearColor( 0, 0, 0, 1);
	
		//  Load shaders and initialize attribute buffers
		
		// To connect these entities, we use the following function (involves reading source code, compiling individual parts and linking everything together)
		var program = initShaders( gl, "vertex-shader", "fragment-shader" );	// program variable holds our shaders (one for each shader)
		gl.useProgram( program );
	
        
        pointList =  [vec2(-1, -1), vec2(0, 1), vec2(1, -1)];
        colorList = [vec4(0,0,1,1), vec4(1,0,0,1), vec4(0,1,0,1)];
		// Load the data into the GPU
		
		// The following creates a vertex buffer object on the GPU and then places our data in it 
		var buffer = gl.createBuffer();
		gl.bindBuffer( gl.ARRAY_BUFFER, buffer );	//gl.ARRAY_BUFFER indicates that the data in the buffer will be vertex attribute data rather than indices to the data
		// The binding operation makes this buffer the current buffer. Subsequent functions that put data in a buffer will use this buffer until we bind a different buffer.
		
		gl.bufferData( gl.ARRAY_BUFFER, flatten(pointList), gl.STATIC_DRAW );	// Accepts only native types (not JS objs) --> therefore flatten used
		// The above places the data into the buffer		
				
		
		// Used to specify how to pull data out of your buffer and provide them to your vertex shaders 
		// The code above just pushed all the data. The code below indicates what the data represents 
		
		// Establishes a connection between the array in the application and the input array vPosition in the shader.
		var vPosition = gl.getAttribLocation( program, "vPosition" );
		gl.vertexAttribPointer( vPosition, 2, gl.FLOAT, false, 0, 0 );	
        gl.enableVertexAttribArray( vPosition );
        

        var buffer2 = gl.createBuffer();
        gl.bindBuffer( gl.ARRAY_BUFFER, buffer2 );
        gl.bufferData( gl.ARRAY_BUFFER, flatten(colorList), gl.STATIC_DRAW );
    
       
    
        var vCol = gl.getAttribLocation(program, "vCol");
        gl.vertexAttribPointer(vCol, 4, gl.FLOAT, false, 0, 0); 
        gl.enableVertexAttribArray(vCol);
    
		
		render();
	
  
};
 

function render() 		// Controls the drawing onto the canvas 
{
    gl.clear( gl.COLOR_BUFFER_BIT );
	gl.drawArrays(gl.TRIANGLES,0,pointList.length);
	
}




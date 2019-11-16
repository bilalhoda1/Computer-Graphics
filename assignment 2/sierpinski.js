//Used Basem's files as the base code
"use strict";

var gl;
var pointList = [];


window.onload = function init()		// If we want a function to be executed first, we have to wait for this function call (called the onload event)
// It occurs when all the script files have been read in the HTML
{
    var canvas = document.getElementById( "gl-canvas" );	// Acts like a pointer; gets the position of the element gl-canvas 
	// The return value of the function above is a WebGL context. 
    
	gl = WebGLUtils.setupWebGL( canvas );
	// Functions such as gl.bindbuffer, gl.FLOAT, gl.TRIANGLES are all members of this object 
    
	if ( !gl ) { alert( "WebGL isn't available" ); }

   
	//checks if the input is correct or not.
	var recursionDepth = prompt("Please specify recursion depth (Enter less than 16 otherwise recursion depth would exceed)");
	var flag = true;
	while (flag){
		if (recursionDepth==null)
		{
			break;
		}
		else if (parseInt(recursionDepth)>15)
		{
			recursionDepth = prompt("Please enter an integer value less than 16");
		}

		else if (parseInt(recursionDepth) == recursionDepth){
			flag = false;
		}
		else{
			recursionDepth = prompt("Please enter an integer value");
		}
	}
	
	if (recursionDepth!=null) {

		recursionDepth = parseInt(recursionDepth);
		var vertices = [vec2(-1,-1),vec2(1,-1),vec2(0,1)]
		generateSierpinski(vertices,recursionDepth);
		
		
		// We can adjust the h/w of the viewport to match the aspect ratio of the clipping rectangle
	
		gl.viewport( 0, 0, canvas.width, canvas.height );	
		gl.clearColor( 1.0, 1.0, 1.0, 1.0 );
	
				
		// The initialization, creation of geometry, and rendering code are all written in JavaScript whereas the shaders are written in GLSL. 
		// To connect these entities, we use the following function (involves reading source code, compiling individual parts and linking everything together)
		var program = initShaders( gl, "vertex-shader", "fragment-shader" );	// program variable holds our shaders (one for each shader)
		gl.useProgram( program );
	
		
	
		// The following creates a vertex buffer object on the GPU and then places our data in it 
		var bufferId = gl.createBuffer();
		gl.bindBuffer( gl.ARRAY_BUFFER, bufferId );	//gl.ARRAY_BUFFER indicates that the data in the buffer will be vertex attribute data rather than indices to the data
		// The binding operation makes this buffer the current buffer. Subsequent functions that put data in a buffer will use this buffer until we bind a different buffer.
		
		gl.bufferData( gl.ARRAY_BUFFER, flatten(pointList), gl.STATIC_DRAW );	// Accepts only native types (not JS objs) --> therefore flatten used
		// The above places the data into the buffer
		// Last parameter determines how we will use the data. If we are sending them once and displaying them only then gl.STATIC_DRAW suffices
		
		
		
		// Associate our shader variables with our data buffer
		
		
		// Used to specify how to pull data out of your buffer and provide them to your vertex shaders 
		// The code above just pushed all the data. The code below indicates what the data represents 
		
		// Establishes a connection between the array in the application and the input array vPosition in the shader.
		var vPosition = gl.getAttribLocation( program, "vPosition" );
		gl.vertexAttribPointer( vPosition, 2, gl.FLOAT, false, 0, 0 );	
		gl.enableVertexAttribArray( vPosition );
		render();
	
  }
};
 
function generateSierpinski(edges, depth) {
	if(depth === 0) {
	  pointList.push(...edges[0]);
	  pointList.push(...edges[1]);
	  return pointList.push(...edges[2]);
	}
	var midPoints = [
	  mix(edges[0], edges[1], 0.5),
	  mix(edges[0], edges[2], 0.5),
	  mix(edges[1], edges[2], 0.5)
	];
	depth--;
	generateSierpinski([edges[0], midPoints[0], midPoints[1]], depth);
	generateSierpinski([edges[1], midPoints[0], midPoints[2]], depth);
	generateSierpinski([edges[2], midPoints[1], midPoints[2]], depth);
  }

function render() 		// Controls the drawing onto the canvas 
{
    gl.clear( gl.COLOR_BUFFER_BIT );
	gl.drawArrays(gl.TRIANGLES,0,pointList.length);
	// First parameter could be gl.POINTS, gl.LINES, gl.TRIANGLES, gl.LINE_STRIP, gl.LINE_LOOP etc. 
	// Last parameter states how many points to display NOT the end position 
	
}




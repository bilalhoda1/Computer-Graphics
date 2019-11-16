//Reference: some code has been taken from author's website 
"use strict";
var canvas;
var gl;
var boundary = false;
var interior = true;
var interpolate = false;
var rgb1 = [1,0,0,1];
var rgb2 = [1,0,0,1];
var rgb3 = [1,0,0,1];
var colors = [];
var vertices = [];
function init()
{
    canvas = document.getElementById( "gl-canvas" );

    gl = WebGLUtils.setupWebGL( canvas );
    if ( !gl ) { alert( "WebGL isn't available" ); }

    //  Configure WebGL
 
    gl.viewport( 0, 0, canvas.width, canvas.height );
    gl.clearColor( 1.0, 1.0, 1.0, 1.0 );
    //  Load shaders and initialize attribute buffers
    var program = initShaders( gl, "vertex-shader", "fragment-shader" );
    gl.useProgram( program );

    vertices = [
        vec2(  -1,  0 ),
        vec2( 1,  0 ),
        vec2(  0,  1 ),
        vec2(  -1,  0 ),
        vec2( 1,  0 ),
        vec2(  0,  1 ),
    ]
    if (interpolate == true) {
        colors = 
        [vec4(rgb1), vec4(rgb2),
        vec4(rgb3), vec4(rgb1),
        vec4(rgb2), vec4(rgb3)                
       ];

    }
   else {
        colors = 
        [vec4(rgb1), vec4(rgb1),
        vec4(rgb1), vec4(rgb1),
        vec4(rgb1), vec4(rgb1),                
        ];
    }
    var program = initShaders( gl, "vertex-shader", "fragment-shader" );
    gl.useProgram( program );

    var bufferId = gl.createBuffer();
    gl.bindBuffer( gl.ARRAY_BUFFER, bufferId );  
    gl.bufferData( gl.ARRAY_BUFFER, flatten(vertices), gl.STATIC_DRAW );
    
    var vPosition = gl.getAttribLocation( program, "vPosition" );
    gl.vertexAttribPointer( vPosition, 2, gl.FLOAT, false, 0, 0 );	
    gl.enableVertexAttribArray( vPosition );
    
    var bufferId2 = gl.createBuffer();
    gl.bindBuffer( gl.ARRAY_BUFFER, bufferId2);  
    gl.bufferData( gl.ARRAY_BUFFER, flatten(colors), gl.STATIC_DRAW );
    
    var vColor = gl.getAttribLocation( program, "vColor" );
    gl.vertexAttribPointer( vColor, 4, gl.FLOAT, false, 0, 0 );	
    gl.enableVertexAttribArray( vColor );
    
    render();

};

//Note: we are dividing val by 255 because the colors should be in the range of 0 to 1 
// in web gl

//function to interpolate left vertex
function interpolateVertex1(val,color) {
    val = val/255;
    if (color == 'r'){
		rgb1[0] = parseFloat(val);
	}
	else if (color == 'green'){
		rgb1[1] = parseFloat(val);
	}
	else{
		rgb1[2] = parseFloat(val);
    }

}

//function to interpolate right vertex
function interpolateVertex2(val,color) {
    val = val/255;
    if (color == 'r'){
		rgb2[0] = parseFloat(val);
	}
	else if (color == 'g'){
		rgb2[1] = parseFloat(val);
	}
	else{
		rgb2[2] = parseFloat(val);
    }

}

//function to interpolate top vertex
function interpolateVertex3(val,color) {
    val = val/255;
    if (color == 'r'){
		rgb3[0] = parseFloat(val);
	}
	else if (color == 'g'){
		rgb3[1] = parseFloat(val);
	}
	else{
		rgb3[2] = parseFloat(val);
    }

}

//function to toggle Boundary
function toggleBoundary() {
    var checkbox = document.getElementById("boundary");
    if (checkbox.checked == true){
        boundary = true
    }
    else {
        boundary = false
    }
    render();
}

//function to toggle interior
function toggleInterior() {
    var checkbox = document.getElementById("interior");
    if (checkbox.checked == true){
        interior = true
    }
    else {
        interior = false
    }
    render();
}

//function to toggle interpolation
function toggleInterpolation() {
    var checkbox = document.getElementById("interpolate");
    if (checkbox.checked == true){
        interpolate = true
    }
    else {
        interpolate = false
    }
    render();
}
window.onload = init;

//render function
function render() {

   gl.clear( gl.COLOR_BUFFER_BIT );
   if (interior == true) {
    gl.drawArrays( gl.TRIANGLES, 0, 3);
   }

   if (boundary == true) {
    gl.drawArrays( gl.LINE_LOOP, 3, 3);
   }
	window.requestAnimFrame(init);
   // Requests the browser to display the rendering the next time it wants to refresh the display 
	
}


// Global variables
var points = [];
var colors = [];
var gl;
var NumTimesToSubdivide = 1;

// Flags
var x_rotate = false, y_rotate = true, z_rotate = false,
	translate = false;


var phi = Math.PI/2; // 0 degrees initially
var si = 0.007; //for change
var x = 0, y = 0, z = 0; 

var vRotationMat    = mat4( vec4(1,0,0,0),
					        vec4(0,1,0,0),
						    vec4(0,0,1,0),
						    vec4(0,0,0,1) ); // Rotation matrix

// Vertices

var vertices = [
	vec3(  0.0000,  0.0000, -1.0000 ),
	vec3(  0.0000,  0.9428,  0.3333 ),
	vec3( -0.8165, -0.4714,  0.3333 ),
	vec3(  0.8165, -0.4714,  0.3333 )
];

// Pointers to Vertex Shader vars
var cBuffer; // Color values
var vBuffer; // Vertex points


// (*) Shared pointers
var vPosition;
var vColor;
var vRotation;

window.onload = function init()
{
    var canvas = document.getElementById( "gl-canvas" );
    
    gl = WebGLUtils.setupWebGL( canvas );
    if ( !gl ) { alert( "WebGL isn't available" ); }

    //  Configure WebGL
    gl.viewport( 0, 0, canvas.width, canvas.height );
    
    // enable hidden-surface removal
    gl.enable(gl.DEPTH_TEST);    

    //  Load shaders and initialize attribute buffers
    var program = initShaders( gl, "vertex-shader", "fragment-shader" );
    gl.useProgram( program );
    
    // Create a buffer object, initialize it, and associate it with the
    //  associated attribute variable in our vertex shader
    cBuffer = gl.createBuffer();
    gl.bindBuffer( gl.ARRAY_BUFFER, cBuffer );
    
    vColor = gl.getAttribLocation( program, "vColor" );
    gl.enableVertexAttribArray( vColor );

    vBuffer = gl.createBuffer();
    gl.bindBuffer( gl.ARRAY_BUFFER, vBuffer );

    vPosition = gl.getAttribLocation( program, "vPosition" );
    gl.enableVertexAttribArray( vPosition );
	
	// Transforms
	vRotation = gl.getUniformLocation( program, "vRotation" );

	// Subdivision Slider
    document.getElementById("slider_divisions").onchange = function(event) {
        NumTimesToSubdivide = event.target.value;
		points = []; // Clear previous 3D gasket
		divideTetrahedron( vertices[0], vertices[1], vertices[2], vertices[3],
                     NumTimesToSubdivide);
		
	};
	
	// Rotation Buttons
	document.getElementById("button_rotate_x").onclick = function() {
		x_rotate = true;		
		// diable other rotations
		y_rotate = false;
		z_rotate = false;
		
	};
	document.getElementById("button_rotate_y").onclick = function() {
		y_rotate = true;		
		// diable other rotations
		x_rotate = false;
		z_rotate = false;
		
	
	};
	document.getElementById("button_rotate_z").onclick = function() {
		z_rotate = true;		
		// diable other rotations
		x_rotate = false;
		y_rotate = false;
		
	};
	
    // Initial position state
    divideTetrahedron( vertices[0], vertices[1], vertices[2], vertices[3],
                 NumTimesToSubdivide);
    render(); // Start process
};

//
function rotate( change )
{
	var rotateMat = mat4();
	if(x_rotate){
		// Rotate object about current location x-axis
		phi = (2 * Math.PI * change); // range: [-2*PI, 2*PI]
		rotateMat = mat4( vec4(1,0,0,0),
				          vec4(0,Math.cos(phi),-Math.sin(phi),0),
					      vec4(0,Math.sin(phi),Math.cos(phi),0),
					      vec4(0,0,0,1) );
	}else if(y_rotate){
		// Rotate object about current location y-axis
		phi = (2 * Math.PI * change); // range: [-2*PI, 2*PI]
		rotateMat = mat4( vec4(Math.cos(phi),0,-Math.sin(phi),0),
					      vec4(0,1,0,0),
					      vec4(Math.sin(phi),0,Math.cos(phi),0),
					      vec4(0,0,0,1) );
	}else if(z_rotate){
		// Rotate object about current location z_axis
		phi = (2 * Math.PI * change); // range: [-2*PI, 2*PI]
		rotateMat = mat4( vec4(Math.cos(phi),-Math.sin(phi),0,0),
		   			      vec4(Math.sin(phi),Math.cos(phi),0,0),
					      vec4(0,0,1,0),
					      vec4(0,0,0,1) );
	}
	vRotationMat = mult(rotateMat, vRotationMat); // Update rotation matrix
}

function do_transforms()
{
	gl.uniformMatrix4fv( vRotation, false, flatten(vRotationMat) );
}




function triangle( a, b, c, color )
{
    // add colors and vertices for one triangle
    var baseColors = [
        vec3(1.0, 0.769, 0.145), //Gold
        vec3(0.643, 0.0, 0.275), //Maroon
        vec3(1.0, 0.769, 0.145), //Gold
        vec3(0.643, 0.0, 0.275), //Maroon
    ];

    colors.push( baseColors[color] );
    points.push( a );
    colors.push( baseColors[color] );
    points.push( b );
    colors.push( baseColors[color] );
    points.push( c );
}

function tetra( a, b, c, d )
{
    // tetrahedron with each side using
    // a different color
    triangle( a, c, b, 0 );
    triangle( a, c, d, 1 );
    triangle( a, b, d, 2 );
    triangle( b, c, d, 3 );
}

function divideTetrahedron( a, b, c, d, count )
{
    // check for end of recursion
    if ( count == 0 ) {
        tetra( a, b, c, d );
    }    
    // find midpoints of sides
    // divide four smaller tetrahedra
    else {
        var ab = mix( a, b, 0.5 );
        var ac = mix( a, c, 0.5 );
        var ad = mix( a, d, 0.5 );
        var bc = mix( b, c, 0.5 );
        var bd = mix( b, d, 0.5 );
        var cd = mix( c, d, 0.5 );

        --count;
        
        divideTetrahedron(  a, ab, ac, ad, count );
        divideTetrahedron( ab,  b, bc, bd, count );
        divideTetrahedron( ac, bc,  c, cd, count );
        divideTetrahedron( ad, bd, cd,  d, count );
    }
}

function render()
{
	setTimeout(function () {
	
        requestAnimFrame(render);
		gl.clearColor( 1, 1, 1.0, 1.0 );
		gl.clear( gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);
		rotate(si);
		// Load the data into the GPU
		 // (1) Position
		gl.bindBuffer( gl.ARRAY_BUFFER, vBuffer );
		gl.vertexAttribPointer( vPosition, 3, gl.FLOAT, false, 0, 0 );
		gl.bufferData( gl.ARRAY_BUFFER, flatten(points), gl.STATIC_DRAW );
		 // (2) Color
		gl.bindBuffer( gl.ARRAY_BUFFER, cBuffer );
		gl.vertexAttribPointer( vColor, 3, gl.FLOAT, false, 0, 0 );
		gl.bufferData( gl.ARRAY_BUFFER, flatten(colors), gl.STATIC_DRAW );
		
		// Apply transforms
		do_transforms();
		
		// Draw figure
		gl.drawArrays( gl.TRIANGLES, 0, points.length );	
		}, 18);

}

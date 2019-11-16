
var gl;
var canvas;
var circles;

// onload = myFunction;

// var vertices = [];

function quad(coordinates) {
	newCoords = [];
	
	for (var i = 0; i < coordinates.length; i++) {
		
		newCoords.push(coordinates[i]);
		var temp;
		
		if ( i == coordinates.length - 1 )
			temp = normalize(mix(coordinates[i], coordinates[0], 0.5));
		else
			temp = normalize(mix(coordinates[i], coordinates[i+1], 0.5));
		
		newCoords.push(temp);
	}
	return newCoords;	
}

/* function quad(coordinates, a, b, c, d) {
    transformed = []
    for (var i = 0; i < coordinates.length; i++) {
		transformed.push(subtract( scale(2, coordinates[i]), vec3(1,1,1) ))
    }
    return [transformed[a], transformed[b], transformed[c],
	    transformed[a], transformed[c], transformed[d]];
} */

window.onload = function init()
{
    canvas = document.getElementById( "gl-canvas" );
    
    gl = WebGLUtils.setupWebGL( canvas );
    if ( !gl ) { alert( "WebGL isn't available" ); }
	
	circles = parseInt(prompt("How many circles y'all wanna see? "));
	
	while ( circles > 6 || circles < 1 || isNaN(circles) ) {
		alert("Value must be an integer between 1-6 (inclusive)");
		circles = parseInt(prompt("How many circles y'all wanna see? "));
	}	

    //  Configure WebGL
    gl.viewport( 0, 12, canvas.width/6, canvas.height-12 );  // (x, y, w, h)
    gl.clearColor( 1.0, 1.0, 1.0, 1.0 );
    
    //  Load shaders and initialize attribute buffers
    var program = initShaders( gl, "vertex-shader", "fragment-shader" );
    gl.useProgram( program );
    
    // Compute data.
    var coordinates = [vec2(0,1), vec2(1,0), vec2(0,-1), vec2(-1,0)];    
	var vertices = [];
	vertices.push(...coordinates);
	
	for ( var i = 1; i < circles; i++ ) {
		coordinates	= quad(coordinates);
		vertices.push(...coordinates);
	}
	
    // Load the data into the GPU
    gl.bindBuffer( gl.ARRAY_BUFFER, gl.createBuffer() );
    gl.bufferData( gl.ARRAY_BUFFER, flatten(vertices), gl.STATIC_DRAW );

    // Associate out shader variables with our data buffer
    var vPosition = gl.getAttribLocation( program, "vPosition" );
    gl.vertexAttribPointer( vPosition, 2, gl.FLOAT, false, 0, 0 );  // stride
    gl.enableVertexAttribArray( vPosition );

    render();
};


function render() {
    gl.clear( gl.COLOR_BUFFER_BIT );
	gl.drawArrays( gl.LINE_LOOP, 0, 4 );
	
	for (var i = 1; i < circles; i++) {
		gl.viewport( (canvas.width/6)*i, 12, canvas.width/6, canvas.height-12 );
		gl.drawArrays( gl.LINE_LOOP, Math.pow(2, i+2)-4, Math.pow(2, i+2) );	
	}
    
}


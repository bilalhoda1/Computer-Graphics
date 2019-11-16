var gl;
var coordinates = [];
var colours = [];

window.onload = function init()
{
    canvas = document.getElementById( "gl-canvas" );
    
    gl = WebGLUtils.setupWebGL( canvas );
    if ( !gl ) { alert( "WebGL isn't available" ); }

    //  Configure WebGL
    gl.viewport( 0, 0, canvas.width, canvas.height );  // (x, y, w, h)
    gl.clearColor( 1.0, 1.0, 1.0, 1.0 );
    
    //  Load shaders and initialize attribute buffers
    var program = initShaders( gl, "vertex-shader", "fragment-shader" );
    gl.useProgram( program );
    
    // Compute data.
	color_mandelbrot(canvas.width, 100);	
	
    // Load the data into the GPU
    gl.bindBuffer( gl.ARRAY_BUFFER, gl.createBuffer() );
    gl.bufferData( gl.ARRAY_BUFFER, flatten(coordinates), gl.STATIC_DRAW );

    // Associate out shader variables with our data buffer
    var vPosition = gl.getAttribLocation( program, "vPosition" );
    gl.vertexAttribPointer( vPosition, 2, gl.FLOAT, false, 0, 0 );  // stride
    gl.enableVertexAttribArray( vPosition );
	
	var bufferId_color = gl.createBuffer();     
    gl.bindBuffer( gl.ARRAY_BUFFER, bufferId_color );  
	gl.bufferData( gl.ARRAY_BUFFER, flatten(colours), gl.STATIC_DRAW );
	
    var vColour = gl.getAttribLocation( program, "vColour" );
    gl.vertexAttribPointer( vColour, 4, gl.FLOAT, false, 0, 0 );	
    gl.enableVertexAttribArray( vColour );

    render();
};


function render() {
    gl.clear( gl.COLOR_BUFFER_BIT );
	gl.drawArrays( gl.POINTS, 0, coordinates.length );    
}

function mandelbrot(c, maxIterations) {

	var z = vec2(0,0);
	var escapeTime = 0;
	
	for (var i = 0; i < maxIterations; i++) {
		var a = 2.0 * z[0] * z[1] + c[1];
		z[0] = z[0] * z[0] - z[1] * z[1] + c[0];
		z[1] = a;
		escapeTime++;
		
		if ( length(z) > 2.0 ) {
			break;
		}		
	}
	return escapeTime;
}

function map_point(p, q, a, b, x)
{
	if (p.length != q.length || q.length != x.length)
		alert("inconsistent dimensions for p, q and x");
	else if (a.length != b.length)
		alert("inconsistent dimensions for a and b");
	
	if (typeof p == "number"){
		if (q!=p)
			var alpha = (x-p)/(q-p);		//for scalar values
		else
			alert("Point X is invalid");		
	}
	else
		var alpha = (x[0] - p[0])/(q[0] - p[0]);
	
	if (typeof a == "number"){
		var temp = mix([a,0], [b,0], alpha);	//for scalar values
		return temp[0];
	}
	else
		return mix(a, b, alpha);
}

function adjust_colour(pixel) {
	
	var red, green, blue;
	
	var mid = 0.5;
	
	if (pixel < mid) { 
		blue = 0;
		green = map_point(0, mid, 0, 1, pixel);
		red = map_point(0, mid, 1, 0, pixel);
	} 
	
	if (pixel == mid) {     
		blue = 0;
		red = 0;
		green = 1;
	} 
	
	if (pixel > mid) {
		red = 0;
		blue = map_point(mid, 1, 0, 1, pixel);
		green = map_point(mid, 1, 1, 0, pixel);
	}
	
	return vec4(red, green, blue, 1.0)	
}


function color_mandelbrot(l, maxIterations) {
	
	for(var i = 0; i < l; i++) {
		
		for(var j = 0; j < l; j++) {
			
			var re = map_point(0, l, -2, 2, i);
			var im = map_point(0, l, 2, -2, j);
			
			var c = vec2(re, im);
			var escapeTime = mandelbrot(c, maxIterations);
			
			var glx = map_point(0, l, -1, 1, i);
			var gly = map_point(0, l, 1, -1, j);
			
			var tempC = adjust_colour(escapeTime/maxIterations);
			colours.push(tempC);
			
			coordinates.push(vec2(glx, gly));
		}
	}
}






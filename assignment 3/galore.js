//Reference: some code has been taken from author's website (chapter 3 cad1 and cad2) 
"use strict";

//Global Variables
var gl;
var colors = [];

var mX, mY = 0; //mouse pixels 
var ind = 0; //index
var qCount = 0  //count of quadrilateral points 
var tCount = 0;  //count of triangle points

var totalVertices= 3* 200;

//Flag for triangle and quadrilateral mode
var tflag = true;
var qflag = false;

//Storing indices and count of polygons
var initialize = [0]; 
var totalPolygons = 0;
var positions = [0];



window.onload = function init()					
{

    var canvas = document.getElementById( "gl-canvas" );
    gl = WebGLUtils.setupWebGL( canvas );
    if ( !gl ) { alert( "WebGL isn't available" ); }

    //  Configure WebGL
    gl.viewport( 0, 0, canvas.width, canvas.height );
    gl.clearColor( 1.0, 1.0, 1.0, 1.0 );
	
    //  Load shaders and initialize attribute buffers
    var program = initShaders( gl, "vertex-shader", "fragment-shader" );
    gl.useProgram( program );
	
	colors = produceColors(colors);
	// Load the data into the GPU
	var vBuffer = gl.createBuffer();
	gl.bindBuffer( gl.ARRAY_BUFFER, vBuffer );
	gl.bufferData( gl.ARRAY_BUFFER, 8*totalVertices, gl.STATIC_DRAW );
	
	var vPosition = gl.getAttribLocation( program, "vPosition" );
	gl.vertexAttribPointer( vPosition, 2, gl.FLOAT, false, 0, 0 );
	gl.enableVertexAttribArray( vPosition );
	
	var cBuffer = gl.createBuffer();
	gl.bindBuffer( gl.ARRAY_BUFFER, cBuffer );
	gl.bufferData( gl.ARRAY_BUFFER, 16*totalVertices, gl.STATIC_DRAW );

	var vColor = gl.getAttribLocation(program, "vColor");
	gl.vertexAttribPointer(vColor, 4, gl.FLOAT, false, 0, 0); 
	gl.enableVertexAttribArray(vColor);
		
	//Detect mouse click 
	var coordinates, rand;
	canvas.addEventListener("mousedown", function(event){
		
		gl.bindBuffer( gl.ARRAY_BUFFER, vBuffer );
		//Get position of mouse on canvas
		mX = event.offsetX;
		mY = event.offsetY;

		//Increment clicks based on mode
		if (tflag == true){
			tCount += 1;
		}
		else if (qflag == true){
			qCount += 1;
		}
		
		//Send data to buffer
		coordinates = convertToWebGL(canvas.width,vec2(mY, mX));
		gl.bufferSubData(gl.ARRAY_BUFFER, 8*ind, flatten(coordinates));
	
		//Select a random index from colors array 
		rand = Math.floor(Math.random()*colors.length);
		
		gl.bindBuffer( gl.ARRAY_BUFFER, cBuffer );
		gl.bufferSubData(gl.ARRAY_BUFFER, 16*ind, flatten(colors[rand]));
		
		positions[totalPolygons]+=1;
		ind+=1;
		
		//Increase number of polygons once the shape is drawn
		if (qflag && qCount === 4){
			qCount = 0; //resets the quadrilateral point count
			totalPolygons+=1;
			positions[totalPolygons] = 0;
			initialize[totalPolygons] = ind;
		}
		if (tflag && tCount === 3){
			tCount = 0; //resets the triangle point count
			totalPolygons+=1;
			positions[totalPolygons] = 0;
			initialize[totalPolygons] = ind;
		}
	});
	//Detecting R and T key press
	document.onkeydown = function(event){
		if (event.key === 'R' || event.key === 'r'){ 
			//Switches to triangle mode (the default mode)
			tflag = true;
			qflag = false;
			//Clears buffers
			gl.clear( gl.COLOR_BUFFER_BIT );
			//reset all counts
			totalPolygons = 0; 
			qCount = 0; 
			tCount= 0; 
			ind = 0;
			initialize = [0];
			positions = [0];
	
		}
	
		else if (event.key === 'T' || event.key === 't'){   //Change modes
			if (tflag == true){
				qflag = true;
				tflag = false;
				if (tCount !== 0){
					qCount = tCount;
				}
			}
			else if (qflag == true){
				qflag = false;
				tflag = true;
				if (qCount !== 0){
					tCount = qCount;
				}
			}
		}
	};

	render();
	
};



//Helper function to convert pixel values to webGL coordinates
function convertToWebGL(L, pixel){
	var x,y
	x = map_point(0,L,-1,1,pixel[1]);
	y = map_point(0,L,1,-1,pixel[0]);
	return vec2(x, y);
}

//produces colors for the shapes
function produceColors(lst) {
	var red, green, blue;
	var i = 0;
	while ( i < 60){
		blue = Math.random();
		red = Math.random();
		green = Math.random();
		lst.push(vec4(red,green,blue,1.0));
		i++;
	}
	return lst;
}

//map point function for mapping points
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
		return  mix(a, b, alpha); //for vectors
}

//renders the shapes
function render() {
	gl.clear( gl.COLOR_BUFFER_BIT );
	//Draws points 
	gl.drawArrays( gl.POINTS, initialize[totalPolygons], positions[totalPolygons]);
	var i = 0;
	while (i<totalPolygons){
		gl.drawArrays( gl.TRIANGLE_FAN, initialize[i], positions[i]);
		i+=1;
	}
    window.requestAnimFrame(render);
}

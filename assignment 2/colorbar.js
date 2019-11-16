//Used Basem's files as the base code
"use strict";

//array of gl and canvases because we are creating two canvases one for grey and other for colored
var gl=[];   
var canvas=[]; 

window.onload = function init()// If we want a function to be executed first, we have to wait for this function call (called the onload event)
// It occurs when all the script files have been read in the HTML
{	var i=0;
	while(i<2)
	{
		var pointList = [];   
		var colorList = [];
		//these coordinates represent the first line
		pointList = [vec2(-1,-1), vec2(-1,1)]   
		//red color
		colorList = [vec4( 0, 0, 0, 1 ), vec4( 0, 0, 0, 1 )]   

		canvas[i] = document.getElementById( "gl-canvas"+(i+1)); // Acts like a pointer; gets the position of the element gl-canvas 
		// The return value of the function above is a WebGL context. It is a JS object that contains all the WebGL functions and parameters

	// Functions such as gl.bindbuffer, gl.FLOAT, gl.TRIANGLES are all members of this object 
		gl[i] = WebGLUtils.setupWebGL( canvas[i] );
		
		if ( !gl[i] ) { alert( "Webgl isn't available" ); }
				
		gl[i].viewport(0, 0, canvas[i].width, canvas[i].height);	
		gl[i].clearColor( 1, 1, 1, 1 );

		interpolation(canvas[i].width, pointList, colorList,i);		
		var program = initShaders( gl[i], "vertex-shader", "fragment-shader" );
		gl[i].useProgram( program );

		var bufferId = gl[i].createBuffer();
		gl[i].bindBuffer( gl[i].ARRAY_BUFFER, bufferId );  
		gl[i].bufferData( gl[i].ARRAY_BUFFER, flatten(pointList), gl[i].STATIC_DRAW );
		
		var vPosition = gl[i].getAttribLocation( program, "vPosition" );
		gl[i].vertexAttribPointer( vPosition, 2, gl[i].FLOAT, false, 0, 0 );	
		gl[i].enableVertexAttribArray( vPosition );
		
		var bufferId2 = gl[i].createBuffer();
		gl[i].bindBuffer( gl[i].ARRAY_BUFFER, bufferId2);  
		gl[i].bufferData( gl[i].ARRAY_BUFFER, flatten(colorList), gl[i].STATIC_DRAW );
		
		var vColor = gl[i].getAttribLocation( program, "vColor" );
		gl[i].vertexAttribPointer( vColor, 4, gl[i].FLOAT, false, 0, 0 );	
		gl[i].enableVertexAttribArray( vColor );
		i+=1;
	}
	render(pointList);
};


function render(points)
{   
	//used a loop because we have two canvases
	var i=0;
	while(i<2)
	{
		gl[i].clear( gl[i].COLOR_BUFFER_BIT );
		gl[i].drawArrays( gl[i].LINES, 0, points.length);
		i+=1;
	}
}


function map_point(p, q, x, a, b)
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


function interpolation(w,points,colList,option) {
	//for grey canvas
	if(option==0) {   
		
		var i = 0;
		while(i<w) {
			var coordinate = map_point(0,w,i,-1,1)
			points.push(vec2(coordinate,-1),vec2(coordinate,1))
			var color = map_point(0,w,i,0,1)
			colList.push(vec4(color,color,color, 1), vec4(color,color,color, 1))
			i+=1
		}
	}

	//for colored canvas
	if(option==1) {   
		
		var j = 0;
		while(j<w) {
			var coordinate = map_point(0,w,j,-1,1)
			points.push(vec2(coordinate,-1),vec2(coordinate,1))

			if(j<w/2) {
				var color = map_point(0,w/2, j,[1,0,0,1],[0,1,0,1]);
			}
			else if(j==2) {
				var color = vec4(0,0,1,1)
			}
			else if(j>w/2) {
				var color = map_point(w/2,w,j,[0,1,0,1],[0,0,1,1]);
			}
			//console.log(color)
			colList.push(color,color)
			j+=1
		}
	}

}

var Init = function(){
	console.log('James bbq and foot massage');

	var canvas = document.getElementById('gl-canvas');
	var gl = canvas.getContext('webgl'); //WebGLUtils.setupWebGL( canvas );
	
	//put in browser checks for experimental-webgl support
	
	if ( !gl ) { alert( "WebGL isn't available" ); }

    //gl.viewport( 0, 0, canvas.width, canvas.height );
	gl.clearColor(1.0, 1.0, 1.0, 1.0);
	gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);
	
	// QUESTION 3 - TEST CASES
	// var test = map_point([4,0], [2,0], [8,0], [4,0], [2.5,0]);
	// alert(test);	
	// test = map_point(4, 2, [8,0], [4,0], 2.5);
	// alert(test);	
	// test = map_point([4,0], [2,0], 8, 4, [2.5,0]);
	// alert(test);
	
	/*
	var program = initShaders( gl, "vertex-shader", "fragment-shader" );	// program variable holds our shaders (one for each shader)
    gl.useProgram( program );
	
	var bufferId = gl.createBuffer();
    gl.bindBuffer( gl.ARRAY_BUFFER, bufferId );
	gl.bufferData( gl.ARRAY_BUFFER, flatten(points), gl.STATIC_DRAW );
	
	var vPosition = gl.getAttribLocation( program, "vPosition" );
    gl.vertexAttribPointer( vPosition, 2, gl.FLOAT, false, 0, 0 );
	gl.enableVertexAttribArray( vPosition );
    render();
	*/
};

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
		return "[" + mix(a, b, alpha) + "]";
}

function interpolation(w,pixel) {
	
	alert("The corresponding WebGL coordinate is: "+map_point([0,0],[w,w],[-1,0],[1,0],pixel));
	alert("The value of corresponding shade of gray is: "+map_point([0,0],[w,w],[0,0,0],[1,1,1],pixel));
	if(pixel[0]<=w/2) {
		alert("The value of corresponding color is: "+map_point([0,0],[w/2,w/2],[1,0,0],[0,1,0],pixel));
	}
	else if(pixel[0]>w/2) {
		alert("The value of corresponding color is: "+map_point([w/2,w/2],[w,w],[0,1,0],[0,0,1],pixel));
	}

}
/*
function render() 		// Controls the drawing onto the canvas 
{
    gl.clear( gl.COLOR_BUFFER_BIT );
	gl.drawArrays( gl.POINTS, 0, points.length );
}
*/
while(true) {

	var width = prompt("Enter height of canvas ");
	if (width == null){
		break;
	}
	var x = prompt("Enter x co-ordinate of pixel ");
	if (x == null){
		break;
	}
	
	var y = 0 //prompt("Enter y co-ordinate of pixel ");
	if (y == null){
		break;
	}
	
	width = parseInt(width);
	x = parseInt(x);
	y = parseInt(y);
	
	if(isNaN(width) == false && isNaN(x) == false && isNaN(y) == false && x<width) {
		break;
	}
	if (width == null || x == null || y == null){
		break;
	}
	if (x==width) {
		alert("X coordinate should be less than width");
	}
	else {
		alert("Input values should be integers");
	}
}
if (width != null && x != null && y != null){
	interpolation(width,[x,y]);
}

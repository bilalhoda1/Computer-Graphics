var Init = function(){
	console.log('James bbq and foot massage');

	var canvas = document.getElementById('gl-canvas');
	var gl = canvas.getContext('webgl'); //WebGLUtils.setupWebGL( canvas );
	
	//put in browser checks for experimental-webgl support
	
	if ( !gl ) { alert( "WebGL isn't available" ); }

    //gl.viewport( 0, 0, canvas.width, canvas.height );
	gl.clearColor(1.0, 1.0, 1.0, 1.0);
	gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);
	
};

function map_point(p, q, a, b, x)
{
	if (p.length != q.length || q.length != x.length)
		alert("inconsistent dimensions for p, q and x");
	else if (a.length != b.length)
		alert("inconsistent dimensions for a and b");
	
	if (typeof p == "number"){
		if (q != p)
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

/*
function render() 		// Controls the drawing onto the canvas 
{
    gl.clear( gl.COLOR_BUFFER_BIT );
	gl.drawArrays( gl.POINTS, 0, points.length );
}
*/
function mandelbrot(l,pixel) {
	alert("The complex x co-ordinate is "+ map_point(0,l,-2,2,pixel[1])+"\n The complex y co-ordinate is "+ map_point(0,l,2,-2,pixel[0]));
	alert("The WebGL x co-ordinate is "+ map_point(0,l,-1,1,pixel[1])+"\n The WebGL y co-ordinate is "+ map_point(0,l,1,-1,pixel[0]));

}
while(true) {
	var height = prompt("Enter height of canvas ");
	if (height == null){
		break;
	}
	var x = prompt("Enter row number ");
	if (x == null){
		break;
	}
	var y = prompt("Enter column number ");
	if (y == null){
		break;
	}
	
	height = parseInt(height);
	x = parseInt(x);
	y = parseInt(y);

	if(isNaN(height) == false && isNaN(x) == false && isNaN(y) == false) {
		break;
	}
	else if (x > height || y > height) {
		alert("x and y coordinates should be in the range [0,height] ");
	}
	else {
		alert("Input values should be integers");
	}
}
if (height != null && x != null && y != null){
	mandelbrot(height,[x,y]);
}


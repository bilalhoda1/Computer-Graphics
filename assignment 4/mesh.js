//Code referenced from the author's book and a few online sources
"use strict";

//Global Variables
var gl;
var program;
var vertices = [], colors = [], faces = [], pointList = [];
var thetaLoc;
var initPoints;
var request;
var file = "bun_zipper.ply";
var val = 4; //holds the rotation value
var coordinates = [0,1,2];
var theta = [0,0,0];
var scale = [5,5,-5];
var translate = [0, 0, 0];
var shear = [0,0,0,0,0,0] //the order is xy,xz,yx,yz,zx,zy
var flag = true;
var rotated = [false,false,false];

window.onload =  function init()
{
    var canvas = document.getElementById( "gl-canvas" );
    
    gl = WebGLUtils.setupWebGL( canvas );
    if ( !gl ) { alert( "WebGL isn't available" ); }

    //  Configure WebGL
    gl.viewport( 0, 0, canvas.width, canvas.height );
    gl.clearColor( 1.0, 1.0, 1.0, 1.0 );
    gl.enable(gl.DEPTH_TEST);
	
    //  Load shaders and initialize attribute buffers
    program = initShaders( gl, "vertex-shader", "fragment-shader" );
    gl.useProgram( program );
	
	fileReader(file);
	var i = 0;
	while ( i < faces.length){
		colors.push(vec4(0.3,0.1,0.7,1), vec4(0.3,0.3,0.5,1), vec4(0.4,0.2,0.3,1));
		pointList.push(vec3(vertices[faces[i][0]]));
		pointList.push(vec3(vertices[faces[i][1]]));
		pointList.push(vec3(vertices[faces[i][2]]));
		i++;
	}
	initPoints = pointList;
	draw();
};

//reads the file
function fileReader(fileName){
	var initial = new XMLHttpRequest();
    initial.open("GET", fileName, false);
    initial.onreadystatechange = function ()
    {
        if(initial.readyState === 4)
        {
            if(initial.status === 200 || initial.status == 0)
            {
                var text = initial.responseText;
                var lst = fileParser(text);
				vertices = lst[0];
				faces = lst[1];
            }
        }
    }
    initial.send(null);
}

//parses the file
function fileParser(data){
	var face = [], vertex = [];
	var r = false;
	var lines = data.split('\n');
	var i = 0;
	while (i < lines.length){
		if (lines[i-1] === "end_header"){
			r = true;
		}
		if (r==true){
			var value = lines[i].split(" ");
			if (value[0] === "3"){
				face.push(vec3(parseFloat(value[1]), parseFloat(value[2]), parseFloat(value[3])));
			}
			else{
				vertex.push(vec3(parseFloat(value[0]), parseFloat(value[1]), parseFloat(value[2])));
			}
		}
		i++;
	}
	vertex.splice(35947, 1);
	return [vertex, face];
}

//contains all the transformation matrices
function draw(){

	var scaleMatrix = new Float32Array([
            scale[0],   0.0,  0.0,  0.0,
            0.0,  scale[1],   0.0,  0.0,
            0.0,  0.0,  scale[2],   0.0,
            0.0,  0.0,  0.0,  1.0  
	]);

	var translationMatrix = new Float32Array([
        1,0,0,translate[0],
        0,1,0,translate[1],
        0,0,1,translate[2],
        0,0,0,1
	]);

	var shearMatrix = new Float32Array([
		1.0,  shear[0], shear[1],  0.0,
		shear[2], 1.0,  shear[3],  0.0,
		shear[4],  shear[5], 1.0,  0.0,
		0.0,  0.0,  0.0,  1.0  
	]);

	var u_scale = gl.getUniformLocation(program, "u_scale");
    gl.uniformMatrix4fv(u_scale, false, scaleMatrix);
    
	var u_translation = gl.getUniformLocation(program, "u_translation");
	gl.uniformMatrix4fv(u_translation, false, translationMatrix);

	var u_shear = gl.getUniformLocation(program, "u_shear");
	gl.uniformMatrix4fv(u_shear, false, shearMatrix);
	
	window.cancelAnimationFrame(request);
	
	// Load the data into the GPU
	var vertex_buffer = gl.createBuffer();
	gl.bindBuffer( gl.ARRAY_BUFFER, vertex_buffer );
	gl.bufferData( gl.ARRAY_BUFFER, flatten(pointList), gl.STATIC_DRAW );
	var vPosition = gl.getAttribLocation( program, "vPosition" );
	gl.vertexAttribPointer( vPosition, 3, gl.FLOAT, false, 0, 0 );
	gl.enableVertexAttribArray( vPosition );
	thetaLoc = gl.getUniformLocation(program,"theta");
	
	var color_buffer = gl.createBuffer();
	gl.bindBuffer( gl.ARRAY_BUFFER, color_buffer );
	gl.bufferData( gl.ARRAY_BUFFER, flatten(colors), gl.STATIC_DRAW );

	var vColor = gl.getAttribLocation(program, "vColor");
	gl.vertexAttribPointer(vColor, 4, gl.FLOAT, false, 0, 0); 
	gl.enableVertexAttribArray(vColor);

	render();
}
//renders the output
function render() {
	if (val!=4){
		gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);
		
		if (flag==true){
			theta[val]+=2.5;
		}
		else{
			theta[val]-=2.5;
		}
    	gl.uniform3fv(thetaLoc,theta);
		gl.drawArrays( gl.TRIANGLES, 0, pointList.length); 
		request = window.requestAnimFrame(render);	
	}
    else{
    	gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);
    	gl.drawArrays( gl.TRIANGLES, 0, pointList.length); 
		request = window.requestAnimFrame(render);		
    }

}
//redraws when user scales or translates
function redraw(input){
	//for scaling
	if(input==0)
	{	var temp = []
		temp[0] = parseFloat(document.getElementById("xScale").value);
		temp[1] = parseFloat(document.getElementById("yScale").value);
		temp[2] = parseFloat(document.getElementById("zScale").value);
		if (isNaN(temp[0])) {
			temp[0] = 5			
		}
		if (isNaN(temp[1])) {
			temp[1] = 5			
		}
		if (isNaN(temp[2])) {
			temp[2] = 5			
		}
		scale[0] = temp[0]
		scale[1] = temp[1]
		scale[2] = temp[2]
		draw();	
	}
	//for translation
	else if (input==1) {
		var temp = []
		temp[0] = parseFloat(document.getElementById("xTranslate").value);
		temp[1] = parseFloat(document.getElementById("yTranslate").value);
		temp[2] = parseFloat(document.getElementById("zTranslate").value);
		if (isNaN(temp[0])) {
			temp[0] = 5			
		}
		if (isNaN(temp[1])) {
			temp[1] = 5			
		}
		if (isNaN(temp[2])) {
			temp[2] = 5			
		}

		translate[0] = temp[0]
		translate[1] = temp[1]
		translate[2] = temp[2]
		draw();
	}

}

//rotates the figure
function rotate(input){
	//for x direction
	if (input==0) {
		val = coordinates[0];
		draw();	
	}
	//for y direction
	else if(input==1) {
		val = coordinates[1];
		draw();	
	}
	//for z direction
	else if (input==2) {
		val = coordinates[2];
		draw();
	}

}

//changes the orientation of rotation
function orientation(){
	if (flag){
		flag = false;
	}
	else{
		flag = true;
	}
	draw();
}

//reflects along a particular axis
function reflect(input){
	//for x direction
	if (input==0){
		var i = 0;
		while (i<pointList.length){
			pointList[i][1] = -pointList[i][1]
			pointList[i][2] = -pointList[i][2]
			i++
		}
		rotated[0] = !rotated[0];
		draw();	
	}
	//for y direction
	else if (input==1)	{
		var i = 0;
		while (i<pointList.length){
			pointList[i][0] = -pointList[i][0]
			pointList[i][2] = -pointList[i][2]
			i++
		}
		rotated[1] = !rotated[1];
		draw();	
	}
	//for z direction
	else if(input==2) {
		var i =0;
		while (i<pointList.length){
			pointList[i][1] = -pointList[i][1]
			pointList[i][0] = -pointList[i][0]
			i++
		}
		rotated[2] = !rotated[2];
		draw();
	}

}

//Shear function 
function shearing(input){
	//for xy and xz direction
	if(input==0) {
		var temp = []
		temp[0] = parseFloat(document.getElementById("xy").value);
		temp[1] = parseFloat(document.getElementById("xz").value);
		if(isNaN(temp[0])) {
			temp[0] = 0
		}
		if(isNaN(temp[1])) {
			temp[1] = 0
		}
		shear[0] = temp[0]
		shear[1] = temp[1]
		console.log(shear[0],shear[1])
		draw();	
	}
	//for yx and yz direction
	else if (input==1) {
		var temp = []
		temp[0] = parseFloat(document.getElementById("yx").value);
		temp[1] = parseFloat(document.getElementById("yz").value);
		if(isNaN(temp[0])) {
			temp[0] = 0
		}
		if(isNaN(temp[1])) {
			temp[1] = 0
		}
		shear[2] = temp[0] 
		shear[3] = temp[1]
		draw();		
	}
	//for zx and zy direction
	else if(input==2) {
		var temp = []
		temp[0] = parseFloat(document.getElementById("zx").value);
		temp[1] = parseFloat(document.getElementById("zy").value);
		if(isNaN(temp[0])) {
			temp[0] = 0
		}
		if(isNaN(temp[1])) {
			temp[1] = 0
		}
		shear[4] = temp[0]
		shear[5] = temp[1]
		draw();		
	}
}
//Resets all transformations
function reset(){
	translate = [0,0,0];
	scale = [5,5,-5];	
	shear = [0,0,0,0,0,0];
	val = 4;
	theta = [0,0,0];
	//if in x direction
	if (rotated[0]){
		var i=0;
		while (i<pointList.length){
		pointList[i][1] = -pointList[i][1]
		pointList[i][2] = -pointList[i][2]
		i++
		}
		rotated[0] = false;
	}
	//if in y direction
	if (rotated[1]){
		var i = 0;
		while (i<pointList.length){
		pointList[i][0] = -pointList[i][0]
		pointList[i][2] = -pointList[i][2]
		i++
		}
		rotated[1] = false;
	}
	//if in z direction
	if (rotated[2]){
		var i = 0;
		while (i<pointList.length){
		pointList[i][1] = -pointList[i][1]
		pointList[i][0] = -pointList[i][0]
		i++
		}
		rotated[2] = false;
	}
	pointList = initPoints;
	gl.uniform3fv(thetaLoc,theta);
	draw();
}

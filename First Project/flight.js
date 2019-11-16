"use strict";

//Global Variables
var gl;
var program;
var colors = [];
var vertices = [];
var normals = [];
var keysPressed = {};
var vertex_buffer;
var normal_buffer;
var color_buffer;
var facesDict = {};

var lightPosition = vec4(1.0, 0.5, 1.0, 0.0 );
var lightAmbient = vec4(0.8, 0.8, 0.8, 1.0 );
var lightDiffuse = vec4( 1.0, 1.0, 1.0, 1.0 );
var lightSpecular = vec4( 1.0, 1.0, 1.0, 1.0 );

var materialAmbient = vec4( 1.0, 1.0, 1.0, 1.0 );
var materialDiffuse = vec4( 1.0, 0.8, 0.0, 1.0 );
var materialSpecular = vec4( 1.0, 1.0, 1.0, 1.0 );
var materialShininess = 20.0;
;
//Variables required for perspective view
var near = 0.1;
var far = 200.0;
var radius = 6.0;
var theta = 55.0;
var phi = 50;
var ftrack = 0;
var fov = 45.5;
var velocity = 0;
var offset = 0;
var acc = 0.01;

var aspect;
var modelViewMatrix, projectionMatrix;
var modelViewMatrixLoc, projectionMatrixLoc, normalMatrixLoc;
var normalMatrix;
var eye;
var at = vec3(0.0, 0.0, 0.0);
var up = vec3(0.0, 1.0, 0.0);

var x = vec2(-5,5), z = vec2(-10,10);

//flags
var wireframe = true;
var flat_shading = false;
var smooth_shading = false;

var myAudio;
var playCount = 0;

window.onload =  function init()
{
	document.onkeydown = handleKeyDown;
	document.onkeyup = handleKeyUp;

    var canvas = document.getElementById( "gl-canvas" );
    
    gl = WebGLUtils.setupWebGL( canvas );
    if ( !gl ) { alert( "WebGL isn't available" ); }
	
	program = initShaders( gl, "vertex-shader", "fragment-shader" );
    gl.useProgram( program );
	
    //  Configure WebGL
    gl.viewport( 0, 0, canvas.width, canvas.height );
	gl.clearColor( 0.0, 0.0, 0.0, 1.0 );
    gl.enable(gl.DEPTH_TEST);
	
	vertex_buffer = gl.createBuffer();
	normal_buffer = gl.createBuffer();
	color_buffer = gl.createBuffer();
	myAudio = new Audio('flying.mp3');
	aspect = canvas.width/canvas.height;
	generateTerrain(x,z);
	draw();
};


/*Function to initialize buffers*/
function draw(){
	
	var ambientProduct = mult(lightAmbient, materialAmbient);
    var diffuseProduct = mult(lightDiffuse, materialDiffuse);
    var specularProduct = mult(lightSpecular, materialSpecular);
	
	vertex_buffer = gl.createBuffer();
	gl.bindBuffer( gl.ARRAY_BUFFER, vertex_buffer );
	gl.bufferData( gl.ARRAY_BUFFER, flatten(vertices), gl.STATIC_DRAW );
	
	var vPosition = gl.getAttribLocation( program, "vPosition" );
	gl.vertexAttribPointer( vPosition, 3, gl.FLOAT, false, 0, 0 );
	gl.enableVertexAttribArray( vPosition );
	
	normal_buffer = gl.createBuffer();
	gl.bindBuffer( gl.ARRAY_BUFFER, normal_buffer );
	gl.bufferData( gl.ARRAY_BUFFER, flatten(normals), gl.STATIC_DRAW );
	
	var vNormal = gl.getAttribLocation(program, "vNormal");
	gl.vertexAttribPointer( vNormal, 4, gl.FLOAT, false, 0, 0 );
	gl.enableVertexAttribArray( vNormal );
	
	color_buffer = gl.createBuffer();
	gl.bindBuffer( gl.ARRAY_BUFFER, color_buffer );
	gl.bufferData( gl.ARRAY_BUFFER, flatten(colors), gl.STATIC_DRAW );
	var vColor = gl.getAttribLocation(program, "vColor");
	gl.vertexAttribPointer(vColor, 4, gl.FLOAT, false, 0, 0); 
	gl.enableVertexAttribArray(vColor);

	modelViewMatrixLoc = gl.getUniformLocation(program, "modelViewMatrix");
	projectionMatrixLoc = gl.getUniformLocation(program, "projectionMatrix");
	normalMatrixLoc = gl.getUniformLocation(program, "normalMatrix");
	
	gl.uniform4fv( gl.getUniformLocation(program, "ambientProduct"),flatten(ambientProduct) );
    gl.uniform4fv( gl.getUniformLocation(program,"diffuseProduct"),flatten(diffuseProduct) );
    gl.uniform4fv( gl.getUniformLocation(program,"specularProduct"),flatten(specularProduct) );
    gl.uniform4fv( gl.getUniformLocation(program,"lightPosition"),flatten(lightPosition) );
    gl.uniform1f( gl.getUniformLocation(program,"shininess"),materialShininess );
	
	render();
}

/*Generation of terrain mesh */
function generateTerrain(x, z){
	//Add vertices 
	var scl = 0.08;
	var minX = x[0], minZ = z[0];
	var maxX = x[1], maxZ = z[1];
	var i, j;
	var ind = 0;
	
	//Using perlin noise to get smooth mountainous curves at y coordinate of grid points (library implementation)
	var num = Math.random();
	noise.seed(10);
	
	while (minZ <= maxZ){
		i = minZ;
		minX = x[0];
		while (minX <= maxX){
			j = minX;
			if (wireframe){
				vertices.push(vec3(j,0,i));
				vertices.push(vec3(j,0,i+scl));
				vertices.push(vec3(j,0,i+scl));
				vertices.push(vec3(j+scl,0,i));
				vertices.push(vec3(j+scl,0,i));
				vertices.push(vec3(j,0,i));
				colors.push(vec4(1,1,1,1));
				colors.push(vec4(1,1,1,1));
				colors.push(vec4(1,1,1,1));
				colors.push(vec4(1,1,1,1));
				colors.push(vec4(1,1,1,1));
				colors.push(vec4(1,1,1,1));
				materialAmbient = vec4(1.0, 1.0, 1.0, 1.0);
			}
			else if (flat_shading || smooth_shading){
				vertices.push(vec3(j,0,i));
				vertices.push(vec3(j,0,i+scl));
				vertices.push(vec3(j+scl,0,i));
				vertices.push(vec3(j+scl,0,i+scl));
				
				vertices.push(vec3(j+scl,0,i));
				vertices.push(vec3(j,0,i+scl));
				
			}
			minX+=scl;
		}
		minZ+=scl;
	}
	
	for (var k=2; k<vertices.length-2; k++){

		vertices[k-2][1] = noise.perlin2(vertices[k-2][0], vertices[k-2][2]);
		
		if (smooth_shading){
			facesDict[vertices[k-2]] = computeNormal(vertices[k-2], vertices[k-1], vertices[k]);	
		}
		if (flat_shading || smooth_shading){
			if (vertices[k-2][1] < -0.05){
				colors.push(vec4(0,0,1,1));
			}
			else if (vertices[k-2][1] >= -0.05 && vertices[k-2][1] < 0.1){
				colors.push(vec4(0,1,0,1));
			}
			else if( vertices[k-2][1] >= 0.45){
				colors.push(vec4(1.0,1.0,1.0,1.0));
			}
			else{
				colors.push(vec4(0.6,0.4,0.2,1));
			}
		}	
	}
	if (flat_shading){
		generateNormals(vertices, 0, vertices.length);
	}
	else if (smooth_shading){
		var result = vec4(0,0,0,0);
		var avg;
		var val1;
		var val2;
		var val3;
		var val4;
		for (var key in facesDict){
			avg = add(result, facesDict[key])/3;
			val1 = add(result, facesDict[key])[0]/3;
			val2 = add(result, facesDict[key])[1]/3;	
			val3 = add(result, facesDict[key])[2]/3;			
			val4 = add(result, facesDict[key])[3]/3;
			normals.push(vec4(val1,val2,val3,val4));
		}
	}
}

function computeNormal(a, b, c){
	var v1 = subtract(b,a);
	var v2 = subtract(c,a);
	
	var n = normalize(cross(v2, v1));
	n = vec4(n);
	return n;
}

function generateNormals(points, start, num)
{
	for (var i=1; i < num; i++){
		
		var a = points[i-1];
		var b = points[i];
		var c = points[i+1];
		if (b === undefined || c === undefined){
			break;
		}
		var v1 = subtract(b,a);
		var v2 = subtract(c,a);
		var n = normalize(cross(v2, v1));
		n = vec4(n);
		normals.push(n);
	}
	
}

function render() {
	gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);
	offset += acc;	
	//Using perlin noise to get smooth mountainous curves at y coordinate of grid points (library implementation)
	var num = Math.random();
	noise.seed(10);
	colors = []
	updateMovement();
	
	if (smooth_shading){
		normals = [];
	}
	for (var k=0; k<vertices.length; k++){
		vertices[k][1] = noise.perlin2(vertices[k][0]+offset, vertices[k][2]);
		
		if (flat_shading || smooth_shading){
			if (vertices[k][1] < -0.05){
				colors.push(vec4(0,0,1,1));
			}
			else if (vertices[k][1] >= -0.05 && vertices[k][1] < 0.1){
				colors.push(vec4(0,1,0,1));
			}
			else if( vertices[k][1] >= 0.45){
				colors.push(vec4(1.0,1.0,1.0,1.0));
			}
			else{
				colors.push(vec4(0.6,0.4,0.2,1));
			}
		}	
	
	}

	gl.bindBuffer( gl.ARRAY_BUFFER, vertex_buffer );
	gl.bufferData( gl.ARRAY_BUFFER, flatten(vertices), gl.STATIC_DRAW );
	
	gl.bindBuffer( gl.ARRAY_BUFFER, normal_buffer );
	gl.bufferData( gl.ARRAY_BUFFER, flatten(normals), gl.STATIC_DRAW );
	
	gl.bindBuffer( gl.ARRAY_BUFFER, color_buffer );
	gl.bufferData( gl.ARRAY_BUFFER, flatten(colors), gl.STATIC_DRAW );

	//Implementing the perspective view
	eye = vec3(radius*Math.sin(theta)*Math.cos(phi), radius*Math.sin(theta)*Math.sin(phi), radius*Math.cos(theta));
	modelViewMatrix = lookAt(eye, at , up);
    projectionMatrix = perspective(fov, aspect, near, far);
		
	normalMatrix = [
        vec3(modelViewMatrix[0][0], modelViewMatrix[0][1], modelViewMatrix[0][2]),
        vec3(modelViewMatrix[1][0], modelViewMatrix[1][1], modelViewMatrix[1][2]),
        vec3(modelViewMatrix[2][0], modelViewMatrix[2][1], modelViewMatrix[2][2])
    ];
    gl.uniformMatrix4fv( modelViewMatrixLoc, false, flatten(modelViewMatrix) );
    gl.uniformMatrix4fv( projectionMatrixLoc, false, flatten(projectionMatrix) );
	gl.uniformMatrix3fv(normalMatrixLoc, false, flatten(normalMatrix) );
	
	if (wireframe){
		gl.drawArrays( gl.LINES, 0, vertices.length);
	}
	else if (flat_shading || smooth_shading){
		gl.drawArrays( gl.TRIANGLES, 0, vertices.length);
	}
	window.requestAnimFrame(render);	
}

function handleKeyDown(e) {
	keysPressed[e.keyCode] = true;
	
	if (e.keyCode == 84 && flat_shading) {
		console.log('smooth shading is on');
		flat_shading = false;
		smooth_shading = true;
		vertices = [];
		normals = [];
		colors = [];
		generateTerrain(x,z);
		draw();
	} else if (e.keyCode == 84) {
		wireframe = false;
		flat_shading = true;
		vertices = [];
		colors = [];
		generateTerrain(x,z);
		//draw();
	} else if(e.keyCode == 78){ 	// Near(n)
		if (ftrack >-10) {
			fov -= 1;
			ftrack -= 1;
		}

	} else if(e.keyCode == 70){ 	// Far(f)
		if (ftrack < 10) {
			fov += 1;
			ftrack += 1;
		}
	} else if(e.keyCode == 87){ //w
        if (at[1] < 2) {
            at[1] += 0.5;
        }
	} else if(e.keyCode == 83){ //s
        if (at[1] > -2) {
            at[1] -= 0.5;
        }
	} else if(e.keyCode == 65){ //a
        if (at[2] > -1) {
            at[2] -= 0.4;   
        }
	} else if(e.keyCode == 68){ //d
        if (at[2] < 1) {
            at[2] += 0.4
        }
            
	}
	if (playCount == 1 && e.keyCode === 80){
		myAudio.currentTime = 0;
		myAudio.pause();
		playCount = 0;
		
	}
	else if (playCount ==0 && e.keyCode === 80){
		playCount++;
		myAudio.play();
		myAudio.loop = true;
	}
}

function handleKeyUp(e) {
  keysPressed[e.keyCode] = false;
}

/* Roll Functions */
function rollRight() {
	if (!(Math.floor(up[2]) >= 1.0))		
		up[2] += 0.01;
}

function rollLeft() {
	if (!(Math.ceil(up[2]) <= -1.0))
		up[2] -= 0.01;
}

/* Yaw Functions */
function yawRight() {
	if (!(Math.floor(at[2]) >= 1.0))
		at[2] += 0.05;
}

function yawLeft() {
	if (!(Math.ceil(at[2]) <= -1.0))
		at[2] -= 0.05;
}

/* Pitch Functions */
function pitchUp() {
	if (!(Math.floor(at[1]) >= 1.5))
		at[1] += 0.05;
}

function pitchDown() {
	if (!(Math.ceil(at[1]) <= -0.05))
		at[1] -= 0.05;
}

function accelerate() {
	if(acc < 0.4)
		acc += 0.001;	
}

function decelerate() {
	if(acc > 0.05)
		acc -= 0.001;	
}

function updateMovement() {
	
	if (keysPressed[74])	// Roll left
		rollLeft();
	if (keysPressed[76])	// Roll right
		rollRight();
	if (keysPressed[73])	// Pitch up
		pitchUp();
	if (keysPressed[75])	// Pitch down
		pitchDown();
	if (keysPressed[37])	// Yaw left
		yawLeft();
	if (keysPressed[39])	// Yaw right
		yawRight();
	if (keysPressed[187])
		accelerate();
	if (keysPressed[189])
		decelerate();
}
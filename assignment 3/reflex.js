var gl;
var vertices = [];
var alive = true;
var score = 0;
var timeLeft = 30;

var colours = [
    vec4( 0.0, 0.0, 0.0, 1.0 ),  // black
    vec4( 1.0, 0.0, 0.0, 1.0 ),  // red
    vec4( 1.0, 1.0, 0.0, 1.0 ),  // yellow
    vec4( 0.0, 1.0, 0.0, 1.0 ),  // green
    vec4( 0.0, 0.0, 1.0, 1.0 ),  // blue
    vec4( 1.0, 0.0, 1.0, 1.0 ),  // magenta
    vec4( 0.0, 1.0, 1.0, 1.0 )   // cyan
];

function init()
{
	if (!alive) {
		console.log("bruh");
		return;
	}	
    canvas = document.getElementById( "gl-canvas" );
    
    gl = WebGLUtils.setupWebGL( canvas );
    if ( !gl ) { alert( "WebGL isn't available" ); }

    //  Configure WebGL
    gl.viewport( 0, 0, canvas.width, canvas.height );  // (x, y, w, h)
    gl.clearColor( 0.0, 1.0, 1.0, 0.2 );
	render();
	
	//  Load shaders and initialize attribute buffers
	var program = initShaders( gl, "vertex-shader", "fragment-shader" );
	gl.useProgram( program );
	
	var vBuffer = gl.createBuffer();
	var cBuffer = gl.createBuffer();    
	
	// Compute data.
	var click;			//store mouse click coordinates
	var check = 3;		//checks if no click for 3 shapes
	
	//get output element for score
	var countScore = document.getElementById("score-count");
	countScore.innerHTML = score;
	
	//get output element for timer
	var elem = document.getElementById("time-left");
	elem.innerHTML = timeLeft;
	
	//checks click
	canvas.addEventListener("click", function(event) {
		click = storeGuess(event);
		checkClick(click, countScore);	
		check = 3;
	});
	
	//main game loop
	var game = setInterval(function() {
		if (!alive || score < 0) {
			clearInterval(game);
			endGame();
		}
		
		play(program, vBuffer, cBuffer)	
		check--;
		
		//if no click for 3 shapes
		if (check == 0){
			score--;
			check = 3;
		}
		countScore.innerHTML = score;			
		document.getElementById("quit-button").addEventListener("click", function() {
			clearInterval(game);
			alive = false;
			endGame();
		});
	}, 1000);
	
	//countdown timer
	var timerId = setInterval(function() {
		timer(elem, timerId);
    }, 1000);    
};

function render() {
    gl.clear( gl.COLOR_BUFFER_BIT );
	gl.drawArrays( gl.TRIANGLES, 0, vertices.length );
}

//updates score element
function checkClick(click, countScore) {
	if (alive) {
		if ( inTriangle(click, vertices[0], vertices[1], vertices[2]) ){
			score++;				
		} else {
			score--;
		}
	} else {
		endGame();
	}
	if ( score < 0 ) {
		alive = false;
	}		
	countScore = document.getElementById("score-count");
	countScore.innerHTML = score;
}

//updates timer element
function timer(elem, timerId) {
	if (!alive || score < 0)
		clearInterval(timerId);	
		
	elem.innerHTML = timeLeft;
	
	if (timeLeft == 0) {
		clearInterval(timerId);
		alive = false;
	} else {
		timeLeft--;
	}    
}

//updates label on game over
function endGame() {
	var end = document.getElementById("score-label");
	end.innerHTML = "Game Over! Final Score: ";
}

//helps inTriangle function
function sign(p, q, r) {
	return (p[0] - r[0]) * (q[1] - r[1]) - (q[0] - r[0]) * (p[1] - r[1]);
}

//checks if clicked on triangle
function inTriangle(pt, v1, v2, v3){
    var b1 = false;
    var b2 = false;
    var b3 = false;
	if ( sign(pt, v1, v2) < 0.0 )
		b1 = true;
	if ( sign(pt, v2, v3) < 0.0 )
		b2 = true;
	if ( sign(pt, v3, v1) < 0.0 )
		b3 = true;
    return ((b1 == b2) && (b2 == b3))
}

//generates random vertices for triangle
function generateCoords() {
	
	// generate random coordinates 
	var xcor = (Math.random() * 1.8) - 1;
	var ycor = (Math.random() * 1.8) - 1;
	vertices = [ vec2(xcor, ycor), vec2(xcor+0.1, ycor+0.2), vec2(xcor+0.2, ycor) ];
}

function play(program, vBuffer, cBuffer) {
	
	generateCoords();
	var a = Math.round(Math.random() * 6);
	var temp = [ colours[a], colours[a], colours[a] ];
	
	gl.bindBuffer( gl.ARRAY_BUFFER, vBuffer );
	gl.bufferData( gl.ARRAY_BUFFER, flatten(vertices), gl.STATIC_DRAW );

	var vPosition = gl.getAttribLocation( program, "vPosition" );
	gl.vertexAttribPointer( vPosition, 2, gl.FLOAT, false, 0, 0 );
	gl.enableVertexAttribArray( vPosition );
	 
	gl.bindBuffer( gl.ARRAY_BUFFER, cBuffer );  
	gl.bufferData( gl.ARRAY_BUFFER, flatten(temp), gl.STATIC_DRAW );		
	
	var vColour = gl.getAttribLocation( program, "vColour" );
	gl.vertexAttribPointer( vColour, 4, gl.FLOAT, false, 0, 0 );	
	gl.enableVertexAttribArray( vColour );
	
	render();
}

//returns mouse click coordinates
function storeGuess(event) {
		
	var newP = vec2(2 * event.offsetX / canvas.width - 1, 
				2 * (canvas.height - event.offsetY) / canvas.height - 1);
	return newP;
}



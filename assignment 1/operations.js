"use strict";

//Takes the dimension and vectors as input from user
function userInput() {
    var flag = true;
    while(flag) {
        var dim = prompt("Enter dimensions between 2 and 4 inclusive:");
        var dimensions = parseInt(dim)
        if (dimensions<=4 && dimensions>=2) {
            break;
        }

        if (dim==null) {
            return [[],[]]
        }
    }
    var firstInput = [] 
    var secondInput = []
    var temp = 0.0
    for(var i=0;i<dimensions;i++) {
        temp = prompt("Input value "+i.toString()+" for first vector");
        if (temp==null) {
            return [[],[]]
        }        
        temp = parseFloat(temp)
        if (isNaN(temp)==true) {
            firstInput[i] = 0.0
        }
        else {
            firstInput[i] = temp 
        }
    }
    for(var i=0;i<dimensions;i++) {
        temp = prompt("Input value "+i.toString()+" for first vector");
        if (temp==null) {
            return [[],[]]
        }        
        temp = parseFloat(temp)
        if (isNaN(temp)==true) {
            secondInput[i] = 0.0
        }
        else {
            secondInput[i] = temp 
        }

    }
    if (dimensions==2) {
        var firstVector = vec2(firstInput);
        var secondVector = vec2(secondInput);
    }
    else if (dimensions==3) {
        var firstVector = vec3(firstInput);
        var secondVector = vec3(secondInput);
    }
    else if (dimensions==4) {
        var firstVector = vec4(firstInput);
        var secondVector = vec4(secondInput);
    }
    return [firstVector,secondVector]
}

//The vectors are passed on to this function and the menu is shown to the user
function menu(input) {
    var flag = true; 
    while(flag) {
        var option = prompt("The two vectors are: \n"+ "first: ["+input[0]+"] \n second: ["
        + input[1]+
        "] \n Enter any one of the following option numbers in the box below: \n \
         1) Tell whether the vectors are equal \n \
         2) Show the lengths of the vectors \n \
         3) Show the normalized vectors \n \
         4) Show the sum of the vectors \n \
         5) Show the difference of the vectors \n \
         6) Show the dot product of the vectors \n \
         7) Show the cross product of the vectors \n \
         8) Exit \n \
                    ")
        var optionNumber = parseInt(option)
        if (optionNumber<=8 && optionNumber>=1) {
            if (optionNumber==1) {
                alert(equal(input[0],input[1]));
            }
            else if (optionNumber==2) {
                alert("The length of first vector is "+ length(input[0])+ "\n" + "The length of second vector is "
                +length(input[1]));
            }
            else if (optionNumber==3) {
                var normalizedVec1 = Array.from(input[0])
                var normalizedVec2 = Array.from(input[1])
                alert("The normalized form of first vector "+ normalize(normalizedVec1)+"\n"+"The normalized form of the second vector "+ normalize(normalizedVec2))
            }
            else if (optionNumber==4) {
                alert("The sum of two vectors is "+add(input[0],input[1]));
            }
            else if (optionNumber==5) {
                alert("The difference of two vectors is "+subtract(input[0],input[1]));
            }
            else if (optionNumber==6) {
                alert("The dot product of two vectors is "+dot(input[0],input[1]));                
            }
            else if (optionNumber==7) {
                alert("The cross product of two vectors is "+cross(input[0],input[1]));
            }
            else if (optionNumber==8) {
                return;
            }    
        }
        else if (option==null) {
            return;
        }
    }
}

var vectors = userInput()
 
if(vectors[0].length!=0 && vectors[1].length!=0)
{
    menu(vectors);
}

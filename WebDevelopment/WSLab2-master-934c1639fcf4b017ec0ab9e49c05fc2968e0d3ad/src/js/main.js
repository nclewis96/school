/*
 * S18 CSCI470 Web Science
 * Single Page Web App in Browser: Basic Calculator
 * Application Behaviors
 * 
 * Phillip J. Curtiss, Assistant Professor
 * Department of Computer Science, Montana Tech
 * pcurtiss@mtech.edu, 406-496-4807
 * (c) 2018 All Rights Reserved
 */

(function() {
    // Get all the keys from the in the calculator div
    var keys = document.querySelectorAll('#calculator span');
    var operators = ['+', '-', '*', '/', '^2', 'e^', '√'];
    var decimalAdded = false;
    var squareVal = false;
    var squareRoot = false;
    var eulPow = false;
	
	
    function btnClickHandler(e) {
        // Get the input and button values
        var input = document.querySelector('#display');
        var tickerTape = document.querySelector('#ticker');
        var inputVal = input.innerHTML;
        var btnVal = this.innerHTML;

        // Take actions depending on the value of the button pressed
        switch (btnVal) {
            case 'C':
                { // Clear expression and reset if Clear button pressed
                    input.innerHTML = '';
                    decimalAdded = false;
                    squareVal = false;
                    break;
                }

            case '=':
                { // Evaluate the expression and return the result
                    var equation = inputVal;
                    var lastChar = equation[equation.length - 1];
					tickerTape.innerHTML += equation + '<br/>';
                    // Get rid of last char if operator or decimal
                    if (operators.indexOf(lastChar) > -1 || lastChar == '.')
                        equation = equation.replace(/.$/, '');
					
					if(squareVal && equation){
						equation = equation.replace('^2', '');
						equation = Math.pow(eval(equation),2);
						input.innerHTML = equation;
					}else if(squareRoot && equation){
						equation = equation.replace('√', '');
						equation = Math.sqrt(eval(equation))
						input.innerHTML = equation;
					}else if(eulPow && equation) {
						equation = equation.replace('e^', '');
						equation = Math.exp(eval(equation))
						input.innerHTML = equation;
					}
                    
                    // Evaluate the expression and replace in display
                    if (equation)
                        input.innerHTML = eval(equation);
					
					squareVal = false;
					squareRoot = false;
					eulPow = false;
                    decimalAdded = false;
                    
                    
                    break;
                }
            case '-':
                {
                    var lastChar = inputVal[inputVal.length - 1];
                    if (operators.indexOf(lastChar) == -1)
                        input.innerHTML += btnVal;

                    decimalAdded = false;
                    break;
                }
            case '+':
            case '*':
            case '/':
                {
                    var lastChar = inputVal[inputVal.length - 1];
                    if (inputVal != '' && operators.indexOf(lastChar) == -1)
                        input.innerHTML += btnVal;

                    if (inputVal.length > 1 && operators.indexOf(lastChar) > -1)
                        input.innerHTML = inputVal.replace(/.$/, btnVal);

                    decimalAdded = false;
                    break;
                }
            case '.':
                {
                    if (!decimalAdded) {
                        input.innerHTML += btnVal;
                        decimalAdded = true;
                    }
                    break;
                }
			case 'x^2':
				{
					var lastChar = inputVal[inputVal.length - 1];
					if(inputVal != '' && operators.indexOf(lastChar) == -1)
						input.innerHTML += '^2';
					if(inputVal.length > 1 && operators.indexOf(lastChar) > -1)
						input.innerHTML = inputVal.replace(/.$/, '^2');
					squareVal = true;
					break;
				}
			case 'sqrt(x)':
				{
					var lastChar = inputVal[inputVal.length - 1];
					if(inputVal != '' && operators.indexOf(lastChar) == -1)
						input.innerHTML = '√' + input.innerHTML;
					if(inputVal.length > 1 && operators.indexOf(lastChar) > -1)
					{
						input.innerHTML = inputVal.replace(/.$/, '');
						input.innerHTML = '√' + input.innerHTML;
					}
					squareRoot = true;
					break;
				}
			case '1/x' :
				{
					var lastChar = inputVal[inputVal.length - 1];
                    if (inputVal != '' && operators.indexOf(lastChar) == -1)
                        input.innerHTML = '1/' + input.innerHTML;

                    if (inputVal.length > 1 && operators.indexOf(lastChar) > -1)
                    {
                        input.innerHTML = inputVal.replace(/.$/, '');
                    	input.innerHTML = '1/' + input.innerHTML;
                    }
					break;
				}
			case 'e^x' :
				{
					var lastChar = inputVal[inputVal.length - 1];
					if(inputVal != '' && operators.indexOf(lastChar) == -1)
						input.innerHTML = 'e^' + input.innerHTML;
					if(inputVal.length > 1 && operators.indexOf(lastChar) > -1)
					{
						input.innerHTML = inputVal.replace(/.$/, '');
						input.innerHTML = 'e^' + input.innerHTML;
					}
					eulPow = true;
					break;
				}
            default:
                {
                    input.innerHTML += btnVal;
                }
        }

        e.preventDefault();
    }
	
	//Changes background color based on user selection
	changeBackColor = document.getElementById("BackColor");
	changeBackColor.addEventListener("click", function(e) {
		var colorBack = document.getElementById("BackColor").value;
		document.body.style.background = colorBack;
	});
	
	//Changes the font color of the calculator based on user selection
	changeFontColor = document.getElementById("TextColor");
	changeFontColor.addEventListener("click",function(e) {
		var colorText = document.getElementById("TextColor").value;
		var calc = document.getElementById("display");
		var ticker = document.getElementById("tape")
		calc.style.color = colorText;
		ticker.style.color = colorText;
	});
	
	
    // Add onclick event to all the keys and perform operations
    for (var i = 0; i < keys.length; i++)
        keys[i].addEventListener("click", btnClickHandler);
})();
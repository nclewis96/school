/*
 * S18 CSCI470 Web Science
 * Towers of Hanoi 
 * 
 * Phillip J. Curtiss, Assistant Professor
 * Department of Computer Science, Montana Tech
 * pcurtiss@mtech.edu, 406-496-4807
 * (c) 2018 All rights reserved
 */

towersApp = (function() { // towersApp app namespace - property of window
    // Private module data
	var disc;
    // Private module methods
	
	resetGame.addEventListener("click",function(e) {
		window.location.reload();
	}, false);
	
	document.addEventListener("dragstart",function(e){
		//var currentTarget = event.target.getAttribute("data-stack");
		//e.dataTransfer.setData("block", currentTarget);
		
		
		//Check to see if we're trying to drag the right things
		if(event.target.parentNode.parentNode.id == "towers"){
			//Returns the current stack of data-blocks
			var currentStack = event.target.parentNode.children;
			//If there's only one data-block, just grab it
			if(+currentStack.length == 1){
				disc = event.target;
			}
			//If there's more than one, check to see if you're grabbing the smallest one
			else if(+currentStack.length > 1){
				for(var i = 0; i < currentStack.length; i++){
					if(+currentStack[i].getAttribute("data-block") < +event.target.getAttribute("data-block")){
						disc = null;
					}else{
						disc = event.target;
					}
				}
			}
		
		}
		
		
	}, false);
	
	//Makes it so that it doesn't reset the drag objects location
	document.addEventListener("dragover", function(e){
		event.preventDefault();
	}, false);
	
	//Implements game logic
	document.addEventListener("drop", function(e){
		event.preventDefault();
		var biggerBlock = false;
		if(disc != null){
			
			if(event.target.parentNode.id == "towers"){
				//Returns the current stack of data-blocks
				var currentStack = event.target.children;
				//If there's no blocks in the tower, place disc
				if(+currentStack.length == 0){
					disc.parentNode.removeChild(disc);
					event.target.appendChild(disc);
				}
				//If there's more than one, check to see if a smaller one is in the stack
				else if(+currentStack.length > 0){
					for(var i = 0; i < currentStack.length; i++){
						if(+currentStack[i].getAttribute("data-block") < +disc.getAttribute("data-block")){
							biggerBlock = true;
						}
					}
					if(!biggerBlock){
						disc.parentNode.removeChild(disc);
						event.target.appendChild(disc);
						
					}
				}
		
			}			
		}
		winCond();
		
	}, false);
	
	function winCond(){
		var stack = disc.parentNode.getAttribute("data-stack");
		var numBlocks = disc.parentNode.children.length;
		if( (+stack == 2 || +stack == 3) && +numBlocks == 4){
			window.setTimeout(winAlert, 50);
		}
	}
	
	function winAlert(){
		alert("Congratulations, you won!");
	}
	
	
    return {
        // Public module data
        // Public module methods
    };
})();
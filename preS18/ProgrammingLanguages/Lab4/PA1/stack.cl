(*
 *  CS305 Fall 16
 *
 *  Programming Assignment 1
 *    Implementation of a simple stack machine.
 *
 *  Skeleton file
 *)

class Main inherits IO {
	
	
   main() : Object {
   		let nextChar : String, newStack : StackADT <- new StackADT in
		{
			
   		
   			while not nextChar = "x" loop {
   	
				nextChar <- in_string();
   				
				if nextChar = "e" then 
   					newStack.eval()    
				else if nextChar = "d" then 
   					newStack.display()
   				else
   					newStack.push(nextChar)
   				fi fi ;
   		
   			}pool ;
   			
   		}
   };

};

class StackADT inherits IO{
	
	stack : String <- "";
	
	push(newChar : String) : SELF_TYPE {
		{

			stack <- newChar.concat(stack);
			self;
		}
	};
	
	pop() : String {
		let poppedChar : String <- stack.substr(0, 1) in {
			
			stack  <- stack.substr(1, stack.length() - 1 );
			poppedChar;
			
		}
	};
	
	peek() : String {
		
		stack.substr(0, 1)
	}; 
	
	swap() : SELF_TYPE {
		let swapChar1 : String, swapChar2 : String in {
			if 2 < stack.length() then
			{
				pop();
				swapChar1 <- pop();
				swapChar2 <- pop();
				push(swapChar1);
				push(swapChar2);
			}
			else
				out_string("")
			fi;
		}
	};
	
	eval() : Object {
		if 0 < stack.length() then 
		{
			let evalChar : String <- peek() in 
			{
				if evalChar = "+" then 
					add()  
				else if evalChar = "s" then
					swap()
				else
					out_string("")
				 fi fi;
			};
		}
		else
			out_string("")
		fi
	};
	
	
	display() : SELF_TYPE {
		out_string(stack.concat(" \n"))
		
	};
	
	add() : SELF_TYPE {
		
		let expr1 : Int, expr2 : Int, sum : Int, change : A2I <- new A2I in {

			pop();
			expr1 <- change.c2i(peek() );
			pop();
			expr2 <- change.c2i(peek() );
			pop();
		
			sum <- expr1 + expr2;
		
			push( change.i2c(sum) );
			
		}
	};

};
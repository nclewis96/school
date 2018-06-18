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
   		nextChar : String;
   		stack : StackADT;
   		while true loop
   	
   		nextChar <- in_string();
   		
   		if nextChar = "e" then stack.eval()    else
   		if nextChar = "d" then stack.display() else
   		if nextChar = "x" then else abort()    else
   		{stack.push(nextChar) ;}
   		
   		
   		pool
   		
   };

};

class StackADT inherits String{
	
	stack : String;
	
	push(newChar : String) : SELF_TYPE {
		newChar.concat(stack);
		stack <- newChar;
		self;
	}
	
	pop() : String {
		poppedChar : String;
		poppedChar <- stack.substr(0, 1);
		stack  <- stack.substr(1, stack.length() - 1);
		poppedChar;
	};
	
	peek() : String {
		peekedChar : String;
		peekedChar <- stack.substr(0, 1);
	}; 
	
	swap() : Bool {
		swapChar1 : String;
		swapChar2 : String;
		swapChar1 <- stack.pop();
		swapChar2 <- stack.pop();
		stack.push(swapChar1);
		stack.push(swapChar2);

	};
	
	eval() : SELF_TYPE {
		evalChar : String;
		evalChar <- stack.peep();
		if evalChar = "+" then stack.add()  else
		if evalChar = "s" then stack.swap() else
		{abort(); self }
		fi fi
	
	};
	
	display() : String {
		out_string(stack);
	};
	
	add() : String {
		expr1  : Int;
		expr2  : Int;
		sum    : Int
		change : A2I;
		
		stack.pop();
		expr1 <- change.c2i(stack.peek() );
		stack.pop();
		expr2 <- change.c2i(stack.peek() );
		stack.pop();
		
		sum <- expr1 + expr2;
		
		stack.push( change.i2c(sum) );
		
	};

};

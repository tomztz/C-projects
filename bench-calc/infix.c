#include "infix.h"
#include "postfix.h"

// evaluate expression stored as an array of string tokens
double evaluate_infix_expression(char ** args, int nargs) {
	char **postfix = (char**)malloc(sizeof(char*)*nargs);
	int postfix_length=0;
	struct double_stack *stack0=double_stack_new(nargs);

	for(int i=0;i<nargs;i++){
	if((args[i][0]>='0'&& args[i][0]<='9')||(args[i][1]>='0'&&args[i][1]<='9')){
	postfix[postfix_length]=args[i];
	postfix_length++;
}
	else if(args[i][0]=='('){
	double_stack_push(stack0,i);

}
	
	else if((strlen(args[i])==1)&&(*args[i]=='+'||*args[i]=='-'||*args[i]=='X'||*args[i]=='/'||*args[i]=='^')){
	while((*args[(int)double_stack_peek(stack0)]=='+'||*args[(int)double_stack_peek(stack0)]=='-'||*args[(int)double_stack_peek(stack0)]=='X'||
*args[(int)double_stack_peek(stack0)]=='/'||*args[(int)double_stack_peek(stack0)]=='^')&&(*args[(int)double_stack_peek(stack0)]>=*args[i])){
//operators with high precedence has higher ascii value

	char* op=args[(int)double_stack_pop(stack0)];
	postfix[postfix_length]=op;
	postfix_length++;
}

double_stack_push(stack0,i);
}
	else if(args[i][0]==')'){
	while(*args[(int)double_stack_peek(stack0)]!='('){

	char* op=args[(int)double_stack_pop(stack0)];
	postfix[postfix_length]=op;
	postfix_length++;
}
	double_stack_pop(stack0);
}

}
	while(stack0->top!=0){
	char* operator=args[(int)double_stack_pop(stack0)];
	postfix[postfix_length]=operator;
	postfix_length++;
}
	for(int j=0;j<postfix_length;j++){
	printf("infix to postfix is:%s\n",postfix[j]);
}

return evaluate_postfix_expression( postfix, postfix_length);
}

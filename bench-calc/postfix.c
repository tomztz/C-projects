#include "postfix.h"


double op1,op2,result,operand;
// evaluate expression stored as an array of string tokens
double evaluate_postfix_expression(char ** args, int nargs) {
	struct double_stack *stack=double_stack_new(nargs-1);
	for(int i=0;i<nargs;i++){
	if((args[i][0]>='0'&& args[i][0]<='9')||(args[i][1]>='0'&&args[i][1]<='9')){
	operand=atof(args[i]);
	double_stack_push(stack,operand);
	printf("pushed %f to stack\n",operand);

}
	else if(strlen(args[i])==1){
	switch(args[i][0]){
case '+':
	op2=double_stack_pop(stack);
	op1=double_stack_pop(stack);
	result=op1+op2;
	double_stack_push(stack,result);
	printf("pushed %f to stack\n",result);
	break;
case '-':
	
	op2=double_stack_pop(stack);
        op1=double_stack_pop(stack);
        result=op1-op2;
        double_stack_push(stack,result);
        printf("pushed %f to stack\n",result);
        break;	
case'X':
	 op2=double_stack_pop(stack);
        op1=double_stack_pop(stack);
        result=op1*op2;
        double_stack_push(stack,result);
        printf("pushed %f to stack\n",result);
        break;
case'/':
	 op2=double_stack_pop(stack);
        op1=double_stack_pop(stack);
        result=op1/op2;
        double_stack_push(stack,result);
        printf("pushed %f to stack\n",result);
        break;
case'^':
	op2=double_stack_pop(stack);
        op1=double_stack_pop(stack);
        result=pow(op1,op2);
        double_stack_push(stack,result);
        printf("pushed %f to stack\n",result);
        break;
}



}

}
return result;
}

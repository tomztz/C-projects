// code for a huffman coder


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>

#include "huff.h"

// create a new huffcoder structure
struct huffcoder *  huffcoder_new()
{
	struct huffcoder *result=malloc(sizeof(struct huffcoder));
	result->tree=NULL;
	for(int i=0;i<256;i++){
	result->freqs[i]=0;
	result->code_lengths[i]=0;
	result->codes[i]=NULL;

}
	return result;


}

// count the frequency of characters in a file; set chars with zero
// frequency to one
void huffcoder_count(struct huffcoder * this, char * filename)
{
	FILE* fp=fopen(filename,"r");
	unsigned char c;
	while(!feof(fp)){
	c=fgetc(fp);
	this->freqs[(int)c]++;
}
	for(int i=0;i<256;i++){
	if(this->freqs[i]==0){
	this->freqs[i]++;

}
}

}

// using the character frequencies build the tree of compound
// and simple characters that are used to compute the Huffman codes
void huffcoder_build_tree(struct huffcoder * this)
{
	struct huffchar **list;
	list=malloc(sizeof(struct huffchar*)*256);
	for(int i=0;i<256;i++){
	list[i]=malloc(sizeof(struct huffchar));
	list[i]->freq=(this->freqs[i]);
	list[i]->is_compound=0;
	list[i]->seqno=i;
	list[i]->u.c=i;
}
	int list_size=256;
	while(list_size>1){
	int smallest=find_least_freq(list,list_size);
	struct huffchar *min1=list[smallest];
	list[smallest]=list[list_size-1];
	smallest=find_least_freq(list,list_size-1);
	struct huffchar *min2=list[smallest];
	list[smallest]=list[list_size-2];

	struct huffchar *compound;
	int new_seqno= 256+(256-list_size);
	compound=new_compound(min1,min2,new_seqno);
	list[list_size-2]=compound;
	list_size--;

	}
	this->tree=*list;
}


int find_least_freq(struct huffchar **list,int list_size){
	int seqno=list[0]->seqno;
	int min=list[0]->freq;
	int min_idx=0;
	for(int i=1;i<list_size;i++){
	if((list[i]->freq<min)||(list[i]->freq==min&&list[i]->seqno<seqno)){
	min=list[i]->freq;
	min_idx=i;
	seqno=list[i]->seqno;

}
}
return min_idx;

}
struct huffchar *new_compound(struct huffchar *min1,struct huffchar *min2,int seqno){
	struct huffchar *compound;
	compound=malloc(sizeof(struct huffcoder));
	compound->freq=(min1->freq)+(min2->freq);
	compound->is_compound=1;
	compound->seqno=seqno;
	compound->u.compound.left=min1;
	compound->u.compound.right=min2;
	return compound;


}
// using the Huffman tree, build a table of the Huffman codes
// with the huffcoder object
void huffcoder_tree2table(struct huffcoder * this)
{
	char *path=malloc(sizeof(char)*256);
	int depth=0;
	write_codes_recursive(this->tree,path,depth,this->codes,this->code_lengths);

}
void write_codes_recursive(struct huffchar*current,char *path,int depth,char **codes,int *code_lengths){

	if(current->is_compound){
	path[depth]='0';
	write_codes_recursive(current->u.compound.left,path,depth+1,codes,code_lengths);
	path[depth]='1';
	write_codes_recursive(current->u.compound.right,path,depth+1,codes,code_lengths);


}
else{
	int c=(int)current->u.c;
	code_lengths[c]=depth;
	path[depth]='0';
	codes[c]=malloc(sizeof(char)*depth+1);
	strncpy(codes[c], path, depth);
}

}



// print the Huffman codes for each character in order;
// you should not modify this function
void huffcoder_print_codes(struct huffcoder * this)
{
  for ( int i = 0; i < NUM_CHARS; i++ ) {
    // print the code
    printf("char: %d, freq: %d, code: %s\n", i, this->freqs[i], this->codes[i]);;
  }
}

// encode the input file and write the encoding to the output file
void huffcoder_encode(struct huffcoder * this, char * input_filename,
    char * output_filename)
{

        FILE* fp=fopen(input_filename,"r");
        FILE* fp1=fopen(output_filename,"w");


	unsigned char c=fgetc(fp);
	 while(!feof(fp)){
	fputs(this->codes[c],fp1);
	c=fgetc(fp);
}

	fputs(this->codes[4], fp1);
	fclose(fp);
        fclose(fp1);

}

// decode the input file and write the decoding to the output file
void huffcoder_decode(struct huffcoder * this, char * input_filename,
    char * output_filename)
{
 	FILE* fp=fopen(input_filename,"r");
	FILE* fp1=fopen(output_filename,"w");

	unsigned char c=fgetc(fp);
	while(!feof(fp)){
	struct huffchar *p=this->tree;
	while(p->is_compound){
	if(c=='0'){
	p=p->u.compound.left;
}
	else{
	p=p->u.compound.right;


}
	c=fgetc(fp);
}
if(p->u.c!= (unsigned char)4){
  fputc(p->u.c,fp1);}
}
	fclose(fp);
	fclose(fp1);

}

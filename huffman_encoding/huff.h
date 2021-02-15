// header file for Huffman coder

#ifndef HUFF_H
#define HUFF_H

#define NUM_CHARS 256

// node in a Huffman tree is either a compound char (internal node)
// or a simple char (leaf)
struct huffchar {
  int freq;
  int is_compound;
  int seqno;
  union {
    struct {
      struct huffchar * left;
      struct huffchar * right;
    } compound;
    unsigned char c;
  } u;
};


struct huffcoder {
  int freqs[NUM_CHARS];
  int code_lengths[NUM_CHARS];
  char * codes[NUM_CHARS];
  struct huffchar * tree;
};

// create a new huffcoder structure
struct huffcoder *  huffcoder_new();

// count the frequency of characters in a file; set chars with zero
// frequency to one
void huffcoder_count(struct huffcoder * this, char * filename);

// using the character frequencies build the tree of compound
// and simple characters that are used to compute the Huffman codes
void huffcoder_build_tree(struct huffcoder * this);

// using the Huffman tree, build a table of the Huffman codes
// with the huffcoder object
void huffcoder_tree2table(struct huffcoder * this);

int find_least_freq(struct huffchar **list,int list_size);

struct huffchar *new_compound(struct huffchar *min1,struct huffchar *min2,int seqno);

void write_codes_recursive(struct huffchar*current,char *path,int depth,char **codes,int *code_lengths);


// print the Huffman codes for each character in order
void huffcoder_print_codes(struct huffcoder * this);

// encode the input file and write the encoding to the output file
void huffcoder_encode(struct huffcoder * this, char * input_filename,
      char * output_filename);

// decode the input file and write the decoding to the output file
void huffcoder_decode(struct huffcoder * this, char * input_filename,
      char * output_filename);

#endif // HUFF_H

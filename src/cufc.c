#include <stdio.h>

enum node_type
{
	TOKEN,
	TOKEN_LAST,
	CALL,
	CALL_LAST,
	LIST,
	LIST_LAST,
	ERR
};

struct expr_node
{
	enum node_type type;
	size_t lr[2];
};

enum token_type
{
	TOK,	//generic token
	L_PAR,	//left parenthesis
	R_PAR,	//right parenthesis
	SPACE,	//space
	COMMA,
  END //
};

struct token_info
{
	enum token_type type;
	size_t beg, end;
};

struct token_info get_token(char *v, size_t pos )
{
	struct token_info ret;
	ret.beg=pos;
	switch(v[pos])
	{
		case '"':
			for(;v[++pos] != '"'; pos += v[pos] == '\\');
      pos++;
			ret.type = TOK;
		break;
		case '(':
			do pos++;
			while( v[pos] == ' ' || v[pos] == '\t' || v[pos] == '\n' );
			ret.type = L_PAR;
		break;
		case ')':
			ret.type = R_PAR;
			pos++;
		break;
		case ' ':
		case '\t':
			do pos++;
			while( v[pos] == ' ' || v[pos] == '\t' );
			switch(v[pos])
			{
				case '\n':
					goto new_line;
				break;
				case ',':
					goto comma_;
				default:
					ret.type = SPACE;
				break;
			}
		break;
		case '\n':
		new_line:
			do pos++;
			while( v[pos] == ' ' || v[pos] == '\t' || v[pos] == '\n' );
			switch(v[pos])
			{
				case ')':
					ret.type = R_PAR;
					pos++;
				break;
				case ',':
					goto comma_;
				default:
					ret.type = COMMA;
			}
		break;
		case ',':
		comma_:
			do pos++;
			while( v[pos] == ' ' || v[pos] == '\t' || v[pos] == '\n' );
			ret.type = COMMA;
    case '\0':
      ret.type = END;
    break;
		default:
			do pos++;
			while(
				v[pos] != '"' && v[pos] != '('  && v[pos] != ')'  &&
				v[pos] != ' ' && v[pos] != '\t' && v[pos] != '\n' &&
			  v[pos] != ',' && v[pos] != 0
			);
			ret.type = TOK;
	}
	ret.end = pos;
	return ret;
}

//upon open paranthesis the following
//happens: push (list,call,base)
//but base is either token or ( list )
//so you can just push list,call,list,call over and over again
//so actually you can just do everything with an intger and mod 2



void parse(char *v, struct expr_node *nodes )
{
	size_t state=2;
	size_t node_idx=0;
	do
  {
    printf("%s\n", v );
    struct token_info tok; tok.end=0;
    //do
    //{
    tok = get_token(v, tok.end );
    printf("tok.type: 0x%0x, tok.beg: 0x%0x, tok.end: 0x%0x,\n tokstr: %.*s\n", tok.type, tok.beg, tok.end, tok.end-tok.beg, v+tok.beg );
    //here you 
    //} while(tok.type != END);

    if(state&1) //list state
	  {

	  }
	  else //call state
	  {
	  }
  }
	while(state);
}

int main()
{
	char v[2048] =
    "let main (.\\ void int (\n"
    "\tprintln \"Hello World!\\\\\"\n"
    "\t0\n"
    "))";
  struct expr_node nodes[1024];
  return 0;
}

typedef enum {

	T_ID,
	T_ERR,
	T_EOF,
	T_EOL,
	T_INTVALUE,
	T_DOUBLEVALUE,
	T_STRINGVALUE,
	T_ADD,			// ** +
	T_SUB,			// ** -
	T_MULTIPLY,		// ** *
	T_DIVIDE,		// ** /
	T_INTDIVIDE,	// ** \ result as integer
	T_SEMICOLON,	// ** ;
	T_COLON,		// ** ,
	T_LEFTBRACKET,	// ** (
	T_RIGHTBRACKET,	// ** )
	T_ASSIGN,		// ** =
	T_NOTEQUAL,		// ** <>
	T_LESS,			// ** <
	T_GREATER,		// ** >
	T_GREATEROREQUAL,	// ** >=
	T_LESSEROREQUAL,	// ** <=

	T_AS,			// ** KeyWords
	T_ASC,
	T_DECLARE,
	T_DIM,
	T_DO,
	T_DOUBLE,
	T_ELSE,
	T_END,
	T_CHR,
	T_FUNCTION,
	T_IF,
	T_INPUT,
	T_INTEGER,
	T_LENGHT,
	T_LOOP,
	T_PRINT,
	T_RETURN,
	T_SCOPE,
	T_STRING,
	T_SUBSTRING,
	T_THEN,
	T_WHILE,

	T_RESERVEDWORD, //vvvvv ReservedWords Bonus tasks
	T_AND,
	T_BOOLEAN,
	T_CONTINUE,
	T_ELSEIF,
	T_EXIT,
	T_FALSE,
	T_FOR,
	T_NEXT,
	T_NOT,
	T_OR,
	T_SHARED,
	T_STATIC,
	T_TRUE

} TokenType;
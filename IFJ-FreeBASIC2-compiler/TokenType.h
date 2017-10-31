typedef enum {

	Type_Scope,				// ** Beginnig of main body
	Type_ID,				// ** Identifier
	Type_Dim,				// ** Declare value
	Type_EOF,				// ** End of file
	Type_DeclareFunction,	// ** Declaration of function	
	Type_Function,			// ** Function
	Type_As,				// ** Return function type
	Type_Return,			// ** Return 
	
	Type_Input,				// ** Input "id"
	Type_Print,				// ** Print exprression1; ...;expressionn;
	
	Type_String,			// ** String
	Type_Int,				// ** Integer
	Type_Doble,				// ** Double
	Type_Boolean,			// ** Boolean

	Type_If,				// ** If
	Type_ElseIf,			// ** Else If
	Type_Then,				// ** Then
	Type_Else,				// ** Else
	Type_End,				// ** End
	Type_Do,				// ** 

	Type_While,				// ** While cycle
	Type_For,				// ** For cycle
	Type_Loop,				// ** End of cycle
	
	Type_Addition,			// ** '+'
	Type_Substraction,		// ** '-'
	Type_Multiplication,	// ** '*'
	Type_Division,			// ** '/'
	Type_DivisionInteger,	// ** '\' Output is integer
	Type_Less,				// ** '<'
	Type_Greater,			// ** '>'
	Type_LessOrEqual,		// ** '<='
	Type_GreaterOrEqual,	// ** '>='
	Type_Equal,				// ** '='
	Type_NotEqual,			// ** '<>'

	Type_Exponent,			// ** 'X' e/E '+/-' 'Y'
	Type_LeftBracket,		// ** '('
	Type_RightBracket,		// ** ')'

	/* Functions */
	Type_Lenght,			// ** Lenght of string
	Type_SubStr,			// ** Substring from parameters
	Type_Asc,				// ** ASCII value
	Type_Chr,				// ** Char value

	/** 
	 *	TODO 
	 *  And, Continue, Exit, False, Next, Not, Or, Shared,
	 *  Static, True
	 */

} TokenType;


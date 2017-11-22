#pragma once
#ifndef ERRORS
#define ERRORS


typedef enum ERR_CODE
{
	LEX_ERR = 1,
	SYNTAX_ERR = 2,
	SEMANT_ERR_DEF = 3,
	SEMANT_ERR_TYPE = 4,
	SEMANT_ERR_OTHER = 6,
	INTERNAL_ERR = 99,

	//OK_ERR = true   !Opravit -- spatne
} ERR_CODE;

#endif // !ERRORS

typedef enum {

	S_Start,
	S_Number,
	S_ID,
	S_Less,
	S_Greater,
	S_ExcString,
	S_Double,
	S_Exp,
	S_ExpSign,
	S_Comment,
	S_BlockcommentOrDivide

}tState;

void AddToString(int c, tToken *Token);
void RemoveString(tToken *Token);
void ConvertStringToInteger(tToken *Token);
void ConvertStringToDouble(tToken *Token);
TokenType CompareWithKeywords(char* string);
tToken* GetNextToken();
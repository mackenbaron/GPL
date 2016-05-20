#pragma once


class JsonString  
{  
public:  
	typedef const char* Location;  
	JsonString();  

	/* ���json�ַ�����ʽ�Ƿ�Ϸ� */  
	bool CheckFormat(const char *begin, const char *end);  

private:  
	enum TokenType  
	{  
		tokenEndOfStream = 0,  
		tokenObjectBegin,  
		tokenObjectEnd,  
		tokenArrayBegin,  
		tokenArrayEnd,  
		tokenString,  
		tokenNumber,  
		tokenTrue,  
		tokenFalse,  
		tokenNull,  
		tokenArraySeparator,  
		tokenMemberSeparator,  
		tokenError  
	};  

	class Token  
	{  
	public:  
		TokenType type_;  
	};  

private:  
	void SkipSpace();  
	char GetNextChar();  
	bool Match(Location pattern, int patternLength);  
	bool ReadToken(Token &token);  

	bool ReadString();  
	void ReadNumber();  
	bool ReadValue();  
	bool ReadObject(Token &token);  
	bool ReadArray(Token &token);  

private:  
	Location begin_;  
	Location end_;  
	Location current_;  

	/* ���ڼ�¼��������� */  
	int objnum;  
}; 


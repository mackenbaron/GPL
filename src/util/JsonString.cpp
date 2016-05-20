#include "StdAfx.h"
#include "JsonString.h"


JsonString::JsonString()  
{  
	objnum = 0;  
}  

/* ��֤json�ַ����ĺϷ��� */  
bool JsonString::CheckFormat(const char* strbegin, const char *strend)  
{  
	begin_   = strbegin;  
	end_     = strend;  
	current_ = begin_;  

	bool succssful = ReadValue();  
	if(objnum == 0)  
	{  
		return false;  
	}  
	return succssful;  
}  

/* �����հ��ַ� */  
void JsonString::SkipSpace()  
{  
	while(current_ != end_)  
	{  
		char c = *current_;  
		if(c == ' ' || c == '\t' || c == '\r' || c == '\n')  
		{  
			++current_;  
		}  
		else  
		{  
			break;  
		}  
	}  
}  

/* �����һ���ַ� */  
char JsonString::GetNextChar()  
{  
	if(current_ == end_)  
	{  
		return 0;  
	}  
	return *current_++;  
}  

/* �ַ���ƥ�� */  
bool JsonString::Match(Location pattern, int patternlength)  
{  
	if((end_ - current_) < patternlength )  
	{  
		return false;  
	}  
	int index = patternlength;  
	while(index --)  
	{  
		if(current_[index] != pattern[index] )  
		{  
			return false;  
		}  
	}  
	current_ += patternlength;  
	return true;  
}  

/* ��ȡ�ַ��� */  
bool JsonString::ReadString()  
{  
	char c = 0;  
	while(current_ != end_)  
	{  
		c= GetNextChar();  
		if( c == '\\')  
		{  
			c = GetNextChar();  
		}  
		else if( c == '"')  
		{  
			break;  
		}  
	}  
	return (c == '"');  
}  

/* */  
void JsonString::ReadNumber()  
{  
	while(current_ != end_)  
	{  
		if(!(*current_ >= '0' && *current_ <= '9')  
			&& !(*current_ == '.' || *current_ == 'e'  
			|| *current_ == 'E' || *current_ == '+'  
			|| *current_ == '-'))  
		{  
			break;  
		}  
		++current_;  
	}  
}  

bool JsonString::ReadToken( Token &token)  
{  
	SkipSpace();  
	char c = GetNextChar();  
	SkipSpace();  
	if(c == ',' && *current_ == '}')  
	{  
		return false;  
	}  
	bool ok = true;  

	switch(c)  
	{  
	case '{':  
		token.type_ = tokenObjectBegin;  
		break;  
	case '}':  
		token.type_ = tokenObjectEnd;  
		break;  
	case '[':  
		token.type_ = tokenArrayBegin;  
		break;  
	case ']':  
		token.type_ = tokenArrayEnd;  
		break;  
	case '"':  
		token.type_ = tokenString;  
		ok = ReadString();  
		break;  
	case '0':  
	case '1':  
	case '2':  
	case '3':  
	case '4':  
	case '5':  
	case '6':  
	case '7':  
	case '8':  
	case '9':  
	case '-':  
		token.type_ = tokenNumber;  
		ReadNumber();  
		break;  
	case 't':  
		token.type_ = tokenTrue;  
		ok = Match( "rue", 3 );  
		break;  
	case 'f':  
		token.type_ = tokenFalse;  
		ok = Match( "alse", 4 );  
		break;  
	case 'n':  
		token.type_ = tokenNull;  
		ok = Match( "ull", 3 );  
		break;  
	case ',':  
		token.type_ = tokenArraySeparator;  
		break;  
	case ':':  
		token.type_ = tokenMemberSeparator;  
		break;  
	case 0:  
		token.type_ = tokenEndOfStream;  
		break;  
	default:  
		ok = false;  
		break;  
	}  
	if ( !ok )  
		token.type_ = tokenError;  
	return true;  
}  

bool JsonString::ReadObject(Token &tokenstart)  
{  
	Token tokenname;  
	while(ReadToken(tokenname))  
	{  
		if(tokenname.type_ == tokenObjectEnd)  
		{  
			return true;  
		}  
		if(tokenname.type_ != tokenString)  
		{  
			break;  
		}  

		Token colon;  
		if(!ReadToken(colon) || colon.type_ != tokenMemberSeparator)  
		{  
			return false;  
		}  
		bool ok = ReadValue();  
		if(!ok)  
		{  
			return false;  
		}  

		Token comma;  
		if(!ReadToken(comma)   
			||(comma.type_  != tokenObjectEnd   
			&& comma.type_ != tokenArraySeparator))  
		{  
			return false;  
		}  
		if(comma.type_ == tokenObjectEnd)  
		{  
			return true;  
		}  
	}  
	return false;  
}  

bool JsonString::ReadArray(Token &tokenstart)  
{  
	SkipSpace();  
	if(*current_ == ']')  
	{  
		Token endArray;  
		ReadToken(endArray);  
		return true;  
	}  

	int index = 0;  
	while(true)  
	{  
		bool ok = ReadValue();  
		if(!ok)  
		{  
			return false;  
		}  

		Token token;  
		ok = ReadToken(token);  

		bool badTokentype =   
			(token.type_ == tokenArraySeparator  
			&& token.type_ == tokenArrayEnd);  
		if( !ok & badTokentype)  
		{  
			return false;  
		}  
		if(token.type_ == tokenArrayEnd)  
		{  
			break;  
		}  
	}  
	return true;  
}  

bool JsonString::ReadValue()  
{  
	Token token;  
	ReadToken(token);  
	bool successful = true;  

	switch(token.type_)  
	{  
	case tokenObjectBegin:  
		objnum++;  
		successful = ReadObject(token);  
		break;  
	case tokenArrayBegin:  
		successful = ReadArray(token);  
		break;  
	case tokenNumber:  
	case tokenString:  
	case tokenTrue:  
	case tokenFalse:  
	case tokenNull:  
		break;  
	default:  
		return false;  
	}  
	return successful;  
}  

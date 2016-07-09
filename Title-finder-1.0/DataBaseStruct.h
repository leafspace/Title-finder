#include "stdafx.h"

class OnechoiceQuestion :public CRecordset
{
public:
	OnechoiceQuestion(CDatabase* pDatabase = NULL) :CRecordset(pDatabase) {
	}
	int m_numRows;
	int m_numCols;
};

class MorechoiceQuestion :public CRecordset
{
public:
	MorechoiceQuestion(CDatabase* pDatabase = NULL) :CRecordset(pDatabase) {
	}
};

class JudgeQuestion :public CRecordset
{
public:
	JudgeQuestion(CDatabase* pDatabase = NULL) :CRecordset(pDatabase) {
	}
};

class ShortQuestion :public CRecordset
{
public:
	ShortQuestion(CDatabase* pDatabase = NULL) :CRecordset(pDatabase) {
	}
};
#include "DrawField.h"

bool DrawField::init()
{
	_d = NULL;
	return true;
}

void DrawField::setJSON(rapidjson::Document * d)
{
	_d = d;
}

DrawField::~DrawField()
{
}

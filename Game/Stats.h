#ifndef STATS_H
#define STATS_H

#include <typeinfo>
#include <SFML/Graphics.hpp>

//union Value
//{
//	Value() {}
//	Value(const Value& val) {
//		_str = val._str;
//		_flo = val._flo;
//	}
//	~Value() {}
//
//	std::string _str;
//	float _flo;
//};

enum statType {
	eFloat, eString
};

struct Stat {
	/*Stat(const std::string& name, const std::string& type, const Value& val, const std::string& drawStyle)
		: _name(name), _type(type), _val(val), _drawStyle(drawStyle) {}*/

	Stat(const std::string& name, const statType& type, const std::string& str, float flo)
		: _name(name), _type(type), _str(str), _flo(flo) {}

	const std::string _name;
	const statType _type;
	//Value _val;

	const float _flo;
	const std::string _str;

	/*Stat& operator=(const Stat& stat) {
		//return Stat(stat._name, stat._type, stat._val, stat._drawStyle);
		return Stat(stat._name, stat._type, stat._str, stat._flo, stat._drawStyle);
        }*/
};

#endif // !STATS_H

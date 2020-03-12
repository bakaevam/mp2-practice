#include "Edge.h"

Edge::Edge()
{
	begin = 0;
	end = 0;
	weight = 0;
};

Edge::Edge(const Edge& copy)
{
	begin = copy.begin;
	end = copy.end;
	weight = copy.weight;
};

Edge::Edge(int _begin, int _end, int _weight)
{
	begin = _begin;
	end = _end;
	weight = _weight;
};

Edge::~Edge()
{
	begin = 0;
	end = 0;
	weight = 0;
};

bool Edge::operator<(const Edge& tmp) const
{
	return (weight < tmp.weight);
};

const Edge& Edge::operator=(const Edge& tmp)
{
	if (this == &tmp)
		return *this;

	begin = tmp.begin;
	end = tmp.end;
	weight = tmp.weight;

	return *this;
};

int Edge::GetBegin() const
{
	return begin;
};

int Edge::GetEnd() const
{
	return end;
};

int Edge::GetWeight() const
{
	return weight;
};
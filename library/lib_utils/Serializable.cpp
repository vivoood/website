/*
 * Serializable.cpp
 *
 *  Created on: Sep 28, 2011
 *      Author: Ventsislav Boev
 */

#include "Serializable.h"

#include <sstream>

void Serializable::Serialize(std::string& out)
{
	std::ostringstream stream(std::ostringstream::binary);

	SerializationStream serializationStream(stream);
	SerializeInternal(serializationStream);

	out = stream.str();
}

void Serializable::Serialize(std::ostream& out)
{
	SerializationStream serializationStream(out);
	SerializeInternal(serializationStream);
}

bool Serializable::Deserialize(const std::string& in)
{
	std::istringstream stream(in, std::istringstream::binary);

	SerializationStream serializationStream(stream);
	SerializeInternal(serializationStream);

	return stream.good() && ValidateInternal();
}

bool Serializable::Deserialize(std::istream& in)
{
	SerializationStream serializationStream(in);
	SerializeInternal(serializationStream);

	return in.good() && ValidateInternal();
}

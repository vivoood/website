/*
 * Serializable.h
 *
 *  Created on: Sep 28, 2011
 *      Author: Ventsislav Boev
 *  $Id: Serializable.h,v 1.1.2.1 2015/01/07 12:38:05 sopotski Exp $
 */

#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include <vector>
#include <string>
#include <iostream>
#include <stdint.h>

#define SERIALIZE(value, stream) ::SerializeObject(value, stream);
#define SERIALIZE_8(value, stream) ::Serialize<int8_t>(value, stream);
#define SERIALIZE_16(value, stream) ::Serialize<int16_t>(value, stream);
#define SERIALIZE_32(value, stream) ::Serialize<int32_t>(value, stream);
#define SERIALIZE_64(value, stream) ::Serialize<int64_t>(value, stream);

#define SERIALIZE_ARRAY_8(value, size, stream) ::SerializeArray<int8_t, size>(value, stream);
#define SERIALIZE_ARRAY_16(value, size, stream) ::SerializeArray<int16_t, size>(value, stream);
#define SERIALIZE_ARRAY_32(value, size, stream) ::SerializeArray<int32_t, size>(value, stream);
#define SERIALIZE_ARRAY_64(value, size, stream) ::SerializeArray<int64_t, size>(value, stream);

#define SERIALIZE_TWO_DIMENSIONAL_ARRAY_8(value, size1, size2, stream) ::SerializeArray<int8_t, size1, size2>(value, stream);
#define SERIALIZE_TWO_DIMENSIONAL_ARRAY_16(value, size1, size2, stream) ::SerializeArray<int16_t, size1, size2>(value, stream);
#define SERIALIZE_TWO_DIMENSIONAL_ARRAY_32(value, size1, size2, stream) ::SerializeArray<int32_t, size1, size2>(value, stream);
#define SERIALIZE_TWO_DIMENSIONAL_ARRAY_64(value, size1, size2, stream) ::SerializeArray<int64_t, size1, size2>(value, stream);

#define SERIALIZE_STRING(value, stream) ::SerializeString(value, stream);

class SerializationStream
{
public:

	/** Constructor */
	explicit SerializationStream(std::istream& in) : m_isReading(true), m_readingStream(&in), m_writingStream(0) {}

	/** Constructor */
	explicit SerializationStream(std::ostream& out) : m_isReading(false), m_readingStream(0), m_writingStream(&out) {}

	/**
	 * IsReading
	 * @return true if reading
	 */
	bool IsReading() { return m_isReading; }

	/**
	 * GetReadingStream
	 * @return the reading stream
	 */
	std::istream* GetReadingStream() { return m_readingStream; }

	/**
	 * GetWritingStream
	 * @return the writing stream
	 */
	std::ostream* GetWritingStream() { return m_writingStream; }

private:
	/** Indicates I/O stream */
	bool m_isReading;

	/** Pointer to input stream */
	std::istream* m_readingStream;

	/** Pointer to output stream */
	std::ostream* m_writingStream;
};

class Serializable
{
public:

	/** Destructor */
	virtual ~Serializable() = 0;

	/**
	 *
	 * @param out
	 */
	void Serialize(std::ostream& out);

	/**
	 *
	 * @param out
	 */
	void Serialize(std::string& out);

	/**
	 *
	 * @param in
	 * @return
	 */
	bool Deserialize(std::istream& in);

	/**
	 *
	 * @param in
	 * @return
	 */
	bool Deserialize(const std::string& in);

protected:

	/**
	 *
	 * @return
	 */
	virtual bool ValidateInternal() { return true; }

	/**
	 *
	 * @param stream
	 */
	virtual void SerializeInternal(SerializationStream& stream) {}
};

/** Inline Destructor */
inline Serializable::~Serializable()
{
}

inline void SerializeObject(Serializable& value, std::ostream& out)
{
	value.Serialize(out);
}

inline void SerializeObject(Serializable& value, std::istream& in)
{
	value.Deserialize(in);
}

template<typename T1>
inline void SerializeObject(std::vector<T1>& value, std::ostream& out)
{
	uint32_t size = value.size();
	out.write(reinterpret_cast<const char*>(&size), sizeof(size));

	typename std::vector<T1>::iterator currentItem = value.begin();
	typename std::vector<T1>::iterator end = value.end();
	for(; currentItem != end; ++currentItem)
	{
		SerializeObject(*currentItem, out);
	}
}

template<typename T1>
inline void SerializeObject(std::vector<T1>& value, std::istream& in)
{
	uint32_t size = 0;
	in.read(reinterpret_cast<char*>(&size), sizeof(size));

	value.clear();
	for(unsigned int i = 0; i < size; ++i)
	{
		T1 item;
		SerializeObject(item, in);
		value.push_back(item);
	}
}

template<typename T1>
inline void SerializeObject(T1& value, SerializationStream& stream)
{
	if(stream.IsReading())
	{
		SerializeObject(value, *stream.GetReadingStream());
	}
	else
	{
		SerializeObject(value, *stream.GetWritingStream());
	}
}

template<typename T1, typename T2>
inline void Serialize(const T2& value, std::ostream& out)
{
	T1 v = value;
	out.write(reinterpret_cast<const char*>(&v), sizeof(v));
}

template<typename T1, typename T2>
inline void Serialize(T2& value, std::istream& in)
{
	T1 v = 0;
	in.read(reinterpret_cast<char*>(&v), sizeof(v));
	value = static_cast<T2>(v);
}

template<typename T1, typename T2>
inline void Serialize(const std::vector<T2>& value, std::ostream& out)
{
	uint32_t size = value.size();
	out.write(reinterpret_cast<const char*>(&size), sizeof(size));

	typename std::vector<T2>::const_iterator currentItem = value.begin();
	typename std::vector<T2>::const_iterator end = value.end();
	for(; currentItem != end; ++currentItem)
	{
		Serialize<T1>(*currentItem, out);
	}
}

template<typename T1, typename T2>
inline void Serialize(std::vector<T2>& value, std::istream& in)
{
	uint32_t size = 0;
	in.read(reinterpret_cast<char*>(&size), sizeof(size));

	value.clear();
	for(unsigned int i = 0; i < size; ++i)
	{
		T2 item;
		Serialize<T1>(item, in);
		value.push_back(item);
	}
}

template<typename T1, typename T2>
inline void Serialize(T2& value, SerializationStream& stream)
{
	if(stream.IsReading())
	{
		Serialize<T1>(value, *stream.GetReadingStream());
	}
	else
	{
		Serialize<T1>(value, *stream.GetWritingStream());
	}
}

template<typename T1, unsigned int size, typename T2>
inline void SerializeArray(const T2 value[size], std::ostream& out)
{
	for(unsigned int i = 0; i < size; ++i)
	{
		T1 v = value[i];
		out.write(reinterpret_cast<const char*>(&v), sizeof(v));
	}
}

template<typename T1, unsigned int size, typename T2>
inline void SerializeArray(T2 value[size], std::istream& in)
{
	for(unsigned int i = 0; i < size; ++i)
	{
		T1 v = 0;
		in.read(reinterpret_cast<char*>(&v), sizeof(v));
		value[i] = static_cast<T2>(v);
	}
}

template<typename T1, unsigned int size, typename T2>
inline void SerializeArray(T2 value[size], SerializationStream& stream)
{
	if(stream.IsReading())
	{
		SerializeArray<T1, size>(value, *stream.GetReadingStream());
	}
	else
	{
		SerializeArray<T1, size>(value, *stream.GetWritingStream());
	}
}

template<typename T1, unsigned int size1, unsigned int size2, typename T2>
inline void SerializeArray(const T2 value[size1][size2], std::ostream& out)
{
	for(unsigned int i = 0; i < size1; ++i)
	{
		for(unsigned int j = 0; j < size2; ++j)
		{
			T1 v = value[i][j];
			out.write(reinterpret_cast<const char*>(&v), sizeof(v));
		}
	}
}

template<typename T1, unsigned int size1, unsigned int size2, typename T2>
inline void SerializeArray(T2 value[size1][size2], std::istream& in)
{
	for(unsigned int i = 0; i < size1; ++i)
	{
		for(unsigned int j = 0; j < size2; ++j)
		{
			T1 v = 0;
			in.read(reinterpret_cast<char*>(&v), sizeof(v));
			value[i][j] = static_cast<T2>(v);
		}
	}
}

template<typename T1, unsigned int size1, unsigned int size2, typename T2>
inline void SerializeArray(T2 value[size1][size2], SerializationStream& stream)
{
	if(stream.IsReading())
	{
		SerializeArray<T1, size1, size2>(value, *stream.GetReadingStream());
	}
	else
	{
		SerializeArray<T1, size1, size2>(value, *stream.GetWritingStream());
	}
}

inline void SerializeString(const std::string& value, std::ostream& out)
{
	uint32_t size = value.size();
	out.write(reinterpret_cast<const char*>(&size), sizeof(size));

	out.write(value.data(), value.size());
}

inline void SerializeString(std::string& value, std::istream& in)
{
	uint32_t size = 0;
	in.read(reinterpret_cast<char*>(&size), sizeof(size));

	value.resize(size);
	in.read(&value[0], size);
}

inline void SerializeString(std::string& value, SerializationStream& stream)
{
	if(stream.IsReading())
	{
		SerializeString(value, *stream.GetReadingStream());
	}
	else
	{
		SerializeString(value, *stream.GetWritingStream());
	}
}

#endif /* SERIALIZABLE_H */

#ifndef BITSET
#define BITSET

#include <iostream>
class Bitset {
public:
	class BitHolder {
	public:
		friend class Bitset;			
		BitHolder& operator=(const bool rhs);
		~BitHolder() = default;
		operator bool() const;
	private:
		explicit BitHolder(Bitset* bitset = nullptr, const int64_t position = 0);
		BitHolder(const BitHolder& copy) = default;

		Bitset* bitset_ = nullptr;
		int64_t position_ = 0 ;
		
	};
	explicit Bitset(const int64_t size = 0, const bool filler = false);
	Bitset(const std::string& rhs);
	Bitset(const Bitset& copy);
	Bitset& operator=(const Bitset& rhs);
	Bitset& operator&=(const Bitset& rhs);
	Bitset& operator|=(const Bitset& rhs);
	Bitset& operator^=(const Bitset& rhs);
	Bitset& operator>>=(const int64_t rhs);
	Bitset& operator<<=(const int64_t rhs);
	~Bitset();
	bool operator==(const Bitset& rhs) const;
	bool operator!=(const Bitset& rhs) const;
	Bitset operator~() const;
	bool operator[](const int64_t position) const;
	BitHolder operator[](const int64_t position);
	int64_t size() const;
	void resize(const int64_t size, const bool filler = false);
	std::ostream& WriteTo(std::ostream& ostream) const;
	std::istream& ReadFrom(std::istream& istream);
	
private:
	static const int64_t kByteSize = 8 ;
	static constexpr int64_t kClusterBitSize{ sizeof(int8_t) * kByteSize };
	void Swap(Bitset& other) noexcept;
	int64_t size_ = 0;
	uint8_t* data_ = 0;
	int64_t clusters_count_ = 0;
};
Bitset operator>>(const Bitset& lhs, const int64_t rhs);
Bitset operator<<(const Bitset& lhs, const int64_t rhs);
Bitset operator&(const Bitset& lhs, const Bitset& rhs);
Bitset operator|(const Bitset& lhs, const Bitset& rhs);
Bitset operator^(const Bitset& lhs, const Bitset& rhs);
std::ostream& operator<<(std::ostream& ostream, const Bitset& data);
std::istream& operator>>(std::istream& istream, Bitset& data);
#endif
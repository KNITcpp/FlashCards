#include  "FirstElementInjector.h"

namespace FirstElementInjector
{
	static void checkResources(const std::vector<size_t>& data)
	{
		if (data.empty())
			throw std::logic_error("FirstElementInjector::inject() : std::data is empty");
	}


	static auto getNewPositionIterator(const std::vector<size_t>& data) noexcept
	{
		return data.begin() + countPosition(data);
	}


	static void insertElementAtNewPosition(std::vector<size_t>& data)
	{
		data.insert(getNewPositionIterator(data) + 1, data[0]);
	}


	static auto eraseFirstElement(std::vector<size_t>& data)
	{
		return data.erase(data.begin());
	}


	void inject(std::vector<size_t>& data)
	{
		checkResources(data);
		insertElementAtNewPosition(data);
		eraseFirstElement(data);
	}

	size_t inline countPosition(const std::vector<size_t>& data) noexcept
	{
		constexpr int nominator = 3;
		constexpr int denominator = 4;
		return data.size() * nominator / denominator;
	}
}
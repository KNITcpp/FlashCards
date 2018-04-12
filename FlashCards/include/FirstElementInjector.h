#pragma once
#include <vector>


namespace FirstElementInjector
{
	void inject(std::vector<size_t>& data);
	size_t inline countPosition(const std::vector<size_t>& data) noexcept;
};

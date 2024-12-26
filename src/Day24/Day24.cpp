// Day24.cpp : Source file for your target.
//

#include "Day24.h"
#include "Utils.h"

#include "ctre.hpp"

#include <memory>
#include <future>
#include <thread>
#include <ranges>
#include <cassert>

int main()
{
	using std::operator""sv;
	auto startTime = std::chrono::system_clock::now();

	std::filesystem::path inputFile("../Day24_input.txt");
	//auto input = utils::ReadInput(inputFile);

	auto andGate = [](std::shared_future<bool> lhs, std::shared_future<bool> rhs, std::shared_ptr<std::promise<bool>> result)
		{
			result->set_value(lhs.get() && rhs.get());
		};

	auto orGate = [](std::shared_future<bool> lhs, std::shared_future<bool> rhs, std::shared_ptr<std::promise<bool>> result)
		{
			result->set_value(lhs.get() || rhs.get());
		};

	auto xorGate = [](std::shared_future<bool> lhs, std::shared_future<bool> rhs, std::shared_ptr<std::promise<bool>> result)
		{
			result->set_value(lhs.get() != rhs.get());
		};

	std::map<std::string, std::shared_ptr<std::promise<bool>>> promises;
	std::map<std::string, std::shared_future<bool>> futures;

	std::ifstream inStrm(inputFile);
	std::string line;
	//std::map<std::string, bool> initialConditions;

	auto initMatcher = ctre::match<R"((\w{3}): ([01]))">;

	while (std::getline(inStrm, line) && !line.empty())
	{
		auto results = initMatcher.match(line);
		assert(results);
		std::string label = results.get<1>().to_string();
		promises.emplace(label, std::make_shared<std::promise<bool>>());
		futures.emplace(label, promises[label]->get_future().share());
		promises[label]->set_value(results.get<2>().to_number() == 1);
	}

	auto opMatcher = ctre::match<R"(([a-z0-9]{3}) (AND|OR|XOR) ([a-z0-9]{3}) -> ([a-z0-9]{3}))">;

	auto addLabel = [&](const std::string& label)
		{
			if (!promises.contains(label))
			{
				assert(!futures.contains(label));
				promises.emplace(label, std::make_shared<std::promise<bool>>());
				futures.emplace(label, promises[label]->get_future().share());
			}
		};

	std::vector<std::future<void>> gates;

	while (std::getline(inStrm, line))
	{
		auto results = opMatcher.match(line);
		assert(results);

		std::string label1 = results.get<1>().to_string();
		std::string label2 = results.get<3>().to_string();
		std::string label3 = results.get<4>().to_string();
		std::string opName = results.get<2>().to_string();

		addLabel(label1);
		addLabel(label2);
		addLabel(label3);

		if (opName == "AND")
		{
			gates.emplace_back(std::async(std::launch::async, andGate, futures[label1], futures[label2], promises.at(label3)));
		}
		else if (opName == "OR")
		{
			gates.emplace_back(std::async(std::launch::async, orGate, futures[label1], futures[label2], promises.at(label3)));
		}
		else if (opName == "XOR")
		{
			gates.emplace_back(std::async(std::launch::async, xorGate, futures[label1], futures[label2], promises.at(label3)));
		}
	}

	for (auto& f : gates)
	{
		f.get();
	}

	auto outputMatcher = ctre::match<R"(z(\d{2}))">;
	std::uint64_t result = 0;

	auto resultView = futures
		| std::views::filter([&](const std::pair<std::string, std::shared_future<bool>>& f)
			{
				return outputMatcher(f.first);
			})
		| std::views::transform([&](const std::pair<std::string, std::shared_future<bool>>& f)
			{
				return std::make_pair(outputMatcher(f.first).get<1>().to_number(), f.second);
			});

	std::ranges::for_each(resultView, [&](const std::pair<int, std::shared_future<bool>>& r)
		{
			if (r.second.get())
			{
				result += (1ull << r.first);
			}
		});

	utils::PrintResult(result, startTime);

	return 0;
}

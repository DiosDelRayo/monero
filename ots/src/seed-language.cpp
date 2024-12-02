#include "ots.hpp"

namespace ots {

	std::string SeedLanguage::name() const {
		return m_name;
	}

	std::string SeedLanguage::englishName() const {
		return m_englishName;
	}

	std::string SeedLanguage::code() const {
		return m_code;
	}

	bool SeedLanguage::supported(SeedType type) const {
		for(const auto& item : list()) {
			auto it = item.m_supported.find(type);
			if(it != item.m_supported.end())
				return it->second;
		}
		return false;
	}

	bool SeedLanguage::isDefault(SeedType type) const {
		auto it = s_default.find(type);
		return it != s_default.end() && it->second.m_code == this->m_code;
	}

	bool SeedLanguage::operator==(const SeedLanguage& other) const {
		return m_code == other.m_code;
	}

	const SeedLanguage SeedLanguage::fromName(const std::string& name) {
		for(auto item : list())
			if(item.name() == name)
				return item;
		throw ots::exception::seed::LanguageNotFound();
	}

	const SeedLanguage SeedLanguage::fromEnglishName(const std::string& name) {
		for(auto item : list())
			if(item.englishName() == name)
				return item;
		throw ots::exception::seed::LanguageNotFound();
	}

	const SeedLanguage SeedLanguage::fromCode(const std::string& code) {
		for(auto item : list())
			if(item.code() == code)
				return item;
		throw ots::exception::seed::LanguageNotFound();
	}

	const std::vector<SeedLanguage>& SeedLanguage::list() {
		if(s_list.size() == 0) {
			// TODO: generate s_list
		}
		return s_list;
	}

	const std::vector<SeedLanguage> SeedLanguage::listFor(SeedType type) {
		std::vector<SeedLanguage> out;
		for(auto item : list()) {
			if(item.supported(type))
				out.push_back(item);
		}
		return out;
	}

	const SeedLanguage& SeedLanguage::defaultLanguage(SeedType type) {
		auto it = s_default.find(type);
		if(it != s_default.end())
			return it->second;
		throw ots::exception::seed::NoDefaultLanguageSet();
	}
}

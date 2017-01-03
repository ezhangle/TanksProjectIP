#pragma once

#include "SFML\Graphics.hpp"
#include <memory>
#include <map>
#include <exception>
#include <string>
#include <algorithm>

template<typename Resource, typename Identifier>
class ResourceHolder {
public:
	void											load(Identifier id, const std::string& pathfile);
	Resource&										get(Identifier id);
	void											insertResource(Identifier id, std::unique_ptr<Resource> res);
private:
	std::map<Identifier, std::unique_ptr<Resource>> mResourceMap;
};

template<typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string& pathfile) {
	std::unique_ptr<Resource> resource(new Resource());

	if (!resource->loadFromFile(pathfile)) {
		throw std::runtime_error("Resource missing.\n");
	}

	insertResource(id, std::move(resource));
}

template<typename Resource, typename Identifier>
Resource& ResourceHolder<Resource, Identifier>::get(Identifier id) {
	auto res = mResourceMap.find(id);

	return *res->second;
}

template<typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::insertResource(Identifier id, std::unique_ptr<Resource> res) {
	mResourceMap.insert(std::make_pair(id, std::move(res)));
}
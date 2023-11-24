#pragma once

class ResourceManager {
public:
	static ResourceManager& getInstance();
	void operator=(ResourceManager const&) = delete;
private:
	ResourceManager();
};

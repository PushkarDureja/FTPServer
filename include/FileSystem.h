#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include<string>
#include <vector>

static class FileSystem
{
public:

	static std::vector<std::string> GetDirectoryListing(std::string path);
	static std::string GetCombinedPath(std::string path1, std::string path2);
	static std::string SanitizePath(std::string path);
	static bool CheckExists(std::string path);
	static bool IsPathWithinAllowed(std::string allowedPath, std::string requestedPath);

};

#endif


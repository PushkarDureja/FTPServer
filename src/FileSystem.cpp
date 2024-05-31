#include "FileSystem.h"
#include <iostream>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

vector<string> FileSystem::GetDirectoryListing(string path) {
	vector<string> result;

	for (const auto& entry : fs::directory_iterator(path))
		result.push_back(entry.path().filename().string());

	return result;
}

string FileSystem::GetCombinedPath(string path1, string path2) {
	fs::path castedPath1(path1);
	fs::path castedPath2(path2);
	fs::path combinedPath = castedPath1 / castedPath2;
	return combinedPath.string();
}

string FileSystem::SanitizePath(string path) {
	fs::path pathObj(path);
	fs::path absPath = fs::absolute(pathObj);
	fs::path normPath = absPath.lexically_normal();

	return normPath.string();
}

bool FileSystem::CheckExists(string path) {
	return fs::exists(path);
}

bool FileSystem::IsPathWithinAllowed(string allowedPath, string requestedPath) {
	fs::path relative = std::filesystem::relative(requestedPath, allowedPath);

	return !(relative.string().find("..") == 0);
}


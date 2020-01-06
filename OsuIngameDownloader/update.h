#pragma once
#include <iostream>
#include <vector>
#define VERSION "0.8.1"

using namespace std;

namespace Update {
	void CheckUpdateService();
	bool CheckUpdate(string& cnblogMirrorUrl, string& githubReleaseUrl);
	bool NeedUpdate(string localVersion, string remoteVersion);
	void VersionStringtoArray(string version, vector<int>& vecVersion);
	int DownloadUpdate(string url);
}
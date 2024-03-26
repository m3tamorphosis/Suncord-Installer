#include <filesystem>
#include <iostream>
#include <map>
#include <string>

// Installers configuration

enum class PACKAGEMANAGER {
  APT,
  YUM,
  EMERGE,
  PACMAN,
  ZYPPER,
  URPMI,
  NIX_ENV,
  PKG,
  PKG_ADD,
  APK,
  UNKNOWN,
};

auto PackageManager = CheckPackageManagers();

bool IsWindows() {
#ifdef _WIN32
  return true;
#else
  return false;
#endif
}

static std::map<std::string, PACKAGEMANAGER> managers = {
    {"apt", PACKAGEMANAGER::APT},         {"yum", PACKAGEMANAGER::YUM},
    {"emerge", PACKAGEMANAGER::EMERGE},   {"pacman", PACKAGEMANAGER::PACMAN},
    {"zypper", PACKAGEMANAGER::ZYPPER},   {"urpmi", PACKAGEMANAGER::URPMI},
    {"nix-env", PACKAGEMANAGER::NIX_ENV}, {"pkg", PACKAGEMANAGER::PKG},
    {"pkg_add", PACKAGEMANAGER::PKG_ADD}, {"apk", PACKAGEMANAGER::APK}};

PACKAGEMANAGER CheckPackageManagers() {
  std::string PM[] = {"apt",   "yum",     "emerge", "pacman",  "zypper",
                      "urpmi", "nix-env", "pkg",    "pkg_add", "apk"};

  for (const std::string &manager : PM) {
    if (VerifyManager(manager)) {
      auto PM = managers.find(manager);

      if (PM != managers.end()) {
        return PM->second;
      }
    }
  }

  printf("Could not find available package managers, please install git "
         "manually \n");
  return PACKAGEMANAGER::UNKNOWN;
}

bool VerifyManager(const std::string &manager) {
  std::string command = "which " + manager;
  int result = std::system(command.c_str());
  return (result == 0);
}

// Installation

void InstallGit() {
  int result;
  std::filesystem::path cache =
      std::filesystem::temp_directory_path() / "git-cache";

  printf("Creating git-cache directory\n");

  if (!std::filesystem::exists(cache)) {
    std::filesystem::create_directory(cache);
  }

  printf("Installing Git...\n");

  if (IsWindows()) {
    result = std::system("curl -o Git-Installer.exe "
                         "https://github.com/git-for-windows/git/releases/"
                         "download/v2.44.0.windows.1/Git-2.44.0-64-bit.exe");

    if (result == 0) {
      printf("Downloaded Git installer\n");
      result = std::system("git-cache/Git-Installer.exe");

      if (result == 0) {
        printf("Git installed\n");
      }
    }

    else {
      printf("Failed to install Git\n");
    }
  }

  else {
    printf("Failed to download git installer\n");
  }

  if (!IsWindows()) {
    InstallLinuxDependency("git");
  }
}

void InstallNPM() {
  int result;
  std::filesystem::path cache =
      std::filesystem::temp_directory_path() / "npm-cache";

  printf("Creating npm-cache directory\n");

  if (!std::filesystem::exists(cache)) {
    std::filesystem::create_directory(cache);
  }

  printf("Installing NPM...\n");

  if (IsWindows()) {
    result =
        std::system("curl -o npm-installer.msi "
                    "https://nodejs.org/dist/v21.7.1/node-v21.7.1-x64.msi");

    if (result == 0) {
      printf("Downloaded NPM installer\n");
      result = std::system("npm-cache/npm-installer.msi");

      if (result == 0) {
        printf("Installed NPM\n");
      } else {
        printf("Failed to install NPM, please install manually\n");
      }
    } else {
      printf("Failed to download NPM installer\n");
    }
  }

  if (!IsWindows()) {
    InstallLinuxDependency("npm");
  }
}

void InstallPNPM() { system("npm i -g pnpm"); }

void InstallLinuxDependency(std::string dep) {
  printf("Using %s", PackageManager);

  switch (PackageManager) {
  case PACKAGEMANAGER::APK:
    std::system(("sudo apk add " + dep).c_str());
    break;
  case PACKAGEMANAGER::APT:
    std::system(("sudo apt-get install " + dep).c_str());
    break;
  case PACKAGEMANAGER::EMERGE:
    std::system(("sudo emerge --ask --verbose " + dep).c_str());
    break;
  case PACKAGEMANAGER::NIX_ENV:
    std::system(("sudo nix-env -i " + dep).c_str());
    break;
  case PACKAGEMANAGER::PACMAN:
    std::system(("sudo pacman -S " + dep).c_str());
    break;
  case PACKAGEMANAGER::PKG:
    std::system(("sudo pkg install " + dep).c_str());
    break;
  case PACKAGEMANAGER::PKG_ADD:
    std::system(("sudo pkg_add " + dep).c_str());
    break;
  case PACKAGEMANAGER::URPMI:
    std::system(("sudo urmpi " + dep).c_str());
    break;
  case PACKAGEMANAGER::YUM:
    std::system(("sudo yum install " + dep).c_str());
    break;
  case PACKAGEMANAGER::ZYPPER:
    std::system(("sudo zypper install " + dep).c_str());
    break;
  }
}

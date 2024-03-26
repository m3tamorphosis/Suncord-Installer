#include <iostream>
#include <string>
#include <filesystem>
#include <cstdlib>
#include <map>

// Suncord Github: https://github.com/verticalsync/Suncord
// My contact: @xbhl

// This is the first time I've written an installer in C++
// Any issues I urge you make an issue report in github.


enum class PackageManager {
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

static std::map<std::string, PackageManager> managers = {
    {"apt", PackageManager::APT},
    {"yum", PackageManager::YUM},
    {"emerge", PackageManager::EMERGE},
    {"pacman", PackageManager::PACMAN},
    {"zypper", PackageManager::ZYPPER},
    {"urpmi", PackageManager::URPMI},
    {"nix-env", PackageManager::NIX_ENV},
    {"pkg", PackageManager::PKG},
    {"pkg_add", PackageManager::PKG_ADD},
    {"apk", PackageManager::APK}
};

PackageManager CheckPackageManagers() {
    std::string PM[] = {"apt", "yum", "emerge", "pacman", "zypper", "urpmi", "nix-env", "pkg", "pkg_add","apk"};

    for(const std::string& manager : PM) {
        if(VerifyManager(manager)) {
          auto PM = managers.find(manager);
          if(PM != managers.end()) 
          {
            return PM->second;
          }
        }
    }
    
    std::cout << "Could not find the manager 💀" << std::endl;
    return PackageManager::UNKNOWN;
}

bool VerifyManager(const std::string& manager) {
    std::string command = "which " + manager;
    int result = std::system(command.c_str());
    return (result == 0);
}


bool isWindows()
{
  #ifdef _WIN32
    return true;
  #else
    return false;
  #endif
}

bool CheckGit()
{
  printf("Checking if GIT is installed");
  int result = std::system("git --version");
  if(result == 0)
  {
    printf("Git is installed");
    return true;
  }
  else  {
    printf("Git is not installed");
    return false;
  }
}

void InstallGit()
{
  int result;
  std::filesystem::path cache = std::filesystem::temp_directory_path() / "git-cache";
  
  printf("Creating git-cache directory");

  if(!std::filesystem::exists(cache))
  {
    std::filesystem::create_directory(cache);
  }

  printf("Installing Git...");

  if(isWindows())
  {
    result = std::system("curl -o Git-Installer.exe https://github.com/git-for-windows/git/releases/download/v2.44.0.windows.1/Git-2.44.0-64-bit.exe");
    if(result == 0)
    {
      printf("Installed Git!");
    }
    else{
      printf("Failed to install Git");
    }
  }

  else
  {
    printf("Failed to download git installer");
  }

  if(!isWindows())
  {
    PackageManager PM = CheckPackageManagers();
    printf("Using %s", PM);
    
    switch(PM)
    {
      case PackageManager::APK:
        std::system("sudo apk add git");
        break;
      case PackageManager::APT:
        std::system("sudo apt-get install git");
        break;
      case PackageManager::EMERGE:
        std::system("sudo emerge --ask --verbose dev-vcs/git");
        break;
      case PackageManager::NIX_ENV:
        std::system("sudo nix-env -i git");
        break;
      case PackageManager::PACMAN:
        std::system("sudo pacman -S git");
        break;
      case PackageManager::PKG:
        std::system("sudo pkg install git");
        break;
      case PackageManager::PKG_ADD:
        std::system("sudo pkg_add git");
        break;
      case PackageManager::URPMI:
        std::system("sudo urmpi git");
        break;
      case PackageManager::YUM:
        std::system("sudo yum install git");
        break;
      case PackageManager::ZYPPER:
        std::system("sudo zypper install git");
        break;
    }
  }
}

int main()
{
  printf("Performing checks");
  if(!CheckGit())
  {
    InstallGit();
  }
   return 0;
}

#include <iostream>
#include <string>
#include <filesystem>
#include <cstdlib>


// Suncord Github: https://github.com/verticalsync/Suncord
// My contact: @xbhl

// This is the first time I've written an installer in C++
// Any issues I urge you make an issue report in github.

string CheckPackageManagers()
{
  string PM[] = {"apt", "yum", "emerge", "pacman", "zypper", "urpmi", "nix-env", "pkg", "pkg_add","apk"};
  for(const string manager : PM)
  {
    if(VerifyManager(manager))
    {
      printf("Found %s",manager);
      return manager;
    }
      else {
        printf("Could not find manager");
        return "💀";
      }
  }
}

bool VerifyManager(const std::string& manager)
{
  string command + "which" + manager;
  int result = std::system(command.c_str());
  return (result == 0);
}

bool isWindows()
{
  #ifdef _WIN32
    return true;
  #else
    return false;
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
  
  printf("Creating git-cache directory")
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
    else {
      printf("Failed to install Git");
    }
  else {
        printf("Failed to download installer");
    }
  }

  if(!isWindows())
  {
  }
}

int main()
{
  printf("Performing checks");

   return 0;
}

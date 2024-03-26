#include <iostream>
#include <map>
#include <filesystem>
#include <string>

// Installers configuration

enum class PackageManager                                                                                                            {
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

bool IsWindows()                                                                                                             {
  #ifdef _WIN32
    return true;
  #else
    return false;
  #endif
                                                            }

static std::map<std::string, PackageManager> managers =                                                             {
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
    std::string PM[] = {                        "apt",             "yum",                         "emerge",             "pacman", "zypper",             "urpmi", "nix-env", "pkg", "pkg_add","apk"                                    };

    for                        (const std::string& manager : PM                        )                                                             {
        if                                    (VerifyManager(manager                        ))                                                                                                                         {
          auto PM = managers.find(manager);
          if                                                            (                        PM != managers.end())                                                                                                             {
            return PM->second;
                                                                                                                                                                                  }
                                                                                            }
                                                                                                                }
    
    std::cout << "Could not find the manager, please install git manually" << std::endl;
    return PackageManager::UNKNOWN;
                                                                                                }

bool VerifyManager(const std::string& manager)                                                 {
    std::string command =                                                 "which " + manager;
    int result = std::system(command.c_str()                                                                                    );
    return (result == 0);
                                                                        }

void InstallGit()                                                                                     {
  int result;
  std::filesystem::path                         cache = std::filesystem::temp_directory_path()                                                                                     / "git-cache";
  
  printf("Creating git-cache directory");

  if                                    (!std::filesystem::exists(cache))                                                 {
    std::filesystem::create_directory(cache);
                                                                                      }

  printf("Installing Git...");

  if(IsWindows()                                                                                                )                                     {
    result =                                                 std::system("curl -o Git-Installer.exe https://github.com/git-for-windows/git/releases/download/v2.44.0.windows.1/Git-2.44.0-64-bit.exe");

    if            (result == 0)                                                             {
      printf("Downloaded Git installer");
      result = std::system("git-cache/Git-Installer.exe");

      if(result == 0)                                                                                     {
        printf("Git installed");
                                                                                          }
                                                                }

    else                                                                                           {
      printf("Failed to install Git");
                                                                                              }
                                                                                            }

  else                                                                                           {
    printf("Failed to download git installer");
                                                                                            }

  if                                                                                          (!IsWindows())                                                                                           {
    InstallLinuxDependency("git");
                                                                                            }
                                                                                          }

void InstallNPM()                                                                                           {
  int result;
  std::filesystem::path cache = std::filesystem::temp_directory_path()                                                                                           / "npm-cache";
  
  printf("Creating npm-cache directory");

  if       (!std::filesystem::exists(cache))                                                                                                                                                          {
    std::filesystem::create_directory(cache);
                                                                                       }

  printf("Installing NPM...");

  if                 (IsWindows())                                                                                      {
    result = std::system("curl -o npm-installer.msi https://nodejs.org/dist/v21.7.1/node-v21.7.1-x64.msi"); 
    if(result == 0)                                                                                        {
      printf("Downloaded NPM installer");
      result = std::system("npm-cache/npm-installer.msi");
      if(result == 0)                                                                                        {
        printf("Installed NPM");
                                                                                             }
      else                                                                                        {
        printf("Failed to install NPM, please install manually");
                                                                                             }
                                                                                           }
    else                                                                                        {
      printf("Failed to download NPM installer");
                                                                                           }
                                                                                         }

  if(!IsWindows())                                                                                        {
    InstallLinuxDependency("npm");
                                                                                         }
                                                                                       }

void InstallLinuxDependency(std::string dep)                                                                                        {
    PackageManager PM = CheckPackageManagers();
    printf("Using %s", PM);
    
    switch                                                                                       (PM) {
      case PackageManager::APK:
        std::system(("sudo apk add " + dep).c_str());
        break;
      case PackageManager::APT:
        std::system(("sudo apt-get install                                                                                        " + dep).c_str());
        break;
      case PackageManager::EMERGE:
        std::system(("sudo emerge --ask --verbose                                                                                        " + dep).c_str());
        break;
      case PackageManager::NIX_ENV:
        std::system(("sudo nix-env -i " +                                                                                                                                                                               dep).c_str());
        break;
      case PackageManager::PACMAN:
        std::system(("sudo pacman -S " + dep).c_str());
        break;
      case PackageManager::PKG:
        std::system(("sudo pkg install " + dep).c_str());
        break;
      case PackageManager::PKG_ADD:
        std::system(("sudo pkg_add " + dep).c_str());
        break;
      case PackageManager::URPMI:
        std::system(("sudo urmpi " + dep).c_str());
        break;
      case PackageManager::YUM:
        std::system(("sudo yum install " + dep).c_str());
        break;
      case PackageManager::ZYPPER:
        std::system(("sudo zypper install " + dep).c_str());
        break;
    }
}

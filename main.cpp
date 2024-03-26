#include <iostream>
#include <unistd.h>
#include "installer.cpp"

// Suncord Github: https://github.com/verticalsync/Suncord
// My contact: @xbhl

// This is the first time I've written an installer in C++
// Any issues I urge you make an issue report in github.

bool CheckGit() {
  printf("Checking if GIT is installed\n");
  int result = std::system("git --version");
  if(result == 0) {
    printf("Git is installed\n");
    return true;
  }
  else {
    printf("Git is not installed\n");
    return false;
  }
}

bool CheckNPM() {
  printf("Checking for NPM");
  int result = std::system("npm -v");
  if(result == 0) {
    printf("NPM is installed\n");
    return true;
  }
  else {
    printf("NPM is not installed\n");
    return false;
  }
}

bool CheckPNPM() {
  printf("Checking for PNPM\n");
  int result = std::system("pnpm --version");
  if(result == 0) {
    printf("PNPM is installed\n");
    return true;
  }
  else {
    printf("PNPM is not installed\n");
    return false;
  }
}

void Build() {
    printf("Cloning Suncord repository...\n");
    int result = system("git clone https://github.com/verticalsync/Suncord");

    if (result == 0) {
        printf("Cloned Suncord repository.\n");
        if (chdir("Suncord") == 0) {
            printf("Opened repository.\nDownloading external dependencies using PNPM...\n");
            result = system("pnpm install --frozen-lockfile");

            if (result == 0) {
                printf("Installed dependencies!\nBuilding Suncord...\n");
                result = system("pnpm build");

                if (result == 0) {
                    printf("Built Suncord.\nInjecting...\n");
                    result = system("pnpm inject");

                    if (result == 0) {
                        printf("Finished injecting!\n");
                        printf("Press any key to exit.\n");
                        getchar();
                    } else {
                        printf("Failed to inject to Discord client\n");
                    }
                } else {
                    printf("Failed to build Suncord\n");
                }
            } else {
                printf("Failed to install PNPM dependencies.\n");
            }
        } else {
            printf("Couldn't open Suncord directory.\n");
        }
    } else {
        printf("Failed to clone repository\n");
    }
}

int main() {
  printf("Performing checks\n");
  
  bool GitInstalled = CheckGit();
  bool NPMInstalled = CheckNPM();
  bool PNPMInstalled = CheckPNPM();

  if(!GitInstalled) {
    InstallGit();
  }

  if(!NPMInstalled) {
    InstallNPM();
  }

  if(!PNPMInstalled && NPMInstalled) {
    InstallPNPM();
  }

  if(GitInstalled && NPMInstalled && PNPMInstalled) {
    Build();
  }

   return 0;
}

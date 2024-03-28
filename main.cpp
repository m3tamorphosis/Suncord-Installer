#include "installer.cpp"
#include <iostream>
#include <unistd.h>

// Suncord Github: https://github.com/verticalsync/Suncord
// My contact: @xbhl

// This is the first time I've written an installer in C++
// Any issues I urge you make an issue report in github.

bool CheckGit() {
  printf("Checking if GIT is installed \n");
  int result = std::system("git --version");

  if (result == 0) {
    printf("Git is installed \n");
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

  if (result == 0) {
    printf("NPM is installed \n");
    return true;
  }

  else {
    printf("NPM is not installed \n");
    return false;
  }
}

bool CheckPNPM() {
  printf("Checking for PNPM \n");
  int result = std::system("pnpm --version");

  if (result == 0) {
    printf("PNPM is installed \n");
    return true;
  }

  else
    printf("PNPM is not installed \n");
  return false;
}

void Build() {
  printf("Cloning Suncord repository... \n");
  int result = system("git clone https://github.com/verticalsync/Suncord");

  if (result != 0) {
    printf("Failed to clone repository. \n");
    return;
  }

  if (chdir("Suncord") != 0) {
    printf("Couldn't open Suncord directory");
    return;
  }
  printf("Opened Suncord directory!\nInstalling external dependencies using "
         "PNPM...\n");

  result = system("pnpm install --frozen-lockfile");
  if (result != 0) {
    printf("Failed to install frozen lockfile dependencies.\n");
    return;
  }
  printf("Installed frozen lockfile dependencies\nBeginnning build...\n");

  result = system("pnpm build");
  if (result != 0) {
    printf("Failed to build Suncord.\n");
    return;
  }
  printf("Successfully built Suncord! \n");

  result = system("pnpm inject");
  if (result != 0) {
    printf("Failed to inject to Discord \n");
    return;
  }
  printf("Successfully injected!\nPress any key to exit.");
  getchar();
}

int main() {
  printf("Performing checks \n");

  bool GitInstalled = CheckGit();
  bool NPMInstalled = CheckNPM();
  bool PNPMInstalled = CheckPNPM();

  if (!GitInstalled) {
    InstallGit();
    GitInstalled = CheckGit();
    if (!GitInstalled) {
      printf("Error during Git installation.");
      return 1;
    }
  }

  if (!NPMInstalled) {
    InstallNPM();
    NPMInstalled = CheckNPM();
    if (!NPMInstalled) {
      printf("Error during NPM installation");
      return 1;
    }
  }

  if (!PNPMInstalled && NPMInstalled) {
    InstallPNPM();
    PNPMInstalled = CheckPNPM();
    if (!NPMInstalled) {
      printf("Erorr during PNPM installation");
      return 1;
    }
  }

  Build();
  return 0;
}
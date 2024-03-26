#include <iostream>
#include "installer.cpp"

// Suncord Github: https://github.com/verticalsync/Suncord
// My contact: @xbhl

// This is the first time I've written an installer in C++
// Any issues I urge you make an issue report in github.

bool CheckGit() {
  printf("Checking if GIT is installed");
  int result = std::system("git --version");
  if(result == 0) {
    printf("Git is installed");
    return true;
  }
  else {
    printf("Git is not installed");
    return false;
  }
}

bool CheckNPM() {
  printf("Checking for NPM");
  int result = std::system("npm -v");
  if(result == 0) {
    printf("NPM is installed");
    return true;
  }
  else {
    printf("NPM is not installed");
    return false;
  }
}

int main() {
  printf("Performing checks");
  
  if(!CheckGit()) {
    InstallGit();
  }

  if(!CheckNPM()) {
   InstallNPM(); 
  }

   return 0;
}

#pragma once
#include <cstdio>
#include <string>
namespace KTKR {
class File {
   public:
    enum Mode { READ, WRITE };
    File(const std::string& fileName, Mode mode);
    ~File();
    std::string ReadLine();
    std::string ReadAll();
    bool Check(Mode mode);
    bool IsValid();
    bool IsEnd();

   private:
    FILE* pF;
    Mode mode;
    std::string fileName;
    std::string ModeToStr(Mode mode);
};
}  // namespace KTKR

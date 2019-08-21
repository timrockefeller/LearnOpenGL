#include <Util/File.h>
using namespace std;
using namespace KTKR;
File::File(const string& fileName, Mode mode) {
    this->fileName = fileName;
    this->mode = mode;
    pF = fopen(fileName.c_str(), ModeToStr(mode).c_str());
    if (pF == NULL)
        fprintf(stderr, "%s open error\n", fileName.c_str());
}

File::~File() {
	if (pF != NULL) {
		fclose(pF);
		pF = NULL;
	}
}

string File::ReadLine() {
	if (!Check(READ)) {
		fprintf(stderr, "%s can't not read\n", fileName.c_str());
		return "";
	}
	char buffer[1024] = "";
	fgets(buffer, 1024, pF);
	return buffer;
}

string File::ReadAll() {
    if (!Check(READ)) {
        fprintf(stderr, "%s can't not read\n", fileName.c_str());
        return "";
    }
    string rst;
    while (!IsEnd())
        rst += ReadLine();
    return rst;
}

bool File::Check(Mode mode) {
    if (mode == this->mode && IsValid())
        return true;
    else
        return false;
}

bool File::IsValid() {
    return pF != NULL;
}

bool File::IsEnd() {
	return feof(pF);
}

string File::ModeToStr(Mode mode) {
    switch (mode) {
        case READ:
            return "r";
            break;
        case WRITE:
            return "w";
            break;
        default:
            return "";
            break;
    }
}

/**
 * Microsoft - Modern Information Technology
 * https://github.com/Microsoft/ELL/blob/master/libraries/utilities/include/Files.h
 *
 *  Created on: Dec 26, 2018
 *  Student (MIG Virtual Developer): Tung Dang
 */

#include <fstream>
#include <string>
#include <vector>

namespace ell 
{
    namespace utilities
    {
        /* Opens an std::ifstream/ofstream and throws an exception if a problem occurs */
        std::ifstream OpenIfstream(const std::string& filepath);
        std::ofstream OpenOfstream(const std::string& filepath);
        
        /* Opens an std::ifstream/ofstream in binary mode and throws an exceptions if a problem occurs */
        std::ifstream OpenBinaryIfstream(const std::string& filepath);
        std::ofstream OpenBinaryOfstream(const std::string& filepath);

        bool IsFileReadable(const std::string& filepath);
        bool IsFileWritable(const std::string& filepath);
        bool FileExists(const std::string& filepath);

        std::string GetFileExtension(const std::string& filepath, bool toLowercase = false);
        std::string RemoveFileExtension(const std::string& filepath);
        std::string GetFileName(const std::string& filepath);
        std::string GetDirectoryPath(const std::string& filepath);

        bool DirectoryExists(const std::string& path);
        void EnsureDirectoryExists(const std::string& path);

        std::string JoinPaths(const std::string& path1, const std::string& path2);
        std::string JoinPaths(const std::string& path, std::initializer_list<std::string> toAdd);
        std::string JoinPaths(const std::string& path, std::vector<std::string> toAdd);

        std::vector<std::string> SplitPath(const std::string& path);
        std::string GetWorkingDirectory();
        std::string FindExecutable(const std::string& name);
    }
}
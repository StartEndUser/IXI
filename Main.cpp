#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <fstream>
#include <set>
#include <tuple>
#include <type_traits>
#include <vector>
#include <sys/stat.h>
#include <dirent.h>

/**
 * @enum The Path Type.
 */
enum class Path
{
    None,
    File,
    Directory
};

/**
 * @brief Translate Texts With '@' To Normal Texts.
 * @param inputParameter The Input Text.
 * @param outputParameter The Output Text.
 * @param addParameter Adding File(Directory) Or Deleting.
 */
void translateInput(char *inputParameter, std::string &outputParameter, bool &addParameter)
{
    unsigned int inputIndex = 0;

    if (inputParameter[0] == '-')
    {
        addParameter = false;
        inputIndex = 1;
    }
    else
    {
        addParameter = true;
    }

    bool special = true;
    for (; inputIndex < strlen(inputParameter); ++inputIndex)
    {
        if (inputParameter[inputIndex] == '-' && !special)
        {
            special = true;
        }

        if (inputParameter[inputIndex] == '@')
        {
            if (special)
            {
                special = false;
                continue;
            }
            else
            {
                special = true;
            }
        }

        outputParameter += inputParameter[inputIndex];
    }
}

/**
 * @brief Check If Path Exist And Check Type.
 * @param pathParameter The Path.
 * @return Is Exist Or Not And Iit's Type.
 */
Path isExist(std::string pathParameter)
{
    struct stat status;
    if (!stat(pathParameter.c_str(), &status))
    {
        if (status.st_mode & S_IFREG)
        {
            return Path::File;
        }
        else if (status.st_mode & S_IFDIR)
        {
            return Path::Directory;
        }
        else
        {
            return Path::None;
        }
    }

    printf("ERROR: File Type Detection Failed When Detecting: %s\n", pathParameter.c_str());
    exit(-1);
}

/**
 * @brief Get All Files Under A Directory.
 * @param pathParameter The Path.
 * @return The File Names.
 */
std::set<std::string> getFiles(std::string pathParameter)
{
    DIR *directory;
    dirent *pointer;
    std::set<std::string> result;

    directory = opendir(pathParameter.c_str());

    while ((pointer = readdir(directory)))
    {
        if (!strcmp(pointer->d_name, ".") || !strcmp(pointer->d_name, ".."))
        {
            continue;
        }

        std::string path = pathParameter;
        path += "/";
        path += pointer->d_name;
        if (isExist(path) == Path::File)
        {
            if (path.size() > 2 && path[0] == '.' && path[1] == '/')
            {
                result.insert(path.substr(2));
            }
            else
            {
                result.insert(path);
            }
        }
        else
        {
            std::set<std::string> get = getFiles(path);
            result.insert(get.begin(), get.end());
        }
    }

    closedir(directory);

    return result;
}

/**
 * @brief Checked Added A File In List.
 * @param filesParameter The File List.
 * @param detectParameter The File To Check.
 * @return Added Or Not.
 */
bool added(std::vector<std::string> &filesParameter, std::string detectParameter)
{
    return find(filesParameter.begin(), filesParameter.end(), detectParameter) != filesParameter.end();
}

int main(int argumentNumberParameter, char *argumentsParameter[])
{
    // Setup Varibles
    unsigned int argumentNumber = argumentNumberParameter - 1;
    char **arguments = &argumentsParameter[1];
    std::vector<std::string> files;

    // Get And Check Files
    for (unsigned int index = 0; index < argumentNumber; ++index)
    {
        std::string translate = "";
        bool add;
        translateInput(arguments[index], translate, add);

        Path pathType = isExist(translate);
        if (!(bool)pathType)
        {
            printf("ERROR: Unknown File Or Directory: %s\n", translate.c_str());
            return -1;
        }

        if (add)
        {
            if (pathType == Path::File)
            {
                if (added(files, translate))
                {
                    continue;
                }

                files.emplace_back(translate);
            }
            else
            {
                std::set<std::string> get = getFiles(translate);
                while (!get.empty())
                {
                    if (added(files, *get.begin()))
                    {
                        get.erase(get.begin());
                        continue;
                    }

                    files.emplace_back(*get.begin());
                    get.erase(get.begin());
                }
            }
        }
        else
        {
            if (pathType == Path::File)
            {
                for (unsigned int index = 0; index < files.size(); ++index)
                {
                    if (translate == files[index])
                    {
                        files.erase(files.begin() + index);
                        break;
                    }
                }
            }
            else
            {
                std::set<std::string> get = getFiles(translate);
                for (std::set<std::string>::iterator item = get.begin(); item != get.end(); ++item)
                {
                    for (unsigned int index = 0; index < files.size(); ++index)
                    {
                        if (*item == files[index])
                        {
                            files.erase(files.begin() + index);
                            break;
                        }
                    }
                }
            }
        }
    }

    // Targets
    printf("Targets:\n");
    for (unsigned int index = 0; index < files.size(); ++index)
    {
        printf("%s\n", files[index].c_str());
    }
    printf("\n");

    // Tab
    int tabLength = -1;
    size_t size = 16;
    char *buffer = NULL;
    printf("Tab length (skip if nothing):");
    std::ignore = getline(&buffer, &size, stdin);
    for (;;)
    {
        if (strlen(buffer) == 1)
        {
            break;
        }

        tabLength = atoi(buffer);
        if (tabLength || (!tabLength && buffer[0] == '0'))
        {
            break;
        }

        tabLength = -1;
        printf("Tab length (skip if nothing):");
        free(buffer);
        buffer = NULL;
        std::ignore = getline(&buffer, &size, stdin);
    }
    free(buffer);
    buffer = NULL;
    printf("\n");

    // Delete Mode
    char mode = '\0';
    printf("S: Only Delete Useless Spaces\nT: Only Delete Useless Tabs\nA: Delete All Useless Spaces And Tabs\nDelete mode (skip if nothing):");
    std::ignore = getline(&buffer, &size, stdin);
    for (;;)
    {
        if (strlen(buffer) == 1)
        {
            break;
        }

        if (!(strcmp(buffer, "S\n") && strcmp(buffer, "T\n") && strcmp(buffer, "A\n")))
        {
            mode = buffer[0];
            break;
        }

        mode = '\0';
        printf("Delete mode (skip if nothing):");
        free(buffer);
        buffer = NULL;
        std::ignore = getline(&buffer, &size, stdin);
    }
    free(buffer);
    buffer = NULL;
    printf("\n");

    // Last Line
    int lineLength = -1;
    printf("Leave line number (skip if nothing):");
    std::ignore = getline(&buffer, &size, stdin);
    for (;;)
    {
        if (strlen(buffer) == 1)
        {
            break;
        }

        lineLength = atoi(buffer);
        if (lineLength || (!lineLength && buffer[0] == '0'))
        {
            break;
        }

        lineLength = -1;
        printf("Leave line number (skip if nothing):");
        free(buffer);
        buffer = NULL;
        std::ignore = getline(&buffer, &size, stdin);
    }
    free(buffer);
    buffer = NULL;
    printf("\n");

    // Read Files
    if (tabLength == -1 && !mode && lineLength == -1)
    {
        printf("Nothing To Do\n");
        return 0;
    }

    printf("Running:\n");
    while (!files.empty())
    {
        printf("%s\n", files[0].c_str());
        FILE *file = fopen(files[0].c_str(), "r");

        if (file == NULL)
        {
            printf("Error: Failed To Open File: %s\n", files[0].c_str());
            return -1;
        }

        fseek(file, 0, SEEK_END);
        unsigned int size = ftell(file);
        if (!size)
        {
            fclose(file);
            files.erase(files.begin());
            continue;
        }
        std::string fileContent(size, '\0');
        std::string fileResult = "";
        fseek(file, 0, SEEK_SET);
        std::ignore = fread(&fileContent[0], size, sizeof(char), file);

        fclose(file);
        file = fopen(files[0].c_str(), "w");

        bool notEnd = false;
        bool wantContinue = false;

        for (unsigned long long index = 0; index < fileContent.size(); ++index)
        {
            wantContinue = false;
            if (!notEnd && (mode == 'A' || mode == 'S') && fileContent[index] == ' ')
            {
                for (unsigned long long findIndex = index + 1; findIndex < fileContent.size(); ++findIndex)
                {
                    if (fileContent[findIndex] == '\n')
                    {
                        index = findIndex - 1;
                        wantContinue = true;
                        break;
                    }
                    else if (fileContent[findIndex] != ' ' && (mode == 'S' || fileContent[findIndex] != '\t'))
                    {
                        notEnd = true;
                        break;
                    }
                }
            }

            if (wantContinue)
            {
                continue;
            }

            if (!notEnd && (mode == 'A' || mode == 'T') && fileContent[index] == '\t')
            {
                for (unsigned long long findIndex = index + 1; findIndex < fileContent.size(); ++findIndex)
                {
                    if (fileContent[findIndex] == '\n')
                    {
                        index = findIndex - 1;
                        wantContinue = true;
                        break;
                    }
                    else if (fileContent[findIndex] != '\t' && (mode == 'T' || fileContent[findIndex] != ' '))
                    {
                        notEnd = true;
                        break;
                    }
                }
            }

            if (wantContinue)
            {
                continue;
            }

            if (tabLength != -1 && fileContent[index] == '\t')
            {
                wantContinue = true;

                for (unsigned int _ = 0; _ < tabLength; ++_)
                {
                    fileResult += " ";
                }
            }

            if (wantContinue)
            {
                continue;
            }

            if (notEnd && fileContent[index] != ' ' && fileContent[index] != '\t')
            {
                notEnd = false;
            }
            fileResult += fileContent[index];
        }

        if (lineLength != -1)
        {
            // Delete All \n At The Tail
            for (unsigned long long index = fileResult.size() - 1; index >= 0; --index)
            {
                if (fileResult[index] == '\n')
                {
                    fileResult.pop_back();
                }
                else
                {
                    break;
                }
            }

            // Add \n At The Tail
            for (unsigned int _ = 0; _ < lineLength; ++_)
            {
                fileResult += '\n';
            }
        }

        fputs(fileResult.c_str(), file);

        fclose(file);
        files.erase(files.begin());
    }
    printf("\n");

    // Finished
    printf("Finished\n");

    return 0;
}

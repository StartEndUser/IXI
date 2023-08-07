#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <fstream>
#include <set>
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

    while (pointer = readdir(directory))
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

    // Indent
    int indentLength = 4;
    size_t size = 16;
    char *buffer = NULL;
    printf("Indent length (default 4):");
    getline(&buffer, &size, stdin);
    for (;;)
    {
        if (strlen(buffer) == 1)
        {
            break;
        }

        indentLength = atoi(buffer);
        if (indentLength)
        {
            break;
        }

        indentLength = 4;
        printf("Indent length (default 4):");
        free(buffer);
        buffer = NULL;
        getline(&buffer, &size, stdin);
    }
    free(buffer);
    printf("\n");

    // Tab 2 Space
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
        fseek(file, 0, SEEK_SET);
        fread(&fileContent[0], size, sizeof(char), file);

        fclose(file);
        file = fopen(files[0].c_str(), "w");

        for (unsigned long long index = 0; index < fileContent.size(); ++index)
        {
            if (fileContent[index] == '\t')
            {
                for (unsigned int _ = 0; _ < indentLength; ++_)
                {
                    fputc(' ', file);
                }
            }
            else
            {
                fputc(fileContent[index], file);
            }
        }

        fclose(file);
        files.erase(files.begin());
    }
    printf("\n");

    // Finished
    printf("Finished\n");

    return 0;
}

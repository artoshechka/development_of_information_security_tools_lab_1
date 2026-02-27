/// @file
/// @brief Объявление класса для шифратора файлов директорий
/// @author Artemenko Anton
#pragma once
#ifndef GUID_d77f818f_e9d1_416e_939c_72463f45c000
#define GUID_d77f818f_e9d1_416e_939c_72463f45c000
#include <idecryption_module.hpp>

namespace decryption_module
{
/// @brief Класс реализующий шифрование файлов в директориях
class DecryptionModule : public IDecryptionModule
{
};
} // namespace decryption_module
#endif // GUID_d77f818f_e9d1_416e_939c_72463f45c000
/// @file
/// @brief Объявление класса для шифратора файлов директорий
/// @author Artemenko Anton
#pragma once
#ifndef GUID_23829f70_2598_4bf2_85b2_d8cdfe9c0e31
#define GUID_23829f70_2598_4bf2_85b2_d8cdfe9c0e31
#include <iencryption_module.hpp>
namespace encryption_module
{
/// @brief Класс реализующий шифрование файлов в директориях
class EncryptionModule : public IEncryptionModule
{
};
} // namespace encryption_module
#endif // GUID_23829f70_2598_4bf2_85b2_d8cdfe9c0e31
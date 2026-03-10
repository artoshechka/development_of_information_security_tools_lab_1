/// @file
/// @brief Главное приложение
/// @author Artemenko Anton
#include <crypto_manager_factory.hpp>
#include <recursive_stepper.hpp>

#include <QCoreApplication>
#include <QDir>
#include <QTextStream>

namespace
{
/// @brief Сообщение об ошибке при неправильном использовании программы
const QString &errorMsg = "Usage:\nprogram encrypt <path>\nprogram decrypt <path>\n";
} // namespace

/// @brief Точка входа в программу.
/// @param[in] argc количество аргументов командной строки
/// @param[in] argv массив аргументов командной строки
/// @return код завершения приложения
int main(int argc, char *argv[])
{
    QTextStream cin(stdin);
    QTextStream cout(stdout);
    QTextStream cerr(stderr);

    QString mode;
    QString path;

    // Проверка аргументов
    if (argc >= 3)
    {
        mode = argv[1];
        path = QString::fromLocal8Bit(argv[2]);
    }
    else
    {
        cerr << errorMsg;
        return 1;
    }

    QDir dir(path);

    if (!dir.exists())
    {
        cerr << "Directory does not exist\n";
        return 1;
    }

    cout << "Enter password: ";
    cout.flush();
    QString password = cin.readLine();

    const auto &stepper = std::make_shared<recursive_stepper::RecursiveStepper>(path);
    const auto &encoder = crypto_manager::GetCryptoManager();

    for (const auto &file : stepper->BuildIndex())
    {
        bool result = false;

        if (mode == "encrypt")
        {
            result = encoder->EncryptFile(file, password);
        }
        else if (mode == "decrypt")
        {
            result = encoder->DecryptFile(file, password);
        }
        else
        {
            cerr << errorMsg;
            return 1;
        }

        if (result)
        {
            cout << "File processed: " << file << "\n";
        }
        else
        {
            cout << "File skipped: " << file << "\n";
        }
    }

    return 0;
}